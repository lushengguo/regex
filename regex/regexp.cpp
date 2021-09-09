#include "regex/log.hpp"
#include "regex/regexp.hpp"
#include "regex/util.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <vector>
namespace regex
{
TreeNode *Parser::star(TreeNode *node)
{
    if (!node)
    {
        err_ = kInvalidStar;
        return node;
    }

    auto newnode = new_node(kStar);
    if (node->rchild_)
    {
        newnode->lchild_ = node->rchild_;
        node->rchild_ = newnode;
        return node;
    }
    else
    {
        newnode->lchild_ = node->lchild_;
        return newnode;
    }
}

TreeNode *Parser::plus(TreeNode *node)
{
    if (!node)
    {
        err_ = kInvalidPlus;
        return node;
    }

    auto root = new_node(kPlus);
    root->lchild_ = node;
    return root;
}

TreeNode *Parser::alter(TreeNode *lnode, TreeNode *newnode)
{
    if (!lnode || !newnode)
    {
        err_ = kInvalidAlter;
        return lnode;
    }

    auto root = new_node(kAlter);
    root->lchild_ = lnode;
    root->rchild_ = newnode;
    return root;
}

TreeNode *Parser::question_mark(TreeNode *node)
{
    if (!node)
    {
        err_ = kInvalidQuesMark;
        return node;
    }

    auto root = new_node(kQuesMark);
    root->lchild_ = node;
    return root;
}

TreeNode *Parser::concat(TreeNode *lnode, TreeNode *newnode)
{
    if (!lnode)
        return newnode;
    if (!newnode)
        return lnode;

    auto root = new_node(kConcat);
    root->lchild_ = lnode;
    root->rchild_ = newnode;
    return root;
}

TreeNode *Parser::parse(std::string_view p)
{
    err_ = kNoError;
    nodeID_ = 0;
    return parse_impl(p);
}

TreeNode *Parser::parse_impl(std::string_view p)
{
    TreeNode *node = nullptr;
    TreeNode *root = nullptr;
    size_t lparen_cnt = 0;
    while (!p.empty())
    {
        char ch = p.front();
        p.remove_prefix(1);

        switch (ch)
        {
        case '*':
            node = star(node);
            break;
        case '?':
            node = question_mark(node);
            break;
        case '|':
            node = alter(node, parse_impl(p));
            break;
        case '+':
            node = plus(node);
            break;
        case '(':
        {
            lparen_cnt++;
            for (size_t i = 0; i < p.size(); i++)
            {
                if (p[i] == '(')
                    lparen_cnt++;
                if (p[i] == ')')
                    lparen_cnt--;
                if (lparen_cnt == 0)
                {
                    LOG("i=%d", i);
                    std::string_view s_between_parentheses(
                      p.data(), i);
                    LOG("string between parentheses %s",
                      std::string(s_between_parentheses)
                        .c_str());
                    node = concat(node,
                      parse_impl(s_between_parentheses));
                    p.remove_prefix(i + 1);
                    break;
                }
            }
            if (lparen_cnt)
                err_ = kInvalidParen;
            break;
        }
        default: // CHAR
        {
            auto newnode = new_node(kChar, ch);
            if (node)
                node = concat(node, newnode);
            else
                node = newnode;
            break;
        }
        }

        if (err_ != kNoError || node == nullptr)
        {
            destroy(root);
            return nullptr;
        }

        root = node;
    }

    return root;
}

void Parser::destroy(TreeNode *node)
{
    if (!node)
        return;

    auto l = node->lchild_;
    auto r = node->rchild_;
    delete node;
    destroy(l);
    destroy(r);
}

TreeNode *Parser::new_node(TokenType type, char val)
{
    return new TreeNode(type, nodeID_++, val);
}

bool Parser::err() const
{
    return err_ != kNoError;
}

Parser::ErrorType Parser::err_type() const
{
    return err_;
}

std::string TokenType_to_string(TokenType type)
{
    switch (type)
    {
    case kChar:
        return "CHAR";
    case kAlter:
        return "ALTER";
    case kConcat:
        return "CONCAT";
    case kDot:
        return "DOT";
    case kStar:
        return "STAR";
    case kQuesMark:
        return "QUESMARK";
    case kPlus:
        return "PLUS";
    case kLParen:
        return "LPAREN";
    case kRParen:
        return "RPAREN";
    }
}

void Parser::debug_print(TreeNode *node)
{
    if (!node)
        return;

    std::ostringstream oss;
    oss << node->id_ << "_"
        << TokenType_to_string(node->type_) << "_";
    if (node->value_ == 0)
        oss << "\\0";
    else
        oss << node->value_;
    oss << "_";
    if (node->lchild_)
        oss << node->lchild_->id_;
    else
        oss << "nil";
    oss << "_";
    if (node->rchild_)
        oss << node->rchild_->id_;
    else
        oss << "nil";

    LOG("%s", oss.str().c_str());
    debug_print(node->lchild_);
    debug_print(node->rchild_);
}
} // namespace regex