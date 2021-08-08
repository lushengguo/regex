#ifndef __NFA_HPP__
#define __NFA_HPP__
#include "regex.hpp"
#include "regexp_tree.hpp"
#include <map>
#include <set>

namespace regex
{
class NFA
{
  public:
    NFA() : terminate_(false) {}

    const std::set<ID> *accept(char ch) const
    {
        return accept_map_.count(ch) ? &accept_map_.at(ch) : nullptr;
    }
    bool is_terminate() const { return terminate_; }
    ID id() const { return id_; }

    static bool build(std::string_view re);
    static const NFA *start() { return nfas.count(0) == 1 ? nfas.at(0) : nullptr; }
    static const NFA *nfa(ID id) { return nfas.at(id); }

  private:
    static std::map<ID, const NFA *> nfas;

    ID id_;
    std::map<char, std::set<ID>> accept_map_;
    bool terminate_;
};

class RegexNFA : RegexApi
{
  public:
    bool regex_match(std::string_view s, Regex re) override;
    std::string regex_replace(std::string_view s, Regex re, std::string_view pattern) override;
    std::unique_ptr<MatchResult> regex_search(std::string_view s, Regex re) override;
};
} // namespace regex

#endif