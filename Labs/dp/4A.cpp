#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

struct P{
    ll acts, resH, resW;
    int divInd;
    P() {}
    P(ll a, ll rH, ll rW, int dI) {
        acts = a; resH = rH, resW = rW; divInd = dI;
    }
    void write() {
        cout << acts << " " << resH << " " << resW << " " << divInd << endl;
    }
};

int n;
vector<ll> H;
vector<ll> W;

vector<vector<P> > dp;
ll INF = 2e18;

void print(vector<int> &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        cout << t[i];
    cout << "\n";
}

void print2() {
    for (int c = 0; c < n; ++c) {
        for (int i = 0; i < n; ++i) {
            if (i + c >= n) continue;
            cout << i << " " << i + c << ": ";
            dp[i][i + c].write();
        }
    }
}

void getAns(int l, int r) {
    // cout << "getAns " << l << " " << r << endl;
    if (l > r)
        return;
    if (r == l) {
        cout << "A";
        return;
    }
    int dI = dp[l][r].divInd;
    cout << "(";
    getAns(l, l + dI);
    getAns(l + dI + 1, r);
    cout << ")";
    return;
}

int main() {
    // freopen("file.in", "r", stdin);
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    cin >> n;
    H.resize(n); W.resize(n); dp.assign(n, vector<P>(n, P(INF, 0, 0, 0)));
    for (int i = 0; i < n; ++i) {
        cin >> H[i] >> W[i];
    }
    for (int i = 0; i < n; ++i) {
        dp[i][i] = P(0LL, H[i], W[i], -1);
    }
    for (int c = 1; c < n; ++c) {
        for (int i = 0; i < n; ++i) {
            if (i + c >= n) continue;
            P curAns = P(INF, 0LL, 0LL, 0);
            for (int d = 0; d < c; ++d) {
                ll curActs = 0LL;
                curActs = dp[i][i + d].acts + dp[i + d + 1][i + c].acts;
                ll H1 = dp[i][i + d].resH;
                ll W1 = dp[i][i + d].resW, W2 = dp[i + d + 1][i + c].resW;
                curActs += H1 * W1 * W2;
                if (curActs < curAns.acts) {
                    curAns = P(curActs, H1, W2, d);
                }
            }
            dp[i][i + c] = curAns;
        }
    }
    // print2();
    getAns(0, n - 1);
    return 0;
}
