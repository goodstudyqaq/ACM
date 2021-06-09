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
const int maxm = 45;
struct node {
	int nxt[3];
	bool flag;
} nodes[maxn * maxm];
int ncnt;

int newnode() {
	ncnt++;
	memset(nodes[ncnt].nxt, -1, sizeof(nodes[ncnt].nxt));
	nodes[ncnt].flag = false;
	return ncnt;
}
int rt = newnode();

void add_num(long long val) {
	int now = rt;
	vector< int > v(maxm, 0);
	int idx = 0;
	while (val) {
		v[idx] = val % 2;
		val /= 2;
		idx++;
	}
	reverse(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) {
		int go = v[i];
		if (nodes[now].nxt[go] == -1) {
			nodes[now].nxt[go] = newnode();
		}
		now = nodes[now].nxt[go];
	}
	nodes[now].flag = true;
}

long long query(long long val) {
	int now = rt;
	vector< int > v(maxm, 0);
	int idx = 0;
	long long val2 = val;
	while (val) {
		v[idx] = val % 2;
		val /= 2;
		idx++;
	}
	reverse(v.begin(), v.end());
	long long res = 0;
	for (int i = 0; i < v.size(); i++) {
		int go;
		if (nodes[now].nxt[v[i] ^ 1] != -1) {
			go = v[i] ^ 1;
		} else {
			go = v[i];
		}
		now = nodes[now].nxt[go];
		res = res * 2 + go;
	}
	return val2 ^ res;
}

long long a[maxn];
int main() {
	int n;
	scanf("%d", &n);
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%I64d", &a[i]);
		ans ^= a[i];
	}
	long long res = ans;
	long long res2 = 0;
	add_num(0);
	for (int i = n; i >= 1; i--) {
		res ^= a[i];
		res2 ^= a[i];
		add_num(res2);
		ans = max(ans, query(res));
		// cout << i << ' ' << res << ' ' << res2 << ' ' << ans << endl;
	}
	printf("%I64d\n", ans);
	return 0;
}