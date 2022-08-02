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
typedef pair< int, int > pii;

struct HeapNode {
	int u;
	long long d;
	bool operator<(const HeapNode& b) const {
		return d > b.d;
	}
};

const long long inf = 0x3f3f3f3f3f;
const long long mod1 = 1610612741;
const long long mod2 = 1222827239;
int n, m, s, t;
bool vis[maxn];
vector< pii > V1[maxn], V2[maxn];
long long d1[maxn], d2[maxn];
long long num1[maxn], num2[maxn];
long long num3[maxn], num4[maxn];
void dijkstra(int s, vector< pii >* edge, long long* d, long long* n1, long long* n2) {
	for (int i = 1; i <= n; i++) {
		vis[i] = 0;
		d[i] = inf;
		n1[i] = 0;
		n2[i] = 0;
	}
	d[s] = 0;
	// vis[s] = 1;
	n1[s] = 1;
	n2[s] = 1;
	priority_queue< HeapNode > Q;
	Q.push((HeapNode){ s, 0 });

	while (!Q.empty()) {
		HeapNode x = Q.top();
		Q.pop();
		if (vis[x.u]) continue;
		vis[x.u] = 1;

		for (auto e : edge[x.u]) {
			int v = e.first;
			long long w = e.second;
			if (d[v] > d[x.u] + w) {
				d[v] = d[x.u] + w;
				n1[v] = n1[x.u];
				n2[v] = n2[x.u];
				Q.push((HeapNode){ v, d[v] });
			} else if (d[v] == d[x.u] + w) {
				n1[v] = (n1[v] + n1[x.u]) % mod1;
				n2[v] = (n2[v] + n2[x.u]) % mod2;
			}
		}
	}
}

typedef pair< pii, int > piii;
piii edges[maxn];

int main() {
	freopen("data1.in", "r", stdin);
	scanf("%d %d %d %d", &n, &m, &s, &t);
	int u, v, w;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		V1[u].push_back({ v, w });
		V2[v].push_back({ u, w });
		edges[i] = { { u, v }, w };
	}
	dijkstra(s, V1, d1, num1, num2);
	dijkstra(t, V2, d2, num3, num4);

	for (int i = 1; i <= n; i++) {
		debug(i, d1[i], d2[i]);
	}

	long long dis = d1[t];
	long long way1 = num1[t];
	long long way2 = num2[t];

	for (int i = 1; i <= m; i++) {
		u = edges[i].first.first, v = edges[i].first.second;
		w = edges[i].second;

		if (d1[u] + d2[v] + w == dis && num1[u] * num3[v] % mod1 == way1 && num2[u] * num4[v] % mod2 == way2) {
			puts("YES");
		} else {
			long long tmp = dis - 1 - d1[u] - d2[v];
			if (tmp > 0) {
				printf("CAN %lld\n", 1LL * w - tmp);
			} else {
				puts("NO");
			}
		}
	}
	return 0;
}