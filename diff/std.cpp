#line 1 "test/verify/yosupo-segment-add-get-min.test.cpp"
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/segment_add_get_min

#line 1 "template/template.hpp"
#include <bits/stdc++.h>
#if __has_include(<atcoder/all>)
#include <atcoder/all>
#endif

using namespace std;

using int64 = long long;

const int64 infll = (1LL << 62) - 1;
const int inf = (1 << 30) - 1;

struct IoSetup {
  IoSetup() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cerr << fixed << setprecision(10);
  }
} iosetup;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
  os << p.first << " " << p.second;
  return os;
}

template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &p) {
  is >> p.first >> p.second;
  return is;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i] << (i + 1 != v.size() ? " " : "");
  }
  return os;
}

template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
  for (T &in : v) is >> in;
  return is;
}

template <typename T1, typename T2>
inline bool chmax(T1 &a, T2 b) {
  return a < b && (a = b, true);
}

template <typename T1, typename T2>
inline bool chmin(T1 &a, T2 b) {
  return a > b && (a = b, true);
}

template <typename T = int64>
vector<T> make_v(size_t a) {
  return vector<T>(a);
}

template <typename T, typename... Ts>
auto make_v(size_t a, Ts... ts) {
  return vector<decltype(make_v<T>(ts...))>(a, make_v<T>(ts...));
}

template <typename T, typename V>
typename enable_if<is_class<T>::value == 0>::type fill_v(T &t, const V &v) {
  t = v;
}

template <typename T, typename V>
typename enable_if<is_class<T>::value != 0>::type fill_v(T &t, const V &v) {
  for (auto &e : t) fill_v(e, v);
}

template <typename F>
struct FixPoint : F {
  explicit FixPoint(F &&f) : F(std::forward<F>(f)) {}

  template <typename... Args>
  decltype(auto) operator()(Args &&...args) const {
    return F::operator()(*this, std::forward<Args>(args)...);
  }
};

template <typename F>
inline decltype(auto) MFP(F &&f) {
  return FixPoint<F>{std::forward<F>(f)};
}
#line 4 "test/verify/yosupo-segment-add-get-min.test.cpp"

#line 1 "structure/convex-hull-trick/dynamic-li-chao-tree.hpp"
/**
 * @brief Dynamic-Li-Chao-Tree
 *
 */
template <typename T, T x_low, T x_high, T id>
struct DynamicLiChaoTree {
  struct Line {
    T a, b;

    Line(T a, T b) : a(a), b(b) {}

    inline T get(T x) const { return a * x + b; }
  };

  struct Node {
    Line x;
    Node *l, *r;

    Node(const Line &x) : x{x}, l{nullptr}, r{nullptr} {}
  };

  Node *root;

  DynamicLiChaoTree() : root{nullptr} {}

  Node *add_line(Node *t, Line &x, const T &l, const T &r, const T &x_l,
                 const T &x_r) {
    if (!t) return new Node(x);

    T t_l = t->x.get(l), t_r = t->x.get(r);

    if (t_l <= x_l && t_r <= x_r) {
      return t;
    } else if (t_l >= x_l && t_r >= x_r) {
      t->x = x;
      return t;
    } else {
      T m = (l + r) / 2;
      if (m == r) --m;
      T t_m = t->x.get(m), x_m = x.get(m);
      if (t_m > x_m) {
        swap(t->x, x);
        if (x_l >= t_l)
          t->l = add_line(t->l, x, l, m, t_l, t_m);
        else
          t->r = add_line(t->r, x, m + 1, r, t_m + x.a, t_r);
      } else {
        if (t_l >= x_l)
          t->l = add_line(t->l, x, l, m, x_l, x_m);
        else
          t->r = add_line(t->r, x, m + 1, r, x_m + x.a, x_r);
      }
      return t;
    }
  }

  void add_line(const T &a, const T &b) {
    Line x(a, b);
    root = add_line(root, x, x_low, x_high, x.get(x_low), x.get(x_high));
  }

  Node *add_segment(Node *t, Line &x, const T &a, const T &b, const T &l,
                    const T &r, const T &x_l, const T &x_r) {
    if (r < a || b < l) return t;
    if (a <= l && r <= b) {
      Line y{x};
      return add_line(t, y, l, r, x_l, x_r);
    }
    if (t) {
      T t_l = t->x.get(l), t_r = t->x.get(r);
      if (t_l <= x_l && t_r <= x_r) return t;
    } else {
      t = new Node(Line(0, id));
    }
    T m = (l + r) / 2;
    if (m == r) --m;
    T x_m = x.get(m);
    t->l = add_segment(t->l, x, a, b, l, m, x_l, x_m);
    t->r = add_segment(t->r, x, a, b, m + 1, r, x_m + x.a, x_r);
    return t;
  }

  void add_segment(const T &l, const T &r, const T &a, const T &b) {
    Line x(a, b);
    root = add_segment(root, x, l, r - 1, x_low, x_high, x.get(x_low),
                       x.get(x_high));
  }

  T query(const Node *t, const T &l, const T &r, const T &x) const {
    if (!t) return id;
    if (l == r) return t->x.get(x);
    T m = (l + r) / 2;
    if (m == r) --m;
    if (x <= m)
      return min(t->x.get(x), query(t->l, l, m, x));
    else
      return min(t->x.get(x), query(t->r, m + 1, r, x));
  }

  T query(const T &x) const { return query(root, x_low, x_high, x); }
};
#line 6 "test/verify/yosupo-segment-add-get-min.test.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  DynamicLiChaoTree< int64, -1000000000, 1000000000, infll > dlct;
  for(int i = 0; i < N; i++) {
    int64 l, r, a, b;
    cin >> l >> r >> a >> b;
    dlct.add_segment(l, r, a, b);
  }
  for(int i = 0; i < Q; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int64 l, r, a, b;
      cin >> l >> r >> a >> b;
      dlct.add_segment(l, r, a, b);
    } else {
      int64 p;
      cin >> p;
      auto ret = dlct.query(p);
      if(ret >= infll) cout << "INFINITY\n";
      else cout << ret << endl;
    }
  }
}

