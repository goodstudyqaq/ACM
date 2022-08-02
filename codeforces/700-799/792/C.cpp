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
const int maxn = 1e5 + 5;
char s[maxn];
char ans[maxn];
int num[maxn];
int cnt[4];
vector< int > V[4];

int work(vector< int >& vis, bool out) {
	set< int > S;
	for (auto v : vis) {
		S.insert(v);
	}
	bool flag = true;
	int len = strlen(s);
	vector< char > ans;
	for (int i = 0; i < len; i++) {
		if (S.count(i)) continue;
		if (flag) {
			if (s[i] - '0' == 0)
				continue;
			else {
				flag = false;
				ans.push_back(s[i]);
			}
		} else {
			ans.push_back(s[i]);
		}
	}
	if (ans.size() == 0) {
		if (cnt[0]) {
			ans.push_back('0');
		}
	}

	if (out) {
		if (ans.size() == 0) {
			puts("-1");
		} else {
			for (auto it : ans) {
				printf("%c", it);
			}
			puts("");
		}
	}

	return ans.size();
}

int main() {
	freopen("data.in", "r", stdin);
	scanf("%s", s);
	int len = strlen(s);
	int res = 0;
	for (int i = 0; i < len; i++) {
		num[i] = (s[i] - '0') % 3;
		cnt[num[i]]++;
		V[num[i]].push_back(i);
		if (num[i])
			V[3].push_back(i);
		res = (res + num[i]) % 3;
	}
	if (!res) {
		printf("%s\n", s);
		return 0;
	}
	if (len == 1) {
		puts("-1");
		return 0;
	}
	debug(res);
	if (res == 1) {
		vector< int > chose_v;
		int mx_len = 0;
		if (V[2].size() >= 2) {
			int sz = V[2].size();
			int c1 = V[2][sz - 1];
			int c2 = V[2][sz - 2];
			vector< int > vis;
			vis.push_back(c1);
			vis.push_back(c2);
			int the_len = work(vis, false);
			mx_len = the_len;
			chose_v = vis;
		}
		if (V[1].size()) {
			int chose = *V[1].rbegin();
			vector< int > vis;
			vis.push_back(chose);
			int the_len = work(vis, false);
			if (mx_len < the_len) {
				mx_len = the_len;
				chose_v = vis;
			}
		}
		work(chose_v, true);

	} else {
		vector< int > chose_v;
		int mx_len = 0;
		if (V[1].size() >= 2) {
			int sz = V[1].size();
			int c1 = V[1][sz - 1];
			int c2 = V[1][sz - 2];
			vector< int > vis;
			vis.push_back(c1);
			vis.push_back(c2);
			int the_len = work(vis, false);
			mx_len = the_len;
			chose_v = vis;
		}
		if (V[2].size()) {
			int chose = *V[2].rbegin();
			vector< int > vis;
			vis.push_back(chose);
			int the_len = work(vis, false);
			if (mx_len < the_len) {
				mx_len = the_len;
				chose_v = vis;
			}
		}
		work(chose_v, true);
	}
}