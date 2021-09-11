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
typedef array< int, 3 > a3;

const int mod = 998244353;
int quick(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2) res = 1LL * res * a % mod;
		b /= 2;
		a = 1LL * a * a % mod;
	}
	return res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector< a3 > mp(n * m + 1);
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int val;
			cin >> val;
			a3 it = { val, i, j };
			mp[++cnt] = it;
		}
	}
	int r, c;
	cin >> r >> c;
	sort(mp.begin() + 1, mp.begin() + 1 + cnt);
	int LIMIT = n * m;
	// sum: x^2 + y^2 sum2: 2x sum3: 2y sum4: dp
	vector< int > sum(LIMIT + 1, 0), sum2(LIMIT + 1, 0), sum3(LIMIT + 1, 0), sum4(LIMIT + 1, 0);
	for (int i = 1; i <= LIMIT;) {
		int go = i;
		while (go <= LIMIT && mp[go][0] == mp[i][0]) {
			go++;
		}
		for (int j = i; j < go; j++) {
			int tmp = (1LL * mp[j][1] * mp[j][1] % mod + 1LL * mp[j][2] * mp[j][2] % mod) % mod;
			int val = ((((sum[i - 1] - 1LL * sum2[i - 1] * mp[j][1] % mod) % mod - 1LL * sum3[i - 1] * mp[j][2] % mod) % mod + 1LL * (i - 1) * tmp % mod) % mod + sum4[i - 1]) % mod;
			val = 1LL * val * quick(i - 1, mod - 2) % mod;
			debug(j, i, val);
			if (mp[j][1] == r && mp[j][2] == c) {
				val = (val + mod) % mod;
				cout << val << endl;
				return 0;
			}
			sum4[j] = (sum4[j - 1] + val) % mod;
			sum[j] = (sum[j - 1] + tmp) % mod;
			sum2[j] = (sum2[j - 1] + 2LL * mp[j][1] % mod) % mod;
			sum3[j] = (sum3[j - 1] + 2LL * mp[j][2] % mod) % mod;
		}
		i = go;
	}
	return 0;
}