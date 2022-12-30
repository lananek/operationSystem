#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>
using namespace std;

mutex mutex_;
condition_variable cv;
bool flag = false;
int nextnum = 0;

bool IsItPrime(int num) {
	for (int i = 2; i * i <= num; i++) {
		if (num % i == 0) return false;
	}
	return true;
}

void NextPrime(int num) {
	unique_lock<mutex> guard(mutex_);
	while (true) {
		if (IsItPrime(num)) break;
		num++;
	}
	nextnum = num;
	flag = true;
	guard.unlock();
	cv.notify_all();
}

void PrintNextPrime() {
	unique_lock<mutex> guard(mutex_);
	while (flag == false) {
		cv.wait(guard);
	}
	cout << nextnum;
}

int main() {
	int num;
	cin >> num;

	thread thr1(NextPrime, num);
	thread thr2(PrintNextPrime);

	thr1.join();
	thr2.join();
}