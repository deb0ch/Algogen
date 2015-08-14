//
// ConfigReader.hh for hello_geno in /home/chauvo_t/Programming/Perso/Tests/Algogen
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Aug 13 11:58:53 2015 deb0ch
// Last update Fri Aug 14 16:49:37 2015 deb0ch
//

#ifndef CONFIGREADER_H_
# define CONFIGREADER_H_

# define CONFIG_FILE_NAME "config.cfg"

class ConfigReader
{
public:
  int		nbThreads() const	{ return _nbThreads; }
  size_t	popSize() const		{ return _popSize; }
  float		selectionRatio() const	{ return _selectionRatio; }
  float		selectionChance() const	{ return _selectionChance; }
  float		mutationRate() const	{ return _mutationRate; }
  int		mutationStep() const	{ return _mutationStep; }
  int		algorithm() const	{ return _algorithm; }
  float		diversity() const	{ return _diversity; }
  int		poolsCount() const	{ return _poolsCount; }

public:
  ConfigReader();
  ~ConfigReader();

private:
  ConfigReader(const ConfigReader &);
  ConfigReader &operator=(const ConfigReader &);

private:
  void		createConfigFile() const;
  void		processLine(const std::string& line, int n);

private:
  int		_nbThreads;
  size_t	_popSize;
  float		_selectionRatio;
  float		_selectionChance;
  float		_mutationRate;
  int		_mutationStep;
  int		_algorithm;
  float		_diversity;
  int		_poolsCount;
};

#endif /* !CONFIGREADER_H_ */
