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

vector< long long > f;
vector< int > stk;
vector< int > a;
int scnt;

int get_idx(int val) {
	int l = 0, r = scnt - 1;
	int ans = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		if (stk[mid] <= val) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return ans;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	a.resize(n + 1);
	stk.resize(n + 1);
	f.resize(n + 1);
	for (int i = 1; i < n; i++) {
		cin >> a[i];
	}

	long long res = 1;
	f[n - 1] = 1;
	stk[scnt++] = n - 1;

	for (int i = n - 2; i >= 1; i--) {
		int idx = get_idx(a[i]);
		// 不可能等于 -1
		idx = stk[idx];

		f[i] = f[idx] + idx - i + n - a[i];
		res += f[i];

		while (scnt > 0 && a[i] >= a[stk[scnt - 1]]) scnt--;
		stk[scnt++] = i;
	}

	cout << res << endl;
	return 0;
}