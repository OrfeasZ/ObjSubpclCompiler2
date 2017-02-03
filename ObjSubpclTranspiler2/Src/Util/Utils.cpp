#include "Utils.h"

#include <sstream>
#include <algorithm>
#include <iterator>

using namespace Util;

std::string Utils::Join(const std::vector<std::string>& p_Strings, const std::string& p_Separator)
{
	if (p_Strings.size() == 0)
		return "";

	if (p_Strings.size() == 1)
		return p_Strings[0];

	std::ostringstream s_Stream;

	std::copy(p_Strings.begin(), p_Strings.end() - 1, std::ostream_iterator<std::string>(s_Stream, p_Separator.c_str()));
	s_Stream << p_Strings.back();

	return s_Stream.str();
}