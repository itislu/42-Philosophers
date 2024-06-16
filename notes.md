forks = shared data (+ forks)

PTHREAD_MUTEX_INITIALIZER - mutexes get initialized at compile time.


# Cool things I do
- Synchronize starting time of threads with a sync mutex that the main thread locks before it creates the threads.
  Each thread tries to lock the mutex at the very beginning of its execution. If the mutex is already locked, the thread waits until it is unlocked.
  After the threads are created, the main thread unlocks the mutex and the threads can start.

- Load balance uneven amount of philos...
