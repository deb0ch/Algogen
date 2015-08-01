//
// Randomizer.cpp for hello_geno in src/utils
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Tue Jul 28 19:19:17 2015 deb0ch
// Last update Thu Jul 30 01:58:36 2015 deb0ch
//

#include "Randomizer.hh"

// Public

int	Randomizer::integer(int min, int max)
{
  return std::uniform_int_distribution<int>(min, max)(_seed);
}

float	Randomizer::real(float min, float max)
{
  return std::uniform_real_distribution<float>(min, max)(_seed);
}

bool	Randomizer::proba(float p)
{
  std::bernoulli_distribution distribution(p);

  return distribution(_seed);
}

Randomizer::Randomizer()
  : _seed(static_cast<unsigned int>(std::chrono::system_clock::now()
							     .time_since_epoch().count()))
{}

// Private
