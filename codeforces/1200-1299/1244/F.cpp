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

char get_c(char s) {
	if (s == 'B') return 'W';
	return 'B';
}

string s;
bool check() {
	char lst = s[s.size() - 1];
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == lst) return false;
		lst = s[i];
	}
	return true;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	cin >> n >> k;
	cin >> s;

	if (check()) {
		// 没有连在一起的
		if (k % 2 == 0) {
			cout << s << endl;
		} else {
			for (int i = 0; i < n; i++) {
				cout << get_c(s[i]);
			}
			cout << endl;
		}
		return 0;
	}

	vector< int > left, right;
	left.resize(n);
	right.resize(n);
	int now = 0;
	while (s[now] != s[(now + n - 1) % n]) {
		now = (now + n - 1) % n;
	}
	left[0] = now;
	for (int i = 1; i < n; i++) {
		if (s[i] == s[i - 1]) {
			left[i] = i;
		} else {
			left[i] = left[i - 1];
		}
	}

	now = n - 1;
	while (s[now] != s[(now + 1) % n]) {
		now = (now + 1) % n;
	}
	right[n - 1] = now;
	for (int i = n - 2; i >= 0; i--) {
		if (s[i] == s[i + 1]) {
			right[i] = i;
		} else {
			right[i] = right[i + 1];
		}
	}

	for (int i = 0; i < n; i++) {
		int l_num = (i - left[i] + n) % n;
		int r_num = (right[i] - i + n) % n;
		int mi = min(l_num, r_num);
		if (mi == 0) {
			cout << s[i];
		} else {
			if (k < mi) {
				if (k % 2) {
					cout << get_c(s[i]);
				} else {
					cout << s[i];
				}
			} else {
				if (l_num == mi) {
					cout << s[left[i]];
				} else {
					cout << s[right[i]];
				}
			}
		}
	}
	cout << endl;
	return 0;
}