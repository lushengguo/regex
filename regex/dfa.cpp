#include "dfa.hpp"
#include "regexp_tree.hpp"
#include <iostream>
#include <memory>
#include <vector>
namespace regex
{
namespace impl
{
struct SetOperation
{
    typedef RegexpTree::ID ID;
    bool equal(const std::set<ID> &rhs) const
    {
        return std::equal(cur_.cbegin(), cur_.cend(), rhs.cbegin());
    }

    std::set<ID> cur_;
    std::set<ID> firstpos_;
    std::set<ID> lastpos_;
    std::set<ID> follow_;
};

} // namespace impl

/*要想清楚 叶子节点的状态集合 和 几个positon之间的关系
//{1,2,3,4} 输入个 5 那么就{1,2,3,4,5}
//{3,4,5} 输入个1 那么就没法接受

1. 接受了一个节点后，就可以接受下一个节点
//如果下一个输入在lastpos里面，就把它接到集合里面去，然后再找下一个lastpos
2. 当下一个输入不符合预期时，怎么开倒车？
//
*/
void DFA::parse(std::string_view re)
{
    RegexpTree tree(re);
    if (tree.err().empty())
    {
        auto root = tree.get_root_node();
        auto symbols_with_id = tree.get_symbol_ids();
        std::set<char> unique_symbols;
        unique_symbols.insert(symbols_with_id.cbegin(), symbols_with_id.cend());

        std::set<RegexpTree::ID> ID_set;
        start_ = new DFANode(RegexpTree::firstpos(root));
        RegexpTree::StateSet sset = start_->accept_state_;
        while (true)
        {
            for (auto symbol : unique_symbols)
            {
                if (lastpos(sset).count(symbol) == 1) {}
            }
        }
    }
    else
    {
        std::cout << tree.err() << std::endl;
    }
}

void DFA::release(DFANode *node)
{
    if (!node)
        return;

    auto next_nodes(std::move(node->conds_));
    delete node;

    for (auto node2 : next_nodes) { release(node2.second); }
}
} // namespace regex