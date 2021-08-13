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

vector< int > prm;

int get_cnt(int val) {
	int res = 0;
	int sz = prm.size();
	int LIMIT = 1 << sz;
	for (int i = 0; i < LIMIT; i++) {
		bool f = 1;
		int tmp = 1;
		for (int j = 0; j < sz; j++) {
			if ((i >> j) & 1) {
				f ^= 1;
				tmp *= prm[j];
			}
		}
		if (f) {
			res += val / tmp;
		} else {
			res -= val / tmp;
		}
		// debug(i, val, res);
	}
	return res;
}

//时间复杂度O(nloglogn)
const int maxn = 1e6 + 5;
bool is[maxn];

int prm2[maxn], id;
void init() {
	memset(is, 1, sizeof(is));
	is[0] = is[1] = 0;
	int k = 0;
	prm2[k++] = 2;
	for (int i = 4; i < maxn; i += 2) is[i] = 0;
	int e = ( int )sqrt(0.0 + maxn) + 1;
	int i;
	for (i = 3; i < e; i += 2)
		if (is[i]) {
			prm2[k++] = i;
			for (int s = 2 * i, j = i * i; j < maxn; j += s)
				is[j] = 0;
		}
	for (; i < maxn; i += 2)
		if (is[i]) prm2[k++] = i;
	id = k;

	long long now = 1;
	for (int i = 0; i < id; i++) {
		now = now * prm2[i];
		if (now > 1e6) {
			debug(i, prm2[i]);
			break;
		}
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	init();
	int T;
	cin >> T;
	while (T--) {
		int x, p, k;
		cin >> x >> p >> k;
		prm.clear();
		if (p == 1) {
			cout << x + k << endl;
			continue;
		}

		for (int i = 2; 1LL * i * i <= p; i++) {
			if (p % i == 0) {
				prm.push_back(i);
				while (p % i == 0) {
					p /= i;
				}
			}
		}
		if (p != 1) {
			prm.push_back(p);
		}

		int low = get_cnt(x);

		debug(low);

		int l = x + 1, r = 2e7;
		int ans = -1;
		while (l <= r) {
			int mid = l + r >> 1;
			if (get_cnt(mid) - low >= k) {
				ans = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		cout << ans << endl;
	}
}