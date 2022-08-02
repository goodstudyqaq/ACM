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
typedef pair< int, int > pii;

const int maxn = 1e6 + 5;
int num[maxn];
vector< int > V[maxn];
int ans[maxn];
int in[maxn];
int f[maxn];
int num_to_idx[maxn];
int nidx;

int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}

int n, m;
void init() {
	for (int i = 0; i < n; i++) {
		map< int, int > lst;
		for (int j = 0; j < m; j++) {
			int idx = i * m + j;
			if (lst.count(num[idx])) {
				int u = lst[num[idx]];
				int v = idx;
				int fu = find(u);
				int fv = find(v);
				f[fu] = fv;
			}
			lst[num[idx]] = idx;
		}
	}

	for (int j = 0; j < m; j++) {
		map< int, int > lst;
		for (int i = 0; i < n; i++) {
			int idx = i * m + j;
			if (lst.count(num[idx])) {
				int u = lst[num[idx]];
				int v = idx;
				int fu = find(u);
				int fv = find(v);
				f[fu] = fv;
			}
			lst[num[idx]] = idx;
		}
	}
}

int main() {
	freopen("data.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n * m; i++) {
		scanf("%d", &num[i]);
		f[i] = i;
	}

	init();

	for (int i = 0; i < n; i++) {
		int start = i * m;
		int end = (i + 1) * m - 1;
		vector< pii > v;
		for (int j = start; j <= end; j++) {
			v.push_back({ num[j], j });
		}
		sort(v.begin(), v.end());
		for (int j = 0; j < m - 1; j++) {
			pii p = v[j];
			pii q = v[j + 1];
			int fp = find(p.second);
			int fq = find(q.second);
			if (fp == fq) continue;
			V[fp].push_back(fq);
			in[fq]++;
		}
	}

	for (int i = 0; i < m; i++) {
		int now_num = 1;
		int now_idx = i;
		vector< pii > v;
		while (now_num <= n) {
			v.push_back({ num[now_idx], now_idx });
			now_num++;
			now_idx += m;
		}
		sort(v.begin(), v.end());
		for (int j = 0; j < n - 1; j++) {
			pii p = v[j];
			pii q = v[j + 1];
			int fp = find(p.second);
			int fq = find(q.second);
			if (fp == fq) continue;
			V[fp].push_back(fq);
			in[fq]++;
		}
	}

	queue< int > q;
	set< int > vis;
	for (int i = 0; i < n * m; i++) {
		int fi = find(i);
		if (!vis.count(fi) && !in[fi]) {
			vis.insert(fi);
			q.push(fi);
			ans[fi] = 1;
		}
	}
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (auto v : V[x]) {
			in[v]--;
			if (!in[v]) {
				q.push(v);
				ans[v] = ans[x] + 1;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int idx = i * m + j;
			printf("%d ", ans[find(idx)]);
		}
		puts("");
	}
	return 0;
}