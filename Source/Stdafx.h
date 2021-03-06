#ifndef PRECOMPILED_HEADER
#define PRECOMPILED_HEADER

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <map>
#include <fstream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <time.h>
#include <vector>
#include <unordered_map>

#if UNICODE
  typedef std::wstring String;
  typedef wchar_t Char;
  typedef std::wostream Ostream;
  typedef std::wofstream Ofstream;

  #define Cout std::wcout
  #define __TEXT(quote) L##quote
#else
  typedef std::string String;
  typedef char Char;
  typedef std::ostream Ostream;
  typedef std::ofstream Ofstream;

  #define Cout std::cout
  #define __TEXT(quote) quote
#endif

#endif
