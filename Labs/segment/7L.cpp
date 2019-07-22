#include <bits/stdc++.h>

using namespace std;
#define ll long long

const ll INF = INT64_MAX;
const size_t SZ = (1 << 17);

vector<vector<uint32_t> > fenw(SZ, vector<uint32_t>());
uint32_t a, b, cur = 0;

uint32_t nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}

uint32_t nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

uint32_t ANS = 0;
uint32_t get_ans(uint32_t ind, uint32_t X, uint32_t Y) {
    uint32_t res = 0;
    for (ptrdiff_t r = ind; r >= 0; r = (r & (r + 1)) - 1) {
        res += (uint32_t)(upper_bound(fenw[r].begin(), fenw[r].end(), Y) -
                lower_bound(fenw[r].begin(), fenw[r].end(), X));
    }
    return res;
}
vector<uint32_t> get_query() {
    uint32_t l, r, x, y;
    l = nextRand17();
    r = nextRand17();
    if (l > r) {
        swap(l, r);
    }
    x = nextRand24();
    y = nextRand24();
    if (x > y) {
        swap(x, y);
    }
    return {l, r, x, y};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    // freopen("file_release.in", "r", stdin);
    uint32_t q, l, r, x, y, cur_ans;
    cin >> q >> a >> b;
    cur = 0;
    vector<uint32_t> f(SZ);
    for (size_t i = 0; i < SZ; ++i) {
        f[i] = nextRand24();
    }
    /*size_t n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> f[i];
    }*/
    for (size_t i = 0; i < SZ; ++i) {
        for (size_t j = i; j < SZ; j = (j | (j + 1))) {
            fenw[j].push_back(f[i]);
        }
    }
    for (size_t i = 0; i < SZ; ++i) {
        sort(fenw[i].begin(), fenw[i].end());
    }
    for (uint32_t k = 0; k < q; ++k) {
        auto p = get_query();
        l = p[0]; r = p[1]; x = p[2]; y = p[3];
        // cin >> l >> r >> x >> y;
        cur_ans = get_ans(r, x, y);
        if (l > 0) {
            cur_ans -= get_ans(l - 1, x, y);
        }
        // cout << cur_ans << "\n";
        ANS += cur_ans;
        b += cur_ans;
    }
    cout << ANS << endl;
    return 0;
}
