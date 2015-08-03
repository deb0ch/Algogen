#ifndef IMUTEX_H_
# define IMUTEX_H_

class IMutex
{
public:
  enum	STATUS
    {
      LOCKED,
      UNLOCKED
    };

  virtual void		lock() = 0;
  virtual bool		trylock() = 0;
  virtual void		unlock() = 0;
  virtual STATUS	status() const = 0;

  virtual		~IMutex() {}
};

#endif /* !IMUTEX_H_ */
