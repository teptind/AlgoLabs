#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int INF = (int)(2e9);

struct rect {
    // (x1, y1) - left lower
    // (x2, y2) - right upper
    int x1, y1, x2, y2;
    rect() = default;
    rect(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    ll square() {
        return ((ll)x2 - x1) * ((ll)y2 - y1);
    }
    void print() {
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    }
};

bool no_intersection(rect &P1, rect &P2) {
    bool ans = (P1.x1 > P2.x2 ||
                P2.x1 > P1.x2 ||
                P1.y1 > P2.y2 ||
                P2.y1 > P1.y2);
    return ans;
}

rect intersect(rect &P1, rect &P2) {
    if (no_intersection(P1, P2)) {
        return {INF, INF, INF, INF};
    }
    return {max(P1.x1, P2.x1), max(P1.y1, P2.y1), min(P1.x2, P2.x2), min(P1.y2, P2.y2)};
}

struct Sparse {
    vector<vector<vector<vector<rect> > > > dp;
    vector<int> twos_power;
    explicit Sparse(vector<vector<rect> > &a) {
        dp.resize(9, vector<vector<vector<rect> > >
                (9, vector<vector<rect> >(129, vector<rect>(129, {INF, INF, INF, INF}))));
        size_t N = a.size() + 2;
        size_t M = a[0].size() + 2;
        size_t mNM = max(N, M);
        twos_power.resize(mNM + 5);
        for (size_t i = 1; i < mNM + 5; ++i) {
            twos_power[i] = (int)(floor(log2(i)));
        }
        auto logn = (size_t)(ceil(log2((double)(N + 1)))) + 1;
        auto logm = (size_t)(ceil(log2((double)(M + 1)))) + 1;
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < a[0].size(); ++j) {
                dp[0][0][i][j] = a[i][j];
            }
            for (size_t Lj = 1; Lj < logm; ++Lj) {
                for (size_t j = 0; j < M; ++j) {
                    if (j + (1 << (Lj - 1)) < M) {
                        dp[0][Lj][i][j] =
                                intersect(dp[0][Lj - 1][i][j],
                                          dp[0][Lj - 1][i][j + (1 << (Lj - 1))]);
                    }
                }
            }
        }

        for (size_t Li = 1; Li < logn; ++Li) {
            for (size_t i = 0; i < N; ++i) {
                for (size_t Lj = 0; Lj < logm; ++Lj) {
                    for (size_t j = 0; j < M; ++j) {
                        if (i + (1 << (Li - 1)) < N) {
                            dp[Li][Lj][i][j] =
                                    intersect(dp[Li - 1][Lj][i][j],
                                              dp[Li - 1][Lj][i + (1 << (Li - 1))][j]);
                        }
                    }
                }
            }
        }
    }
    ll ask_square(int r1, int c1, int r2, int c2) {
        if (r1 > r2) {
            swap(r1, r2);
        }
        if (c1 > c2) {
            swap(c1, c2);
        }
        // cout << "zapros: " << r1 << " " << c1 << " " << r2 << " " << c2 << "\n";
        int k1 = twos_power[r2 - r1 + 1];
        int k2 = twos_power[c2 - c1 + 1];
        rect ans1 = dp[k1][k2][r1][c1];
        rect ans2 = dp[k1][k2][r2 - (1 << k1) + 1][c1];
        rect ans3 = dp[k1][k2][r1][c2 - (1 << k2) + 1];
        rect ans4 = dp[k1][k2][r2 - (1 << k1) + 1][c2 - (1 << k2) + 1];
        rect ans12 = intersect(ans1, ans2);
        rect ans34 = intersect(ans3, ans4);
        rect ans = intersect(ans12, ans34);
        // ans.print();
        return ans.square();
    }
};

ll A, B, V0;
const ll MOD = (ll)(1e9 + 7);
void nextV() {
    V0 = (A * V0 + B) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    // freopen("file.in", "r", stdin);
    size_t n, m;
    cin >> n >> m;
    int x1, y1, x2, y2;
    vector<vector<rect> > Table;
    Table.resize(n);
    for (size_t i = 0; i < n; ++i) {
        Table[i].resize(m);
        for (size_t j = 0; j < m; ++j) {
            cin >> x1 >> y1 >> x2 >> y2;
            if (y1 > y2) {
                swap(y1, y2);
            }
            if (x1 > x2) {
                swap(x1, x2);
            }
            Table[i][j] = rect(x1, y1, x2, y2);
        }
    }
    Sparse sparse(Table);
    int Q;
    cin >> Q;
    cin >> A >> B >> V0;
    ll ANS = 0LL;
    /*for (int r1 = 0; r1 < n; ++r1) {
        for (int c1 = 0; c1 < m; ++c1) {
            for (int r2 = 0; r2 < n; ++r2) {
                for (int c2 = 0; c2 < m; ++c2) {
                    cout << "square: " << " " << sparse.ask_square(r1, c1, r2, c2) << "\n\n";
                }
            }
        }
    }*/
    for (int i = 0; i < Q; ++i) {
        int r1, c1, r2, c2;
        nextV();
        r1 =(int)(V0 % n);
        nextV();
        c1 =(int)(V0 % m);
        nextV();
        r2 =(int)(V0 % n);
        nextV();
        c2 =(int)(V0 % m);
        // cin >> r1 >> c1 >> r2 >> c2;
        ANS = (ANS + sparse.ask_square(r1, c1, r2, c2)) % MOD;
    }
    cout << ANS << endl;
    return 0;
}
