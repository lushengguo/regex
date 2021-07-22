#ifndef __GRAMMAR_TREE_HPP__
#define __GRAMMAR_TREE_HPP__
#include <string_view>

namespace regex
{
struct GrammarTreeNode
{
    GrammarTreeNode() : left_(nullptr), right_(nullptr), token_(0) {}
    GrammarTreeNode *left_;
    GrammarTreeNode *right_;
    char token_;
};

GrammarTreeNode *parse(std::string_view re);
void print_grammar_tree(const GrammarTreeNode &tree);
} // namespace regex

#endif