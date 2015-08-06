
#include "ScopedMutex.hh"

ScopedMutex::ScopedMutex(IMutex *mutex)
  : _mutex(mutex)
{
  _mutex->lock();
}

ScopedMutex::~ScopedMutex()
{
  _mutex->unlock();
}
