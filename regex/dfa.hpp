#ifndef __DFA_HPP__
#define __DFA_HPP__
#include "regexp_tree.hpp"
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <unordered_set>

namespace regex
{
class MatchResult;
class NFA;
class DFA;

class DFA
{
  public:
    struct DFANode
    {
        typedef RegexpTree::ID ID;
        typedef RegexpTree::StateSet StateSet;
        typedef char AcceptInput;
        typedef std::map<AcceptInput, DFANode *> AcceptConditions;

        DFANode(const StateSet &state) : accept_state_(state) {}

        ID id_;
        StateSet accept_state_;
        AcceptConditions conds_;
    };

    DFA(std::string_view re) : start_(nullptr) { parse(re); }
    ~DFA() { release(start_); }

    // cant copy from another, idk why, maybe this class will be intrusive someday
    // as re2 has to face multi-thread problem
    DFA(const DFA &dfa) = delete;
    const DFA &operator=(const DFA &) = delete;

    bool ok() const { return start_; }
    std::string err() const;

    MatchResult full_search(std::string_view text);
    MatchResult partial_search(std::string_view text);
    std::string replace(std::string_view text, std::string_view replace_pattern);

    static bool build(std::string_view re);
    static void destroy();

  private:
    // const DFASet &get() const { return ds_; }
    void parse(std::string_view re);
    void release(DFANode *);

    DFANode *start_;
};

} // namespace regex
#endif