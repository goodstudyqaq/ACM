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

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector< string > mp;
	mp.resize(n + 1);
	vector< int > num(n + 1, 0);
	set< int > S;
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		mp[i] = " " + s;
		for (int j = 1; j <= n; j++) {
			if (mp[i][j] == '1') {
				num[j]++;
			}
			S.insert(i);
		}
	}

	vector< int > guess(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> guess[i];
	}

	int now = n;
	while (now > 0) {
		int chose_idx = -1;
		for (int i = 1; i <= n; i++) {
			if (num[i] == guess[i]) {
				chose_idx = i;
				break;
			}
		}
		if (chose_idx == -1) {
			break;
		}
		now--;
		S.erase(chose_idx);
		for (int i = 1; i <= n; i++) {
			if (mp[chose_idx][i] == '1') {
				num[i]--;
			}
		}
	}

	if (now > 0) {
		cout << now << '\n';
		for (auto it : S) {
			cout << it << ' ';
		}
		cout << endl;
		return 0;
	}

	for (int i = 1; i <= n; i++) {
		if (guess[i] == 0) {
			cout << -1 << endl;
			return 0;
		}
	}
	cout << 0 << endl;
	return 0;
}