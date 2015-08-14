//
// population.cpp for hello_geno in /home/chauvo_t/Epitech/TP/Evolution_Programs_I
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Nov  6 16:03:03 2014 deb0ch
// Last update Fri Aug 14 20:50:35 2015 deb0ch
//

#include <algorithm>
#include <assert.h>

#include "ConfigReader.hh"
#include "Population.hh"
#include "Randomizer.hh"
#include "ThreadPool.hh"

extern ConfigReader	g_config;
extern Randomizer	g_rand;
extern ThreadPool	g_threadPool;

// Public

Population::Population(size_t size)
  : _size(size), _gen(0)
{
  for (size_t i = 0; i < size; ++i)
    {
      _pop.push_back(Individual::generate());
    }
}

Population::~Population()
{
  std::for_each(_pop.begin(), _pop.end(),
		[] (Individual* in) -> void
		{
		  delete in;
		});
}

const Individual& Population::best() const
{
  return **(std::max_element(_pop.begin(), _pop.end(),
			     [] (const Individual* a, const Individual* b) -> bool
			     {
			       return a->fitness() < b->fitness();
			     }));
}

float	Population::avg() const
{
  double sum = 0;

  for (auto it = _pop.begin(); it != _pop.end(); ++it)
    {
      sum += (*it)->fitness();
    }
  return sum / (float)_pop.size();
}

void Population::eval()
{
  std::for_each(_pop.begin(), _pop.end(),
		[ this ] (Individual* in) -> void
		{
		  g_threadPool.addTask(new Task<Individual>(in, &Individual::eval, Any()));
		});
  g_threadPool.waitTasks();
}

void Population::select()
{
  if (g_config.algorithm() == 0)
    this->selectRankSpace();
  else
    this->selectTournament();
  ++_gen;
}

void Population::mate()
{
  while (_pop.size() < _size)
    {
      _pop.push_back(_pop[g_rand.integer(0, _pop.size() - 1)]
		     ->mate(*_pop[g_rand.integer(0, _pop.size() - 1)]));
    }
}

void Population::mutate()
{
  std::for_each(_pop.begin(), _pop.end(),
		[] (Individual* in) -> void
		{
		  in->mutate();
		});
}

void	Population::dump() const
{
  std::for_each(_pop.begin(), _pop.end(),
		[] (Individual* in) -> void
		{
		  std::cout << *in;
		});
}

std::ostream&   operator<<(std::ostream &s, const Population& pop)
{
  s << "Generation: " << pop.generation() << std::endl
    << "best = " << pop.best().genom() << " (" << pop.best().fitness() << ")" << std::endl
    << "average = " << pop.avg() << std::endl
    << "size = " << pop.size() << std::endl
    << std::endl;
  return s;
}

// Private

static std::vector<Individual*>::iterator randomOrderedPick(std::vector<Individual*>& pop)
{
  for (std::vector<Individual*>::iterator it = pop.begin(); it != pop.end(); ++it)
    if (g_rand.proba(g_config.selectionChance()))
      return it;
  return pop.end() - 1;
}

// Rank-Space method:

static void	rankByFitness(std::vector<Individual*>& pop)
{
  std::sort(pop.begin(), pop.end(),
	    [] (const Individual* a, const Individual* b) -> bool
	    {
	      return a->fitness() > b->fitness();
	    });
  for (size_t i = 0; i < pop.size(); ++i)
    {
      assert(pop.at(i)->fitness() >= 0 && pop.at(i)->fitness() <= 1);
      pop.at(i)->setFitnessRank(i);
    }
}

static void	rankByDiversity(std::vector<Individual*>& pop,
				const std::vector<Individual*>& newGen)
{
  for (auto it = pop.begin(); it != pop.end(); ++it)
    {
      (*it)->setDiversity((*it)->diversity()
			  + newGen.back()->distance(**it));
    }
  std::sort(pop.begin(), pop.end(),
	    [] (const Individual* a, const Individual* b) -> bool
	    {
	      return a->diversity() > b->diversity();
	    });
  for (size_t i = 0; i < pop.size(); ++i)
    pop.at(i)->setDiversityRank(i);
}

