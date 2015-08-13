//
// ConfigReader.hh for hello_geno in /home/chauvo_t/Programming/Perso/Tests/Algogen
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Thu Aug 13 11:58:53 2015 deb0ch
// Last update Thu Aug 13 13:29:08 2015 deb0ch
//

#ifndef CONFIGREADER_H_
# define CONFIGREADER_H_

# define CONFIG_FILE_NAME "config.cfg"

class ConfigReader
{
public:
  float		mutationRate() const	{ return _mutationRate; };
  int		mutationStep() const	{ return _mutationStep;};
  size_t	popSize() const		{ return _popSize; };
  float		selectionRatio() const	{ return _selectionRatio; };
  float		selectionChance() const	{ return _selectionChance; };
  float		diversity() const	{ return _diversity; };
  int		nbThreads() const	{ return _nbThreads; };

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
  float		_mutationRate;
  int		_mutationStep;
  size_t	_popSize;
  float		_selectionRatio;
  float		_selectionChance;
  float		_diversity;
  int		_nbThreads;
};

#endif /* !CONFIGREADER_H_ */
