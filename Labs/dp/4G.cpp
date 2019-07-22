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

void print2(vector<vector<int > > &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        print(t[i]);
    cout << "\n";
}

struct meeting {
    int mn, mx, d;
    meeting() {}
    meeting(int a, int b, int c) {
        mn = a;
        mx = b;
        d = c;
    }
};

int dp[1 << 20];
int pr[1 << 20];
int shifts[21];
int INF = 1e9;

int main() {
    // freopen("file.in", "r", stdin);
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
    shifts[0] = 1;
    for (int i = 1; i < 21; ++i)
        shifts[i] = shifts[i - 1] * 2;

    int n, k, a, b, c;
    cin >> n >> k;
    vector<meeting> m(n);
    for (int i = 0; i < n; ++i) {
        cin >> a >> b >> c;
        m[i] = meeting(a, b, c);
    }
    int MASKS = (1 << n);
    for (int i = 0; i < MASKS; ++i) {
        dp[i] = INF;
        pr[i] = -1;
    }

    dp[0] = k;
    pr[0] = -2;
    int ans = 0, ansMask = 0, curr, nMask, nD;
    for (int mask = 1; mask < MASKS; ++mask) {
        curr = 0;
        for (int v = 0; v < n; ++v) {
            if ((mask & shifts[v]) == 0)
                continue;
            curr++;
            nMask = mask ^ shifts[v];
            if (dp[nMask] != INF) {
                nD = dp[nMask];
                if (m[v].mn <= nD && nD <= m[v].mx) {
                    pr[mask] = v;
                    dp[mask] = nD + m[v].d;
                }
            }
        }
        if (ans < curr && dp[mask] != INF) {
            ans = curr;
            ansMask = mask;
        }
    }
    vector<int> res;
    int cMask = ansMask;
    while (pr[cMask] != -2) {
        res.push_back(pr[cMask] + 1);
        cMask ^= shifts[pr[cMask]];
    }
    cout << res.size() << endl;
    reverse(res.begin(), res.end());
    print(res);
    return 0;
}
