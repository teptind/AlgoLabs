#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int INF = INT32_MAX;

struct Node {
    pair<int, int> res = {-1, -1};
    int delta = 0;
    explicit Node(pair<int, int> res_, int delta_) : res(std::move(res_)), delta(delta_) {}
};

const int SHIFT = (int)(1e6);
// const int SHIFT = 0;
const size_t SZ = (size_t)(2e6 + 1);
// const size_t SZ = (size_t)(4 + 1);
Node* DO[4 * SZ];
int X[SZ];
void build_tree(size_t a, size_t l, size_t r) {
    if (r - l == 1) {
        DO[a] = new Node({X[l], l}, 0);
        return;
    }
    size_t m = (l + r) / 2;
    build_tree(a * 2 + 1, l, m);
    build_tree(a * 2 + 2, m, r);
    DO[a] = new Node(max(DO[a * 2 + 1]->res, DO[a * 2 + 2]->res), 0);
}

void push(size_t a) {
    DO[a * 2 + 1]->res.first += DO[a]->delta;
    DO[a * 2 + 2]->res.first += DO[a]->delta;
    DO[a * 2 + 1]->delta += DO[a]->delta;
    DO[a * 2 + 2]->delta += DO[a]->delta;
    DO[a]->delta = 0;
}

pair<int, int> get_max(size_t a, size_t l, size_t r, size_t ql, size_t qr) {
    if (qr <= l || r <= ql) {
        return {-1, -1};
    }
    if (ql <= l && r <= qr) {
        return DO[a]->res;
    }
    push(a);
    size_t m = (l + r) / 2;
    return max(get_max(a * 2 + 1, l, m, ql, qr),
               get_max(a * 2 + 2, m, r, ql, qr));
}

void seg_add(size_t a, size_t l, size_t r, size_t ql, size_t qr, int x) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        // push(a, l, r);
        DO[a]->res.first += x;
        DO[a]->delta += x;
        return;
    }
    push(a);
    size_t m = (l + r) / 2;
    seg_add(a * 2 + 1, l, m, ql, qr, x);
    seg_add(a * 2 + 2, m, r, ql, qr, x);
    DO[a]->res = max(DO[a * 2 + 1]->res, DO[a * 2 + 2]->res);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    // freopen("file.in", "r", stdin);
    size_t n;
    cin >> n;
    vector<vector<int> > queries;
    for (size_t i = 0; i < n; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        y1 += SHIFT;
        y2 += SHIFT;
        queries.push_back({x1, 1, y1, y2 + 1});
        queries.push_back({x2, 2, y1, y2 + 1});
    }
    sort(queries.begin(), queries.end());
    for (int &i : X) {
        i = 0;
    }
    build_tree(0, 0, SZ);
    size_t qsz = queries.size();
    int ansx = INT32_MIN, ansy = INT32_MIN, cnt_ans = -1;
    for (size_t i = 0; i < qsz; ++i) {
        int d = 1;
        if (queries[i][1] == 2) {
            d = -1;
        }
        seg_add(0, 0, SZ, (size_t)queries[i][2], (size_t)(queries[i][3]), d);
        if (d == 1) {
            auto p = get_max(0, 0, SZ, 0, SZ);
            if (p.first > cnt_ans) {
                cnt_ans = p.first;
                ansy = p.second - SHIFT;
                ansx = queries[i][0];
            }
        }
    }
    cout << cnt_ans << "\n" << ansx << " " << ansy << endl;
    return 0;
}
