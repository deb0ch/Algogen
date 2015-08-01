//
// Randomizer.hh for hello_geno in src/utils
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Tue Jul 28 19:14:18 2015 deb0ch
// Last update Tue Jul 28 21:03:51 2015 deb0ch
//

#ifndef		RANDOMIZER_H_
# define	RANDOMIZER_H_

# include <random>
# include <chrono>

class Randomizer
{
public:
  int		integer(int min = (std::numeric_limits<int>::min)(),
			int max = (std::numeric_limits<int>::max)());
  float		real(float min = (std::numeric_limits<float>::min)(),
		     float max = (std::numeric_limits<float>::max)());
  bool		proba(float p);

public:
  Randomizer();
  ~Randomizer() {}

private:
  Randomizer(const Randomizer &);
  Randomizer&		operator=(const Randomizer &);

private:
  std::default_random_engine	_seed;
};

#endif /* !RANDOMIZER_H_ */
