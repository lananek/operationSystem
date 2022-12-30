
#include <thread>
#include <atomic>
using namespace std;

class Spinlock {
     atomic <bool> state;
    Spinlock() : lock(false) {}
    void lock() {
   	    while (state.exchange((true)) {}
    }
    public void unlock() {
   	    state.store(false);
    }
}
