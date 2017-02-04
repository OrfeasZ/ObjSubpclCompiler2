#include "ClassDefinition.h"

#include "ClassHeader.h"
#include <Parser/VariableDeclaration.h>
#include "ClassBody.h"
#include "ClassVariableType.h"
#include <Parser/Identifier.h>

#include <Parser/Procedure/Procedure.h>
#include <Parser/Procedure/ProcedureHeader.h>
#include <Parser/Procedure/ProcedureBody.h>
#include <Parser/Statements/IStatement.h>
#include <Parser/VariableType.h>
#include <Parser/ArrayVariableType.h>
#include <Parser/Expressions/Integer.h>
#include <Parser/Expressions/MemberCall.h>
#include <Parser/Expressions/IDExpression.h>

#include <Managers/ClassManager.h>
#include <Managers/CodeManager.h>

#include <Util/Utils.h>

#include <algorithm>
#include <iterator>

using namespace Parser;

ClassDefinition::ClassDefinition(ClassHeader* p_Header, VariableSeq* p_Variables, ClassBody* p_Body) :
	m_Header(p_Header),
	m_Variables(p_Variables),
	m_Body(p_Body)
{
	Managers::ClassManager::RegisterClass(this);
}

void ClassDefinition::GenerateDefinitions()
{
	// Get the parent class (if there is one).
	ClassDefinition* s_Parent = nullptr;

	if (m_Header->m_Extends != nullptr)
	{
		s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);

		// If we have a parent set but he doesn't exist then something is wrong.
		if (s_Parent == nullptr)
			throw std::exception(("Could not find parent '" + m_Header->m_Extends->m_Name + "' for class '" + m_Header->m_Name->m_Name + "'.").c_str());
	}

	// Generate code for this class.
	GenerateStruct(s_Parent);
	GenerateForwardDeclarations(s_Parent);
	GenerateVtable(s_Parent);
}

void ClassDefinition::GenerateBody()
{
	// Get the parent class (if there is one).
	ClassDefinition* s_Parent = nullptr;

	if (m_Header->m_Extends != nullptr)
		s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);

	// Generate code for this class.
	GenerateConstructor(s_Parent);
	GenerateMethods(s_Parent);
}

std::vector<Procedure*> ClassDefinition::GetMethods(ProcedureType::type p_Type)
{
	std::vector<Procedure*> s_Methods;

	if (m_Body->m_Procedures == nullptr)
		return s_Methods;

	for (auto s_Method : *m_Body->m_Procedures)
		if (s_Method->m_Type == p_Type)
			s_Methods.push_back(s_Method);

	return s_Methods;
}

bool ClassDefinition::IsAbstract()
{
	for (auto s_Method : GetFinalVirtualMethods())
		if (std::get<1>(s_Method)->m_Type == ProcedureType::Abstract)
			return true;

	return false;
}

bool ClassDefinition::HasMember(const std::string& p_Name, VariableType*& p_Type)
{
	// Check local variables.
	if (m_Variables)
	{
		for (auto s_Variable : *m_Variables)
		{
			for (auto s_ID : *s_Variable->m_IDs)
			{
				if (s_ID->m_Name == p_Name)
				{
					p_Type = s_Variable->m_Type;
					return true;
				}
			}
		}
	}

	// Search the parent variables.
	if (m_Header->m_Extends == nullptr)
		return false;

	auto s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);

	// Not sure if we would ever get here, but might as well.
	if (s_Parent == nullptr)
		return false;

	return s_Parent->HasMember(p_Name, p_Type);
}

bool ClassDefinition::HasMethod(const std::string& p_Name, std::string& p_MethodName, bool p_CheckParent)
{
	p_MethodName = m_Header->m_Name->m_Name + "__" + p_Name;

	for (auto s_Method : GetMethods(ProcedureType::Standard))
		if (s_Method->m_Header->m_Name->m_Name == p_Name)
			return true;

	if (!p_CheckParent)
		return false;

	// Search the parent methods.
	if (m_Header->m_Extends == nullptr)
		return false;

	auto s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);

	// Not sure if we would ever get here, but might as well.
	if (s_Parent == nullptr)
		return false;

	return s_Parent->HasMethod(p_Name, p_MethodName, p_CheckParent);
}

bool ClassDefinition::HasVirtualMethod(const std::string& p_Name)
{
	for (auto s_Method : GetAllVirtualMethods())
		if (std::get<0>(s_Method) == p_Name)
			return true;

	return false;
}

