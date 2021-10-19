#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

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

vector< int > id, hp, a;

vector< int > seq;

bool work_left(int idx) {
	bool f = true;
	for (int i = idx; i >= 1; i--) {
		if (id[i]) {
			int val = hp[i];
			bool f2 = true;
			for (int j = i + 1; j <= idx; j++) {
				val += a[j];
				if (val < 0) {
					f2 = false;
					break;
				}
			}
			if (!f2) {
				f = false;
			} else {
				f = true;
				seq.push_back(id[i]);
				for (int j = i + 1; j <= idx; j++) {
					a[j] = 0;
				}
			}
		}
	}
	return f;
}
int n, m;

bool work_right(int idx) {
	bool f = true;
	for (int i = idx; i <= n; i++) {
		if (id[i]) {
			int val = hp[i];
			bool f2 = true;
			for (int j = i - 1; j >= idx; j--) {
				val += a[j];
				if (val < 0) {
					f2 = false;
					break;
				}
			}
			if (!f2) {
				f = false;
			} else {
				f = true;
				seq.push_back(id[i]);
				for (int j = i - 1; j >= idx; j--) {
					a[j] = 0;
				}
			}
		}
	}
	return f;
}

int main() {
	freopen("data.in", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	id.resize(n + 1, 0);
	hp.resize(n + 1);
	a.resize(n + 1);
	int mi_idx = n + 1, mx_idx = 0;
	for (int i = 1; i <= m; i++) {
		int s, h;
		cin >> s >> h;
		id[s] = i;
		hp[s] = h;
		mi_idx = min(mi_idx, s);
		mx_idx = max(mx_idx, s);
	}

	vector< int > aa(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		aa[i] = a[i];
	}

	for (int i = mi_idx; i <= mx_idx; i++) {
		seq.clear();
		for (int j = 1; j <= n; j++) {
			a[j] = aa[j];
		}
		if (!work_left(i)) continue;
		if (!work_right(i + 1)) continue;

		vector< bool > done(n + 1, 0);
		for (int i = 0; i < seq.size(); i++) {
			done[seq[i]] = true;
		}
		for (int i = 1; i <= n; i++) {
			if (id[i] && !done[id[i]]) {
				seq.push_back(id[i]);
			}
		}

		cout << i << endl;
		for (auto v : seq) {
			cout << v << ' ';
		}
		cout << endl;
		return 0;
	}

	for (int i = mi_idx; i <= mx_idx; i++) {
		seq.clear();
		for (int j = 1; j <= n; j++) {
			a[j] = aa[j];
		}
		if (!work_right(i)) continue;
		if (!work_left(i - 1)) continue;
		vector< bool > done(n + 1, 0);
		for (int i = 0; i < seq.size(); i++) {
			done[seq[i]] = true;
		}
		for (int i = 1; i <= n; i++) {
			if (id[i] && !done[id[i]]) {
				seq.push_back(id[i]);
			}
		}

		cout << i << endl;
		for (auto v : seq) {
			cout << v << ' ';
		}
		cout << endl;
		return 0;
	}
	cout << -1 << endl;
	return 0;
}