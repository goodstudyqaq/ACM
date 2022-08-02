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

const int maxn = 1e5 + 5;

#define lowbit(x) x & -x
int sum[maxn];

void add(int idx, int val) {
	while (idx < maxn) {
		sum[idx] += val;
		idx += lowbit(idx);
	}
}

int query(int idx) {
	int res = 0;
	while (idx) {
		res += sum[idx];
		idx -= lowbit(idx);
	}
	return res;
}

int main() {
	freopen("data.in", "r", stdin);
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		add(i, 1);
	}

	int x, y;
	int L = 1, R = n;
	bool is_reverse = false;
	while (q--) {
		int opt;
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d", &x);
			int len = R - L + 1;
			if (x > len / 2) {
				is_reverse ^= 1;
				x = len - x;
			}
			if (is_reverse) {
				for (int i = R; i >= R - x + 1; i--) {
					add(R - x - (i - (R - x + 1)), query(i) - query(i - 1));
				}
				R = R - x;
			} else {
				for (int i = L; i <= L + x - 1; i++) {
					add(L + x + (L + x - 1 - i), query(i) - query(i - 1));
				}
				L = L + x;
			}
		} else {
			scanf("%d %d", &x, &y);
			x++;
			if (is_reverse) {
				int len = y - x + 1;
				printf("%d\n", query(R - x + 1) - query(R - y));

			} else {
				printf("%d\n", query(y + L - 1) - query(L + x - 2));
			}
		}
	}
	return 0;
}