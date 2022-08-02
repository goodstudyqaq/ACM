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

typedef pair< int, int > pii;
const int maxn = 2e3 + 5;
int p[maxn], s[maxn], idx[maxn], idx2[maxn];
const int maxn2 = 2e6 + 5;
pii action[maxn2];

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	// vector< int > p(n + 1);
	// vector< int > s(n + 1);
	// vector< int > idx(n + 1);
	// vector< int > idx2(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		idx[p[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		idx2[s[i]] = i;
	}

	long long res = 0;
	// vector< pii > action(2e6 + 1);
	int acnt = 0;
	for (int i = n; i >= 1; i--) {
		int val = s[i];
		int the_idx = idx[val];
		if (the_idx == i) continue;
		int now = the_idx;
		for (int j = the_idx + 1; j <= i; j++) {
			int tmp_val = p[j];
			int tmp_idx = idx2[tmp_val];
			if (tmp_idx <= now) {
				action[acnt++] = { now, j };
				// action.push_back({ now, j });
				swap(p[now], p[j]);
				swap(idx[p[now]], idx[p[j]]);
				now = j;
			}
		}
		res += abs(the_idx - i);
	}
	cout << res << endl;
	cout << acnt << endl;
	for (int i = 0; i < acnt; i++) {
		auto it = action[i];
		cout << it.first << ' ' << it.second << endl;
	}
	return 0;
}