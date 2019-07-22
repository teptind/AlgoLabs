#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define uint unsigned int

uint n = (1 << 24);
uint delta[1 << 24];

uint a, b;
unsigned int cur = 0;
uint nextRand() {
     cur = cur * a + b;
     return cur >> 8;
}


int main() {
    // freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie();
    int m, q;
    cin >> m >> q >> a >> b;
    for (int i = 0; i < m; ++i) {
        uint add = nextRand();
        uint l = nextRand();
        uint r = nextRand();
        if (l > r) {
            swap(l, r);
        }

        delta[l] += add;
        if (r < n - 1) {
            delta[r + 1] -= add;
        }
        // cout << "add " << x[0] << " " << x[1] << " " << x[2] << "\n";
    }

    for (size_t i = 1; i < n; ++i) {
        delta[i] = delta[i - 1] + delta[i];
    }
    for (size_t i = 1; i < n; ++i) {
        delta[i] = delta[i - 1] + delta[i];
    }

    uint ans = 0;
    for (int i = 0; i < q; ++i) {
        uint l = nextRand();
        uint r = nextRand();
        if (l > r) {
            swap(l, r);
        }

        ans += delta[r];
        if (l > 0) {
            ans -= delta[l - 1];
        }
        // cout << "sum " << x[0] << " " << x[1] << " " << cur << "\n";
    }
    cout << ans << "\n";
    return 0;
}
