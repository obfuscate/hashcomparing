#ifndef PRECOMPILED_HEADER
#define PRECOMPILED_HEADER

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>
#include <time.h>
#include <vector>
#include <unordered_map>

#if UNICODE
  typedef std::wstring String;
  typedef wchar_t Char;

  #define Cout std::wcout
  #define __TEXT(quote) L##quote
#else
  typedef std::string String;
  typedef char Char;

  #define Cout std::cout
  #define __TEXT(quote) quote
#endif

#endif
