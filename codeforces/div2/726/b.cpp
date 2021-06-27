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
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m, x, y;
		scanf("%d %d %d %d", &n, &m, &x, &y);

		vector< int > v1, v2;
		v1.push_back(1);
		v1.push_back(n);
		v2.push_back(1);
		v2.push_back(m);

		int res = -1;
		int chosei, chosej;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				int tmp = abs(v1[i] - x) + abs(v2[j] - y);
				if (res < tmp) {
					res = tmp;
					chosei = i;
					chosej = j;
				}
			}
		}
		printf("%d %d ", v1[chosei], v2[chosej]);
		x = v1[chosei], y = v2[chosej];
		res = 0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				int tmp = abs(v1[i] - x) + abs(v2[j] - y);
				if (res < tmp) {
					res = tmp;
					chosei = i;
					chosej = j;
				}
			}
		}

		printf("%d %d ", v1[chosei], v2[chosej]);
		puts("");
	}
	return 0;
}