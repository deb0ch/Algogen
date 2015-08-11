//
// main.cpp for hello_geno in /home/chauvo_t/Epitech/TP/Evolution_Programs_I
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Nov  6 15:31:45 2014 deb0ch
// Last update Sun Aug  9 23:32:43 2015 deb0ch
//

#include <csignal>
#include <cstdlib>
#include <err.h>
#include <iomanip>
#include <iostream>
#include "Population.hh"
#include "Randomizer.hh"

Randomizer	g_rand;
ThreadPool	g_threadPool;
std::string	g_ref;
std::string	g_legalChars = "abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVXYZ ";

float	g_mutationRate = 0.01;
int	g_mutationStep = g_legalChars.length();
size_t	g_popSize = 200;
float	g_selectionRatio = 0.4;
float	g_selectionChance = 3.f / 4.f;
float	g_diversity = 0.1f;
int	g_nbThreads = 8;

// void	dbg_exit(int);

int	main(int ac, char **av)
{
  int	gen = 0;

  // if (signal(SIGINT, dbg_exit) == SIG_ERR)
  //   errx(EXIT_FAILURE, "signal() failed for SIGINT");
  if (ac != 2)
    errx(EXIT_FAILURE, "Invalid arguments.");
  g_ref = av[1];

  Population pop(g_popSize);

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
