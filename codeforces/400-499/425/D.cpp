/*
平面直角坐标系上有 n 个互不相同的点，求有多少个边与坐标轴平行的正方形，其四个顶点均在这 n 个点中。
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

const int maxn = 1e5 + 5;
typedef pair< int, int > pii;
pii node[maxn];
vector< int > V[maxn];
int n;
set< pii > Snode;
int xx[maxn], xcnt;

bool find(int x, int y) {
	if (x < maxn)
		return binary_search(V[x].begin(), V[x].end(), y);
	else
		return false;
}

int main() {
	// freopen("data.in", "r", stdin);
	scanf("%d", &n);
	int x, y;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &x, &y);
		node[i] = { x, y };
		xx[++xcnt] = x;
	}

	sort(node + 1, node + 1 + n);
	for (int i = 1; i <= n; i++) {
		V[node[i].first].push_back(node[i].second);
	}
	sort(xx + 1, xx + 1 + xcnt);
	xcnt = unique(xx + 1, xx + 1 + xcnt) - xx - 1;
	debug(xcnt);
	int sz = sqrt(maxn);
	int res = 0;
	for (int i = 1; i <= xcnt; i++) {
		x = xx[i];
		if (V[x].size() <= sz) {
			// cal

			for (int j = 0; j < V[x].size(); j++) {
				for (int k = j + 1; k < V[x].size(); k++) {
					int tmp = V[x][k] - V[x][j];
					if (find(x + tmp, V[x][j]) && find(x + tmp, V[x][k]))
						res++;
				}
			}
		} else {
			for (int j = i + 1; j <= xcnt; j++) {
				int x2 = xx[j];
				if (V[x2].size() <= 1) continue;
				for (int k = 0; k < V[x2].size(); k++) {
					int tmp = x2 - x;
					if (find(x, V[x2][k]) && find(x, V[x2][k] + tmp) && find(x2, V[x2][k] + tmp))
						res++;
				}
			}
		}
	}
	cout << res << endl;
}