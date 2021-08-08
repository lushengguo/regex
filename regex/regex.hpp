#ifndef __REGEX_HPP__
#define __REGEX_HPP__
#include "dfa.hpp"
#include "match_result.hpp"
#include <memory>
#include <string_view>
namespace regex
{
class Regex
{
  public:
    bool build_NFA();
    bool build_DFA();

  private:
    std::string pattern_;
};

class RegexApi
{
  public:
    virtual bool regex_match(std::string_view s, Regex re) = 0;
    virtual std::string regex_replace(std::string_view s, Regex re, std::string_view pattern) = 0;
    virtual std::unique_ptr<MatchResult> regex_search(std::string_view s, Regex re) = 0;
};
} // namespace regex
#endif