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

const int mod = 1e9 + 7;

struct Node {
	int one_len, val;
};

vector< int > h;
int cal_val(int idx, Node a) {
	int res = (1LL * a.one_len + 1LL * (h[idx] - 1 - a.one_len) * a.val % mod) % mod;
	return res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	h.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> h[i];
	}

	int res = h[n] - 1;
	Node lxt;
	lxt.one_len = 0, lxt.val = 1;
	for (int i = n - 1; i >= 1; i--) {
		if (h[i] == 1) {
			lxt.one_len = lxt.val = 0;
			continue;
		}
		Node now;
		if (h[i] <= h[i + 1]) {
			// 所有的都相等
			now.one_len = 0;
			int tmp = h[i + 1] - h[i];
			if (lxt.one_len <= tmp) {
				// 没有
				now.val = (1LL * (h[i] - 1) * lxt.val % mod + 1) % mod;
			} else {
				int one_num = min(h[i] - 1, lxt.one_len - tmp);
				int other_num = h[i] - 1 - one_num;
				now.val = ((1LL * one_num + 1LL * other_num * lxt.val % mod) % mod + 1) % mod;
			}
		} else {
			// 超过部分的值为 1
			int tmp = h[i] - h[i + 1];
			now.one_len = tmp;
			int tmp_val = (1LL * lxt.one_len + 1LL * (h[i + 1] - 1 - lxt.one_len) * lxt.val % mod) % mod;
			now.val = (tmp_val + 1) % mod;
		}
		res = (res + cal_val(i, now)) % mod;
		lxt = now;
	}
	res = (res % mod + mod) % mod;
	cout << res << endl;
	return 0;
}