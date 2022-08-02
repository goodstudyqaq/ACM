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

const long long inf = 1e14 + 1;
struct Node {
	int s, t, d, w;
};

vector< Node > V;
typedef pair< int, int > pii;
vector< pii > event;
typedef pair< pii, int > piii;

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	V.resize(k + 1);
	for (int i = 1; i <= k; i++) {
		cin >> V[i].s >> V[i].t >> V[i].d >> V[i].w;
		event.push_back({ V[i].s - 1, i + k });
		event.push_back({ V[i].t, i });
	}

	sort(event.begin(), event.end(), [&](pii a, pii b) { return a.first > b.first; });
	set< piii > S;
	int now_event = 0;

	vector< vector< long long > > dp(n + 2, vector< long long >(m + 1, inf));
	for (int i = 0; i <= m; i++) {
		dp[n + 1][i] = 0;
	}

	for (int i = n; i >= 0; i--) {

		while (now_event < event.size() && event[now_event].first == i) {
			if (event[now_event].second > k) {
				int idx = event[now_event].second - k;
				S.erase({ { V[idx].w, V[idx].d }, idx });
			} else {
				int idx = event[now_event].second;
				S.insert({ { V[idx].w, V[idx].d }, idx });
			}
			now_event++;
		}
		if (S.size() == 0) {
			for (int j = 0; j <= m; j++) {
				if (j > 0) {
					dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
				}
				dp[i][j] = min(dp[i][j], dp[i + 1][j]);
			}
		} else {
			auto it = S.rbegin();
			for (int j = 0; j <= m; j++) {
				dp[i][j] = min(dp[it->first.second + 1][j] + 1LL * (it->first.first), dp[i][j]);
				if (j > 0)
					dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
			}
		}
	}
	cout << dp[0][m] << endl;
}