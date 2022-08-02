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
vector< bool > leg;

void dfs(int u, int pre) {
	leg[u] = 1;
	for (auto v : V[u]) {
		if (v == pre) continue;
		if (V[v].size() <= 2) {
			dfs(v, u);
		}
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	V.resize(n + 1);
	leg.resize(n + 1, 0);
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		V[u].push_back(v);
		V[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		if (V[i].size() == 1) {
			dfs(i, -1);
		}
	}

	vector< int > num;
	num.resize(n + 1, 0);
	for (int i = 1; i <= n; i++) {

		for (auto v : V[i]) {
			if (leg[v]) {
				num[i]++;
				num[i] = min(num[i], 2);
			}
		}
		debug(i, num[i]);
	}

	for (int i = 1; i <= n; i++)
		if (!leg[i]) {
			int cnt = 0;
			for (auto v : V[i]) {
				if (!leg[v]) {
					if (V[v].size() - num[v] > 1) {
						cnt++;
					}
				}
			}
			if (cnt > 2) {
				cout << "No" << endl;
				return 0;
			}
		}
	cout << "Yes" << endl;
	return 0;
}