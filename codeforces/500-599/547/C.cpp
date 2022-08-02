/*
给定一个数组，有一个集合S，最开始S为空，每次询问给定一个下标idx，
如果下标在S里，就把它删掉，如果不在，就把它加进去，每次询问返回集合S里gcd=1的点对数
*/

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
const int maxm = 5e5 + 5;
const int maxnprm = 41600;
int a[maxn];

bool is[maxm];
int prm[maxnprm], id;
void init() {
	int k = 0;
	memset(is, 1, sizeof(is));
	is[0] = is[1] = 0;
	for (int i = 2; i < maxm; i++) {
		if (is[i]) {
			prm[k] = i;
			k++;
		}
		for (int j = 0; j < k && (1LL * i * prm[j] < maxm); j++) {
			is[i * prm[j]] = 0;
			if (i % prm[j] == 0) break;
		}
	}
	id = k;
}
vector< int > V[maxn];

void getFactors(int idx) {
	int tmp = a[idx];
	for (int i = 0; prm[i] <= tmp / prm[i]; i++) {
		if (tmp % prm[i] == 0) {
			V[idx].push_back(prm[i]);
			while (tmp % prm[i] == 0) {
				tmp /= prm[i];
			}
		}
	}
	if (tmp != 1) {
		V[idx].push_back(tmp);
	}
}

bool vis[maxn];
long long ans;
long long tot[maxm];

void update(int idx, int flag) {
	int val = a[idx];
	int prm_size = V[idx].size();
	for (int i = 0; i < (1 << prm_size); i++) {
		int now = 1;
		for (int j = 0; j < prm_size; j++) {
			if ((i >> j) & 1) {
				now = now * V[idx][j];
			}
		}
		tot[now] += flag;
	}
}

long long query(int idx) {
	long long res = 0;
	int prm_size = V[idx].size();
	for (int i = 0; i < (1 << prm_size); i++) {
		int now = 1;
		int cnt = 0;
		for (int j = 0; j < prm_size; j++) {
			if ((i >> j) & 1) {
				cnt++;
				now = now * V[idx][j];
			}
		}
		if (cnt == 0) continue;
		if (cnt % 2) {
			res += tot[now];
		} else {
			res -= tot[now];
		}
	}
	return res;
}

void work(int idx) {
	if (vis[idx]) {
		//delete
		update(idx, -1);
		long long res = query(idx);

		ans = ans - (tot[1] - res);
		vis[idx] = 0;
		printf("%lld\n", ans);
	} else {
		//add
		long long res = query(idx);
		ans = ans + (tot[1] - res);
		update(idx, 1);
		vis[idx] = 1;
		printf("%lld\n", ans);
	}
}

int main() {
	// freopen("data1.in", "r", stdin);
	int n, q;
	init();	 //41538
	// cout << id << endl;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		getFactors(i);
	}

	int idx;
	while (q--) {
		scanf("%d", &idx);
		work(idx);
	}
}