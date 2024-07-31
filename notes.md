# Bonus

- Synchronization:
  - Fork a sync-process,
  - save the pid,
  - create all philosopher processes,
  - all philosophers waitpid() for the sync-process,
  - after all processes created, main process kills the sync-process.
  Don't do the above.
  - Open sync-semaphore in main process with value 0,
  - create all philosopher processes,
  - all philosophers wait to decrement the sync-semaphore,
  - after all processes created, main process gettimeofday() and increments the sync-semaphore,
  - every philo immediately increments the sync-semaphore after it decremented it.
  Alternative:
  - fork a sync-process,
  - create all philosopher processes,
  - all philosophers waitpid() for the sync-process,
  - after all processes created, main process kills the sync-process.


- sem_unlink() can basically be called immediatly after sem_open() bc it will only be deleted when the last process closes it.

- With binary semaphores I can create my own mutexes. The subject only requires that the forks are one countable semaphore.


- Whenever a process could get stuck in a semaphore, I can create a thread before the sem_wait().


---


forks = shared data (+ forks)

PTHREAD_MUTEX_INITIALIZER - mutexes get initialized at compile time.


# Cool things I do
- Synchronize starting time of threads with a sync mutex that the main thread locks before it creates the threads.
  Each thread tries to lock the mutex at the very beginning of its execution. If the mutex is already locked, the thread waits until it is unlocked.
  After the threads are created, the main thread unlocks the mutex and the threads can start.

- Load balance uneven amount of philos...
