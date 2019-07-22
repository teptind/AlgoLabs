#include <bits/stdc++.h>

using namespace std;
#define ll long long

const ll INF = (ll)(2e18);

struct LCASparse {
    vector<vector<pair<int, int> > > dp;
    vector<int> twos_power;
    explicit LCASparse(vector<pair<int, int> > &a) {
        size_t x = a.size() + 1;
        twos_power.resize(x + 2);
        for (size_t i = 1; i < x + 2; ++i) {
            twos_power[i] = (int)(floor(log2(i)));
        }
        auto m = (size_t)(ceil(log2(x)));
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
    int min_(int l, int r) {  // вхождения соответствующих вершин
        int k = twos_power[r - l + 1];

        return min(dp[k][l], dp[k][r - (1LL << k) + 1]).second;
    }
};

vector<int> entry;
vector<pair<int, int> > euler;
vector<vector<int> > children;

void dfs(int v, int d) {
    entry[v] = (int)euler.size();
    euler.emplace_back(d, v);
    for (int u : children[v]) {
        dfs(u, d + 1);
        euler.emplace_back(d, v);
    }
}

int lca(int v, int u, LCASparse &sparse) {
    v = entry[v]; u = entry[u];
    if (v > u) {
        swap(v, u);
    }
    return sparse.min_(v, u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    // freopen("file.in", "r", stdin);
    int m, a, b;
    cin >> m;
    vector<pair<int, int> > queries;
    size_t MAXN = 500000;
    entry.assign(MAXN, 0);
    children.assign(MAXN, vector<int>());
    string act;
    for (int i = 0; i < m; ++i) {
        cin >> act >> a >> b; a--; b--;
        if (act == "ADD") {
            children[a].push_back(b);
        } else {
            queries.emplace_back(a, b);
        }
    }
    dfs(0, 0);
    LCASparse sparse(euler);

    for (auto p : queries) {
        int ans = lca(p.first, p.second, sparse);
        cout << ans + 1 << "\n";
    }
    return 0;
}
