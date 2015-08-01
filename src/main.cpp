//
// main.cpp for hello_geno in /home/chauvo_t/Epitech/TP/Evolution_Programs_I
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Nov  6 15:31:45 2014 deb0ch
// Last update Sat Aug  1 13:55:29 2015 deb0ch
//

#include <cstdlib>
#include <err.h>
#include <iomanip>
#include <iostream>
#include "Population.hh"
#include "Randomizer.hh"

Randomizer	g_rand;
std::string	g_ref;
std::string	g_legalChars = "abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVXYZ ";

float	g_mutationRate = 0.01;
int	g_mutationStep = g_legalChars.length();
size_t	g_popSize = 200;
float	g_selectionRatio = 0.4;
float	g_selectionChance = 3.f / 4.f;
float	g_diversity = 0.2f;

#include <algorithm>

int	main(int ac, char **av)
{
  int	gen = 0;

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
      // pop.dump();
      ++gen;
    }
  std::cout << "And the winner is: " << pop.best().genom() << std::endl;
  return (EXIT_SUCCESS);
}
