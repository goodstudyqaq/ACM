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

map< int, bool > M;
int n, m, k;
bool dfs(int val) {
	if (M.count(val)) {
		return M[val];
	}
	if (val == 1) {
		return false;
	}
	bool flag = true;
	for (int i = 1; 1LL * i * i <= val; i++) {
		if (val % i == 0) {
			if (i >= k) {
				flag &= dfs(i);
				if (flag == 0) {
					break;
				}
			}
			if (i != 1 && val / i != i && val / i >= k) {
				flag &= dfs(val / i);
				if (flag == 0) {
					break;
				}
			}
		}
	}
	if (flag) {
		debug(val, 0);
		return M[val] = 0;
	} else {
		debug(val, 1);
		return M[val] = 1;
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> k;
	if (n % 2 == 0) {
		puts("Marsel");
		return 0;
	}

	if (m % 2 == 0) {
		if (m / 2 < k) {
			puts("Marsel");
			return 0;
		} else {
			puts("Timur");
			return 0;
		}
	}

	if (dfs(m)) {
		puts("Timur");
	} else {
		puts("Marsel");
	}
	debug(M[m]);
	return 0;
}