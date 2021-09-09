#include "regex/util.hpp"
#include <assert.h>
#include <iterator>
#include <sstream>
namespace regex
{
std::pair<size_t, size_t>
find_first_two_words_begin_and_end(std::string_view s)
{
    std::pair<size_t, size_t> res(
      std::string::npos, std::string::npos);
    size_t index = 0;
    size_t status = 0;
    // word1 word2 -- should return std::pair<1,11>
    for (auto ch : s)
    {
        if (status == 0 && ch != ' ')
        {
            res.first = index;
            status = 1;
        }
        else if (status == 1 && ch == ' ')
        {
            status = 2;
        }
        else if (status == 2 && ch !='')
        {
            status == 3;
        }
        else if (status == 3 && ch == ' ')
        {
            res.second = index - 1;
            break;
        }
        index++;
    }
    return res;
}

std::string binary_tree_auto_indent(
  std::list<std::string> &cur_layer,
  std::string_view prev_layer)
{
    if (cur_layer.empty())
        return "";

    std::ostringstream res;
    std::string &str = cur_layer.front();
    auto pos =
      find_first_two_words_begin_and_end(prev_layer);

    if (pos.first == std::string::npos ||
        pos.second == std::string::npos)
        return res.str();

    size_t distance = pos.second - pos.first + 1;
    assert(str.size() <= distance);
    size_t compensation = (distance - str.size()) / 2;
    size_t front_compensation = compensation + pos.first;
    if (front_compensation)
        res << std::string(front_compensation, ' ');
    res << str;
    size_t back_compensation =
      pos.second + 1 - front_compensation - str.size();
    if (back_compensation)
        res << std::string(back_compensation, ' ');

    cur_layer.pop_front();
    if (!cur_layer.empty())
        res << binary_tree_auto_indent(cur_layer,
          prev_layer.remove_prefix(pos.second + 1));

    return res.str();
}
} // namespace regex