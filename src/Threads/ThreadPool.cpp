
#include <vector>
#include "IThread.hpp"
#include "Mutex.hh"
#include "ThreadPool.hh"

ThreadPool::ThreadPool(unsigned int nbThread)
  : _status(RUNNING), _activeThreads(0)
{
  for (unsigned int i = 0; i < nbThread; i++)
    {
      _pool.push_back(new Thread< ThreadPool >());
      _pool[i]->start(this, &ThreadPool::runThread, Any());
    }
}

ThreadPool::~ThreadPool()
{
  while (!_tasks.isEmpty());
  _status = STOPPED;
  _cvTasks.broadcast();
  for (auto it = _pool.begin(); it != _pool.end(); ++it)
    {
      (*it)->wait();
      delete *it;
    }
}

void	ThreadPool::addTask(ITask * task)
{
  _tasks.push(task);
  _cvTasks.broadcast();
}

void	ThreadPool::waitTasks()
{
  while (!_tasks.isEmpty());
  _mutexWait.lock();
  _cvWait.wait(&_mutexWait);
  _mutexWait.unlock();
}

void	ThreadPool::runThread(Any)
{
  ITask*		task;

  while (_status == RUNNING)
    {
      if (_tasks.isEmpty())
	{
	  _mutexWait.lock();
	  if (_activeThreads == 0)
	    {
	      _cvWait.broadcast();
	    }
	  _mutexWait.unlock();
	  _mutex.lock();
	  _cvTasks.wait(&_mutex);
	  _mutex.unlock();
	}
      if (_status == RUNNING)
	{
	  try {
	    task = _tasks.getNextPop();
	    _mutexWait.lock();
	    _activeThreads++;
	    _mutexWait.unlock();
	    (*task)();
	    _mutexWait.lock();
	    _activeThreads--;
	    _mutexWait.unlock();
	  } catch (...) {
	    _mutexWait.lock();
	    _activeThreads--;
	    _mutexWait.unlock();
	    std::cerr << "Task ended due tu Exception thrown." << std::endl;
	  }
	}
    }
}