void ClassDefinition::GenerateForwardDeclarations(ClassDefinition* p_Parent)
{
	Managers::CodeManager::Writer()->WriteLnInd("// Method forward declarations for class " + m_Header->m_Name->m_Name);

	// Constructor forward declaration.
	{
		auto s_Parameters = m_Body->m_Constructor->m_Header->GetParameters();
		s_Parameters.insert(s_Parameters.begin(), "struct " + m_Header->m_Name->m_Name + "_t* th");

		auto s_FinalParameters = Util::Utils::Join(s_Parameters, ", ");

		// Write forward declaration.
		Managers::CodeManager::Writer()->WriteLnInd("void " + m_Header->m_Name->m_Name + "__ctor(" + s_FinalParameters + ");");
	}

	for (auto s_Method : *m_Body->m_Procedures)
	{
		auto s_Parameters = s_Method->m_Header->GetParameters();
		s_Parameters.insert(s_Parameters.begin(), "struct " + m_Header->m_Name->m_Name + "_t* th");

		auto s_FinalParameters = Util::Utils::Join(s_Parameters, ", ");

		// Write forward declaration.
		Managers::CodeManager::Writer()->WriteLnInd("void " + m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name + "(" + s_FinalParameters + ");");
	}

	Managers::CodeManager::Writer()->WriteLn();
}

void ClassDefinition::GenerateVtable(ClassDefinition* p_Parent)
{
	GenerateVtableTypedefs(p_Parent);
	GenerateVtableStructure(p_Parent);
	GenerateVtableVariable(p_Parent);
}

void ClassDefinition::GenerateVtableTypedefs(ClassDefinition* p_Parent)
{
	auto s_Methods = GetUniqueVirtualMethods();

	// Generate method typedefs.
	Managers::CodeManager::Writer()->WriteLnInd("// Vtable method descriptors for class " + m_Header->m_Name->m_Name);

	for (auto s_Method : s_Methods)
	{
		Managers::CodeManager::Writer()->WriteInd("typedef void (*" + m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name + "_t)");

		auto s_Parameters = s_Method->m_Header->GetParameters();
		s_Parameters.insert(s_Parameters.begin(), "struct " + m_Header->m_Name->m_Name + "_t* th");

		auto s_FinalParameters = Util::Utils::Join(s_Parameters, ", ");

		Managers::CodeManager::Writer()->WriteLn("(" + s_FinalParameters + ");");
	}

	Managers::CodeManager::Writer()->WriteLn();
}

void ClassDefinition::GenerateVtableStructure(ClassDefinition* p_Parent)
{
	// Get all virtual methods from parent.
	std::vector<std::tuple<std::string, Procedure*>> s_ParentMethods;

	if (p_Parent)
		s_ParentMethods = p_Parent->GetAllVirtualMethods();

	// Get methods from ourselves.
	auto s_Methods = GetUniqueVirtualMethods();

	if (s_ParentMethods.size() == 0 && s_Methods.size() == 0)
		return;

	// Write the vtable structure.
	Managers::CodeManager::Writer()->WriteLnInd("// Vtable descriptor for class " + m_Header->m_Name->m_Name);
	Managers::CodeManager::Writer()->WriteLnInd("struct " + m_Header->m_Name->m_Name + "_vtbl_t");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	for (auto s_Method : s_ParentMethods)
		Managers::CodeManager::Writer()->WriteLnInd(std::get<0>(s_Method) + "_t " + std::get<1>(s_Method)->m_Header->m_Name->m_Name + ";");

	for (auto s_Method : s_Methods)
		Managers::CodeManager::Writer()->WriteLnInd(m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name + "_t " + s_Method->m_Header->m_Name->m_Name + ";");

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("};");
	Managers::CodeManager::Writer()->WriteLn();
}

