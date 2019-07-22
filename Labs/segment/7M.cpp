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
    int n, m, p;
    cin >> n >> m;
    entry.assign(n, 0);
    children.assign((size_t)n, vector<int>());
    for (int i = 1; i < n; ++i) {
        cin >> p;
        children[p].push_back(i);
    }
    dfs(0, 0);
    LCASparse sparse(euler);

    ll a1, a2, x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    ll ANS = 0LL;

    int cur_ans = lca((int)a1, (int)a2, sparse);
    ANS += cur_ans;
    for (int i = 1; i < m; i++) {
//        cin >> a1 >> a2;
//        int cur_ans = lca((int)a1, (int)a2, sparse);
//        cout << cur_ans << "\n";
        int a3 = int((x * a1 + y * a2 + z) % n);
        int a4 = int((x * a2 + y * a3 + z) % n);
        cur_ans = lca((a3 + cur_ans) % n, a4, sparse);
        ANS += cur_ans;
        a1 = a3;
        a2 = a4;
    }
    cout << ANS << endl;
    return 0;
}
