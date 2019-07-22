#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long


void print(vector<string> &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        cout << t[i] << "\n";
    cout << "\n";
}

/*void print2(vector<vector<int > > &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        print(t[i]);
    cout << "\n";
}*/

ll dp[2000][2000];
ll INF = 2e18;
int cut[2000][2000];
vector<ll> pref;
ll getW(int l, int r) {
    ll ans = pref[r];
    if (l > 0)
        ans -= pref[l - 1];
    return ans;
}

vector<string> code;
string curr = "";
void dfs(int i, int j) {
    // cout << "from " << i << " " << j << endl;
    // cout << curr << endl;
    if (i == j) {
        code[i] = curr;
        return;
    }
    int m = cut[i][j];
    curr.push_back('0');
    dfs(i, m);
    curr.pop_back(); curr.push_back('1');
    dfs(m + 1, j);
    curr.pop_back();
    return;
}

int main() {
    // freopen("file.in", "r", stdin);
    freopen("optimalcode.in", "r", stdin);
    freopen("optimalcode.out", "w", stdout);
    int n; cin >> n;
    code.resize(n);
    vector<ll> f(n);
    pref.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> f[i];
        if (i == 0)
            pref[i] = f[i];
        else
            pref[i] = pref[i - 1] + f[i];
    }
    for (int c = 0; c < n; ++c) {
        for (int i = 0; i + c < n; ++i) {
            if (c == 0) {
                dp[i][i + c] = 0LL;
                cut[i][i + c] = i;
            } else {
                dp[i][i + c] = INF;
                cut[i][i + c] = -1;
            }
        }
    }
    int j, l, r;
    for (int c = 1; c < n; ++c) {
        for (int i = 0; i + c < n; ++i) {
            j = i + c;
            l = cut[i][j - 1];
            r = cut[i + 1][j];
            ll currMin = INF, curr;
            int indMin = l;
            for (int k = l; k < min(r + 1, j); ++k) {
                curr = (dp[i][k] + dp[k + 1][j]);
                if (currMin >= curr) {
                    indMin = k;
                    currMin = curr;
                }
            }
            dp[i][j] = currMin + getW(i, j);
            cut[i][j] = indMin;
        }
    }
    dfs(0, n - 1);
    ll ans = 0LL;
    for (int i = 0; i < n; ++i) {
        ans += (ll)f[i] * (int)code[i].size();
    }
    cout << ans << endl;
    print(code);
    return 0;
}
