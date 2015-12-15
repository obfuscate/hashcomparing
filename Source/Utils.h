#ifndef UTILS_HEADER
#define UTILS_HEADER

#include "Stdafx.h"

namespace Utils
{
  void CreateDictionary(const int            pNbOfWords,
                        const String&        pAlphabet,
                        std::vector<String>& pDictionary);

  void SaveDictionar(const String&              pPath,
                     const std::vector<String>& pDictionary);
}

#endif
