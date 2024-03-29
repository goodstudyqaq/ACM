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

unordered_set< int > S;
void work(int val) {
	if (val == 0) return;
	for (int i = 2; 1LL * i * i <= val; i++) {
		if (val % i == 0) {
			S.insert(i);
			while (val % i == 0) val /= i;
		}
	}
	if (val != 1) {
		S.insert(val);
	}
}

const long long inf = 1e15;
int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, a, b;
	cin >> n >> a >> b;
	vector< int > v(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}

	for (int i = -1; i <= 1; i++) {
		work(v[1] + i);
		work(v[n] + i);
	}

	long long ans = 1LL * a * n;
	vector< long long > c(n + 1);
	for (auto it : S) {
		// debug(it);

		for (int i = 1; i <= n; i++) {
			if (v[i] % it == 0) {
				c[i] = 0;
			} else if ((v[i] + 1) % it == 0 || (v[i] - 1) % it == 0) {
				c[i] = b;
			} else {
				c[i] = inf;
			}
			// debug(i, c[i]);
		}

		vector< vector< long long > > f(n + 1, vector< long long >(3, 0));
		for (int i = 1; i <= n; i++) {
			f[i][0] = min(f[i - 1][0] + c[i], ans);
			f[i][1] = min(min(f[i - 1][0], f[i - 1][1]) + a, ans);
			f[i][2] = min(min(f[i - 1][1] + min(1LL * a, c[i]), f[i - 1][2] + c[i]), ans);
		}

		ans = min({ ans, f[n][0], f[n][1], f[n][2] });
	}
	cout << ans << endl;
	return 0;
}