#ifndef THREADPOOL_H_
# define THREADPOOL_H_

# include <vector>
# include "CondVar.hh"
# include "SafeFifo.hpp"
# include "Task.hpp"

class ThreadPool
{
public:
  ThreadPool(unsigned int nbThread);
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

  eStatus				_status;
  CondVar				_cvTasks;
  CondVar				_cvWait;
  int					_activeThreads;
  Mutex					_mutex;
  Mutex					_mutexWait;
  SafeFifo<ITask *>			_tasks;
  std::vector<Thread< ThreadPool > *>	_pool;
};

#endif /* !THREADPOOL_H_ */
