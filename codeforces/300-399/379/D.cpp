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

struct node {
	int beg, ed;
	int a, b;
	int num[16];
	node(int _beg, int _ed, int _a, int _b) {
		beg = _beg;
		ed = _ed;
		a = _a;
		b = _b;
		memset(num, 0, sizeof(num));
	}
	node() {}
};
const int inf = 1e9 + 1;
node merge(node& x, node& y) {
	int now_beg = x.beg, now_ed = y.ed;
	int now_a = min(x.a + y.a, inf), now_b = min(x.b + y.b, inf);
	node now = node(now_beg, now_ed, now_a, now_b);
	for (int i = 0; i < 16; i++) {
		now.num[i] = min(x.num[i] + y.num[i], inf);
	}
	int tmp = x.ed * 4 + y.beg;
	now.num[tmp] = min(now.num[tmp] + 1, inf);
	return now;
}

node init(int k) {
	vector< node > nodes(k);
	nodes[0] = node(0, 1, 1, 0);
	nodes[1] = node(2, 3, 0, 1);

	for (int i = 2; i < k; i++) {
		node tmp1 = nodes[i - 2];
		node tmp2 = nodes[i - 1];
		nodes[i] = merge(tmp1, tmp2);
	}
	return nodes[k - 1];
}
int k, x, n, m;

bool check(node& tmp, int num1, int num2, char a1, char a2, char b1, char b2) {
	long long val = 1LL * num1 * tmp.a + 1LL * num2 * tmp.b;

	if (a2 == 'A' && b1 == 'C') {
		val = val + tmp.num[6];
	}
	if (b2 == 'A' && a1 == 'C') {
		val = val + tmp.num[12];
	}
	if (b2 == 'A' && b1 == 'C') {
		val = val + tmp.num[14];
	}
	if (val != x) {
		return false;
	}

	if (n == 1 && a1 != a2) return false;
	if (m == 1 && b1 != b2) return false;
	if (n % 2 == 0) {
		if (num1 == n / 2) {
			if (a1 != 'A' || a2 != 'C') return false;
		}
	} else {
		if (num1 == n / 2) {
			if (a1 != 'A' && a2 != 'C' && num1) return false;
		}
	}

	if (m % 2 == 0) {
		if (num2 == m / 2) {
			if (b1 != 'A' || b2 != 'C') return false;
		}
	} else {
		if (num2 == m / 2) {
			if (b1 != 'A' && b2 != 'C' && num2) return false;
		}
	}
	return true;
}

string build(int num, int len, char a1, char a2) {
	string res = string(len, ' ');
	res[0] = a1;
	res[len - 1] = a2;
	if (len == 1) return res;
	int now = 1;
	if (a1 == 'A' && num > 0) {
		res[now++] = 'C';
		num--;
	}
	while (now < len - 1) {
		if (num) {
			res[now++] = 'A';
			res[now++] = 'C';
			num--;
		} else {
			res[now++] = 'B';
		}
	}
	return res;
}

void out(int num1, int num2, char a1, char a2, char b1, char b2) {
	// cout << num1 << ' ' << num2 << ' ' << a1 << ' ' << a2 << ' ' << b1 << ' ' << b2 << endl;

	string s1 = build(num1, n, a1, a2);
	string s2 = build(num2, m, b1, b2);
	cout << s1 << endl
		 << s2 << endl;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> k >> x >> n >> m;
	node now = init(k);
	// debug(now.beg, now.ed, now.a, now.b);
	// for (int i = 0; i < 16; i++) {
	// 	debug(i, now.num[i]);
	// }

	for (int i = 0; i <= n / 2; i++) {
		for (int j = 0; j <= m / 2; j++) {
			for (char a1 = 'A'; a1 <= 'C'; a1++) {
				for (char a2 = 'A'; a2 <= 'C'; a2++) {
					for (char b1 = 'A'; b1 <= 'C'; b1++) {
						for (char b2 = 'A'; b2 <= 'C'; b2++) {
							if (check(now, i, j, a1, a2, b1, b2)) {
								out(i, j, a1, a2, b1, b2);
								return 0;
							}
						}
					}
				}
			}
		}
	}
	cout << "Happy new year!" << endl;
	return 0;
}