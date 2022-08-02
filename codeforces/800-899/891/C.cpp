/*
给定一个带权无向图，每次询问指定若干个边，问这些边能不能全部放到MST里
*/

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

const int maxn = 5e5 + 5;
const int maxm = 1e6 + 5;
struct Edge {
	int from, to;
	int ff, ft;
	long long dist;
	int idx;
	Edge(int _f, int _t, long long _d, int _idx)
		: from(_f), to(_t), dist(_d), idx(_idx) {}
	Edge() {}
	bool operator<(const Edge& b) const {
		return dist < b.dist;
	}
} edges[maxm];
int tot;
void addedge(int u, int v, int dist, int idx) {
	edges[tot++] = Edge(u, v, dist, idx);
}
int f[maxn], e[maxn];
int find(int a) {
	return a == f[a] ? a : f[a] = find(f[a]);
}
void Union(int u, int v) {
	f[u] = v;
}
int n, m;
void kruskal() {
	for (int i = 1; i <= n; i++) {
		f[i] = i;
	}
	sort(edges, edges + tot);
	for (int i = 0; i < tot;) {
		int j = i;
		while (j < tot && edges[j].dist == edges[i].dist) {
			j++;
		}

		for (int k = i; k < j; k++) {
			edges[k].ff = find(edges[k].from);
			edges[k].ft = find(edges[k].to);
		}

		for (int k = i; k < j; k++) {
			int u = edges[k].from;
			int v = edges[k].to;
			int d = edges[k].dist;
			int fu = find(u), fv = find(v);
			if (fu != fv) {
				Union(fu, fv);
			}
		}
		i = j;
	}
}
bool cmp(Edge a, Edge b) {
	return a.idx < b.idx;
}

int main() {
	// 	freopen("data1.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int u, v, dist;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &dist);
		addedge(u, v, dist, i);
	}
	kruskal();
	for (int i = 1; i <= n; i++) {
		f[i] = i;
	}
	// for (int i = 0; i < tot; i++) {
	// 	debug(edges[i].idx, edges[i].ff, edges[i].ft);
	// }

	sort(edges, edges + tot, cmp);
	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++) {
		int k;
		scanf("%d", &k);
		vector< Edge > v;
		int idx;
		for (int j = 1; j <= k; j++) {
			scanf("%d", &idx);
			v.push_back(edges[idx - 1]);
		}
		// sort(v.begin(), v.end());

		bool flag = true;
		for (int j = 0; j < v.size() && flag;) {
			int k = j + 1;

			for (int x = j; x < k; x++) {
				int ff = v[x].ff;
				int ft = v[x].ft;
				// debug(x, ff, ft, find(ff), find(ft));
				if (find(ff) == find(ft)) {
					flag = false;
					break;
				}
				Union(find(ff), ft);
			}
			j = k;
		}
		for (int j = 0; j < v.size(); j++) {
			int ff = v[j].ff;
			int ft = v[j].ft;
			f[ff] = ff;
			f[ft] = ft;
		}
		if (flag) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
	return 0;
}