//
// ExecFinderException.cpp
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Wed Aug 12 08:51:12 2015 deb0ch
// Last update Wed Aug 12 08:52:44 2015 deb0ch
//

#ifdef __linux__
# define _XOPEN_SOURCE 601
#endif

#include <sstream>
#include <cstring>
#include "ExecFinderException.hh"

void ExecFinderException::addError(const int error)
{
  char buffer[512];
  std::string res;

  memset(buffer, 0, 512);
#ifdef _WIN32
  strerror_s(buffer, sizeof(buffer), error);
  this->_info += buffer;
#elif __linux__
  this->_info += strerror_r(error, buffer, sizeof(buffer));
#endif
}

/* Public Constructor */
ExecFinderException::ExecFinderException(const int error)
{
  _info = "ExecFinderException : ";
  this->addError(error);
}

ExecFinderException::ExecFinderException(const std::string &info)
{
  _info = "ExecFinderException : ";
  _info = info;
}

/* Protected Constructor */
ExecFinderException::ExecFinderException(const std::string &prefix, const int error)
{
  _info = prefix;
  this->addError(error);
}

ExecFinderException::ExecFinderException(const std::string &prefix, const std::string &error)
{
  _info = prefix;
  _info += error;
}

/* Methods */
const char*   ExecFinderException::what() const throw()
{
  return (_info.c_str());
}
