//
// main.cpp for hello_geno in /home/chauvo_t/Epitech/TP/Evolution_Programs_I
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Nov  6 15:31:45 2014 deb0ch
// Last update Thu Oct 22 14:22:00 2015 chauvo_t
//

#include <csignal>
#include <cstdlib>
#include <err.h>
#include <iomanip>
#include <iostream>

#include "ConfigReader.hh"
#include "Population.hh"
#include "Randomizer.hh"

Randomizer	g_rand;
std::string	g_legalChars = "abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVXYZ .,?!;:'-()";
std::string	g_ref;

ConfigReader	g_config;
ThreadPool	g_threadPool(g_config.nbThreads());

int	main(int ac, char **av)
{
  int	gen = 0;

  if (ac != 2)
    errx(EXIT_FAILURE, "Invalid arguments.");
  g_ref = av[1];

  Population pop(g_config.popSize());

  pop.eval();
  std::cout << std::setprecision(9) << std::fixed;
  while (pop.best().genom() != g_ref)
    {
      pop.select();
      pop.mate();
      pop.mutate();
      pop.eval();
      std::cout << pop << std::endl;
      ++gen;
    }
  std::cout << "And the winner is: " << pop.best().genom() << std::endl;
  return (EXIT_SUCCESS);
}