void ClassDefinition::GenerateVtableVariable(ClassDefinition* p_Parent)
{
	// Get all virtual methods from ourselves and our parents.
	auto s_Methods = GetFinalVirtualMethods();

	if (s_Methods.size() == 0)
		return;
	
	// Write the static vtable variable.
	Managers::CodeManager::Writer()->WriteLnInd("// Static vtable for class " + m_Header->m_Name->m_Name);
	Managers::CodeManager::Writer()->WriteLnInd("static struct " + m_Header->m_Name->m_Name + "_vtbl_t " + m_Header->m_Name->m_Name + "_vtblptr = ");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	for (auto s_Method : s_Methods)
	{
		Managers::CodeManager::Writer()->WriteInd("." + std::get<1>(s_Method)->m_Header->m_Name->m_Name + " = ");
	
		if (std::get<1>(s_Method)->m_Type == ProcedureType::Abstract)
		{
			Managers::CodeManager::Writer()->Write("NULL");
			Managers::CodeManager::Writer()->WriteLn(",");
		}
		else
		{
			Managers::CodeManager::Writer()->Write(std::get<0>(s_Method));
			Managers::CodeManager::Writer()->WriteLn(",");
		}
	}

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("};");
	Managers::CodeManager::Writer()->WriteLn();
}

void ClassDefinition::GenerateStruct(ClassDefinition* p_Parent)
{
	Managers::CodeManager::Writer()->WriteLnInd("struct " + m_Header->m_Name->m_Name + "_t");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	bool s_HasContent = false;

	// Write our vtable variable.
	// Write only if our parent doesn't have a vtable himself.
	if (GetUniqueVirtualMethods().size() > 0 && (p_Parent == nullptr || p_Parent->GetAllVirtualMethods().size() == 0))
	{
		Managers::CodeManager::Writer()->WriteLnInd("void* vtbl;");
		s_HasContent = true;
	}

	if (p_Parent != nullptr)
	{
		Managers::CodeManager::Writer()->WriteLnInd("struct " + p_Parent->m_Header->m_Name->m_Name + "_t; // Base class");
		s_HasContent = true;
	}

	// Write our variables.
	if (m_Variables)
	{
		s_HasContent = true;

		for (auto s_Variable : *m_Variables)
		{
			// Make sure we're not trying to instantiate an abstract class.
			if (s_Variable->m_Type->m_Type == VariableTypes::Class || s_Variable->m_Type->m_Type == VariableTypes::ClassPointer)
			{
				auto s_ClassType = (ClassVariableType*) s_Variable->m_Type;
				auto s_ClassTypeClass = Managers::ClassManager::GetClass(s_ClassType->m_ClassType->m_Name);

				if (s_ClassTypeClass == nullptr)
					throw std::exception(("Could not find class '" + s_ClassType->m_ClassType->m_Name + "' used for a variable.").c_str());

				if (s_ClassTypeClass->IsAbstract())
					throw std::exception(("Cannot instantiate a variable of abstract type '" + s_ClassType->m_ClassType->m_Name + "'.").c_str());
			}

			for (auto s_ID : *s_Variable->m_IDs)
			{
				Managers::CodeManager::Writer()->WriteInd(s_Variable->m_Type->ToString());
				
				if (s_Variable->m_Type->m_Type == VariableTypes::ClassPointer ||
					s_Variable->m_Type->m_Type == VariableTypes::Class)
					Managers::CodeManager::Writer()->Write("*");

				if (s_Variable->m_Type->m_Type == VariableTypes::Array)
				{
					auto s_Type = (ArrayVariableType*) s_Variable->m_Type;

					if (s_Type->m_InnerType->m_Type == VariableTypes::ClassPointer)
						Managers::CodeManager::Writer()->Write("*");
				}

				Managers::CodeManager::Writer()->Write(" " + s_ID->m_Name);

				// If this is an array then add the element count after the variable name.
				if (s_Variable->m_Type->m_Type == VariableTypes::Array)
				{
					auto s_Type = (ArrayVariableType*) s_Variable->m_Type;
					Managers::CodeManager::Writer()->Write("[");
					Managers::CodeManager::Writer()->Write(s_Type->m_ElementCount->m_Value);
					Managers::CodeManager::Writer()->Write("]");
				}

				Managers::CodeManager::Writer()->WriteLn(";");
			}
		}
	}

	// If we don't have any variables or a vtable or any parent class 
	// then just write a dummy variable to please msvc.
	if (!s_HasContent)
		Managers::CodeManager::Writer()->WriteLnInd("char dummy;");

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("};");
	Managers::CodeManager::Writer()->WriteLn();
}

