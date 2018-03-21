// SourceLine class member-function definitions.

#include <iostream>
using std::cout;
#include <ctype.h> // isalpha, isdigit
#include "SourceLine.h" // SourceLine class definition

// default/conversion constructor
SourceLine::SourceLine() : sourceLine()
{
}

void SourceLine::assign( const char *s, size_t n )
{
   sourceLine.assign( s, n );
}

// start here
// 目前只有按照 delComments -> delStrConst -> delCharConst 的順序呼叫才不會錯
// delStrConst  會刪到//後的""
// delCharConst 會刪到//後及""內的''
//              先放置

// avoid [cout << "a comment:\"// a comment\"\n";]
//                             ^
void SourceLine::delComments()
{
   auto pos { 0u }, size = sourceLine.size();
   bool inStr { false };
   if (size && sourceLine[0] == '"') {
      ++pos;
      inStr = true;
   }
   for (; pos + 1 < size; ++pos) {
      if (sourceLine[pos] == '"' && sourceLine[pos - 1] != '\\' && sourceLine[pos - 1] != '\'')
         inStr = !inStr;
      else if(!inStr && sourceLine[pos] == '/' && sourceLine[pos + 1] == '/') {
         sourceLine.erase(pos);
         break;
      }
   }
}

// avoid [cout << "\"Hello, world!\"\n";] or [char c = '"';]
//                 ^              ^                     ^
void SourceLine::delStrConst()
{
   auto pos { 1u }, len { 0u };
   bool inStr { false };
   if (sourceLine.size() && sourceLine[0] == '"') {
      ++len;
      inStr = true;
   }
   while (sourceLine.size() && pos + len < sourceLine.size()) {
      if (sourceLine[pos + len] == '"' && sourceLine[pos + len - 1] != '\\' && sourceLine[pos + len - 1] != '\'')
         inStr = !inStr;
      if (inStr)
         ++len;
      else {
         if(len > 0u) {
            sourceLine.erase(pos, len + 1);
            len = 0u;
         }
         else
            ++pos;
      }
   }
   if (inStr)
      throw("Invalid line!");
}

// 'a' or '\n'
void SourceLine::delCharConst()
{
   auto begin { 0u }, end { 0u };
   char delimiter = '\'';
   while ((begin = sourceLine.find(delimiter, begin)) != string::npos) {
      end = sourceLine[begin + 1] == '\\' ? begin + 3 : begin + 2;
      if (end < sourceLine.size() && sourceLine[end] == delimiter)
         sourceLine.erase(begin, end - begin + 1);
   }
}

// avoid 0xff, 0u
string SourceLine::delFirstIdentifier()
{
   if (!sourceLine.size())
      return string();

   auto isValidPrefix =
      [](char c) -> bool {
         return isalpha(c) || c == '_';
      };
   auto isValidSuffix =
      [](char c) -> bool {
         return isalpha(c) || c == '_' || isdigit(c);
      };
   auto pos { 1u }, len { 0u };
   bool match { false };
   if (isValidPrefix(sourceLine[0])) {
      ++len;
      --pos;
      match = true;
   }
   while (pos + len < sourceLine.size()) {
      if(match) {
         if (!isValidSuffix(sourceLine[pos + len]))
            match = false;
         else
            ++len;
      }
      else {
         if (len > 0u) {
            string tmp = sourceLine.substr(pos, len);
            sourceLine.erase(0, pos + len);
            return tmp;
         }
         else if (!isValidSuffix(sourceLine[pos + len - 1]) && isValidPrefix(sourceLine[pos + len])) {
            match = true;
            ++len;
         }
         else
            ++pos;
      }
   }
   if (match)
      throw("Invalid line!");
   else
      return string();
}
