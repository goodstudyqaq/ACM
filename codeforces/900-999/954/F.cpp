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

struct Event {
	long long x;
	int val;

	bool operator<(const Event& e) const {
		return x < e.x;
	}
};
vector< Event > V;

const int mod = 1e9 + 7;

struct Node {
	long long Map[3][3], n;

	void out() {
		debug("begin");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << Map[i][j] << ' ';
			}
			cout << endl;
		}
		debug("end");
	}
};

Node mul(Node a, Node b) {
	Node c;
	c.n = a.n;
	int i, j, k;
	for (i = 0; i < a.n; i++) {
		for (j = 0; j < a.n; j++) {
			c.Map[i][j] = 0;
			for (k = 0; k < a.n; k++) {
				c.Map[i][j] = (c.Map[i][j] + a.Map[i][k] * b.Map[k][j] % mod) % mod;
			}
		}
	}
	return c;
}

Node pow(Node p, long long k) {
	Node temp;
	int i, j;
	temp.n = p.n;
	memset(temp.Map, 0, sizeof(temp.Map));
	for (i = 0; i < p.n; i++) {
		temp.Map[i][i] = 1;
	}
	while (k) {
		if (k & 1)
			temp = mul(temp, p);
		p = mul(p, p);
		k >>= 1;
	}
	return temp;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	long long m;
	cin >> n >> m;

	int a;
	long long l, r;
	for (int i = 1; i <= n; i++) {
		cin >> a >> l >> r;
		V.push_back((Event){ l, -a });
		V.push_back((Event){ r + 1, a });
	}
	sort(V.begin(), V.end());

	Node now_matrics, now, other_matrics;
	now_matrics.n = 3;
	other_matrics.n = 3;
	now.n = 3;
	memset(other_matrics.Map, 0, sizeof(other_matrics.Map));
	other_matrics.Map[0][2] = other_matrics.Map[2][0] = -2 * n;
	memset(now_matrics.Map, 0, sizeof(now_matrics.Map));
	memset(now.Map, 0, sizeof(now.Map));
	now_matrics.Map[0][0] = now_matrics.Map[0][1] = now_matrics.Map[1][0] = now_matrics.Map[1][1] = now_matrics.Map[1][2] = now_matrics.Map[2][1] = now_matrics.Map[2][2] = 1;
	now.Map[0][0] = now.Map[1][1] = now.Map[2][2] = 1;
	long long now_idx = 1;
	for (int i = 0; i < V.size(); i++) {
		long long the_idx = V[i].x;
		long long times = the_idx - now_idx - 1;
		if (times > 0) {
			Node tmp = pow(now_matrics, times);
			now = mul(tmp, now);
			now_idx = the_idx - 1;
		}
		int val = V[i].val;
		if (val > 0) {
			for (int i = 0; i < 3; i++) {
				other_matrics.Map[val - 1][i]++;
				// if (i != val - 1)
				// 	other_matrics.Map[i][val - 1]++;
			}
			for (int i = 0; i < 3; i++) {
				if (other_matrics.Map[val - 1][i] == 0) {
					now_matrics.Map[val - 1][i] = 1;
				}
				// if (other_matrics.Map[i][val - 1] == 0) {
				// 	now_matrics.Map[i][val - 1] = 1;
				// }
			}
		} else {
			val = abs(val);
			for (int i = 0; i < 3; i++) {
				other_matrics.Map[val - 1][i]--;
				// if (i != val - 1)
				// 	other_matrics.Map[i][val - 1]--;
			}
			for (int i = 0; i < 3; i++) {
				if (other_matrics.Map[val - 1][i] == -1) {
					now_matrics.Map[val - 1][i] = 0;
				}
				// if (other_matrics.Map[i][val - 1] == -1) {
				// 	now_matrics.Map[i][val - 1] = 0;
				// }
			}
		}
	}
	// now_matrics.out();
	// now.out();
	long long times = m - now_idx;

	Node tmp = pow(now_matrics, times);
	// tmp.out();

	now = mul(tmp, now);
	// now.out();
	long long res = now.Map[1][1];
	cout << res << endl;
	return 0;
}