#ifndef THREADPOOL_H_
# define THREADPOOL_H_

# include <atomic>
# include <thread>
# include <vector>
# include "CondVar.hh"
# include "SafeFifo.hpp"
# include "Task.hpp"

class ThreadPool
{
public:
  ThreadPool(unsigned int nbThread = std::thread::hardware_concurrency());
  ~ThreadPool();

  void			addTask(ITask * task);
  void			waitTasks();
  void			runThread(Any);

private :
  ThreadPool() = delete;
  ThreadPool(const ThreadPool& other) = delete;
  ThreadPool &operator=(const ThreadPool & other) = delete;

private:
  enum	eStatus
    {
      RUNNING,
      STOPPED
    };

  std::atomic<eStatus>			_status;
  CondVar				_cvTasks;
  CondVar				_cvWait;
  Mutex					_mutex;
  Mutex					_mutexTasks;
  SafeFifo<ITask*>			_tasks;
  std::vector<Thread<ThreadPool>*>	_pool;
  size_t				_busyThreads;
};

#endif /* !THREADPOOL_H_ */
