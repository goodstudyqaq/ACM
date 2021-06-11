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

const int maxn = 5005;
const int maxm = 10000 + 50;
struct node {
	int x1, y1, x2, y2;
	node(int _x1, int _y1, int _x2, int _y2)
		: x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
	node() {}
};

bool cmp1(node a, node b) {
	return a.x1 < b.x1;
}

vector< node > a, b;
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

int main() {
	// freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	int x1, y1, x2, y2;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		if (x1 == x2) {
			if (y1 > y2) {
				swap(y1, y2);
			}
			a.push_back(node(x1 + 5001, y1 + 5001, x2 + 5001, y2 + 5001));
		} else {
			if (x1 > x2) {
				swap(x1, x2);
			}
			b.push_back(node(x1 + 5001, y1 + 5001, x2 + 5001, y2 + 5001));
		}
	}

	sort(a.begin(), a.end(), cmp1);

	long long res = 0;
	for (int i = 0; i < a.size(); i++) {
		memset(sum, 0, sizeof(sum));
		set< pair< int, int > > S;
		for (int j = 0; j < b.size(); j++) {
			if (b[j].x1 > a[i].x1 || b[j].x2 <= a[i].x1) {
				continue;
			}
			if (b[j].y1 < a[i].y1 || b[j].y1 > a[i].y2) {
				continue;
			}
			S.insert({ b[j].x2, b[j].y1 });
			add(b[j].y1, 1);
		}

		for (int j = i + 1; j < a.size(); j++) {
			while (!S.empty()) {
				auto u = *S.begin();
				if (u.first < a[j].x1) {
					S.erase(S.begin());
					add(u.second, -1);
				} else {
					break;
				}
			}
			debug(a[j].y2, query(a[j].y2));
			int tmp = query(a[j].y2) - query(a[j].y1 - 1);
			if (tmp != 0)
				res += 1LL * tmp * (tmp - 1) / 2LL;
		}
	}
	cout << res << endl;
	return 0;
}