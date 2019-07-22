#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

void print(vector<int> &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        cout << t[i] << " ";
    cout << "\n";
}

ll dp[2001][2001];
ll MOD = 1e9;

int main() {
    // freopen("file.in", "r", stdin);
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) dp[0][i] = 0LL;
    for (int i = 0; i < n; ++i) dp[1][i] = 1LL;

    for (int c = 2; c <= n; ++c) {
        for (int i = 0; i < n; ++i) {
            if (i + c - 1 >= n)
                break;
            dp[c][i] = (dp[c - 1][i] + dp[c - 1][i + 1]);
            if (a[i] == a[i + c - 1])
                dp[c][i] = (dp[c - 1][i] + dp[c - 1][i + 1] + 1) % MOD;
            else
                dp[c][i] = (dp[c - 1][i] + dp[c - 1][i + 1] - dp[c - 2][i + 1] + MOD) % MOD;
        }
    }
    cout << dp[n][0] << endl;
    return 0;
}
