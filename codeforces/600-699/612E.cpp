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

const int maxn = 1e6 + 5;
int p[maxn], idx[maxn];

bool vis[maxn];
int ans[maxn];
vector< vector< int > > V[maxn];

int main() {
	freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i]);
		idx[p[i]] = i;
	}

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			vector< int > tmp;
			int now_val = i;
			int now_idx = idx[now_val];
			vis[i] = 1;
			tmp.push_back(now_idx);
			while (true) {
				now_idx = now_val;
				now_val = p[now_idx];
				if (now_idx == idx[i]) {
					break;
				}
				vis[now_val] = 1;
				tmp.push_back(now_idx);
			}
			for (int j = 0; j < tmp.size(); j++) {
				debug(j, tmp[j]);
			}

			if (tmp.size() % 2) {
				int other_idx = tmp.size() / 2 + 1;
				for (int j = 0; j < tmp.size() / 2; j++) {
					ans[tmp[j]] = tmp[other_idx];
					ans[tmp[other_idx]] = tmp[j + 1];
					other_idx++;
				}
				ans[tmp[tmp.size() / 2]] = tmp[0];

			} else {
				if (V[tmp.size()].size()) {
					auto other = *V[tmp.size()].rbegin();
					V[tmp.size()].pop_back();

					int sz = tmp.size();
					for (int j = 0; j < sz; j++) {
						int nxt = (j + 1) % tmp.size();
						ans[tmp[j]] = other[j];
						ans[other[j]] = tmp[nxt];
					}
				} else {
					V[tmp.size()].push_back(tmp);
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (V[i].size()) {
			puts("-1");
			return 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	puts("");
}