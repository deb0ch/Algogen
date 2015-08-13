//
// ExecFinderException.hh
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Wed Aug 12 08:50:30 2015 deb0ch
// Last update Wed Aug 12 08:51:09 2015 deb0ch
//

#ifndef EXECFINDEREXCEPTION_H_
# define EXECFINDEREXCEPTION_H_

# include <exception>
# include <iostream>
# include <map>

# ifndef _WIN32
#  include <cerrno>
#  include <cstdio>
#  include <cstring>
# endif

class ExecFinderException : public std::exception
{
public:
  ExecFinderException(const int error);
  ExecFinderException(const std::string &error);
  ~ExecFinderException() throw() {}

public:
  ExecFinderException(const std::string &prefix, const int error);
  ExecFinderException(const std::string &prefix, const std::string &error);

  const char* what() const throw();

private:
  void addError(const int error);
  std::string		_info;
};

#endif /* !EXECFINDEREXCEPTION_H_ */
