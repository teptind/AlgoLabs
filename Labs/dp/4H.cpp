#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

ll dp[1 << 16][16];
ll gcd[16][16];
ll a[16];
ll K, m;
ll INF = 2e18;
int shifts[16];
int MASKS, n;


void print(vector<ll> &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        cout << t[i] << " ";
    cout << "\n";
}

/*void printA(vector<int> &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        cout << a[t[i]] << " ";
    cout << "\n";
}

void print2(vector<vector<int > > &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        print(t[i]);
    cout << "\n";
}*/

ll getGcd(ll a, ll b) {
    return b ? getGcd(b, a % b) : a;
}

void fillGcd() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            gcd[i][j] = getGcd(a[i], a[j]);
}

void printGcd() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            cout << "a[" << i << "]=" << a[i] << " " << "a[";
            cout << j << "]=" << a[j] << " gcd=" << gcd[i][j] << endl;
        }
}

void fillDp() {
    shifts[0] = 1;
    for (int i = 1; i < 16; ++i)
        shifts[i] = shifts[i - 1] * 2;

    MASKS = (1 << n);
    for (int mask = 0; mask < MASKS; ++mask) {
        for (int i = 0; i < n; ++i) {
            dp[mask][i] = 0LL;
        }
    }
    dp[0][0] = 1LL;

    for (int mask = 0; mask < MASKS; ++mask) {
        for (int i = 0; i < n; ++i) {
            if (dp[mask][i] == 0LL)
                continue;
            for (int v = 0; v < n; ++v) {
                if ((mask & shifts[v]) != 0)
                    continue;
                int nMask = (mask ^ shifts[v]);
                if (mask == 0 || gcd[i][v] >= K) {
                    dp[nMask][v] += dp[mask][i];
                }
            }
        }
    }
}

void printDp() {
    for (int mask = 0; mask < MASKS; ++mask) {
        for (int i = 0; i < n; ++i) {
            cout << "dp[";
            for (int c = n - 1; c >= 0; --c)
                cout << ((mask & shifts[c]) != 0);
            cout << "][" << i << "](a[" << i << "]=" << a[i] << ") = " << dp[mask][i] << endl;
        }
    }
}

int main() {
    // freopen("file.in", "r", stdin);
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
    cin >> n >> m >> K;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    fillGcd();
    // printGcd();
    fillDp();
    // printDp();

    int currMask = 0, last = -1, canMask;
    ll currNum = m - 1;
    vector<ll> ans;

    for (int z = 0; z < n; ++z) {
        ll skipped = 0LL, cnt = 0;
        int nw = -1;
        canMask = (currMask ^ (MASKS - 1));
        vector<int> unused = {};
        for (int i = 0; i < n; ++i) {
            if ((currMask & (shifts[i])) == 0) unused.push_back(i);
        }

        // cout << "unused: ";
        // printA(unused);

        for (int x : unused) {
            if (last == -1 || gcd[last][x] >= K) {
                cnt = dp[canMask][x];
                // cout << "dp[unused][" << x << "](a[" << x << "]="
                // << a[x] << ") = " << dp[canMask][x] << endl;
                if (cnt == 0)
                    continue;
                if (skipped + cnt <= currNum) {
                    skipped += cnt;
                } else {
                    nw = x;
                    break;
                }
            }
        }
        if (nw == -1) {
            cout << "-1\n";
            return 0;
        }
        currNum -= skipped;
        ans.push_back(a[nw]);
        last = nw;
        currMask ^= shifts[nw];
    }
    print(ans);
    return 0;
}
