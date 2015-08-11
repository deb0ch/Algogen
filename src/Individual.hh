//
// Individual.hh for hello_geno in /home/chauvo_t/Epitech/TP/Evolution_Programs_I
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Nov  6 16:38:30 2014 deb0ch
// Last update Fri Aug  7 12:51:56 2015 deb0ch
//

#ifndef INDIVIDUAL_H_
# define INDIVIDUAL_H_

# include <iostream>
# include <thread>

#include "Any.hpp"

class Individual
{
public:
  const std::string	genom() const { return _genom; }

  float			fitness() const { return _fitness; }
  size_t		fitnessRank() const { return _fitnessRank; }
  float			diversity() const { return _diversity; }
  size_t		diversityRank() const { return _diversityRank; }

  void			setFitnessRank(size_t r) { _fitnessRank = r; }
  void			setDiversity(float m) { _diversity = m; }
  void			setDiversityRank(size_t r) { _diversityRank = r; }

  void			eval(Any);
  Individual*		mate(const Individual& mate) const;
  void			mutate();

  float			distance(const Individual& ref) const;

  static Individual*	generate();

public:
  Individual(const std::string genom);
  ~Individual();

private:
  Individual();
  Individual(const Individual&);
  Individual &operator=(const Individual&);

protected:
  std::string		_genom;
  std::string		_ref;
  float			_fitness;
  size_t		_fitnessRank;
  float			_diversity;
  size_t		_diversityRank;
};

std::ostream&	operator<<(std::ostream &s, const Individual& p);

#endif /* !INDIVIDUAL_H_ */
