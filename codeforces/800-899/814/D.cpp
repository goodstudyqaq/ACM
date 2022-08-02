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

const int maxn = 1005;
struct circle {
	long long x, y, r;
};
circle c[maxn];


int n;

long long dis2(int idx1, int idx2) {
	long long x = c[idx1].x - c[idx2].x;
	long long y = c[idx1].y - c[idx2].y;
	return x * x + y * y;
}
int in[maxn];
vector<int>V[maxn];
void init() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i != j && dis2(i, j) + c[j].r * c[j].r <= c[i].r * c[i].r) {
				debug(i, j);
				V[i].push_back(j);
				in[j]++;
			}
		}
	}
}

bool vis[maxn];

double ans;
const double pi = acos(-1);

double cal(int idx) {
	return pi * c[idx].r * c[idx].r;
}

void work(int u) {
	queue<pair<int, int>>Q;
	Q.push({u, 1});
	vis[u] = 1;
	while (!Q.empty()) {
		auto it = Q.front(); Q.pop();
		vis[it.first] = 1;
		if (it.second <= 2) {
			ans += cal(it.first);
		} else if (it.second % 2) {
			ans -= cal(it.first);
		} else {
			ans += cal(it.first);
		}
		for (auto v : V[it.first]) {
			in[v]--;
			if (in[v] == 0) {
				Q.push({v, it.second + 1});
			}
		} 
	}
}


int main() {
	freopen("data.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld %lld", &c[i].x, &c[i].y, &c[i].r);
	}
	init();
	for (int i = 1; i <= n; i++) {
		if (in[i] == 0 && vis[i] == 0) {
			debug(i);
			work(i);
		}
	}
	printf("%.9f\n", ans);
	return 0;
}