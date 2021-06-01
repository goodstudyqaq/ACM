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
typedef pair< int, int > pii;
pii line[maxn];

int n;
int d[maxn];
int r[maxn];
void cal() {
	int res = 0;
	r[0] = -2e9;

	for (int i = 1; i <= n; i++) {
		d[i] = d[i - 1];
		if (line[i].first > r[i - 1]) d[i]++;
		r[i] = max(r[i - 1], line[i].second);
	}
}
int _stack[maxn], scnt;

int get_idx(int val) {
	int l = 1, r = scnt;
	int ans = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		if (_stack[mid] > val) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return ans;
}

bool cmp(int a, int b) {
	return a > b;
}

int main() {
	freopen("data.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		scnt = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &line[i].first, &line[i].second);
		}

		sort(line + 1, line + 1 + n);
		cal();
		int ans = 0;

		for (int i = n; i >= 1; i--) {
			int idx = get_idx(r[i - 1]);
			// int idx = lower_bound(_stack + 1, _stack + 1 + scnt, r[i - 1], cmp) - _stack - 1;
			if (idx == -1) {
				ans = max(ans, d[i - 1]);
			} else {
				ans = max(ans, d[i - 1] + idx);
			}

			while (scnt >= 1 && _stack[scnt] <= line[i].second) {
				scnt--;
			}
			_stack[++scnt] = line[i].first;
		}
		cout << ans << endl;
	}
}