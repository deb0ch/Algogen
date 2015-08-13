//
// ExecFinder.hh
//
// Made by chauvo_t
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Jun 12 09:20:54 2014 chauvo_t
// Last update Wed Aug 12 08:49:04 2015 deb0ch
//

#ifndef EXECFINDER_H_
# define EXECFINDER_H_

#include <string>

class ExecFinder
{
public:
  const std::string &	operator()();

public:
  ExecFinder();
  ~ExecFinder();

private:
  ExecFinder(const ExecFinder &);
  ExecFinder &operator=(const ExecFinder &);

private:
  std::string		_path;
};

#endif /* !EXECFINDER_H_ */
