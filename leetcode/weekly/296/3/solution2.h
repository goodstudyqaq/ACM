#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

class TextEditor {
   public:
    string s, t;

    TextEditor() {
        s = "";
        t = "";
    }

    void addText(string text) {
        s += text;
    }

    int deleteText(int k) {
        int sz = s.size();
        k = min(k, sz);
        for (int i = 0; i < k; i++) {
            s.pop_back();
        }
        return k;
    }

    string cursorLeft(int k) {
        int sz = s.size();
        k = min(k, sz);

        for (int i = 0; i < k; i++) {
            char it = s.back();
            s.pop_back();
            t.push_back(it);
        }
        string res = s.substr(max(0, (int)s.size() - 10), min(10, (int)s.size()));
        return res;
    }

    string cursorRight(int k) {
        int sz = t.size();
        k = min(k, sz);
        for (int i = 0; i < k; i++) {
            char it = t.back();
            t.pop_back();
            s.push_back(it);
        }

        string res = s.substr(max(0, (int)s.size() - 10), min(10, (int)s.size()));
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
