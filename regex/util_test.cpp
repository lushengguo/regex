#include "regex/util.hpp"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace regex;

static size_t number = 0;
struct TreeNode
{
    TreeNode() : left(nullptr), right(nullptr), value(0)
    {}
    TreeNode *left;
    TreeNode *right;
    int value;
};

TreeNode *create_tree(int depth)
{
    if (depth == 0)
        return nullptr;

    TreeNode *node = new TreeNode;
    node->value = number++;
    node->left = create_tree(depth - 1);
    node->right = create_tree(depth - 1);
    return node;
}

int main()
{
    auto node = create_tree(3);
    std::function<const TreeNode *(const TreeNode *)>
      get_left_child =
        [](const TreeNode *node) { return node->left; };
    std::function<const TreeNode *(const TreeNode *)>
      get_right_child =
        [](const TreeNode *node) { return node->right; };
    std::function<std::string(const TreeNode *)> serialize =
      [](const TreeNode *node) -> std::string {
        if (!node)
            return "nullptr";
        std::ostringstream oss;
        if (node->left)
            oss << (size_t)node->left;
        else
            oss << "nullptr";
        oss << "_";
        if (node->right)
            oss << (size_t)node->right;
        else
            oss << "nullptr";
        oss << "_" << node->value;
        return oss.str();
    };

    print_binary_tree(
      node, get_left_child, get_right_child, serialize);
}