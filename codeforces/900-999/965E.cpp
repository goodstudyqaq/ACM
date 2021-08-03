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
struct Node {
	int nxt[26];
	bool is_end;
	priority_queue< int > Q;
};
int ncnt;
Node nodes[maxn];
int rt;
long long ans;

int new_node() {
	++ncnt;
	memset(nodes[ncnt].nxt, -1, sizeof(nodes[ncnt].nxt));
	nodes[ncnt].is_end = false;
	return ncnt;
}

void dfs(int u, int dep) {
	for (int i = 0; i < 26; i++) {
		if (nodes[u].nxt[i] != -1) {
			int go = nodes[u].nxt[i];
			dfs(go, dep + 1);
			while (!nodes[go].Q.empty()) {
				int val = nodes[go].Q.top();
				nodes[go].Q.pop();
				nodes[u].Q.push(val);
			}
		}
	}

	if (!nodes[u].Q.empty() && !nodes[u].is_end && u != rt) {
		ans = ans - nodes[u].Q.top() + dep;
		nodes[u].Q.pop();
		nodes[u].Q.push(dep);
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
	rt = new_node();
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;

		int now = rt;
		for (int j = 0; j < s.size(); j++) {
			int go = s[j] - 'a';
			if (nodes[now].nxt[go] == -1) {
				nodes[now].nxt[go] = new_node();
			}
			now = nodes[now].nxt[go];
		}
		nodes[now].is_end = true;
		nodes[now].Q.push(s.size());
		ans += s.size();
	}
	debug(ans);
	dfs(rt, 0);
	cout << ans << endl;
	return 0;
}