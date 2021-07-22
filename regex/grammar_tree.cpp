#include "grammar_tree.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <stack>
#include <vector>
namespace regex
{
GrammarTreeNode *parse(std::string_view re)
{
    GrammarTreeNode *root = nullptr;
    std::stack<char> oper_stack;
    std::stack<char> ch_stack;
    for (auto ch : re)
    {
        switch (ch)
        {
        case '.': oper_stack.push('.'); break;
        case '*':
        {
            GrammarTreeNode *node = new GrammarTreeNode();
            node->token_ = '*';
            node->left_ = root;
            root = node;
            break;
        }
        case '?':
        {
            GrammarTreeNode *node = new GrammarTreeNode();
            node->token_ = '?';
            node->left_ = root;
            root = node;
            break;
        }
        case '+':
        {
            GrammarTreeNode *node = new GrammarTreeNode();
            node->token_ = '+';
            node->left_ = root;
            root = node;
            break;
        }
        case '|':
        {
            GrammarTreeNode *node = new GrammarTreeNode();
            node->token_ = '?';
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
                GrammarTreeNode *node = new GrammarTreeNode();
                node->token_ = 0; // 0 = cat
                node->left_ = root;
                GrammarTreeNode *rnode = new GrammarTreeNode();
                rnode->token_ = ch;
                node->right_ = rnode;
                ch_stack.pop();
                root = node;
            }
            break;
        };
    }
    return root;
}

void print_grammar_tree(const GrammarTreeNode &tree)
{
    const GrammarTreeNode *tr = &tree;
    std::vector<std::string> prsave;
    std::list<GrammarTreeNode *> record[2];
    while (true)
    {
        std::list<GrammarTreeNode *> *using_ptr = record;
        std::ostringstream line;
        for (auto node : *rptr) { line << (node ? std::string(node->token_) : " ") << " "; }
    }
}
} // namespace regex