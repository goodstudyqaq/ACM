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
const int inf = 1e7;
char mp[maxn][maxn];

int d[5][maxn][maxn];

int n, m;
int dir[4][2] = { -1, 0, 1, 0, 0, -1, 0, 1 };
void work(int idx) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			d[idx][i][j] = inf;
		}
	}

	queue< pair< int, int > > q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (mp[i][j] - '0' == idx) {
				d[idx][i][j] = 0;
				q.push({ i, j });
			}
		}
	}

	while (!q.empty()) {
		pair< int, int > x = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int tmpx = x.first + dir[i][0];
			int tmpy = x.second + dir[i][1];
			if (tmpx >= 1 && tmpx <= n && tmpy >= 1 && tmpy <= m) {

				if (mp[tmpx][tmpy] != '#' && d[idx][tmpx][tmpy] > d[idx][x.first][x.second] + 1) {
					d[idx][tmpx][tmpy] = d[idx][x.first][x.second] + 1;
					q.push({ tmpx, tmpy });
				}
			}
		}
	}
}

int get_mi1() {
	vector< int > v;
	for (int i = 1; i <= 3; i++) {
		for (int j = i + 1; j <= 3; j++) {
			int tmpmi = inf;
			for (int x = 1; x <= n; x++) {
				for (int y = 1; y <= m; y++) {
					if (mp[x][y] - '0' == j) {
						tmpmi = min(tmpmi, d[i][x][y]);
					}
				}
			}
			debug(i, j, tmpmi);
			v.push_back(tmpmi - 1);
		}
	}
	sort(v.begin(), v.end());
	return v[0] + v[1];
}

int get_mi2() {
	int mi = inf;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (mp[i][j] == '.')
				mi = min(mi, d[1][i][j] + d[2][i][j] + d[3][i][j] - 2);
		}
	}
	return mi;
}

int main() {
	// freopen("data1.in", "r", stdin);
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		scanf("%s", mp[i] + 1);
	}

	for (int i = 1; i <= 3; i++) {
		work(i);
	}

	int mi1 = get_mi1();

	int mi2 = get_mi2();
	debug(mi1, mi2);
	int mi = min(mi1, mi2);
	if (mi + 2 >= inf) {
		puts("-1");
	} else {
		cout << mi << endl;
	}
}