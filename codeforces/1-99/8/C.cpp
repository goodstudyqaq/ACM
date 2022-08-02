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

const int maxn = 24;
const int maxm = 1 << maxn;
const int inf = 0x3f3f3f3f;
int dp[maxm + 5];
int pre[maxm + 5];
typedef pair< int, int > pii;
pii nodes[maxn + 5];
int work(int x1, int y1, int x2, int y2) {
	int x = x1 - x2;
	int y = y1 - y2;
	return x * x + y * y;
}
int main() {
	freopen("data.in", "r", stdin);
	int x, y;
	scanf("%d %d", &x, &y);

	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &nodes[i].first, &nodes[i].second);
	}
	memset(dp, inf, sizeof(dp));
	dp[0] = 0;
	for (int i = 0; i < (1 << n); i++)
		if (dp[i] != inf) {
			for (int j = 0; j < n; j++) {
				if (((i >> j) & 1) == 0) {
					if (dp[i + (1 << j)] > dp[i] + 2 * work(x, y, nodes[j].first, nodes[j].second)) {
						dp[i + (1 << j)] = dp[i] + 2 * work(x, y, nodes[j].first, nodes[j].second);
						pre[i + (1 << j)] = i;
					}
					for (int k = j + 1; k < n; k++) {
						if (((i >> k) & 1) == 0) {
							int tmp = dp[i] + work(x, y, nodes[j].first, nodes[j].second) + work(nodes[j].first, nodes[j].second, nodes[k].first, nodes[k].second) + work(x, y, nodes[k].first, nodes[k].second);
							if (dp[i + (1 << j) + (1 << k)] > tmp) {
								dp[i + (1 << j) + (1 << k)] = tmp;
								pre[i + (1 << j) + (1 << k)] = i;
							}
						}
					}
					break;
				}
			}
		}

	int res = dp[(1 << n) - 1];
	printf("%d\n", res);
	printf("0 ");
	int now_status = (1 << n) - 1;
	while (now_status) {
		int lxt = pre[now_status];
		int tmp = lxt ^ now_status;
		for (int i = 0; i < n; i++) {
			if ((tmp >> i) & 1) {
				printf("%d ", i + 1);
			}
		}
		printf("0 ");
		now_status = lxt;
	}
}