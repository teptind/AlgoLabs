#include <bits/stdc++.h>

using namespace std;
#define ll long long

const ll INF = 2e18;

struct Node {
    ll min_ = -INF, sum_ = 0, data_ = 0;
    Node(ll min_, ll sum_, ll data_) : min_(min_), sum_(sum_), data_(data_) {}
};

Node* DO[4000001];
ll X[500001];
void build_tree(size_t a, size_t l, size_t r) {
    if (r - l == 1) {
        DO[a] = new Node(X[l], X[l], X[l]);
        return;
    }
    size_t m = (l + r) / 2;
    build_tree(a * 2 + 1, l, m);
    build_tree(a * 2 + 2, m, r);
    DO[a] = new Node(min(DO[a * 2 + 1]->min_, DO[a * 2 + 2]->min_),
            DO[a * 2 + 1]->sum_ + DO[a * 2 + 2]->sum_, 0LL);
}

ll get_sum(size_t a, size_t l, size_t r, size_t ql, size_t qr) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return DO[a]->sum_;
    }
    size_t m = (l + r) / 2;
    return get_sum(a * 2 + 1, l, m, ql, qr) +
           get_sum(a * 2 + 2, m, r, ql, qr);
}

void set_(size_t a, size_t l, size_t r, size_t i, ll x) {
    if (i < l || r <= i) {
        return;
    }
    if (l == i && r == i + 1) {
        DO[a] = new Node(x, x, x);
        return;
    }
    size_t m = (l + r) / 2;
    set_(a * 2 + 1, l, m, i, x);
    set_(a * 2 + 2, m, r, i, x);
    DO[a]->sum_ = DO[a * 2 + 1]->sum_ + DO[a * 2 + 2]->sum_;
    DO[a]->min_ = min(DO[a * 2 + 1]->min_, DO[a * 2 + 2]->min_);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    // freopen("file.in", "r", stdin);
    size_t n;
    cin >> n;
    for (size_t i = 0; i < n; ++i) {
        cin >> X[i];
    }
    build_tree(0, 0, n);
    string act;
    size_t l, r, i;
    ll d;
    while (cin >> act) {
        if (act == "sum") {
            cin >> l >> r; l--; r--;
            cout << get_sum(0, 0, n, l, r + 1) << "\n";
        } else if (act == "set") {
            cin >> i >> d; i--;
            set_(0, 0, n, i, d);
        }
    }
    return 0;
}
