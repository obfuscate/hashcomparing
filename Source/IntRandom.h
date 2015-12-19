#ifndef RANDOM_HEADER
#define RANDOM_HEADER

#include "Stdafx.h"

class IntRandom
{
public:
  IntRandom(const int pMin,
            const int pMax)
  {
    mSeeds = std::array<int, std::mt19937::state_size>();
    std::random_device randomDevice;
    std::generate_n(mSeeds.data(), mSeeds.size(), std::ref(randomDevice));
    std::seed_seq seedSeq(std::begin(mSeeds), std::end(mSeeds));
    mGenerator = std::mt19937(seedSeq);

    mDistribution = std::uniform_int_distribution<int>(pMin, pMax);
  }

  int Next()
  {
    return mDistribution(mGenerator);
    /*std::array<int, std::mt19937::state_size> seeds;
    std::random_device rnd;
    std::generate_n(seeds.data(), seeds.size(), std::ref(rnd));
    std::seed_seq seq(std::begin(seeds), std::end(seeds));
    std::mt19937 gen(seq);
    
        // get random number
      std::uniform_int_distribution<int> distr(1, 7);
      return distr(gen);*/
  }

protected:
  std::array<int, std::mt19937::state_size> mSeeds;
  std::mt19937 mGenerator;
  std::uniform_int_distribution<int> mDistribution;
};

#endif
