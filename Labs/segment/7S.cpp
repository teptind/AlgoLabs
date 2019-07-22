#include <bits/stdc++.h>

using namespace std;
#define ll long long

const ll INF = (ll)(2e18);

struct LCASparse {
    vector<vector<pair<int, int> > > dp;
    vector<int> twos_power;
    explicit LCASparse(vector<pair<int, int> > &a) {
        size_t x = a.size() + 5;
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
vector<int> dep;
vector<pair<int, int> > euler;
vector<vector<int> > children;

void dfs(int v, int d, int p) {
    entry[v] = (int)euler.size();
    dep[v] = d;
    euler.emplace_back(d, v);
    for (int u : children[v]) {
        if (u == p) {
            continue;
        }
        dfs(u, d + 1, v);
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
    int n;
    while (cin >> n) {
        if (n == 0) {
            break;
        }
        entry.clear();
        euler.clear();
        children.clear();
        dep.clear();
        int a, b, m;
        dep.assign(n, 0);
        entry.assign(n, 0);
        children.assign((size_t)n, vector<int>());
        for (int i = 1; i < n; ++i) {
            cin >> a >> b; a--; b--;
            children[b].push_back(a);
            children[a].push_back(b);
        }
        dfs(0, 0, -1);
        LCASparse sparse(euler);
        //////////////////
        string act;
        int root = 0;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            cin >> act;
            if (act == "!") {
                cin >> root; root--;
            } else if (act == "?") {
                cin >> a >> b; a--; b--;
                int res = lca(a, b, sparse);
                int L1 = lca(root, a, sparse);
                int L2 = lca(root, b, sparse);
                if (dep[L1] > dep[res]) {
                    res = L1;
                }
                if (dep[L2] > dep[res]) {
                    res = L2;
                }
                cout << res + 1 << " " << "\n";
            }
        }
    }
    return 0;
}
