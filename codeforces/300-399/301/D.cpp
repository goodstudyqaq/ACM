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

#define lowbit(x) x & -x

const int maxn = 2e5 + 5;
int sum[maxn];
void add(int idx, int val) {
	while (idx < maxn) {
		sum[idx] += val;
		idx += lowbit(idx);
	}
}
int query(int idx) {
	int res = 0;
	while (idx) {
		res += sum[idx];
		idx -= lowbit(idx);
	}
	return res;
}

int a[maxn], b[maxn];
typedef pair< int, int > pii;
pii q[maxn];
vector< int > Q[maxn];
vector< int > V[maxn];
int ans[maxn];
int main() {
	freopen("data.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		b[a[i]] = i;
	}

	int l, r;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &l, &r);
		q[i] = { l, r };
		Q[r].push_back(i);
	}

	for (int i = 1; i <= n; i++) {
		for (auto v : V[i]) {
			add(v, 1);
		}

		for (int j = 1; a[i] * j <= n; j++) {
			int val = j * a[i];
			int idx = b[val];
			if (idx <= i) {
				add(idx, 1);
			} else {
				V[idx].push_back(i);
			}
		}

		for (int j = 0; j < Q[i].size(); j++) {
			int qidx = Q[i][j];
			int l = q[qidx].first, r = q[qidx].second;
			ans[qidx] = query(r) - query(l - 1);
		}
	}

	for (int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