static void	selectBest(std::vector<Individual*>& pop,
			   std::vector<Individual*>& newGen)
{
  std::vector<Individual*>::iterator	it;

  it = std::max_element(pop.begin(), pop.end(),
			[] (const Individual* a, const Individual* b) -> bool
			{
			  return a->fitness() > b->fitness();
			});
  newGen.push_back(*it);
  pop.erase(it);
}

/*
 * Rank-Space Method: "It is as good to be different as to be fit".
 * This means that not only the fitness is taken into account during
 * selection, but also the distance between the individual and the new
 * generation.
 * Here we first keep the best individual into the next gen.
 */
void	Population::selectRankSpace()
{
  std::vector<Individual*>		newGen;
  std::vector<Individual*>::iterator	it;

  selectBest(_pop, newGen);
  std::for_each(_pop.begin(), _pop.end(), [] (Individual* in) -> void { in->setDiversity(0); });
  for (size_t i = 0; i < g_config.selectionRatio() * _size - 1 ; ++i)
    {
      rankByFitness(_pop);
      rankByDiversity(_pop, newGen);
      std::sort(_pop.begin(), _pop.end(),
      		[] (const Individual* a, const Individual* b) -> bool
      		{
      		  return ((1 - g_config.diversity()) * a->fitnessRank()
			  + g_config.diversity() * a->diversityRank()
      			  < (1 - g_config.diversity()) * b->fitnessRank()
			  + g_config.diversity() * b->diversityRank());
      		});
      it = randomOrderedPick(_pop);
      newGen.push_back(*it);
      _pop.erase(it);
    }
  std::for_each(_pop.begin(), _pop.end(), [] (Individual* in) -> void { delete in; });
  _pop.clear();
  _pop = newGen;
  newGen.clear();
}

// Tournaments method:

static void	fillPools(std::vector<Individual*>& pop,
			  std::vector<std::vector<Individual*>*>& pools)
{
  auto itPools = pools.begin();

  while (!pop.empty())
    {
      std::vector<Individual*>::iterator	itPop = pop.begin();

      itPop += g_rand.integer(0, pop.size() - 1);
      (*itPools)->push_back(*itPop);
      pop.erase(itPop);
      ++itPools;
      if (itPools == pools.end())
	itPools = pools.begin();
    }
}

void selectFromPools(std::vector<std::vector<Individual*>*>& pools,
		     std::vector<Individual*>& newGen)
{
  auto itPools = pools.begin();

  while (newGen.size() < g_config.selectionRatio() * g_config.popSize())
    {
      std::vector<Individual*>::iterator	it = randomOrderedPick(**itPools);

      newGen.push_back(*it);
      (*itPools)->erase(it);
      ++itPools;
      if (itPools == pools.end())
	itPools = pools.begin();
    }
}

void Population::selectTournament()
{
  std::vector<Individual*>			newGen;
  std::vector<std::vector<Individual*>*>	pools(g_config.poolsCount());

  selectBest(_pop, newGen);
  std::for_each(pools.begin(), pools.end(),
		[] (std::vector<Individual*>*& pool)
		{
		  pool = new std::vector<Individual*>;
		});
  fillPools(_pop, pools);
  std::for_each(pools.begin(), pools.end(),
		[] (std::vector<Individual*>*& pool)
		{
		  rankByFitness(*pool);
		});
  selectFromPools(pools, newGen);
  std::for_each(pools.begin(), pools.end(),
  		[] (std::vector<Individual*>* pool) -> void
  		{
		  std::for_each(pool->begin(), pool->end(),
				[] (Individual* in) -> void
				{
				  delete in;
				});
  		  pool->clear();
		  delete pool;
  		});
  _pop.clear();
  _pop = newGen;
  newGen.clear();
}
