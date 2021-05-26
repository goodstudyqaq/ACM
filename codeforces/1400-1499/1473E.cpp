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

const int maxn = 2e5 + 5;
const int maxm = 2e5 + 5;

typedef pair< int, int > pll;
vector< pll > edges[maxn];
long long d[maxn][3][3];

int main() {
	freopen("data.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	int u, v, w;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		edges[u].push_back({ v, w });
		edges[v].push_back({ u, w });
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				d[i][j][k] = 1e18;
			}
		}
	}

	d[1][0][0] = 0;
	set< pair< long long, array< int, 3 > > > q;
	q.insert({ 0, { 1, 0, 0 } });

	while (!q.empty()) {
		auto [v, mx, mn] = q.begin()->second;
		q.erase(q.begin());

		for (auto edge : edges[v]) {

			for (int i = 0; i <= 1 - mx; i++) {
				for (int j = 0; j <= 1 - mn; j++) {

					if (d[edge.first][i | mx][j | mn] > d[v][mx][mn] + 1LL * (1 - i + j) * edge.second) {
						if (q.count({ d[edge.first][i | mx][j | mn], { edge.first, i | mx, j | mn } })) {
							q.erase({ d[edge.first][i | mx][j | mn], { edge.first, i | mx, j | mn } });
						}
						d[edge.first][i | mx][j | mn] = d[v][mx][mn] + 1LL * (1 - i + j) * edge.second;
						q.insert({ d[edge.first][i | mx][j | mn], { edge.first, i | mx, j | mn } });
					}
				}
			}
		}
	}
	for (int i = 2; i <= n; i++) {
		printf("%lld ", d[i][1][1]);
	}
	puts("");
	return 0;
}