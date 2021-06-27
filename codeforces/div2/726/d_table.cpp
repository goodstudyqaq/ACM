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

const int maxn = 10000;
bool is[maxn];
int prm[maxn], id;
void init() {
	int k = 0;
	memset(is, 1, sizeof(is));
	is[0] = is[1] = 0;
	for (int i = 2; i < maxn; ++i) {
		if (is[i]) prm[k++] = i;
		for (int j = 0; j < k && (i * prm[j] < maxn); ++j) {
			is[i * prm[j]] = 0;
			if (i % prm[j] == 0) break;
		}
	}
	id = k;
}
long long factor[100][2];
int fatCnt;
int getFactors(long long x) {
	fatCnt = 0;
	long long tmp = x;
	for (int i = 0; prm[i] <= tmp / prm[i]; i++) {
		factor[fatCnt][1] = 0;
		if (tmp % prm[i] == 0) {
			factor[fatCnt][0] = prm[i];
			while (tmp % prm[i] == 0) {
				factor[fatCnt][1]++;
				tmp /= prm[i];
			}
			fatCnt++;
		}
	}
	if (tmp != 1) {
		factor[fatCnt][0] = tmp;
		factor[fatCnt++][1] = 1;
	}
	return fatCnt;
}

bool win[maxn];
int main() {
	for (int i = 4; i <= 2000; i++) {
		bool flag = false;
		for (int j = 2; j < i; j++) {
			if (i % j == 0) {
				int tmp = i - j;
				if (!win[tmp]) {
					flag = true;
					break;
				}
			}
		}
		win[i] = flag;
		if (win[i]) {
			cout << i << endl;
		}
	}
	return 0;
}