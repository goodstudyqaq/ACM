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
vector< int > V[maxn];
vector< int > big_idx, small_idx;

int ans1, ans2;

int b[2 * maxn], bcnt;
int n;
bool vis[2 * maxn];
bool check_big() {
	for (int i = 0; i < big_idx.size(); i++) {
		for (int j = 0; j < V[big_idx[i]].size(); j++) {
			vis[V[big_idx[i]][j]] = 1;
		}

		for (int j = 1; j <= n; j++)
			if (j != big_idx[i]) {
				int cnt = 0;
				for (int k = 0; k < V[j].size(); k++) {
					if (vis[V[j][k]]) {
						cnt++;
					}
				}
				if (cnt >= 2) {
					ans1 = big_idx[i], ans2 = j;
					if (ans1 > ans2) {
						swap(ans1, ans2);
					}
					return true;
				}
			}

		for (int j = 0; j < V[big_idx[i]].size(); j++) {
			vis[V[big_idx[i]][j]] = 0;
		}
	}
	return false;
}

vector< pair< int, int > > g[maxn * 2];
int id[maxn * 2];
bool check_small() {

	for (int i = 1; i <= bcnt; i++) {
		g[i].clear();
	}

	for (int i = 0; i < small_idx.size(); i++) {
		int idx = small_idx[i];
		for (int j = 0; j < V[idx].size(); j++) {
			for (int k = j + 1; k < V[idx].size(); k++) {
				int val1 = V[idx][j];
				int val2 = V[idx][k];
				if (val1 > val2) {
					swap(val1, val2);
				}
				g[val1].push_back({ val2, idx });
			}
		}
	}

	for (int i = 1; i <= bcnt; i++) {
		id[i] = 0;
	}
	for (int i = 1; i <= bcnt; i++) {
		if (g[i].size()) {
			for (auto v : g[i]) {
				if (id[v.first]) {
					ans1 = v.second;
					ans2 = id[v.first];
					if (ans1 > ans2) {
						swap(ans1, ans2);
						return true;
					}
				}
				id[v.first] = v.second;
			}

			for (auto v : g[i]) {
				id[v.first] = 0;
			}
		}
	}

	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);

		for (int i = 1; i <= n; i++) {
			V[i].clear();
		}
		big_idx.clear();
		small_idx.clear();
		bcnt = 0;

		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			int k, a;
			scanf("%d", &k);
			cnt += k;
			for (int j = 1; j <= k; j++) {
				scanf("%d", &a);
				V[i].push_back(a);
				b[++bcnt] = a;
			}
		}

		sort(b + 1, b + 1 + bcnt);
		bcnt = unique(b + 1, b + 1 + bcnt) - b - 1;
		debug(bcnt);

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < V[i].size(); j++) {
				int idx = lower_bound(b + 1, b + 1 + bcnt, V[i][j]) - b;
				V[i][j] = idx;
			}
		}

		int m = sqrt(cnt);

		for (int i = 1; i <= n; i++) {
			if (V[i].size() > m) {
				big_idx.push_back(i);
			} else {
				small_idx.push_back(i);
			}
		}

		for (int i = 1; i <= bcnt; i++) {
			vis[i] = 0;
		}

		if (check_big()) {
			printf("%d %d\n", ans1, ans2);
		} else if (check_small()) {
			printf("%d %d\n", ans1, ans2);
		} else {
			puts("-1");
		}
	}
	return 0;
}