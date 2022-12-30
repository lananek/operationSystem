#include <iostream>
#include <vector>
#include <thread>
using namespace std;

long long MatrixPower(vector <vector <int>>& Matrix1, vector <vector <int>>& Matrix2,
	int row, int column) {

	long long result = 0;
	for (int i = 0; i < Matrix1[0].size(); i++) {
		result += Matrix1[row][i] * Matrix2[i][column];
	}
	return result;

}

int main() {
	int m, n, k;
	//строки первой, столбцы первой и строки второй, столбцы второй
	cin >> m >> n >> k;
	
	vector <vector <int>> Matrix1(m, vector <int>(n));
	vector <vector <int>> Matrix2(n, vector <int>(k));

	cout << "Fill the first matrix" << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> Matrix1[i][j];
		}
	}

	cout << "Fill the second matrix" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cin >> Matrix2[i][j];
		}
	}

	vector <vector <long long>> result(m, vector <long long>(k));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			result[i][j] = 0;
		}
	}

	vector <thread> threads;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			threads.emplace_back([&result, &Matrix1, &Matrix2, i, j]() {
				result[i][j] = MatrixPower(Matrix1, Matrix2, i, j);
				});
		}
	}

	for (auto& i : threads) {
		i.join();
	}

	for (auto& i : result) {
		for (auto& j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	
	return 0;
}