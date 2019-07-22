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

ll MOD = 999999937LL;
vector<vector<ll> > m0(5, vector<ll>(5));
vector<vector<ll> > curr(5, vector<ll>(5));
vector<vector<ll> > powN(5, vector<ll>(5));
vector<vector<ll> > E(5, vector<ll>(5));

vector<vector<ll> > multiply(vector<vector<ll> > &A, vector<vector<ll> > &B) {
    int x = (int)A.size(), y = (int)B[0].size(), z = (int)B.size();
    vector<vector<ll> > res(x, vector<ll>(y, 0LL));
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                res[i][j] = (res[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
            }
        }
    }
    return res;
}

vector<vector<ll> > makePow(ll n) {
    vector<vector<ll> > res;
    if (n == 0)
        return E;
    if (n % 2 == 0) {
        curr = makePow(n / 2);
        res = multiply(curr, curr);
    } else {
        curr = makePow(n - 1);
        res = multiply(curr, m0);
    }
    return res;
}

int main() {
    // freopen("file.in", "r", stdin);
    freopen("sequences.in", "r", stdin);
    freopen("sequences.out", "w", stdout);
    ll n = -1LL;
    while (n != 0LL) {
        cin >> n;
        // cout << "n = " << n << endl;
        if (n == 0LL)
            break;
        m0[0] = {1LL, 1LL, 1LL, 1LL, 1LL};
        m0[1] = {1LL, 1LL, 1LL, 1LL, 1LL};
        m0[2] = {1LL, 1LL, 1LL, 1LL, 1LL};
        m0[3] = {1LL, 1LL, 0LL, 1LL, 0LL};
        m0[4] = {1LL, 1LL, 0LL, 1LL, 0LL};

        E[0] = {1LL, 0LL, 0LL, 0LL, 0LL};
        E[1] = {0LL, 1LL, 0LL, 0LL, 0LL};
        E[2] = {0LL, 0LL, 1LL, 0LL, 0LL};
        E[3] = {0LL, 0LL, 0LL, 1LL, 0LL};
        E[4] = {0LL, 0LL, 0LL, 0LL, 1LL};
        vector<vector<ll> > st = {{1LL}, {1LL}, {1LL}, {1LL}, {1LL}};
        vector<vector<ll> > powN = makePow(n - 1);
        vector<vector<ll> > ans = multiply(powN, st);
        // print2(powN);
        ll sum = 0LL;
        // cout << "done\n";
        // print2(st);
        for (int i = 0; i < 5; ++i) {
            sum = (sum + ans[i][0]) % MOD;
        }
        cout << sum << endl;
    }
    return 0;
}
