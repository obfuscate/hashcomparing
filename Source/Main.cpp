#include "Stdafx.h"
#include "Utils.h"
#include "AcyclicGraph.h"

using namespace std;

int main(int pArgC, char** pArgV)
{
  std::vector<String> dictionary;

  const String alphabet = __TEXT("ABCDEFGHIKLMNOPQRSTVXYZ");
  const int nbOfWords = 100000;

  Utils::CreateDictionary(nbOfWords, alphabet, dictionary);

  for (const auto& word : dictionary)
  {
    //Cout << word << endl;
  }

  AcyclicGraph graph;

  clock_t begin = clock();

  graph.Build(dictionary); using namespace std;

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "Seconds: " << elapsed_secs << std::endl;
}
