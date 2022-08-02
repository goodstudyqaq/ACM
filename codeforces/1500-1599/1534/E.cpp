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

void out2(int res) {
	cout << "! " << res << endl;
	fflush(stdout);
}

int out(unordered_set< int >& v) {
	cout << '?';
	for (auto it : v) {
		cout << ' ' << it;
	}
	cout << endl;
	fflush(stdout);
	int val;
	cin >> val;
	return val;
}

int main() {
	// #ifdef LOCAL
	// 	freopen("data.in", "r", stdin);
	// #endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k;
	cin >> n >> k;

	if (n == k) {
		unordered_set< int > v;
		for (int i = 1; i <= n; i++) v.insert(i);
		int res = out(v);
		out2(res);
		return 0;
	}
	vector< int > f(n + 1, -1), pre(n + 1, -1), chong(n + 1, -1);
	f[k] = 1;
	queue< int > Q;
	Q.push(k);
	while (!Q.empty()) {
		int x = Q.front();
		debug(x);
		Q.pop();
		for (int i = 0; i <= x; i++) {
			if (i > k) break;
			if (x + k - i > n) continue;
			int y = x + k - 2 * i;
			if (y <= n && y > 0 && f[y] == -1) {
				f[y] = f[x] + 1;
				pre[y] = x;
				chong[y] = i;
				Q.push(y);
			}
		}
	}

	if (f[n] == -1) {
		cout << -1 << endl;
		fflush(stdout);
		return 0;
	}
	// int now2 = n;
	// while (now2 != -1) {
	// 	debug(now2);
	// 	now2 = pre[now2];
	// }

	debug(f[n]);
	int ans = 0;
	unordered_set< int > s1;
	for (int i = 1; i <= n; i++) s1.insert(i);
	int now = n;
	while (now != -1) {
		int same = chong[now];
		int nw = k - same;
		debug(now, same);
		unordered_set< int > v;
		for (auto it : s1) {
			if (v.size() == nw) break;
			v.insert(it);
		}
		for (auto it : v) {
			s1.erase(it);
		}

		for (int i = 1; i <= n; i++) {
			if (v.size() == k) break;
			if (!s1.count(i) && !v.count(i)) {
				v.insert(i);
				s1.insert(i);
			}
		}
		int tmp = out(v);
		ans ^= tmp;
		now = pre[now];
	}
	out2(ans);
	return 0;
}