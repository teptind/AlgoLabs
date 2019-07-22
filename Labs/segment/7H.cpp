#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int INF = 1e9;

struct Node {
    int min_ = INF;
    Node(int min_) : min_(min_) {}
};

Node* DO[400000];
int X[100000];
void build_tree(size_t a, size_t l, size_t r) {
    if (r - l == 1) {
        DO[a] = new Node(X[l]);
        return;
    }
    size_t m = (l + r) / 2;
    build_tree(a * 2 + 1, l, m);
    build_tree(a * 2 + 2, m, r);
    DO[a] = new Node(min(DO[a * 2 + 1]->min_, DO[a * 2 + 2]->min_));
}

int get_min(size_t a, size_t l, size_t r, size_t ql, size_t qr) {
    if (qr <= l || r <= ql) {
        return INF;
    }
    if (ql <= l && r <= qr) {
        return DO[a]->min_;
    }
    size_t m = (l + r) / 2;
    return min(get_min(a * 2 + 1, l, m, ql, qr),
               get_min(a * 2 + 2, m, r, ql, qr));
}

void set_(size_t a, size_t l, size_t r, size_t i, int x) {
    if (i < l || r <= i) {
        return;
    }
    if (l == i && r == i + 1) {
        DO[a] = new Node(x);
        return;
    }
    size_t m = (l + r) / 2;
    set_(a * 2 + 1, l, m, i, x);
    set_(a * 2 + 2, m, r, i, x);
    DO[a]->min_ = min(DO[a * 2 + 1]->min_, DO[a * 2 + 2]->min_);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    // freopen("file.in", "r", stdin);
    size_t n, m;
    cin >> n >> m;
    for (size_t i = 0; i < n; ++i) {
        X[i] = (int)i;
    }
    build_tree(0, 0, n);
    int ans;
    string act;
    size_t i;
    for (size_t j = 0; j < m; ++j) {
        cin >> act;
        if (act == "enter") {
            cin >> i; i--;
            ans = get_min(0, 0, n, i, n);
            if (ans == INF) {
                ans = get_min(0, 0, n, 0, i);
            }
            cout << ans + 1 << "\n";
            set_(0, 0, n, (size_t)ans, INF);
        } else if (act == "exit") {
            cin >> i; i--;
            set_(0, 0, n, i, (int)i);
        }
    }
    return 0;
}
