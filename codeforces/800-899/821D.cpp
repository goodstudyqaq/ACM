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

const int maxn = 1e4 + 5;
const int inf = 0x3f3f3f3f;
typedef pair< int, int > pii;
pii node[maxn];
int n, m, k;
int d[maxn];
bool vis[maxn];

struct HeapNode {
	int u, d;
	bool operator<(const HeapNode& b) const {
		return d > b.d;
	}
};

void dijkstra(int s) {
	priority_queue< HeapNode > Q;
	memset(d, inf, sizeof(d));
	d[s] = 0;
	Q.push((HeapNode){ s, 0 });
	while (!Q.empty()) {
		HeapNode x = Q.top();
		Q.pop();
		if (vis[x.u]) continue;
		vis[x.u] = 1;

		for (int i = 1; i <= k; i++) {
			int dx = abs(node[x.u].first - node[i].first);
			int dy = abs(node[x.u].second - node[i].second);
			int val;
			if (dx + dy == 1) {
				val = 0;
			} else if (dx <= 2 || dy <= 2) {
				val = 1;
			} else {
				continue;
			}
			if (d[i] > d[x.u] + val) {
				d[i] = d[x.u] + val;
				Q.push((HeapNode){ i, d[i] });
			}
		}
	}
}

int main() {
	freopen("data.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	int x, y;
	int s = -1, e = -1;
	for (int i = 1; i <= k; i++) {
		scanf("%d %d", &x, &y);
		node[i] = { x, y };
		if (x == n && y == m) {
			e = i;
		}
		if (x == 1 && y == 1) {
			s = i;
		}
	}
	if (e == -1) {
		node[k + 1] = { n + 1, m + 1 };
		k++;
		e = k;
	}
	dijkstra(s);
	if (d[e] == inf) d[e] = -1;
	cout << d[e] << endl;
}