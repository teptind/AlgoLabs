#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

void print(vector<string> t) {
    for (string a : t)
        cout << a << "\n";
    cout << endl;
}

unsigned int cur = 0, a1, b1;

uint nextRand24() {
    cur = cur * a1 + b1;
    return cur >> 8;
}

uint nextRand32() {
    uint a = nextRand24(), b = nextRand24();
    return (a << 8) ^ b;
}

int pp[100001][2];
int curr[100001][2];

const int C = 65536;

int cnt[C];
int place[C];


int main() {
    // freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t, n;
    ll x;
    cin >> t >> n;
    for (int tt = 0; tt < t; ++tt) {
        // cur = 0;
        cin >> a1 >> b1;
        for (int i = 0; i < n; ++i) {
            x = nextRand32();
            pp[i][0] = x & 0x0000ffff;
            pp[i][1] = (x & 0xffff0000) >> 16;
        }
        for (int k = 0; k < 2; ++k) {
            for (int i = 0; i < C; ++i)
                cnt[i] = 0;
            for (int i = 0; i < n; ++i) {
                cnt[pp[i][k]]++;
            }
            place[0] = 0;
            for (int i = 1; i < C; ++i) {
                place[i] = place[i - 1] + cnt[i - 1];
            }
            for (int i = 0; i < n; ++i) {
                curr[place[pp[i][k]]][0] = pp[i][0];
                curr[place[pp[i][k]]][1] = pp[i][1];
                place[pp[i][k]]++;
            }
            for (int i = 0; i < n; ++i) {
                pp[i][0] = curr[i][0];
                pp[i][1] = curr[i][1];
            }
        }
        ull ans = 0LL;
        for (int i = 0; i < n; ++i) {
            // cout << pp[i][1] << " " << pp[i][0] << " ";
            // cout << (((ll)pp[i][1] << 16) + pp[i][0]) << endl;
            ans += (ull)(((ll)pp[i][1] << 16) + pp[i][0]) * (i + 1);
        }
        cout << ans << "\n";
    }
    return 0;
}
