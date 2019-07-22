#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

void print(vector<ll> &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        cout << t[i] << " ";
    cout << "\n";
}

void print2(vector<vector<ll> > &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        print(t[i]);
    cout << "\n";
}

int INF = 2e9;
int c[20][20];
int dp[20][1 << 20];
int n;
int shifts[20];

int getAns() {
    int M = (1 << n), curr, nMask;
    bool b;
    for (int mask = 0; mask < M; ++mask) {
        for (int v = 0; v < n; ++v) {
                if (v == 0 && mask == 0)
                    continue;
                curr = INF;
                for (int i = 0; i < n; ++i) {
                    b = ((mask & (shifts[i])) != 0);
                    if (b && c[v][i] != -1) {
                        nMask = (mask ^ (shifts[i]));
                        curr = min(curr, dp[i][nMask] + c[v][i]);
                    }
                }
                dp[v][mask] = curr;
            }
        }
    return dp[0][M - 1];
}

int main() {
    // freopen("file.in", "r", stdin);
    freopen("salesman.in", "r", stdin);
    freopen("salesman.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int m, x, y, MASKS, w;
    cin >> n >> m;
    n++;
    shifts[0] = 1;
    for (int i = 1; i < 20; ++i)
        shifts[i] = shifts[i - 1] * 2;

    MASKS = (1 << n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            c[i][j] = -1;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < MASKS; ++j)
            dp[i][j] = INF;

    dp[0][0] = 0LL;
    for (int i = 1; i < n; ++i) {
        c[0][i] = 0LL;
        c[i][0] = 0LL;
    }
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> w;
        c[x][y] = w;
        c[y][x] = w;
    }
    // print2(c);
    int ans = getAns();
    if (ans == INF) ans = -1;
    cout << ans << endl;
    return 0;
}
