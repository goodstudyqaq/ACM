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

stack< long long > num;
stack< char > op;

long long cal3(long long a, long long b, char c) {
	if (c == '*') return a * b;
	return a + b;
}

void cal2() {
	char type = op.top();
	op.pop();
	long long a = num.top();
	num.pop();
	long long b = num.top();
	num.pop();
	num.push(cal3(a, b, type));
}

long long cal(string& s) {
	while (!num.empty()) num.pop();
	while (!op.empty()) op.pop();
	debug(s);
	for (int i = 0; i < s.size(); i++) {
		char cc = s[i];
		if (cc >= '0' && cc <= '9') {
			num.push(cc - '0');
		} else if (cc == '(') {
			op.push(cc);
		} else if (cc == ')') {
			while (op.top() != '(') {
				cal2();
			}
			op.pop();
		} else {
			if (cc == '+') {
				while (!op.empty() && op.top() == '*') {
					cal2();
				}
				op.push('+');
			} else {
				op.push('*');
			}
		}
	}

	while (!op.empty()) cal2();

	return num.top();
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s;
	cin >> s;
	int n = s.size();
	vector< int > v1, v2;
	v1.push_back(0);
	v2.push_back(n);
	for (int i = 0; i < n; i++) {
		if (s[i] == '*') {
			v1.push_back(i + 1);
			v2.push_back(i);
		}
	}
	long long ans = 0;
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v2.size(); j++) {
			if (v1[i] < v2[j]) {
				string now = "";
				for (int k = 0; k < n; k++) {
					if (k == v1[i]) {
						now.push_back('(');
					}
					if (k == v2[j]) {
						now.push_back(')');
					}
					now.push_back(s[k]);
				}
				if (v2[j] == n) {
					now.push_back(')');
				}
				long long tmp = cal(now);
				debug(now, tmp);
				ans = max(ans, tmp);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
