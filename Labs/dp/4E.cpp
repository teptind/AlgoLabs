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

int dp[5001][5001];
ll MOD = 1e9;

int min_(int a, int b, int c) {
    return min(a, min(b, c));
}

int main() {
    // freopen("file.in", "r", stdin);
    freopen("levenshtein.in", "r", stdin);
    freopen("levenshtein.out", "w", stdout);

    string s1, s2; cin >> s1 >> s2;
    int n = (int)s1.length(), m = (int)s2.length();

    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) dp[i][0] = i;
    for (int j = 1; j <= m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = min_(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1;
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}
