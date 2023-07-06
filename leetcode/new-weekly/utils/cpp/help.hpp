#include <bits/stdc++.h>
using namespace std;

void convert_params(string s, long long &res);
struct TreeNode {
    long long val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(long long x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(long long x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    TreeNode(vector<string> v);
    vector<string> bfs_order();
};
struct ListNode {
    long long val;
    ListNode *next;

    ListNode(long long x) : val(x), next(NULL) {}
    ListNode(vector<long long> x);
    vector<long long> to_vector();
};
/*
    调试输出
*/
template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string &s) {
    return '"' + s + '"';
}

string to_string(const char *s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

string to_string(TreeNode *rt) {
    return to_string(rt->bfs_order());
}

void debug_out() {
    cerr << endl;
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

TreeNode::TreeNode(vector<string> v) {
    // bfs 序构建整颗树
    assert(v.size() > 0);
    int son_idx = 1;
    queue<TreeNode *> Q;
    // 第一个不可能是 null
    assert(v[0] != "null");
    convert_params(v[0], this->val);
    this->left = this->right = NULL;
    Q.push(this);
    while (!Q.empty()) {
        TreeNode *now = Q.front();
        Q.pop();
        if (son_idx < v.size() && v[son_idx] != "null") {
            long long left_son_val;
            convert_params(v[son_idx], left_son_val);
            TreeNode *tmp = new TreeNode(left_son_val);
            now->left = tmp;
            Q.push(tmp);
        }
        if (son_idx + 1 < v.size() && v[son_idx + 1] != "null") {
            long long right_son_val;
            convert_params(v[son_idx + 1], right_son_val);
            TreeNode *tmp = new TreeNode(right_son_val);
            now->right = tmp;
            Q.push(tmp);
        }
        son_idx += 2;
    }
}

vector<string> TreeNode::bfs_order() {
    vector<string> res;
    res.push_back(to_string(this->val));
    queue<TreeNode *> Q;
    Q.push(this);
    while (!Q.empty()) {
        TreeNode *now = Q.front();
        Q.pop();
        if (now->left != NULL) {
            Q.push(now->left);
            res.push_back(to_string(now->left->val));
        } else {
            res.push_back("null");
        }
        if (now->right != NULL) {
            Q.push(now->right);
            res.push_back(to_string(now->right->val));
        } else {
            res.push_back("null");
        }
    }
    // 去掉末尾 0
    int idx = res.size() - 1;
    while (idx >= 0 && res[idx] == "null") idx--;
    res.resize(idx + 1);
    return res;
}

ListNode::ListNode(vector<long long> x) {
    assert(x.size() > 0);
    this->next = NULL;
    this->val = x[0];
    ListNode *now = this;
    for (int i = 1; i < x.size(); i++) {
        long long val = x[i];
        ListNode *nxt = new ListNode(val);
        now->next = nxt;
        now = nxt;
    }
}
vector<long long> ListNode::to_vector() {
    ListNode *now = this;
    vector<long long> ans;
    while (now != NULL) {
        long long val = now->val;
        ans.push_back(val);
        now = now->next;
    }
    return ans;
}

// compare_result 实现
template <typename T>
bool compare_result(string sample_idx, T &my_ans, T &result) {
    bool equal = (my_ans == result);
    debug(my_ans);
    debug(result);
    if (!equal) {
        cerr << "[fail!] 样例 " << sample_idx << " 错误! 请勿提交!" << endl;
    } else {
        cerr << "样例 " << sample_idx << " 通过测试!" << endl;
    }
    return equal;
}

bool compare_result(string sample_idx, TreeNode *my_ans, TreeNode *result) {
    vector<string> a = my_ans->bfs_order();
    vector<string> b = result->bfs_order();
    return compare_result(sample_idx, a, b);
};

bool compare_result(string sample_idx, ListNode *my_ans, ListNode *result) {
    vector<long long> a = my_ans->to_vector();
    vector<long long> b = result->to_vector();
    return compare_result(sample_idx, a, b);
}

void convert_params(string s, int &res) {
    res = 0;
    if (s.size() == 0) return;
    int beg = 0;
    int flag = 1;
    if (s[0] == '-') flag = -1, beg = 1;
    for (int i = beg; i < s.size(); i++) {
        res = res * 10 + s[i] - '0';
    }
    res *= flag;
}

void convert_params(string s, bool &res) {
    if (s == "true")
        res = true;
    else
        res = false;
}

void convert_params(string s, long long &res) {
    res = 0;
    if (s.size() == 0) return;
    int beg = 0;
    int flag = 1;
    if (s[0] == '-') flag = -1, beg = 1;
    for (int i = beg; i < s.size(); i++) {
        res = res * 10 + s[i] - '0';
    }
    res *= flag;
}

void convert_params(string str, string &res) {
    int len = str.size();
    res = str.substr(1, len - 2);
}

template <class T>
void convert_params(string str, vector<T> &v) {
    // 去掉 s 的开头和结尾
    string s2 = str.substr(1, str.size() - 2);
    debug(s2);
    if (s2.size() == 0) {
        return;
    }
    int sz = s2.size();
    int now = 0;
    int now_score = 0;
    while (now < sz) {
        int go = now;
        while (go < sz) {
            if (s2[go] == '[') {
                now_score++;
            } else if (s2[go] == ']') {
                now_score--;
            } else if (s2[go] == ',' && now_score == 0) {
                break;
            }
            go++;
        }
        T res;
        string new_s = s2.substr(now, go - now);
        convert_params(new_s, res);
        v.push_back(res);
        now = go + 1;
    }
}

void convert_params(string str, ListNode *&res) {
    vector<long long> v;
    convert_params(str, v);
    res = new ListNode(v);
}

vector<string> split(string &s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

void convert_params(string str, TreeNode *&res) {
    vector<string> v;
    str = str.substr(1, str.size() - 2);
    v = split(str, ",");
    res = new TreeNode(v);
}

vector<string> split_str_to_func(string s) {
    s = s.substr(1, s.size() - 2);
    vector<string> res = split(s, ",");
    for (int i = 0; i < res.size(); i++) {
        res[i] = res[i].substr(1, res[i].size() - 2);
    }
    return res;
}

vector<string> split_str_to_params(string s) {
    s = s.substr(1, s.size() - 2);
    // 不能简单的根据逗号 split

    vector<string> ans;
    int sz = s.size();
    int now = 0;
    int now_score = 0;
    while (now < sz) {
        int go = now;
        while (go < sz) {
            if (s[go] == '[') {
                now_score++;
            } else if (s[go] == ']') {
                now_score--;
            } else if (s[go] == ',' && now_score == 0) {
                // todo: 不一定，可能字符串里面含有逗号，需要验证
                break;
            }
            go++;
        }
        string new_s = s.substr(now, go - now);
        ans.push_back(new_s);
        now = go + 1;
    }
    return ans;
}
