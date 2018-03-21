#include <iostream>
using std::cout;

int main()
{
   cout << "\"// a comment\"\n";
   cout << 'a' << '\'' << 'b' << '\\' << '\"' << 'c' << "\\\\\\Hello world///" << '\n' << '"'; // comment
   auto _max = 0xffffu;
   auto tmp = 1000000000ull;
}