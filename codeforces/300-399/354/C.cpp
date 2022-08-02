#include <bits/stdc++.h>

using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
	return '"' + s + '"';
}

string to_string(const char* s) {
	return to_string(( string )s);
}

string to_string(bool b) {
	return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
	bool first = true;
	string res = "{";
	for (int i = 0; i < static_cast< int >(v.size()); i++) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(v[i]);
	}
	res += "}";
	return res;
}

template < size_t N >
string to_string(bitset< N > v) {
	string res = "";
	for (size_t i = 0; i < N; i++) {
		res += static_cast< char >('0' + v[i]);
	}
	return res;
}

template < typename A >
string to_string(A v) {
	bool first = true;
	string res = "{";
	for (const auto& x : v) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(x);
	}
	res += "}";
	return res;
}

template < typename A, typename B >
string to_string(pair< A, B > p) {
	return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
	return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
	return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
	cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
	cerr << " " << to_string(H);
	debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

int n, k;
vector< int > a;
vector< int > sum;
int mx;
bool work(int val) {
	int res = 0;
	for (int i = val; i <= mx; i += val) {
		res += sum[min(i + k, mx)] - sum[i - 1];
	}
	return res == n;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	a.resize(n + 1);
	int mi = 1e6;
	mx = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		mi = min(mi, a[i]);
		mx = max(mx, a[i]);
	}
	sum.resize(mx + 1);
	for (int i = 1; i <= mx; i++) sum[i] = 0;

	for (int i = 1; i <= n; i++) {
		sum[a[i]]++;
	}
	for (int i = 1; i <= mx; i++) {
		sum[i] += sum[i - 1];
		// debug(i, sum[i]);
	}

	if (k >= mi - 1) {
		cout << mi << endl;
		return 0;
	}

	vector< int > S;
	// for (int i = mi - k; i <= mi; i++) {
	// 	for (int j = 1; j * j <= i; j++) {
	// 		if (i % j == 0) {
	// 			S.insert(j);
	// 			S.insert(i / j);
	// 		}
	// 	}
	// }

	for (int i = 1; i <= mi; i++) {
		if (mi % i <= k) {
			S.push_back(i);
		}
	}
	sort(S.begin(), S.end());

	int ans = 0;

	for (int i = S.size() - 1; i >= 0; i--) {
		int val = S[i];
		if (work(val)) {
			cout << val << endl;
			return 0;
		}
	}
}