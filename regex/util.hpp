#ifndef __UTIL_HPP__
#define __UTIL_HPP__
#include <set>
namespace regex
{
template <typename T>
std::set<T> set_union(const std::set<T> &s1, const std::set<T> &s2)
{
    std::set<T> s;
    s.insert(s1.cbegin(), s1.cend());
    s.insert(s2.cbegin(), s2.cend());
    return s;
}
} // namespace regex
#endif