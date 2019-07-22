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

bool dp[10010][10010];
ll MOD = 1e9;

int min_(int a, int b, int c) {
    return min(a, min(b, c));
}

void PrintDp(int n, int m) {
    for (int i = 0 ; i <= n; ++i) {
        for (int j = 0; j <= m; ++j)
            cout << dp[i][j];
        cout << endl;
    }
    cout << endl;
}

int main() {
    // freopen("file.in", "r", stdin);
    // freopen("levenshtein.in", "r", stdin);
    // freopen("levenshtein.out", "w", stdout);

    string s1, s2; cin >> s1 >> s2; s1 = "$" + s1 + "$"; s2 = "$" + s2 + "$";
    int n = (int)s1.length(), m = (int)s2.length();

    dp[0][0] = true;
    for (int j = 1; j <= m; ++j) dp[0][j] = false;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (s1[i - 1] == '*') {
                if (j == 0) dp[i][j] = dp[i - 1][j];
                else dp[i][j] = (dp[i][j - 1] | dp[i - 1][j]);
            } else if (s1[i - 1] == '?') {
                if (j == 0) dp[i][j] = false;
                else dp[i][j] = dp[i - 1][j - 1];
            } else {
                if (j != 0 && s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                else dp[i][j] = 0;
            }
        }
        // PrintDp(n, m);
    }
    if (dp[n][m] == true)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}
