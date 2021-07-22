#include "nfa.hpp"
#include <algorithm>
#include <stack>
namespace regex
{

StateMachine::ID StateMachine::append_jump_condition(ID id, CharType jump_char)
{
    if (machine_.count(id == 1) && machine_[id].count(jump_char) == 0)
    {
        machine_.at(id).insert(std::make_pair(jump_char, ++biggest_));
        return biggest_;
    }
    return -1;
}

// support anchor : *|.?
StateMachine NFA::compile(const Regex &regex)
{
    StateMachine machine;
    std::stack<std::string> anchor_stack;
    std::stack<std::string> char_stack;
    StateMachine::ID id = 0;

    for (auto ch : regex) { id = machine.append_jump_condition(id, ch); }

    return machine;
}

bool NFA::regex_match(std::string_view str, const Regex &regex, MatchFlag flag)
{
    MatchResult r = search(str, regex, flag);
    if (!r.matched() && r.size() != 1)
        return false;

    return r.first()->prefix_.empty() && r.first()->subfix_.empty();
}

MatchResult NFA::search(std::string_view str, const Regex &regex, MatchFlag flag)
{
    StateMachine machine = compile(regex);
    switch (flag)
    {
    case kFullMatch: return full_search(str, machine);
    case kPartialMatch: return partial_search(str, machine);
    default: return MatchResult();
    }
}

std::string NFA::format(const MatchResult &r, std::string_view format)
{
    std::string result;
    for (auto iter = r.first(); iter <= r.last(); ++iter) {}
    return result;
}

} // namespace regex