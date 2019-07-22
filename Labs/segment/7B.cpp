#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct Sparse {
    vector<vector<ll> > dp;
    vector<ll> twos_power;

    explicit Sparse(vector<ll> &a) {
        size_t x = a.size() + 1;
        twos_power.resize(x + 2);
        for (size_t i = 1; i < x + 2; ++i) {
            twos_power[i] = (ll) (floor(log2(i)));
        }
        auto m = (size_t) (ceil(log2(x)));
        dp.resize(m);
        dp[0].resize(x);
        for (size_t i = 0; i < x; ++i) {
            dp[0][i] = a[i];
        }
        for (size_t i = 1; i < m; ++i) {
            dp[i].resize(x);
            for (size_t j = 0; j < x; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (j + (1 << (i - 1)) < x)
                    dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    ll min_(int l, int r) {
        ll k = twos_power[r - l + 1];

        return min(dp[k][l], dp[k][r - (1LL << k) + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    // freopen("file.in", "r", stdin);
    // freopen("sparse.in", "r", stdin);
    // freopen("sparse.out", "w", stdout);
    ll v, u, ans;
    size_t n, m;
    cin >> n >> m;
    vector<ll> a(n);
    cin >> a[0];
    for (size_t i = 1; i < n; ++i) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    Sparse sparse(a);
    cin >> u >> v;
    for (size_t i = 1; i < m; ++i) {
        if (u > v)
            ans = sparse.min_((int) v - 1, (int) u - 1);
        else
            ans = sparse.min_((int) u - 1, (int) v - 1);
        u = ((17 * u + 751 + (ans % n) + 2 * i) % n) + 1;
        v = ((13 * v + 593 + (ans % n) + 5 * i) % n) + 1;
    }
    if (u > v)
        ans = sparse.min_((int) v - 1, (int) u - 1);
    else
        ans = sparse.min_((int) u - 1, (int) v - 1);
    cout << u << " " << v << " " << ans << "\n";
    return 0;
}
