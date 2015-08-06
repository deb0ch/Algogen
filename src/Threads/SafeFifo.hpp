#ifndef SAFEFIFO_H_
# define SAFEFIFO_H_

# include <list>
# include "Threads.hh"
# include "SafeFifoException.hh"

template <typename T>
class SafeFifo
{
public:
  SafeFifo(){}
  virtual ~SafeFifo() {}

  void	push(const T &value)
  {
    ScopedMutex p(&_mutex);

    _fifo.push_back(value);
  }

  size_t	size()
  {
    ScopedMutex p(&_mutex);

    return _fifo.size();
  }

  bool	tryPop(const T &value)
  {
    ScopedMutex p(&_mutex);

    if (_fifo.front() == value)
      {
	_fifo.erase(_fifo.begin());
	return true;
      }
    return false;
  }

  T &getNext(void)
  {
    ScopedMutex p(&_mutex);

    if (_fifo.empty())
      throw SafeFifoException("The fifo is empty");
    return _fifo.front();
  }

  T &getNextPop(void)
  {
    ScopedMutex p(&_mutex);
    static T	res;

    if (_fifo.empty())
      throw SafeFifoException("The fifo is empty");
    res = _fifo.front();
    _fifo.pop_front();
    return res;
  }

  bool	isEmpty(void)
  {
    ScopedMutex p(&_mutex);

    return _fifo.empty();
  }

  void	clear(void)
  {
    ScopedMutex p(&_mutex);

    while (_fifo.size())
      _fifo.pop_back();
  }

  bool	pop(void)
  {
    ScopedMutex p(&_mutex);

    if (_fifo.empty())
      return false;
    _fifo.erase(_fifo.begin());
    return true;
  }

protected:
  Mutex			_mutex;
  std::list<T>		_fifo;

private:
  SafeFifo(const SafeFifo& ref) = delete;
  SafeFifo& operator=(const SafeFifo& ref) = delete;
};

#endif /* !SAFEFIFO_H_ */
