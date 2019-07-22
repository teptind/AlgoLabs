#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

void print(vector<int> &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        cout << t[i] << "";
    cout << "\n";
}

struct pnt {
    ll a;  // use
    ll b;  // !use
    pnt() {}
    pnt(ll a1, ll b1) {
        a = a1;
        b = b1;
    }
};

pnt dp[100005];
bool was[100005];
vector<vector<pair<int, ll> > > g;

void PrintDp(int n) {
    for (int i = 0 ; i < n; ++i) {
            cout << i << ": " << dp[i].a << " " << dp[i].b << "\n";
    }
    cout << endl;
}

void dfs(int v) {
    was[v] = true;
    dp[v].a = 0LL;
    dp[v].b = 0LL;
    int u; ll c;
    for (pair<int, ll> uw : g[v]) {
        u = uw.first; c = uw.second;
        if (was[u])
            continue;
        dfs(u);
        dp[v].a = max(dp[v].a, dp[u].b + c - max(dp[u].a, dp[u].b));
        dp[v].b += max(dp[u].a, dp[u].b);
    }
    dp[v].a += dp[v].b;
}

int main() {
    // freopen("file.in", "r", stdin);
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    int n, x, y;
    ll w;
    cin >> n;
    g.assign(n, vector<pair<int, ll> >());
    for (int i = 0; i < n - 1; ++i) {
        cin >> x >> y >> w; x--; y--;
        g[x].push_back({y, w});
        g[y].push_back({x, w});
    }
    for (int i = 0; i < n; ++i) {
        if (g[i].size() == 1 && i != 0)
            dp[i] = pnt(0LL, 0LL);
        else
            dp[i] = pnt(-1LL, -1LL);
        was[i] = false;
    }
    dfs(0);
    cout << max(dp[0].a, dp[0].b);
    return 0;
}
