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

const int maxn = 3e5 + 5;
const int maxm = 1e6 + 5;
int sum[maxm];

#define lowbit(x) x & -x

void add(int idx, int val) {
	while (idx < maxm) {
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

struct node {
	int l, r, idx;
	bool operator<(const node& b) const {
		if (l != b.l) {
			return l > b.l;
		}
		if (r != b.r)
			return r < b.r;
		return idx < b.idx;
	}
} nodes[maxn * 3];
int ncnt;
int ans[maxn];
int main() {
	freopen("data.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		nodes[++ncnt] = (node){ l, r, 0 };
	}
	for (int i = 1; i <= m; i++) {
		int cnt;
		scanf("%d", &cnt);
		int lxt = 0;
		int x;
		for (int j = 1; j <= cnt; j++) {
			scanf("%d", &x);
			if (lxt + 1 <= x - 1)
				nodes[++ncnt] = (node){ lxt + 1, x - 1, i };
			lxt = x;
		}
		nodes[++ncnt] = (node){ lxt + 1, int(1e6 + 2), i };
	}
	sort(nodes + 1, nodes + 1 + ncnt);
	for (int i = 1; i <= ncnt; i++) {
		debug(i, nodes[i].idx, nodes[i].l, nodes[i].r);
		if (nodes[i].idx == 0) {
			add(nodes[i].r, 1);
		} else {
			int tmp = query(nodes[i].r) - query(nodes[i].l - 1);
			debug(tmp);
			ans[nodes[i].idx] += tmp;
		}
	}

	for (int i = 1; i <= m; i++) {
		printf("%d\n", n - ans[i]);
	}
	return 0;
}