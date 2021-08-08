#ifndef __REGEXP_TREE_HPP__
#define __REGEXP_TREE_HPP__
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string_view>

namespace regex
{
typedef int ID;

struct RegexpTreeNode
{
    const static char CatSymbol = '\0';

    RegexpTreeNode() : left_(nullptr), right_(nullptr), parent_(nullptr), id_(0) {}

    RegexpTreeNode *left_;
    RegexpTreeNode *right_;
    RegexpTreeNode *parent_;
    char value_;
    ID id_;
};

class RegexpTree
{
  public:
    typedef int ID;
    typedef ID IDSum;
    typedef std::set<ID> StateSet;
    enum ErrorType
    {
        kNormal
    };

    RegexpTree(std::string_view re) : err_(kNormal), root_(nullptr)
    {
        parse(re);
        if (root_)
            arrange_id();
    }

    ~RegexpTree() { release(root_); }

    RegexpTree(const RegexpTree &&) = delete;
    const RegexpTree &operator=(const RegexpTree &) = delete;

    // return root
    const RegexpTreeNode *get_root_node() const { return root_; }
    std::map<char, std::set<ID>> get_symbol_ids();
    std::string err() const;
    std::string to_string(const RegexpTreeNode &root, size_t value_align) const;

    void parse(std::string_view re);

    static bool nullable(const RegexpTreeNode *node);
    static StateSet firstpos(const RegexpTreeNode *node, bool calc_lastpos = false);
    static StateSet lastpos(const RegexpTreeNode *node);
    static StateSet followpos(const RegexpTreeNode *node);

  private:
    void arrange_id();
    void get_sorted_leaf(std::list<RegexpTreeNode *> &l, RegexpTreeNode *root);
    void release(RegexpTreeNode *node);
    ErrorType err_;
    RegexpTreeNode *root_;
};
// print tree
template <typename ValueType>

} // namespace regex

#endif