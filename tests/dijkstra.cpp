#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <semaphore.h>
#include <thread>

constexpr const size_t N = 5;  // number of philosophers (and forks)
enum class State
{
    THINKING = 0,  // philosopher is THINKING
    HUNGRY = 1,    // philosopher is trying to get forks
    EATING = 2,    // philosopher is EATING
};

size_t inline left(size_t i)
{
    return (i - 1 + N) % N; // N is added for the case when  i - 1 is negative
}

size_t inline right(size_t i)
{
    return (i + 1) % N;
}

State state[N];  // array to keep track of everyone's state

std::mutex critical_region_mtx;  // mutual exclusion for critical regions
std::mutex output_mtx;  // for synchronized cout (printing THINKING/HUNGRY/EATING status)

// array of POSIX semaphores, one semaphore per philosopher.
sem_t both_forks_available[N];

size_t my_rand(size_t min, size_t max)
{
    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

void test(size_t i)
{
    if (state[i] == State::HUNGRY &&
        state[left(i)] != State::EATING &&
        state[right(i)] != State::EATING)
    {
        state[i] = State::EATING;
        sem_post(&both_forks_available[i]); // forks are no longer needed for this eat session
    }
}

void think(size_t i)
{
    size_t duration = my_rand(400, 800);
    {
        std::lock_guard<std::mutex> lk(output_mtx);
        std::cout << i << " is thinking " << duration << "ms\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void take_forks(size_t i)
{
    {
        std::lock_guard<std::mutex> lk{critical_region_mtx};  // enter critical region
        state[i] = State::HUNGRY;  // record fact that philosopher i is HUNGRY
        {
            std::lock_guard<std::mutex> lk(output_mtx);
            std::cout << "\t\t" << i << " is HUNGRY\n";
        }
        test(i);                        // try to acquire 2 forks
    }                                   // exit critical region
    sem_wait(&both_forks_available[i]);  // block if forks were not acquired
}

void eat(size_t i)
{
    size_t duration = my_rand(400, 800);
    {
        std::lock_guard<std::mutex> lk(output_mtx);
        std::cout << "\t\t\t\t" << i << " is eating " << duration << "ms\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void put_forks(size_t i)
{
    std::lock_guard<std::mutex> lk{critical_region_mtx};    // enter critical region
    state[i] = State::THINKING;  // philosopher has finished EATING
    test(left(i));               // see if left neighbor can now eat
    test(right(i));              // see if right neighbor can now eat
}

void philosopher(size_t i)
{
    while (true)
    {                         // repeat forever
        think(i);             // philosopher is THINKING
        take_forks(i);        // acquire two forks or block
        eat(i);               // yum-yum, spaghetti
        put_forks(i);         // put both forks back on table
    }
}

int main() {
    std::cout << "dp_14\n";

    // Initialize the semaphores
    for (size_t i = 0; i < N; ++i) {
        sem_init(&both_forks_available[i], 0, 0);
    }

    std::thread t0([&] { philosopher(0); });
    std::thread t1([&] { philosopher(1); });
    std::thread t2([&] { philosopher(2); });
    std::thread t3([&] { philosopher(3); });
    std::thread t4([&] { philosopher(4); });

    // Join the threads
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // Destroy the semaphores
    for (size_t i = 0; i < N; ++i) {
        sem_destroy(&both_forks_available[i]);
    }
}