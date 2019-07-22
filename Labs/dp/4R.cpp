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

bool dp[1005][1005];
pair<int, int> p[1005][1005];

void PrintDp(int n, int m) {
    for (int i = 0 ; i <= n; ++i) {
        for (int j = 0; j <= m; ++j)
            if (dp[i][j]) {
                cout << "mod sum " << i << " " << j << " true, prev = ";
                cout << p[i][j].first << " " << p[i][j].second << endl;
            }
            else
                cout << "mod sum " << i << " " << j << " false" << endl;
        cout << endl;
    }
    cout << endl;
}

int main() {
    // freopen("file.in", "r", stdin);
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    int n; cin >> n;
    for (int i = 0; i < 1005; ++i)
        for (int j = 0; j < 1005; ++j) {
            dp[i][j] = false;
            p[i][j] = {-2, -2};
        }
    queue<pair<int, int> > q;
    bool br = false;
    int mod1, sum1, mod, sum;
    dp[0][0] = true; p[0][0] = {-1, -1}; q.push({0, 0});
    while (!q.empty() && !br) {
        mod = q.front().first;
        sum = q.front().second;
        q.pop();
        for (int k = 0; k < 10; ++k) {
            if (mod == 0 && k == 0)
                continue;
            mod1 = ((mod * 10) + k) % n;
            sum1 = sum + k;
            if (sum1 <= n && dp[mod1][sum1] == false) {
                dp[mod1][sum1] = true;
                p[mod1][sum1] = {mod, sum};
                q.push({mod1, sum1});
                if (mod1 == 0 && sum1 == n)
                    br = true;
            }
        }
    }
    vector<int> ans;
    pair<int, int> curr = {0, n};
    // PrintDp(n - 1, n);
    while (curr.second != -1) {
        mod1 = p[curr.first][curr.second].first;
        sum1 = p[curr.first][curr.second].second;
        if (sum1 != -1)
            ans.push_back(curr.second - sum1);
        curr = {mod1, sum1};
    }
    reverse(ans.begin(), ans.end());
    print(ans);
    return 0;
}
