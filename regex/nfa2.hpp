#ifndef __NFA_HPP__
#define __NFA_HPP__
#include "regex/regexp.hpp"
#include <unordered_set>
namespace regex
{
struct NFANode
{
    enum AcceptType { kChar, kDot, kNil };

    struct AcceptInfo
    {
        AcceptInfo(
          AcceptType type, char value, NFANode *next)
          : type_(type), value_(value), next_(next)
        {}
        AcceptType type_;
        char value_;
        NFANode *next_;
    };

    NFANode(size_t id) : id_(id)
    {}

    void concat(NFANode *node,
      AcceptType type = kNil,
      char value = 0);
    std::unordered_set<NFANode *> accept(char value);
    bool reach_end();

    std::list<AcceptInfo> acc_;
    size_t id_;
};

class NFA
{
  public:
    typedef NFANode *StartNode;
    typedef NFANode *EndNode;
    typedef std::pair<StartNode, EndNode> NodeChunk;

    NFA() : start_(nullptr), max_node_id_(0)
    {}
    ~NFA()
    {
        recursive_destroy(start_);
    }

    // both of them are not thread safe
    // call compile first
    // then match
    bool compile(std::string_view re);
    bool match(std::string_view s);

  private:
    NFANode *new_node();
    void recursive_destroy(NFANode *node);

    NodeChunk build(TreeNode *root);
    NodeChunk handle_concat(TreeNode *root);
    NodeChunk handle_star(TreeNode *root);
    NodeChunk handle_dot(TreeNode *root);
    NodeChunk handle_quesmark(TreeNode *root);
    NodeChunk handle_plus(TreeNode *root);
    NodeChunk handle_char(TreeNode *root);
    NodeChunk handle_alter(TreeNode *root);

    void debug_print(NFANode *node);

    NFANode *start_;
    size_t max_node_id_;
};
} // namespace regex
#endif