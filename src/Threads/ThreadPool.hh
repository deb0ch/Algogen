//
// ThreadPool.hh for threadpool_test
//
// Made by deb0ch
// Login   <chauvo_t@epitech.net>
//
// Started on  Wed Aug  5 19:17:04 2015 deb0ch
// Last update Mon Aug 10 21:10:34 2015 deb0ch
//

#ifndef THREADPOOL_H_
# define THREADPOOL_H_

# include <atomic>
# include <deque>
# include <condition_variable>
# include <functional>
# include <list>
# include <mutex>
# include <thread>
# include <vector>

# include "Task.hpp"

class ThreadPool
{
public:
  ThreadPool(unsigned int n = std::thread::hardware_concurrency());
  ~ThreadPool();

  void addTask(ITask* task);
  void waitTasks();

private:
  void runThread();

private:
  std::vector<std::thread>		_pool;
  std::list<ITask*>			_tasks;
  std::mutex				_mutex;
  std::condition_variable		_cvTasks;
  std::condition_variable		_cvWait;
  std::atomic<int>			_busy;
  bool					_running;
};

#endif /* !THREADPOOL_H_ */
