//
// ThreadPool.cpp for threadpool_test
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Wed Aug  5 19:18:27 2015 deb0ch
// Last update Mon Aug 10 22:57:54 2015 deb0ch
//

#include "ThreadPool.hh"

ThreadPool::ThreadPool(unsigned int nbThread)
  : _busy(0), _running(true)
{
  _pool.reserve(nbThread);
  for (unsigned int i = 0; i < nbThread; ++i)
    _pool.emplace_back(std::bind(&ThreadPool::runThread, this));
}

ThreadPool::~ThreadPool()
{
  std::unique_lock<std::mutex> lock(_mutex);

  _running = false;
  _cvTasks.notify_all();
  lock.unlock();
  for (std::thread& thread : _pool)
    thread.join();
}

void ThreadPool::addTask(ITask* task)
{
  std::unique_lock<std::mutex> lock(_mutex);

  _tasks.push_back(task);
  _cvTasks.notify_one();
}

void ThreadPool::runThread()
{
  while (true)
    {
      std::unique_lock<std::mutex> lock(_mutex);

      _cvTasks.wait(lock,
		    [ this ] ()
		    {
		      return !_running || !_tasks.empty();
		    });
      if (!_tasks.empty())
        {
	  ++_busy;
	  auto fn = _tasks.front();
	  _tasks.pop_front();
	  lock.unlock();
	  (*fn)();
	  delete fn;
	  lock.lock();
	  --_busy;
	  _cvWait.notify_one();
        }
      else if (!_running)
	break;
    }
}

void ThreadPool::waitTasks()
{
  std::unique_lock<std::mutex> lock(_mutex);

  _cvWait.wait(lock,
	       [ this ] ()
	       {
		 return _tasks.empty() && (_busy == 0);
	       });
}
