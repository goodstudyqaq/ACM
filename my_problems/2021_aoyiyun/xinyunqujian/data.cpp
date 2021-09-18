#include <bits/stdc++.h>

using namespace std;

int main() {
	srand(( unsigned int )time(NULL));
	string OUT = "data1.in";
	ofstream my_file;
	my_file.open(OUT);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout << rand() << endl;
	int n = 100000;
	// cout << n << endl;
	my_file << n << endl;
	int LIMIT = 0.4 * n;
	cout << LIMIT << endl;
	for (int i = 1; i <= n; i++) {
		int sample = 1LL * rand() * rand() % n + 1;
		// cout << sample << endl;
		if (sample < LIMIT) {
			my_file << 1 << ' ';
		} else {
			int val = 1LL * rand() * rand() % 4 + 1;
			my_file << val << ' ';
		}
	}
	my_file << endl;
	my_file.close();
	return 0;
}