#include "nfa.hpp"
#include <assert.h>
#include <iterator>
#include <set>
namespace regex
{
bool NFA::build(std::string_view re) {}

bool RegexNFA::regex_match(std::string_view s, Regex re)
{
    auto result(regex_search(s, re));
    return result->matched() && result->prefix().empty() && result->suffix().empty();
}

std::string RegexNFA::regex_replace(std::string_view s, Regex re, std::string_view pattern)
{
    std::string result;
    std::string_view modifying_segment(s);
    while (modifying_segment.size())
    {
        auto r(regex_search(s, re));
        if (!r->matched())
        {
            result.append(r->suffix());
            return result;
        }
        else
        {
            result.append(r->prefix());
            result.append(r->replace(pattern));
            modifying_segment.remove_prefix(r->prefix().size() + r->match().size());
        }
    }
    return result;
}

// greedy version
std::unique_ptr<MatchResult> RegexNFA::regex_search(std::string_view s, Regex re)
{
    std::unique_ptr<MatchResult> result(new MatchResult(s));
    if (!re.build_NFA())
        return result;

    // NFA promise start exist
    std::set<ID> current(1, NFA::start()->id());
    std::set<ID> next;
    std::string_view::const_iterator startIter = s.cbegin();
    std::string_view::const_iterator termIter = s.cend();

    for (auto charIter = s.cbegin(); charIter != s.cend(); charIter++)
    {
        // get next accept stage
        for (auto id : current)
        {
            auto nfa = NFA::nfa(id);
            if (next.count(id) == 1)
                continue;
            const std::set<ID> *accept = nfa->accept(*charIter);
            if (accept)
                next.insert(accept->cbegin(), accept->cend());
        }

        if (next.empty())
        {
            // greedy match success
            if (termIter != s.cend())
            {
                result->set_prefix(std::distance(s.cbegin(), startIter));
                result->set_match(std::distance(startIter, termIter));
                result->set_suffix(std::distance(termIter, s.cend()));
                return result;
            }

            // nothing matched
            if (std::next(charIter) == s.cend())
                return result;

            // try next start point
            current.clear();
            current.insert(NFA::start()->id());
            charIter = startIter;
            startIter = std::next(startIter);
            continue;
        }

        // check terminate - slide window
        for (auto id : next)
        {
            if (NFA::nfa(id)->is_terminate())
                termIter = charIter;
        }

        current.swap(next);
        next.clear();
    }

    return result;
}
} // namespace regex