void ClassDefinition::GenerateConstructor(ClassDefinition* p_Parent)
{
	auto s_Parameters = m_Body->m_Constructor->m_Header->GetParameters();
	s_Parameters.insert(s_Parameters.begin(), "struct " + m_Header->m_Name->m_Name + "_t* th");

	auto s_FinalParameters = Util::Utils::Join(s_Parameters, ", ");

	Managers::CodeManager::Writer()->WriteLnInd("void " + m_Header->m_Name->m_Name + "__ctor(" + s_FinalParameters + ")");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	// TODO: Generate constructor scoped variables.

	// Clear our memory.
	Managers::CodeManager::Writer()->WriteLnInd("memset(th, 0x00, sizeof(struct " + m_Header->m_Name->m_Name + "_t));");
	
	// If we have a parent then make sure we're calling his constructor.
	if (p_Parent)
	{
		auto s_ParentArgumentSize = p_Parent->m_Body->m_Constructor->m_Header->m_Parameters ? p_Parent->m_Body->m_Constructor->m_Header->m_Parameters->size() : 0;
		bool s_HasConstructorCall = false;

		// Try to find a super.ctor() call.
		for (auto s_Statement : *m_Body->m_Constructor->m_Body->m_Body)
		{
			if (!s_Statement->IsMemberCall())
				continue;

			s_Statement->SetParents(m_Body->m_Constructor->m_Header->m_Parameters, m_Body->m_Constructor->m_Body->m_Variables, this);

			auto s_MemberCall = (MemberCall*) s_Statement;

			if (!s_MemberCall->m_VariableExpression->IsID())
				continue;

			auto s_VariableExpression = (IDExpression*) s_MemberCall->m_VariableExpression;

			if (s_VariableExpression->m_ID->m_Name != "super")
				continue;

			if (s_MemberCall->m_Name->m_Name != "ctor")
				continue;

			auto s_ArgumentSize = s_MemberCall->m_Arguments ? s_MemberCall->m_Arguments->size() : 0;
			if (s_ArgumentSize != s_ParentArgumentSize)
				throw std::exception(("Attempting to call base constructor of '" + m_Header->m_Name->m_Name + "' with the wrong number of arguments.").c_str());

			std::vector<std::string> s_Arguments;

			// Serialize our arguments.
			if (s_MemberCall->m_Arguments)
			{
				for (auto s_Expression : *s_MemberCall->m_Arguments)
				{
					s_Expression->SetParents(s_Statement);
					s_Arguments.push_back(s_Expression->ToString());
				}
			}

			// If this is a class call add th as the first argument.
			s_Arguments.insert(s_Arguments.begin(), "th");

			Managers::CodeManager::Writer()->WriteInd(m_Header->m_Extends->m_Name + "__ctor");
			Managers::CodeManager::Writer()->WriteLn("(" + Util::Utils::Join(s_Arguments, ", ") + ");");

			s_HasConstructorCall = true;
			break;
		}

		// If we haven't found one and the parent constructor has args then we're doing something wrong.
		if (!s_HasConstructorCall && s_ParentArgumentSize > 0)
			throw std::exception(("Constructor of class '" + m_Header->m_Name->m_Name + "' does not call base class constructor.").c_str());

		// Otherwise, if there are no arguments just generate a standard constructor call.
		if (!s_HasConstructorCall)
			Managers::CodeManager::Writer()->WriteLnInd(m_Header->m_Extends->m_Name + "__ctor(th);");
	}

	// Init our vtable.
	if (GetFinalVirtualMethods().size() > 0)
		Managers::CodeManager::Writer()->WriteLnInd("th->vtbl = &" + m_Header->m_Name->m_Name + "_vtblptr;");

	// TODO: Initialize class member variables.
	
	// Generate constructor statements.
	m_Body->m_Constructor->m_Body->m_Body->SetParents(m_Body->m_Constructor->m_Header->m_Parameters, m_Body->m_Constructor->m_Body->m_Variables, this);
	m_Body->m_Constructor->m_Body->m_Body->Generate();

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("}");
	Managers::CodeManager::Writer()->WriteLn();
}

void ClassDefinition::GenerateMethods(ClassDefinition* p_Parent)
{
	for (auto s_Method : GetMethods(ProcedureType::Dynamic))
		GenerateMethod(s_Method);

	for (auto s_Method : GetMethods(ProcedureType::Standard))
		GenerateMethod(s_Method);
}

