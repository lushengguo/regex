#ifndef __REGEX_HPP__
#define __REGEX_HPP__
#include <string_view>
namespace regex
{
class MatchResult;
class Regex;

bool regex_match(Regex pattern, MatchResult result, std::string_view str);

bool regex_search(Regex pattern, MatchResult result, std::string_view str);

bool regex_replace(Regex pattern, std::string_view str, std::string_view format);
} // namespace regex
#endif