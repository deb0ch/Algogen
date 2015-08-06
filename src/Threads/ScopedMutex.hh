#ifndef SCOPEDMUTEX_H_
# define SCOPEDMUTEX_H_

# include "IMutex.hh"

class ScopedMutex
{
public:
  ScopedMutex(IMutex *mutex);
  ~ScopedMutex();

private:
  ScopedMutex() = delete;
  ScopedMutex(const ScopedMutex & other) = delete;
  ScopedMutex &operator=(const ScopedMutex & other) = delete;

private :
  IMutex	*_mutex;
};

#endif /* !SCOPEDMUTEX_H_ */
