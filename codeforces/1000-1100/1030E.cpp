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

const int maxn = 3e5 + 5;
long long a[maxn];
int lxt[70];
int number[maxn];

int get_num(long long val) {
	int res = 0;
	while (val) {
		if (val % 2) res++;
		val /= 2;
	}
	return res;
}
int sum[maxn];
int sum2[maxn][2];

int main() {
	freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	memset(lxt, -1, sizeof(lxt));
	long long ans = 0;
	sum2[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		int num = get_num(a[i]);
		number[i] = num;
		sum[i] = sum[i - 1] + num;
		sum2[i][0] = sum2[i - 1][0];
		sum2[i][1] = sum2[i - 1][1];
		sum2[i][sum[i] % 2]++;
		lxt[num] = i;
		int go = i;
		int now = number[go];
		while (go >= 1 && now <= 126) {
			if (now % 2 == 0) {
				int tmp = now / 2;
				bool flag = true;
				for (int j = tmp + 1; j <= 63; j++) {
					if(lxt[j] >= go) {
						flag = false;
						break;
					}
				}
				if (flag) {
					ans++;
				}
			}
			go--;
			now += number[go];
		}
		if (go - 1>= 0)
		ans += sum2[go - 1][sum[i] % 2];
	}
	cout << ans << endl;
	return 0;
}