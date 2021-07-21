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

long long ans;
vector< int > a;

void erase(int idx) {
	if (a[idx] > a[idx - 1] && a[idx] > a[idx + 1]) {
		ans -= a[idx];
	} else if (a[idx] < a[idx - 1] && a[idx] < a[idx + 1]) {
		ans += a[idx];
	}
}

void add(int idx) {
	if (a[idx] > a[idx - 1] && a[idx] > a[idx + 1]) {
		ans += a[idx];
	} else if (a[idx] < a[idx - 1] && a[idx] < a[idx + 1]) {
		ans -= a[idx];
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;
	while (T--) {
		ans = 0;
		int n, q;
		cin >> n >> q;
		a.resize(n + 2);
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		a[0] = 0;
		a[n + 1] = 0;

		for (int i = 1; i <= n; i++) {
			if (a[i] > a[i - 1] && a[i] > a[i + 1]) {
				ans += a[i];
			} else if (a[i] < a[i - 1] && a[i] < a[i + 1]) {
				ans -= a[i];
			}
		}

		cout << ans << endl;

		while (q--) {
			int l, r;
			cin >> l >> r;
			unordered_set< int > S;
			for (int i = -1; i <= 1; i++) {
				int tmp = l + i;
				if (tmp >= 1 && tmp <= n) {
					S.insert(tmp);
				}
				tmp = r + i;
				if (tmp >= 1 && tmp <= n) {
					S.insert(tmp);
				}
			}
			for (auto val : S) {
				erase(val);
			}

			swap(a[l], a[r]);
			for (auto val : S) {
				add(val);
			}
			cout << ans << endl;
		}
	}
}