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

map< long long, int > M;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int h, q;
	cin >> h >> q;

	if (q == 0) {
		if (h == 1) {
			cout << 1 << endl;
		} else {
			cout << "Data not sufficient!" << endl;
		}
		return 0;
	}

	long long left = 1, right = 1;
	int d = 1;
	while (d < h) {
		left = left * 2;
		right = right * 2 + 1;
		d++;
	}
	M[left] = M[right] = 0;

	for (int i = 1; i <= q; i++) {
		long long a, L, R, ans;
		cin >> a >> L >> R >> ans;
		while (a != h) {
			L = L * 2;
			R = R * 2 + 1;
			a++;
		}
		debug(L, R, ans);
		if (ans == 1) {
			M[L]++;
			M[R + 1]--;
		} else {
			M[left]++;
			M[L]--;
			M[R + 1]++;
			M[right + 1]--;
		}
	}

	long long cnt = 0, ans = -1;
	int sum = 0;
	long long pre = -1;
	// 被选中 q 次的数的个数
	for (auto it : M) {
		debug(it.first, it.second);
		if (pre != -1) {
			cnt += it.first - pre;
		}
		sum += it.second;
		if (sum == q) {
			pre = it.first;
			ans = it.first;
		} else {
			pre = -1;
		}
	}
	if (cnt == 1) {
		cout << ans << endl;
	} else if (cnt > 1) {
		cout << "Data not sufficient!" << endl;
	} else {
		cout << "Game cheated!" << endl;
	}
	return 0;
}