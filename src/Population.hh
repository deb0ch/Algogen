//
// population.hh for hello_geno in /home/chauvo_t/Epitech/TP/Evolution_Programs_I
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Nov  6 16:03:17 2014 deb0ch
// Last update Fri Jul 31 23:28:09 2015 deb0ch
//

#ifndef POPULATION_H_
# define POPULATION_H_

# include <iostream>
# include <utility>
# include <vector>
# include "Individual.hh"

class Population
{
public:
  size_t			generation() const { return _gen; };
  size_t			size() const { return _pop.size(); };
  const Individual&		best() const;
  float				avg() const;

  void				eval();
  void				select();
  void				mate();
  void				mutate();

  void				dump() const;

public:
  Population(size_t size);
  ~Population();

private:
  Population();
  Population(const Population &);
  Population &operator=(const Population &);

public:
  std::vector<Individual*>	_pop;
  size_t			_size;
  size_t			_gen;
};

std::ostream&	operator<<(std::ostream &s, const Population& p);

#endif /* !POPULATION_H_ */
