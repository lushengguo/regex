#ifndef __REGEX_HPP__
#define __REGEX_HPP__
#include "dfa.hpp"
#include "match_result.hpp"
#include "nfa.hpp"
#include <memory>
#include <string_view>
namespace regex
{
class Regex
{
  public:
    explicit Regex(std::string_view s) : pattern_(s)
    {
        build_NFA();
        build_DFA();
    }

    ~Regex()
    {
        destroy_NFA();
        destroy_DFA();
    }

  private:
    bool build_NFA() const { return NFA::build(pattern_); }
    bool build_DFA() const { return DFA::build(pattern_); }
    void destroy_NFA() const { NFA::destroy(); }
    void destroy_DFA() const { DFA::destroy(); }

  private:
    std::string pattern_;
};

class RegexApi
{
  public:
    virtual bool regex_match(std::string_view s, const Regex &re) = 0;
    virtual std::string regex_replace(
      std::string_view s, const Regex &re, std::string_view pattern) = 0;
    virtual std::unique_ptr<MatchResult> regex_search(std::string_view s, const Regex &re) = 0;
};
} // namespace regex
#endif