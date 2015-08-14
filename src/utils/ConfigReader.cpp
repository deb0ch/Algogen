//
// ConfigReader.cpp for hello_geno in /home/chauvo_t/Programming/Perso/Tests/Algogen
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Aug 13 11:59:19 2015 deb0ch
// Last update Fri Aug 14 16:53:04 2015 deb0ch
//

#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>

#include "ConfigReader.hh"
#include "ExecFinder.hh"

extern std::string	g_legalChars;

// Public

ConfigReader::ConfigReader()
  : _nbThreads(std::thread::hardware_concurrency()),
    _popSize(200),
    _selectionRatio(0.4),
    _selectionChance(3.f / 4.f),
    _mutationRate(0.01),
    _mutationStep(g_legalChars.length()),
    _algorithm(0),
    _diversity(0.1f),
    _poolsCount(1)
{
  std::ifstream	file;
  std::string	line;
  int		n;

  if (access((ExecFinder()() + CONFIG_FILE_NAME).c_str(), R_OK) == -1)
    {
      std::cout << "Creating configuration file..." << std::endl;
      this->createConfigFile();
    }
  file.open(ExecFinder()() + CONFIG_FILE_NAME);
  if (file.is_open())
    {
      n = 1;
      while (std::getline(file, line))
	{
	  this->processLine(line, n);
	  ++n;
	}
    }
  file.close();
}

ConfigReader::~ConfigReader() {}

// Private

void    ConfigReader::createConfigFile() const
{
  std::ofstream         file;

  file.open(ExecFinder()() + CONFIG_FILE_NAME, std::ios::out);

  file << "nbThreads=8" << std::endl;
  file << std::endl;
  file << "popSize=200" << std::endl;
  file << std::endl;
  file << "# Proportion of survivors over newborns individuals in the next generation"
       << std::endl;
  file << "selectionRatio=0.4" << std::endl;
  file << std::endl;
  file << "# From the first to the last in the ranking, each individual" << std::endl
       << "# has in turn this probability of being selected to the next gen. With" << std::endl
       << "# that method, even the lowest ones have a chance of being selected." << std::endl;
  file << "selectionChance=0.75" << std::endl;
  file << std::endl;
  file << "mutationRate=0.01" << std::endl;
  file << std::endl;
  file << "mutationStep=52" << std::endl;
  file << std::endl;
  file << "# 0 = Rank-Space, other = Tournaments:" << std::endl;
  file << "algorithm=0" << std::endl;
  file << std::endl;
  file << "# Rank-Space algorithm specific:" << std::endl;
  file << "# How difference counts over fitness" << std::endl;
  file << "diversity=0.1" << std::endl;
  file << std::endl;
  file << "# Tournament algorithm specific:" << std::endl;
  file << "poolsCount=1" << std::endl;
  file << std::endl;
  file.close();
}

void	ConfigReader::processLine(const std::string &line, int n)
{
  std::string	token;

  if (line[0] == '#' || line == "")
    return;
  token = line.substr(0, line.find('='));
  try {
    if (token == "nbThreads")
      _nbThreads = std::stof(line.substr(line.find('=') + 1));
    else if (token == "popSize")
      _popSize = std::stof(line.substr(line.find('=') + 1));
    else if (token == "selectionRatio")
      _selectionRatio = std::stof(line.substr(line.find('=') + 1));
    else if (token == "selectionChance")
      _selectionChance = std::stof(line.substr(line.find('=') + 1));
    else if (token == "mutationRate")
      _mutationRate = std::stof(line.substr(line.find('=') + 1));
    else if (token == "mutationStep")
      _mutationStep = std::stof(line.substr(line.find('=') + 1));
    else if (token == "algorithm")
      _algorithm = std::stof(line.substr(line.find('=') + 1));
    else if (token == "diversity")
      _diversity = std::stof(line.substr(line.find('=') + 1));
    else if (token == "poolsCount")
      _poolsCount = std::stoi(line.substr(line.find('=') + 1));
    else
      std::cerr << "Error in configuration file: line "
		<< n << ": invalid token '" << token << "'"
		<< std::endl;
  } catch (std::invalid_argument e) {
    std::cerr << "Error in configuration file: line "
	      << n << ": non numeric value." << std::endl;
  } catch (std::out_of_range e) {
    std::cerr << "Error in configuration file: line "
	      << n << ": out of range value." << std::endl;
  }
}
