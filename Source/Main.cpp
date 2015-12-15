#include "Stdafx.h"
#include "Utils.h"
#include "AcyclicGraph.h"

int main(int pArgC, char** pArgV)
{
  std::vector<String> dictionary;

  const String alphabet = __TEXT("ABCDEFGHIKLMNOPQRSTVXYZ");
  const int nbOfWords = 1000000;

  Utils::CreateDictionary(nbOfWords, alphabet, dictionary);

  AcyclicGraph graph;

  clock_t begin = clock();

  graph.Build(dictionary);

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "Seconds: " << elapsed_secs << std::endl;

  std::set<int> hashes;
  for (const auto& word : dictionary)
  {
    const int hash = graph.Hash(word);
    if (hashes.find(hash) != hashes.cend())
    {
      std::cout << "WTF?!" << std::endl;
    }
    else
    {
      hashes.emplace(hash);
    }
  }
}
