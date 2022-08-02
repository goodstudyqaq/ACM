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

unordered_map< bitset< 30 >, int > sg;
unordered_map< int, bitset< 30 > > to;

void init() {
	for (int i = 1; i < 30; i++) {
		bitset< 30 > v;
		v.set();
		for (int j = i; j < 30; j += i) {
			v[j] = 0;
		}
		to[i] = v;
	}
}

// 不到 30 位
int dfs(bitset< 30 >& status) {
	if (sg.count(status)) {
		return sg[status];
	}
	if (status == 0) return 0;
	unordered_set< int > have;

	for (int i = status._Find_first(); i != status.size(); i = status._Find_next(i)) {
		auto it = to[i];
		bitset< 30 > go = status & it;
		have.insert(dfs(go));
	}

	int now = 0;
	while (have.count(now)) {
		now++;
	}
	return sg[status] = now;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	init();

	bitset< 30 > now;
	vector< int > tmp_v({ 1, 2, 1, 4, 3, 2, 1, 5, 6, 2, 1, 8, 7, 5, 9, 8, 7, 3, 4, 7, 4, 2, 1, 10, 9, 3, 6, 11, 12 });
	now.reset();
	for (int i = 1; i < 30; i++) {
		now[i] = 1;
		sg[now] = tmp_v[i - 1];
	}

	int n;
	cin >> n;

	int res = 0;
	int i;
	unordered_map< int, int > M;
	for (i = 1; 1LL * i * i <= n; i++) {
		if (i == 1) {
			res ^= 1;
		} else {
			if (M.count(i)) {
				int val = M[i];
				M[i * val] = val;
				M.erase(i);
				continue;
			}
			int now_d = 1;
			long long now_val = i;
			bitset< 30 > now_status;
			now_status.reset();
			while (now_val <= n) {
				now_status[now_d] = 1;
				now_val *= i;
				now_d++;
			}
			int tmp = dfs(now_status);
			res ^= tmp;
			M[i * i] = i;
		}
	}
	// 还没有被搞过的点
	int left_num = n - i + 1;

	for (auto it : M) {
		auto it2 = it;
		long long val = it2.first;
		while (val <= n) {
			left_num--;
			val = val * it2.second;
		}
	}

	debug(i, left_num, res);
	if (left_num % 2) {
		res ^= 1;
	}
	if (res) {
		cout << "Vasya" << endl;
	} else {
		cout << "Petya" << endl;
	}
	return 0;
}