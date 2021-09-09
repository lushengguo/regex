#include "regex/nfa2.hpp"
#include <iostream>
using namespace regex;
using namespace std;

int main()
{
    NFA nfa;
    nfa.compile("(abc*)d");
    cout << boolalpha << nfa.match("abcccccccd") << endl;
}
