#ifndef __NFA_HPP__
#define __NFA_HPP__

#include <string_view>
namespace regex
{

struct SMachine
{};

class NFA
{
  public:
    void compile(std::string_view regex);
};
} // namespace regex
#endif