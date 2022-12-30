#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

bool isPrime(int num) {
	if (num == 0 || num == 1) 
		return false;
	for (int i = 2; i * i <= num; i++) {
		if (num % i == 0) return false;
	}
	return true;
}

vector<int> vec;
vector<bool> boolPrime;
mutex mutex_;
int j = 0;
int i = 0;

void primeVec() {

	while (true) {
		unique_lock<mutex> guard(mutex_);
		if (j == vec.size()) return;
		j++;
		i = j;
		guard.unlock();
		if (isPrime(vec[i - 1])) {
			boolPrime[i - 1] = 1;
		}
	}
}

int main() {
	
	
	int n;
	cin >> n;
	
	vec.resize(n);
	boolPrime.resize(n);

	for (int i = 0; i < n; i++) {
		boolPrime[i] = 0;
	}
	
	for (int i = 0; i < n; i++) {
		cin >> vec[i];
	}
	
	int number_of_threads;
	cin >> number_of_threads;
	vector<thread> thr;

	for (int i = 0; i < number_of_threads; i++) {
		thr.emplace_back([]() {primeVec(); });
	}

	for (int i = 0; i < thr.size(); i++) {
		thr[i].join();
	}

	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << boolPrime[i] << " ";
	}
}
