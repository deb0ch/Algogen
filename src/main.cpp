//
// main.cpp for hello_geno in /home/chauvo_t/Epitech/TP/Evolution_Programs_I
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Nov  6 15:31:45 2014 deb0ch
// Last update Sat Oct 24 15:27:28 2015 chauvo_t
//

#include <csignal>
#include <cstdlib>
#include <err.h>
#include <iomanip>
#include <iostream>

#include "gnuplot-iostream.h"

#include "ConfigReader.hh"
#include "Population.hh"
#include "Randomizer.hh"

Randomizer	g_rand;
std::string	g_legalChars = "abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVXYZ .,?!;:'-()";
std::string	g_ref;

ConfigReader	g_config;
ThreadPool	g_threadPool(g_config.nbThreads());

void	plot_stats(Gnuplot & gp, int gen, double bestFit, double average)
{
  static double xmin = gen;
  static double xmax = gen;
  static double ymin = bestFit;
  static double ymax = bestFit;
  static std::vector<boost::tuple<double, double> > gpBest;
  static std::vector<boost::tuple<double, double> > gpAverage;

  if (gen <= xmin)
    xmin = gen;
  if (gen >= xmax)
    xmax = gen;
  if (bestFit <= ymin)
    ymin = bestFit;
  if (bestFit >= ymax)
    ymax = bestFit;

  gpBest.push_back(boost::make_tuple(gen, bestFit));
  gpAverage.push_back(boost::make_tuple(gen, average));

  gp << "set xrange [" << xmin << ":" << xmax << "]\n "
     << "set yrange [" << ymin << ":" << ymax << "]\n";
  gp << "plot '-' with lines title 'best', '-' with lines title 'average'\n";
  gp.send1d(gpBest);
  gp.send1d(gpAverage);
}

int	main(int ac, char **av)
{
  int	gen = 0;

  if (ac != 2)
    errx(EXIT_FAILURE, "Invalid arguments.");
  g_ref = av[1];

  Gnuplot gp;
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
      plot_stats(gp, gen, pop.best().fitness(), pop.avg());
      ++gen;
    }
  std::cout << "And the winner is: " << pop.best().genom() << std::endl;
  return (EXIT_SUCCESS);
}
