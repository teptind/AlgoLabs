#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

int shift = 0;

struct Dsu {
    pair<int, int>* p;
    int* sz;
    Dsu() {}
    Dsu(int n) {
        p = new pair<int, int>[n];
        sz = new int[n];
        for (int i = 0; i < n; ++i) {
            p[i] = {i, 0};
            sz[i] = 1;
        }
    }
    pair<int, int> get_(int x) {
        if (x != p[x].first) {
            int way = p[x].second;
            p[x] = get_(p[x].first);
            p[x].second = (p[x].second + way) % 2;
        }
        return p[x];
    }

    void join(int x, int y) {
        pair<int, int> ux = get_(x); x = ux.first; int wx = ux.second;
        pair<int, int> uy = get_(y); y = uy.first; int wy = uy.second;
        if (x == y) return;
        if (sz[y] < sz[x])
           swap(x, y);
        p[x] = {y, wx ^ wy ^ 1};
        sz[y] += sz[x];
    }
    bool get_ans(int x, int y) {
        pair<int, int> ux = get_(x); x = ux.first; int wx = ux.second;
        pair<int, int> uy = get_(y); y = uy.first; int wy = uy.second;
        return (wx == wy);
    }
};

int main() {
    // freopen("file.in", "r", stdin);
    // freopen("restructure.in", "r", stdin);
    // freopen("restructure.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie();
    int n, q, type, a, b;
    cin >> n >> q;
    string s;
    Dsu dsu = Dsu(n);
    for (int i = 0; i < q; ++i) {
        cin >> type >> a >> b; a--; b--;
        a = (a + shift) % n; b = (b + shift) % n;
        if (type == 0) {
            dsu.join(a, b);
        }
        if (type == 1) {
            if (dsu.get_ans(a, b)) {
                s += "YES\n";
                shift++;
            }
            else
                s += "NO\n";
        }
    }
    cout << s << endl;
    return 0;
}
