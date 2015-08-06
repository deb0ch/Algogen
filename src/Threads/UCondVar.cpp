#ifdef __linux__
# include "UCondVar.hh"

CondVar::CondVar()
{
  pthread_cond_init(&_cond, NULL);
}

CondVar::~CondVar()
{
  pthread_cond_destroy(&_cond);
}

void CondVar::wait(Mutex *mutex)
{
  pthread_cond_wait(&_cond, &mutex->_mutex);
}

void CondVar::signal(void)
{
  pthread_cond_signal(&_cond);
}

void CondVar::broadcast(void)
{
  pthread_cond_broadcast(&_cond);
}

#endif /* !__linux__ */
