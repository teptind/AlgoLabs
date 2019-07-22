#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

void print(vector<pair<int, int> > &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        cout << "(" << t[i].first << " " << t[i].second << ") ";
    cout << "\n";
}

void print2(vector<vector<pair<int, int> > > &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        print(t[i]);
    cout << "\n";
}

int x, A, y, B, LEN;

bool ok(int ANS) {
    // cout << "CHECKING " << ANS << endl;
    vector<vector<pair<int, int> > > dp(x + 1, vector<pair<int, int> >(y + 1, {-1, -1}));
    dp[0][0] = {0, 0};
    for (int i = 0; i <= x; ++i) {
        for (int j = 0; j <= y; ++j) {
            if (i == x && j == y)
                continue;
            int rows = dp[i][j].first, curr = dp[i][j].second, nRows, nCurr;
            if (i < x) {
                if (curr + A >= ANS) {
                    nRows = rows + 1;
                    nCurr = 0;
                } else {
                    nRows = rows;
                    nCurr = curr + A;
                }
                dp[i + 1][j] = max(dp[i + 1][j], {nRows, nCurr});
            }
            if (j < y) {
                if (curr + B >= ANS) {
                    nRows = rows + 1;
                    nCurr = 0;
                } else {
                    nRows = rows;
                    nCurr = curr + B;
                }
                dp[i][j + 1] = max(dp[i][j + 1], {nRows, nCurr});
            }
        }
    }
    // print2(dp);
    // cout << dp[x][y].first << " " << LEN << endl;
    if (dp[x][y].first >= LEN)
        return true;
    return false;
}


int main() {
    // freopen("file.in", "r", stdin);
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
    cin >> x >> A >> y >> B >> LEN;
    int L = 0, R = 1e5, mid;
    while (R - L > 1) {
        mid = (R + L) / 2;
        if (ok(mid))
            L = mid;
        else
            R = mid;
    }
    cout << L << endl;
    return 0;
}
