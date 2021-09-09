#ifndef __UTIL_HPP__
#define __UTIL_HPP__
#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <string_view>
namespace regex
{

std::string binary_tree_auto_indent(
  std::list<std::string> cur_layer,
  std::string_view prev_layer);

template <typename TreeNode>
void print_binary_tree(const TreeNode *root,
  std::function<const TreeNode *(const TreeNode *)>
    get_left_child,
  std::function<const TreeNode *(const TreeNode *)>
    get_right_child,
  std::function<std::string(const TreeNode *)> serialize)
{
    if (!root)
        return;

    std::list<std::list<std::string>> layer_strings;
    std::list<const TreeNode *> cur_layer(1, root);
    std::list<const TreeNode *> next_layer;

    while (!cur_layer.empty())
    {
        std::list<std::string> layer_string;
        next_layer.resize(0);
        for (const TreeNode *node : cur_layer)
        {
            layer_string.emplace_back(serialize(node));
            next_layer.emplace_back(get_left_child(node));
            next_layer.emplace_back(get_right_child(node));
        }
        layer_strings.emplace_back(std::move(layer_string));
        if (std::count(next_layer.cbegin(),
              next_layer.cend(),
              nullptr) == next_layer.size())
            break;
        cur_layer.swap(next_layer);
    }

    for (auto layer_string : layer_strings)
    {
        for (auto str : layer_string)
            std::cout << str << " ";
        std::cout << std::endl;
    }
}

} // namespace regex
#endif