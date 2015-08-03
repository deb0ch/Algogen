//
// Individual.cpp for hello_geno in /home/chauvo_t/Epitech/TP/Evolution_Programs_I
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Nov  6 16:38:53 2014 deb0ch
// Last update Mon Aug  3 17:24:43 2015 deb0ch
//

#include <iomanip>
#include <string>
#include "Individual.hh"
#include "Randomizer.hh"
#include "Threads.hh"

Mutex			g_mutex;

extern Randomizer	g_rand;
extern std::string	g_ref;
extern std::string	g_legalChars;

extern float	g_mutationRate;
extern int	g_mutationStep;
extern size_t	g_popSize;
extern float	g_selectionRatio;
extern float	g_diversity;

Individual::Individual(const std::string genom)
  : _genom(genom), _fitness(0), _fitnessRank(0), _diversity(0), _diversityRank(0)
{
  _ref = g_ref.c_str();
}

Individual::~Individual() {}

void Individual::eval(Any)
{
  for (int j = 0; j < 100000; ++j)
  {
    size_t i = 0;

    _fitness = 0;
    while (i < _genom.length())
      {
	if (_ref[i] == _genom[i])
	  _fitness += 1;
	++i;
      }
    _fitness /= (float)_genom.length();
  }
}

Individual* Individual::mate(const Individual& mate) const
{
  std::string n(_genom.size(), 0);

  for (size_t i = 0; i < _genom.size(); ++i)
    {
      n[i] = g_rand.proba(1 / 2.f) ? _genom[i] : mate.genom()[i];
    }
  return new Individual(n);
}

void Individual::mutate()
{
  for (size_t i = 0; i < _genom.size(); ++i)
    {
      if (g_rand.proba(g_mutationRate))
	{
	  int g = g_legalChars.find(_genom[i]);

	  _genom[i] = g_legalChars[(g + g_rand.integer(-g_mutationStep, g_mutationStep))
				   % g_legalChars.length()];
	}
    }
}

float	Individual::distance(const Individual& ref) const
{
  size_t	i = 0;
  float		dst = 0;

  dst = 0;
  while (i < ref.genom().length() && i < _genom.length())
    {
      if (ref.genom()[i] != _genom[i])
	dst += 1;
      ++i;
    }
  return dst / (float)_genom.length();
}

Individual* Individual::generate()
{
  std::string n(g_ref.size(), 0);

  for (size_t i = 0; i < g_ref.length(); ++i)
    {
      n[i] = g_legalChars[g_rand.integer(0, g_legalChars.size() - 1)];
    }
  return new Individual(n);
}

std::ostream&   operator<<(std::ostream &s, const Individual& p)
{
  s << p.genom() << ", "
    << "fitness = " << std::setw(20) << p.fitness() << ", "
    << "fitnessRank = " << std::setw(20) << p.fitnessRank() << ", "
    << "diversity = " << std::setw(20) << p.diversity() << ", "
    << "diversityRank = " << std::setw(20) << p.diversityRank() << ", "
    << "Combined rank = " << std::setw(20) << (1 - g_diversity) * p.fitnessRank() + g_diversity * p.diversityRank() << ", "
    << std::endl;
  return s;
}
