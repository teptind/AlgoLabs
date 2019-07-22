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

int dp[1002][10002];

void printDp(int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<int> ans;
vector<int> w;
vector<int> c;

void getAns(int i, int sum) {
    if (dp[i][sum] == 0) return;
    if (dp[i][sum] == dp[i - 1][sum]) {
        getAns(i - 1, sum);
    } else {
        ans.push_back(i);
        getAns(i - 1, sum - w[i - 1]);
    }
}

int main() {
    // freopen("file.in", "r", stdin);
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    int n, M;
    cin >> n >> M;
    w.resize(n);
    for (int i = 0; i < n; ++i) cin >> w[i];
    c.resize(n);
    for (int i = 0; i < n; ++i) cin >> c[i];

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= M; ++j) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else
                dp[i][j] = -1e9;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int sum = 1; sum <= M; ++sum) {
            dp[i][sum] = dp[i - 1][sum];
            if (sum >= w[i - 1]) {
                dp[i][sum] = max(dp[i - 1][sum], dp[i - 1][sum - w[i - 1]] + c[i - 1]);
            }
        }
    }
    getAns(n, M);
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    print(ans);
    return 0;
}