void ClassDefinition::GenerateMethod(Procedure* p_Procedure)
{
	auto s_Parameters = p_Procedure->m_Header->GetParameters();
	s_Parameters.insert(s_Parameters.begin(), "struct " + m_Header->m_Name->m_Name + "_t* th");

	auto s_FinalParameters = Util::Utils::Join(s_Parameters, ", ");

	Managers::CodeManager::Writer()->WriteLnInd("void " + m_Header->m_Name->m_Name + "__" + p_Procedure->m_Header->m_Name->m_Name + "(" + s_FinalParameters + ")");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	// TODO: Generate method scoped variables.
	
	// Generate method statements.
	p_Procedure->m_Body->m_Body->SetParents(p_Procedure->m_Header->m_Parameters, p_Procedure->m_Body->m_Variables, this);
	p_Procedure->m_Body->m_Body->Generate();

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("}");
	Managers::CodeManager::Writer()->WriteLn();
}

std::vector<std::tuple<std::string, Procedure*>> ClassDefinition::GetAllVirtualMethods()
{
	std::vector<std::tuple<std::string, Procedure*>> s_Methods;

	// Add virtual methods from our parents.
	if (m_Header->m_Extends)
	{
		auto s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);
		auto s_ParentMethods = s_Parent->GetAllVirtualMethods();

		for (auto s_Method : s_ParentMethods)
			s_Methods.push_back(s_Method);
	}

	// And then add methods from ourselves.
	for (auto s_Method : GetUniqueVirtualMethods())
		s_Methods.push_back(std::make_tuple(m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name, s_Method));

	return s_Methods;
}

std::vector<std::tuple<std::string, Procedure*>> ClassDefinition::GetFinalVirtualMethods()
{
	std::vector<std::tuple<std::string, Procedure*>> s_AllMethods = GetAllVirtualMethods();
	std::vector<std::tuple<std::string, Procedure*>> s_FinalMethods;

	for (auto s_VirtualMethod : s_AllMethods)
	{
		if (!m_Body->m_Procedures)
		{
			s_FinalMethods.push_back(s_VirtualMethod);
			continue;
		}

		// See if our own class has this method defined.
		bool s_MethodFound = false;
		for (auto s_Method : *m_Body->m_Procedures)
		{
			if (s_Method->m_Type == ProcedureType::Abstract)
				continue;

			if (s_Method->m_Header->m_Name->m_Name == std::get<1>(s_VirtualMethod)->m_Header->m_Name->m_Name)
			{
				s_MethodFound = true;
				s_FinalMethods.push_back(std::make_tuple(m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name, s_Method));
				break;
			}
		}

		if (s_MethodFound)
			continue;

		s_FinalMethods.push_back(s_VirtualMethod);
	}
	
	return s_FinalMethods;
}

std::vector<Procedure*> ClassDefinition::GetUniqueVirtualMethods()
{
	auto s_PureVirtualMethods = GetMethods(ProcedureType::Abstract);
	auto s_VirtualMethods = GetMethods(ProcedureType::Dynamic);

	// Combine methods.
	std::vector<Procedure*> s_FinalMethods;
	s_FinalMethods.reserve(s_PureVirtualMethods.size() + s_VirtualMethods.size());
	s_FinalMethods.insert(s_FinalMethods.end(), s_PureVirtualMethods.begin(), s_PureVirtualMethods.end());
	s_FinalMethods.insert(s_FinalMethods.end(), s_VirtualMethods.begin(), s_VirtualMethods.end());

	// Sort methods.
	std::sort(s_FinalMethods.begin(), s_FinalMethods.end(), [](const Procedure* p_Left, const Procedure* p_Right)
	{
		return p_Left->m_Header->m_Name->m_Name < p_Right->m_Header->m_Name->m_Name;
	});

	if (m_Header->m_Extends == nullptr)
		return s_FinalMethods;

	// Remove any methods that also exist in our parents.
	auto s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);
	auto s_ParentMethods = s_Parent->GetAllVirtualMethods();

	std::vector<Procedure*> s_FilteredMethods;
	std::copy_if(s_FinalMethods.begin(), s_FinalMethods.end(), std::back_inserter(s_FilteredMethods), [s_ParentMethods](Procedure* p_Procedure)
	{
		for (auto s_ParentMethod : s_ParentMethods)
			if (std::get<1>(s_ParentMethod)->m_Header->m_Name->m_Name == p_Procedure->m_Header->m_Name->m_Name)
				return false;

		return true;
	});

	return s_FilteredMethods;
}