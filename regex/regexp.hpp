#ifndef __REGEXP_TREE_HPP__
#define __REGEXP_TREE_HPP__
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <string_view>

namespace regex
{
typedef int ID;
typedef int ValueType;

enum TokenType {
    kChar,
    kAlter,
    kConcat,
    kDot,
    kStar,
    kQuesMark,
    kPlus,
    kLParen,
    kRParen
};

struct TreeNode
{

    TreeNode(TokenType type, size_t id, char value = 0)
      : lchild_(nullptr),
        rchild_(nullptr),
        type_(type),
        value_(value),
        id_(id)
    {}

    TreeNode *lchild_;
    TreeNode *rchild_;
    TokenType type_;
    char value_;
    size_t id_;
};

class RegexpTree;

class Parser
{
  public:
    enum ErrorType {
        kNoError,
        kInvalidStar,
        kInvalidAlter,
        kInvalidQuesMark,
        kInvalidParen,
        kParserError,
        kInvalidPlus
    };

    Parser() : err_(kNoError), nodeID_(0)
    {}

    TreeNode *parse(std::string_view p);
    void destroy(TreeNode *root);
    void debug_print(TreeNode *node);

    bool err() const;
    ErrorType err_type() const;

  private:
    TreeNode *parse_impl(std::string_view p);

    TreeNode *new_node(TokenType type, char val = 0);

    TreeNode *plus(TreeNode *node);
    TreeNode *star(TreeNode *node);
    TreeNode *question_mark(TreeNode *node);
    // TreeNode *back_slash(TreeNode *node);
    TreeNode *concat(TreeNode *lnode, TreeNode *rnode);
    TreeNode *alter(TreeNode *lnode, TreeNode *rnode);

    ErrorType err_;
    size_t nodeID_;
};

} // namespace regex

#endif