/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

template <typename T>
struct Node {
    int next, last;
    T w;
    Node(T _w = ' ', int _next = -1, int _last = -1) : w(_w), next(_next), last(_last) {}
};

template <typename T>
struct List {
    vector<Node<T>> nodes;
    Node<T> ed;
    int init() {
        nodes.clear();
        ed = Node<T>();
        nodes.emplace_back(ed);
        return nodes.size() - 1;
    }

    void link(int a, int b) {
        nodes[a].next = b;
        nodes[b].last = a;
    }
    // 在 idx 后面新加一个 node
    int new_node(int idx, char _w) {
        Node<T> it = Node<T>(_w);
        nodes.emplace_back(it);
        int sz = nodes.size() - 1;
        int last = nodes[idx].last;
        if (last != -1) {
            link(last, sz);
        }
        link(sz, idx);
        return sz;
    }

    // 删除 idx 这个 node
    int erase_node(int idx) {
        int last = nodes[idx].last, next = nodes[idx].next;

        if (last != -1) {
            nodes[last].next = -1;
        }
        if (next != -1) {
            nodes[next].last = -1;
        }

        if (last != -1 && next != -1) {
            link(last, next);
        }
        return last;
    }
};

class TextEditor {
   public:
    int now;
    List<char> list;
    TextEditor() {
        now = list.init();
    }

    void addText(string text) {
        int n = text.size();
        int tmp_now = now;
        for (int i = n - 1; i >= 0; i--) {
            tmp_now = list.new_node(tmp_now, text[i]);
        }
    }

    int deleteText(int k) {
        int cnt = 0;
        for (int i = 0; i < k; i++) {
            if (list.nodes[now].last == -1) {
                break;
            }
            cnt++;
            list.erase_node(list.nodes[now].last);
        }
        return cnt;
    }

    string cursorLeft(int k) {
        for (int i = 0; i < k; i++) {
            if (list.nodes[now].last == -1) {
                break;
            }
            now = list.nodes[now].last;
        }

        string res = "";
        int tmp_now = now;
        for (int i = 0; i < 10; i++) {
            if (list.nodes[tmp_now].last == -1) {
                break;
            }
            tmp_now = list.nodes[tmp_now].last;
            res += list.nodes[tmp_now].w;
        }
        reverse(res.begin(), res.end());
        return res;
    }

    string cursorRight(int k) {
        for (int i = 0; i < k; i++) {
            if (list.nodes[now].next == -1) {
                break;
            }
            now = list.nodes[now].next;
        }
        string res = "";
        int tmp_now = now;
        for (int i = 0; i < 10; i++) {
            if (list.nodes[tmp_now].last == -1) {
                break;
            }
            tmp_now = list.nodes[tmp_now].last;
            res += list.nodes[tmp_now].w;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */