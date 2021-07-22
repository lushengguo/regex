#ifndef __NFA_HPP__
#define __NFA_HPP__

#include "match_result.hpp"
#include <set>
#include <string_view>
#include <unordered_map>
namespace regex
{

typedef std::string Regex;

class StateMachine
{
  public:
    typedef char CharType;
    typedef int ID;
    typedef std::unordered_map<CharType, ID> JumpConditions;
    typedef std::unordered_map<ID, JumpConditions> Machine;

    StateMachine() : biggest_(0) {}
    ~StateMachine() = default;

    ID append_jump_condition(ID id, CharType jump_char);
    bool ok() const { return machine_.size() > 1; }

  private:
    Machine machine_;
    ID biggest_;
};

class NFA
{
  public:
    enum MatchFlag
    {
        kFullMatch,
        kPartialMatch
    };
    bool regex_match(std::string_view str, const Regex &, MatchFlag = kFullMatch);

  private:
    StateMachine compile(const Regex &);
    MatchResult search(std::string_view str, const Regex &, MatchFlag);
    MatchResult full_search(std::string_view str, const StateMachine &);
    MatchResult partial_search(std::string_view str, const StateMachine &);

    std::string format(const MatchResult &, std::string_view format);
};
} // namespace regex
#endif