#include "regex/log.hpp"
#include "regex/nfa2.hpp"
#include <assert.h>
namespace regex
{
std::unordered_set<NFANode *> NFANode::accept(char value)
{
    std::unordered_set<NFANode *> res;
    // end node accept nothing
    for (auto acc : acc_)
    {
        if (acc.type_ == kDot ||
            (acc.type_ == kChar && acc.value_ == value))
        {
            res.insert(acc.next_);
        }
        else if (acc.type_ == kNil)
        {
            auto next = acc.next_;
            // hint "reach end"
            if (next->acc_.empty())
            {
                res.emplace(next);
            }
            else
            {
                res.merge(next->accept(value));
            }
        }
    }
    return res;
}

void NFANode::concat(
  NFANode *node, AcceptType type, char value)
{
    acc_.emplace_back(AcceptInfo(type, value, node));
}

bool NFANode::reach_end()
{
    return acc_.empty();
}

bool NFA::compile(std::string_view re)
{
    recursive_destroy(start_);
    Parser p;
    auto root = p.parse(re);
    if (!root)
    {
        LOG(
          "bulid regexp tree failed, err=%d", p.err_type());
        return false;
    }
    p.debug_print(root);

    start_ = build(root).first;
    debug_print(start_);
    if (!start_)
        LOG("build NFA failed");

    return start_ != nullptr;
}

bool NFA::match(std::string_view s)
{
    if (!start_)
        return false;

    std::unordered_set<NFANode *> nextnodes;
    std::unordered_set<NFANode *> curnodes;
    curnodes.insert(start_);

    while (!s.empty())
    {
        auto ch = s.front();
        s.remove_prefix(1);

        for (NFANode *node : curnodes)
        {
            nextnodes.merge(node->accept(ch));
            LOG("NFA has %d way to accept char %c",
              nextnodes.size(),
              ch);
        }
        // well ,end node will be included
        if (nextnodes.empty())
            return false;
        curnodes = std::move(nextnodes);
    }

    for (auto node : curnodes)
    {
        if (node->reach_end())
            return true;
    }

    return false;
}

NFA::NodeChunk NFA::build(TreeNode *root)
{
    switch (root->type_)
    {
    case kDot:
        return handle_dot(root);
    case kChar:
        return handle_char(root);
    case kQuesMark:
        return handle_quesmark(root);
    case kStar:
        return handle_star(root);
    case kAlter:
        return handle_alter(root);
    case kConcat:
        return handle_concat(root);
    case kPlus:
        return handle_plus(root);
    default:
        // TODO
        return handle_concat(root);
    }
}

NFA::NodeChunk NFA::handle_concat(TreeNode *root)
{
    auto chunk1 = build(root->lchild_);
    auto chunk2 = build(root->rchild_);
    chunk1.second->concat(chunk2.first);
    return std::pair(chunk1.first, chunk2.second);
}

NFA::NodeChunk NFA::handle_star(TreeNode *root)
{
    auto chunk1 = build(root->lchild_);
    auto start = new_node();
    auto end = new_node();
    start->concat(end);
    end->concat(start);
    start->concat(chunk1.first);
    chunk1.second->concat(end);
    return std::pair(start, end);
}

NFA::NodeChunk NFA::handle_dot(TreeNode *root)
{
    auto start = new_node();
    auto end = new_node();
    start->concat(end, NFANode::AcceptType::kDot);
    return std::pair(start, end);
}

NFA::NodeChunk NFA::handle_quesmark(TreeNode *root)
{
    auto chunk1 = build(root->lchild_);
    auto start = new_node();
    auto end = new_node();
    start->concat(end);
    start->concat(chunk1.first);
    chunk1.second->concat(end);
    return std::pair(start, end);
}

NFA::NodeChunk NFA::handle_plus(TreeNode *root)
{
    auto chunk1 = build(root->lchild_);
    auto start = new_node();
    auto end = new_node();
    start->concat(chunk1.first);
    chunk1.second->concat(end);
    end->concat(start);
    return std::pair(start, end);
}

NFA::NodeChunk NFA::handle_char(TreeNode *root)
{
    auto start = new_node();
    auto end = new_node();
    start->concat(
      end, NFANode::AcceptType::kChar, root->value_);
    return std::pair(start, end);
}

NFA::NodeChunk NFA::handle_alter(TreeNode *root)
{
    auto start = new_node();
    auto end = new_node();
    auto chunk1 = build(root->lchild_);
    auto chunk2 = build(root->rchild_);
    start->concat(chunk1.first);
    start->concat(chunk2.first);
    chunk1.second->concat(end);
    chunk2.second->concat(end);
    return std::pair(start, end);
}

void NFA::recursive_destroy(NFANode *node)
{
    if (!node)
        return;

    auto acclist = std::move(node->acc_);
    delete node;

    for (auto &acc : acclist)
        recursive_destroy(acc.next_);
}

NFANode *NFA::new_node()
{
    return new NFANode(max_node_id_++);
}

std::string AcceptType_to_string(NFANode::AcceptType type)
{
    switch (type)
    {
    case NFANode::AcceptType::kChar:
        return "CHAR";
    case NFANode::AcceptType::kDot:
        return "DOT";
    case NFANode::AcceptType::kNil:
        return "NIL";
    default:
        return "UNKNOWN";
    }
}

void NFA::debug_print(NFANode *node)
{
    LOG("debug print NFA");
    if (!node)
    {
        LOG("nil");
        return;
    }

    std::list<NFANode *> cur_nodes_(1, node);
    std::list<NFANode *> next_nodes_;
    while (!cur_nodes_.empty())
    {
        next_nodes_.clear();
        for (auto n : cur_nodes_)
        {
            for (auto acc : n->acc_)
            {
                if (acc.next_)
                {
                    if (acc.next_->id_ > n->id_)
                        next_nodes_.emplace_back(acc.next_);
                }
                LOG("id=%d,has %d accept "
                    "node,acctype=%s,nextid=%d,accval=%c",
                  n->id_,
                  n->acc_.size(),
                  AcceptType_to_string(acc.type_).c_str(),
                  (acc.next_ ? acc.next_->id_ : -1),
                  acc.value_);
            }
        }
        cur_nodes_.swap(next_nodes_);
    }
}
} // namespace regex