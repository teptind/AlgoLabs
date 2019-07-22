#include <bits/stdc++.h>

using namespace std;
#define ll long long

const ll INF = (ll)(2e18);
int P;
size_t N;

struct zhopa {
    int l, r, ind;
    explicit zhopa(int l1, int r1, int ind1) : l(l1), r(r1), ind(ind1) {}
    zhopa() = default;
};

bool comp(zhopa const &a, zhopa const &b) {
    int Q1 = a.l / P, Q2 = b.l / P;
    if (Q1 != Q2) {
        return Q1 < Q2;
    } else {
        return a.r < b.r;
    }
}

int cnt[1000001];
int a[200001];

void move_bound(size_t X, size_t qX, ll &cur_ans, bool right) {
    if (X < qX) {
        if (right) {
            for (size_t i = X + 1; i <= qX; ++i) {
                int c = cnt[a[i]];
                cur_ans -= (ll)c * c * a[i];
                cnt[a[i]]++;
                c = cnt[a[i]];
                cur_ans += (ll)c * c * a[i];
            }
        } else {
            for (size_t i = X; i < qX; ++i) {
                int c = cnt[a[i]];
                cur_ans -= (ll)c * c * a[i];
                cnt[a[i]]--;
                c = cnt[a[i]];
                cur_ans += (ll)c * c * a[i];
            }
        }
    } else {
        auto pqX = (ptrdiff_t)qX;
        if (right) {
            for (auto i = (ptrdiff_t)X; i > pqX; --i) {
                int c = cnt[a[i]];
                cur_ans -= (ll)c * c * a[i];
                cnt[a[i]]--;
                c = cnt[a[i]];
                cur_ans += (ll)c * c * a[i];
            }
        } else {
            for (ptrdiff_t i = (ptrdiff_t)X - 1; i >= pqX; --i) {
                int c = cnt[a[i]];
                cur_ans -= (ll)c * c * a[i];
                cnt[a[i]]++;
                c = cnt[a[i]];
                cur_ans += (ll)c * c * a[i];
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    // freopen("file.in", "r", stdin);
    int l, r;
    size_t t;
    cin >> N >> t;
    P = (int)sqrt((double)N);
    for (size_t i = 0; i < N; ++i) {
        cin >> a[i];
        cnt[i] = 0;
    }
    cnt[a[0]] = 1LL;
    vector<zhopa> queries((size_t)t);
    for (size_t i = 0; i < t; ++i) {
        cin >> l >> r; l--; r--;
        queries[i] = zhopa(l, r, (int)i);
    }
    sort(queries.begin(), queries.end(), comp);
    size_t L = 0, R = 0, qL, qR;
    ll cur_ans = a[0];
    vector<ll> ans((size_t)t);
    for (auto &p : queries) {
        qL = (size_t)(p.l);
        qR = (size_t)(p.r);
        move_bound(L, qL, cur_ans, false);
        move_bound(R, qR, cur_ans, true);
        ans[p.ind] = cur_ans;
        L = qL;
        R = qR;
    }
    for (ll x : ans) {
        cout << x << "\n";
    }
    cout << endl;
    return 0;
}
