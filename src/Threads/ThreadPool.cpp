
#include "IThread.hpp"
#include "Mutex.hh"
#include "ThreadPool.hh"

ThreadPool::ThreadPool(unsigned int nbThread)
  : _status(RUNNING), _busyThreads(nbThread)
{
  for (unsigned int i = 0; i < nbThread; i++)
    {
      _pool.push_back(new Thread< ThreadPool >());
      _pool[i]->start(this, &ThreadPool::runThread, Any());
    }
}

ThreadPool::~ThreadPool()
{
  _mutex.lock();
  while (!_tasks.isEmpty())
    Thread<ThreadPool>::yield();
  _status = STOPPED;
  _cvTasks.broadcast();
  _mutex.unlock();
  for (auto it = _pool.begin(); it != _pool.end(); ++it)
    {
      (*it)->wait();
      delete *it;
    }
}

void	ThreadPool::addTask(ITask * task)
{
  _mutex.lock();
  _tasks.push(task);
  _cvTasks.broadcast();
  _mutex.unlock();
}

void	ThreadPool::waitTasks()
{
  _mutex.lock();
  while (!_tasks.isEmpty() || _busyThreads != 0)
    _cvWait.wait(&_mutex);
  _mutex.unlock();
}

void	ThreadPool::runThread(Any)
{
  ITask*		task;

  while (_status == RUNNING)
    {
      _mutex.lock();
      if (_tasks.isEmpty() && _status == RUNNING)
	{
	  _busyThreads--;
	  _cvWait.signal();
	  _cvTasks.wait(&_mutex);
	  _busyThreads++;
	}
      _mutex.unlock();
      if (_status == RUNNING)
	{
	  try {
	    _mutexTasks.lock();
	    task = _tasks.getNextPop();
	    _mutexTasks.unlock();
	  } catch (SafeFifoException e) {
	    _mutexTasks.unlock();
	    continue;
	  } catch (...) {
	    _mutexTasks.unlock();
	    throw;
	  }
	  try {
	    (*task)();
	    delete task;
	  } catch (...) {
	    std::cerr << "Threadpool: Task ended due to Exception" << std::endl;
	  }
	}
    }
}
