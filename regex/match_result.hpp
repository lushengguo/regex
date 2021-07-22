#ifndef __MATCH_RESULT_HPP__
#define __MATCH_RESULT_HPP__

#include <string>
#include <string_view>
#include <vector>
namespace regex
{
class MatchResult
{
  private:
    struct SubMatch
    {
        std::string_view prefix_;
        std::string_view match_;
        std::string_view subfix_;

        std::vector<std::string_view> bracket_matchs_;
    };
    typedef std::vector<SubMatch>::const_iterator ResultIter;
    std::vector<SubMatch> matchs_;
    std::string copy_;
    std::string_view view_copy_;

  public:
    bool matched() const { return !matchs_.empty(); }
    size_t size() const { return matchs_.size(); }
    ResultIter first() const { return matchs_.cbegin(); }
    ResultIter last() const { return matchs_.cend() - 1; }
};
} // namespace regex

#endif