#include "regexp_tree.hpp"
#include "util.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <stack>
#include <vector>
namespace regex
{

namespace print_binary_tree_impl
{
void binary_tree_to_string(const RegexpTreeNode &tree)
{
    typedef std::vector<const RegexpTreeNode *> OneLayer;
    std::vector<OneLayer> layers(1, OneLayer(1, &tree));

    while (true)
    {
        OneLayer layer;
        layer.reserve(2 * layers.back().size());
        for (auto node : layers.back())
        {
            if (node)
            {
                layer.emplace_back(node->left_);
                layer.emplace_back(node->right_);
            }
            else
            {
                layer.emplace_back(nullptr);
                layer.emplace_back(nullptr);
            }
        }

        if (std::find(layer.cbegin(), layer.cend(), true) == layer.cend())
            break;
        else
            layers.emplace_back(std::move(layer));
    }

    std::vector<std::ostringstream> print_layer;
    print_layer.reserve(layers.size());

    //每个node占三个字节长度
    /*
                *
              /   \
            +       -
           / \     / \
          a   b   c  nil
    */
    for (auto iter = layers.rbegin(); iter != layers.rend(); iter++) {}
}
} // namespace print_binary_tree_impl

void RegexpTree::release(RegexpTreeNode *node)
{
    if (!node)
        return;

    release(node->left_);
    release(node->right_);
    delete node;
}

void RegexpTree::parse(std::string_view re)
{
    char CatOperator = 0;
    RegexpTreeNode *root = nullptr;
    std::stack<char> oper_stack;
    std::stack<char> ch_stack;
    for (auto ch : re)
    {
        switch (ch)
        {
        case '.': oper_stack.push('.'); break;
        case '*':
        {
            RegexpTreeNode *node = new RegexpTreeNode();
            node->value_ = '*';
            node->left_ = root;
            root = node;
            break;
        }
        case '?':
        {
            RegexpTreeNode *node = new RegexpTreeNode();
            node->value_ = '?';
            node->left_ = root;
            root = node;
            break;
        }
        case '+':
        {
            RegexpTreeNode *node = new RegexpTreeNode();
            node->value_ = '+';
            node->left_ = root;
            root = node;
            break;
        }
        case '|':
        {
            RegexpTreeNode *node = new RegexpTreeNode();
            node->value_ = '?';
            node->left_ = root;
            root = node;
            break;
        }
        default:
            if (ch_stack.empty())
            {
                ch_stack.emplace(ch);
            }
            else // abacd
            {
                RegexpTreeNode *node = new RegexpTreeNode();
                node->value_ = CatOperator; // 0 = cat
                node->left_ = root;
                RegexpTreeNode *rnode = new RegexpTreeNode();
                rnode->value_ = ch;
                node->right_ = rnode;
                ch_stack.pop();
                root = node;
            }
            break;
        };
    }

    root_ = root;
}

std::map<char, std::set<RegexpTree::ID>> RegexpTree::get_symbol_ids()
{
    std::map<char, std::set<RegexpTree::ID>> mmp;
    std::list<RegexpTreeNode *> l;
    get_sorted_leaf(l, root_);
    for (auto leaf : l)
    {
        if (leaf)
        {
            if (mmp.count(leaf->value_) == 0)
                mmp.insert(std::make_pair(leaf->value_, std::set<RegexpTree::ID>()));
            mmp.at(leaf->value_).insert(leaf->id_);
        }
    }
    return mmp;
}

void RegexpTree::get_sorted_leaf(std::list<RegexpTreeNode *> &l, RegexpTreeNode *root)
{
    if (root && !root->left_ && !root->right_)
    {
        l.emplace_back(root);
        return;
    }

    get_sorted_leaf(l, root->left_);
    get_sorted_leaf(l, root->right_);
}

void RegexpTree::arrange_id()
{
    int id = 0;
    std::list<RegexpTreeNode *> leafs;
    get_sorted_leaf(leafs, root_);
    for (auto leaf : leafs)
    {
        if (leaf)
            leaf->id_ = id++;
    }
}

//一个节点是否可以为空？叶子节点为空或者操作符节点为'*'|'?'时，都表示可以为空
bool RegexpTree::nullable(const RegexpTreeNode *node)
{
    if (!node)
        return true;

    if (!node->left_ && !node->right_)
        return false;

    return nullable(node->left_) && nullable(node->right_);
}

//首个开始匹配字符的可选项集合 ,partial match时特别有用
RegexpTree::StateSet RegexpTree::firstpos(const RegexpTreeNode *node, bool calc_lastpos)
{
    StateSet po;
    if (!node)
        return po;

    if (!node->left_ && !node->right_)
        return StateSet({node->id_});

    if (node->left_ || node->right_)
    {
        switch (node->value_)
        {
        case '|':
        case '*': //'*'只有一个子节点
        {
            auto p1 = firstpos(node->left_);
            auto p2 = firstpos(node->right_);
            p1.insert(p2.begin(), p2.end());
            return p1;
        }
        case RegexpTreeNode::CatSymbol:
            RegexpTreeNode *consider_node = calc_lastpos ? node->right_ : node->left_;
            if (nullable(consider_node))
                return set_union(firstpos(node->left_), firstpos(node->right_));
            else
                return firstpos(consider_node);
        }
    }
}

//进入到下一个状态的可选字符集合
// cat节点那就是右子树的firstpos，代表从右边重头开始
// '|'节点代表
RegexpTree::StateSet RegexpTree::lastpos(const RegexpTreeNode *node)
{
    return firstpos(node, true);
}

//匹配到某个字符时,可以接受的下一个字符的集合
RegexpTree::StateSet RegexpTree::followpos(const RegexpTreeNode *node)
{
    switch (node->value_)
    {
    case RegexpTreeNode::CatSymbol: return set_union(firstpos(node->right_), lastpos(node->left_));
    case '*': return lastpos(node);
    default: break;
    }
}
} // namespace regex