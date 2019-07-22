#include <bits/stdc++.h>

using namespace std;
#define ll long long

const ll INF = INT64_MAX;

struct Node {
    ll min_ = INF, delta = 0, setter = INF;
    Node(ll min_, ll delta, ll setter) : min_(min_), delta(delta), setter(setter) {}
    /*Node& operator=(Node *node) {
        this->min_ = node->min_;
        this->delta = node->delta;
        this->setter = node->setter;
        return *this;
    }*/
};

Node* DO[4000001];
ll X[500001];
void build_tree(size_t a, size_t l, size_t r) {
    if (r - l == 1) {
        DO[a] = new Node(X[l], 0LL, INF);
        return;
    }
    size_t m = (l + r) / 2;
    build_tree(a * 2 + 1, l, m);
    build_tree(a * 2 + 2, m, r);
    DO[a] = new Node(min(DO[a * 2 + 1]->min_, DO[a * 2 + 2]->min_), 0LL, INF);
}

void push(size_t a) {
    if (DO[a]->setter != INF) {
        // if (r - l > 1) {

        *DO[a * 2 + 1] = *DO[a];
        *DO[a * 2 + 2] = *DO[a];
        /*DO[a * 2 + 1]->min_ = DO[a]->min_;
        DO[a * 2 + 1]->delta = DO[a]->delta;
        DO[a * 2 + 1]->setter = DO[a]->setter;

        DO[a * 2 + 2]->min_ = DO[a]->min_;
        DO[a * 2 + 2]->delta = DO[a]->delta;
        DO[a * 2 + 2]->setter = DO[a]->setter;*/
        // }
        DO[a]->setter = INF;
    } else {
        // if (r - l > 1) {
            DO[a * 2 + 1]->min_ += DO[a]->delta;
            DO[a * 2 + 2]->min_ += DO[a]->delta;
            DO[a * 2 + 1]->delta += DO[a]->delta;
            DO[a * 2 + 2]->delta += DO[a]->delta;
        // }
    }
    DO[a]->delta = 0LL;
}

ll get_min(size_t a, size_t l, size_t r, size_t ql, size_t qr) {
    if (qr <= l || r <= ql) {
        return INF;
    }
    if (ql <= l && r <= qr) {
        return DO[a]->min_;
    }
    push(a);
    size_t m = (l + r) / 2;
    return min(get_min(a * 2 + 1, l, m, ql, qr),
                 get_min(a * 2 + 2, m, r, ql, qr));
}

void seg_add(size_t a, size_t l, size_t r, size_t ql, size_t qr, ll x) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        // push(a, l, r);
        DO[a]->min_ += x;
        DO[a]->delta += x;
        return;
    }
    push(a);
    size_t m = (l + r) / 2;
    seg_add(a * 2 + 1, l, m, ql, qr, x);
    seg_add(a * 2 + 2, m, r, ql, qr, x);
    DO[a]->min_ = min(DO[a * 2 + 1]->min_, DO[a * 2 + 2]->min_);
}

void seg_set(size_t a, size_t l, size_t r, size_t ql, size_t qr, ll x) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        // push(a, l, r);
        DO[a]->min_ = x;
        DO[a]->delta = 0LL;
        DO[a]->setter = x;
        return;
    }
    push(a);
    size_t m = (l + r) / 2;
    seg_set(a * 2 + 1, l, m, ql, qr, x);
    seg_set(a * 2 + 2, m, r, ql, qr, x);
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
    size_t l, r;
    ll d;
    while (cin >> act) {
        if (act == "min") {
            cin >> l >> r; l--; r--;
            cout << get_min(0, 0, n, l, r + 1) << "\n";
        } else if (act == "set") {
            cin >> l >> r >> d; l--; r--;
            if (r < l) {
                continue;
            }
            seg_set(0, 0, n, l, r + 1, d);
        }  else if (act == "add") {
            cin >> l >> r >> d; l--; r--;
            if (r < l) {
                continue;
            }
            seg_add(0, 0, n, l, r + 1, d);
        }
    }
    return 0;
}
