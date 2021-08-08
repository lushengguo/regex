#ifndef __MATCH_RESULT_HPP__
#define __MATCH_RESULT_HPP__

#include <iterator>
#include <string>
#include <string_view>
#include <vector>
namespace regex
{
class MatchResult
{
  private:
    typedef size_t Length;
    std::string copy_;
    Length prefix_;
    Length suffix_;
    Length match_;
    std::vector<std::string_view> submatch_;

  public:
    MatchResult(std::string_view s) : copy_(s), prefix_(0), match_(0), suffix_(0) {}
    bool matched() const { return match_ > 0; }
    std::string_view prefix() const { return std::string_view(copy_.c_str(), prefix_); }
    std::string_view match() const { return std::string_view(copy_.c_str() + prefix_, match_); }
    std::string_view suffix() const
    {
        return std::string_view(copy_.c_str() + prefix_ + match_, suffix_);
    }
    // std::string_view operator[](size_t index) const { return submatch_.at(index); }
    std::string replace(std::string_view pattern) const;

    void set_prefix(Length len) { prefix_ = len; }
    void set_suffix(Length len) { suffix_ = len; }
    void set_match(Length len) { match_ = len; }
};
} // namespace regex

#endif