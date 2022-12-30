#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
using namespace std;

public class Spinlock {
    AtomicBoolean state = new AtomicBoolean(false);

    public void lock() {
   	 while (state.getAndSet(true)) {}
    }
    public void unlock() {
   	 state.set(false);
    }
}
