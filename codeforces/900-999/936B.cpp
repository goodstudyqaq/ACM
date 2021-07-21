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

vector< vector< int > > V;
vector< vector< int > > vis;
vector< int > road;
bool circle;

void dfs(int u, int d) {
	if (V[u].size() == 0 && d) {
		cout << "Win" << endl;
		for (auto v : road) {
			cout << v << ' ';
		}
		cout << endl;
		exit(0);
	}
	if (vis[u][d] == 1) {
		circle = true;
		return;
	} else if (vis[u][d] == 2) {
		return;
	}
	vis[u][d] = 1;
	for (auto v : V[u]) {
		road.push_back(v);
		dfs(v, d ^ 1);
		road.pop_back();
	}
	vis[u][d] = 2;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	V.resize(n + 1);
	circle = false;
	vis.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		vis[i].resize(2);
	}
	for (int i = 1; i <= n; i++) {
		int num;
		cin >> num;
		for (int j = 1; j <= num; j++) {
			int v;
			cin >> v;
			V[i].push_back(v);
		}
	}
	int s;
	cin >> s;
	road.push_back(s);
	dfs(s, 0);
	if (circle) {
		cout << "Draw" << endl;
	} else {
		cout << "Lose" << endl;
	}
	return 0;
}
