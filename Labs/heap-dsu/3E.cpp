#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

struct dsu {
    int* p;
    int* sz;
    int* emp;
    dsu() {}
    dsu(int n) {
        p = new int[n];
        sz = new int[n];
        emp = new int[n + 1];
        for (int i = 0; i < n; ++i) {
            p[i] = i;
            sz[i] = 1;
            emp[i] = i;
        }
    }
    int get_(int x) {
        if (x != p[x])
            x = get_(p[x]);
        return x;
    }

    void join(int x, int y) {
        x = get_(x);
        y = get_(y);
        emp[x] = emp[y];
        if (x == y) return;
        if (sz[y] < sz[x])
           swap(x, y);
        p[x] = y;
        sz[y] += sz[x];
    }
};

int main() {
    // freopen("file.in", "r", stdin);
    freopen("restructure.in", "r", stdin);
    freopen("restructure.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie();
    int n, q, type, a, b;
    cin >> n >> q;
    string s;
    dsu place = dsu(n);
    dsu ans = dsu(n);
    for (int i = 0; i < q; ++i) {
        cin >> type >> a >> b; a--; b--;
        if (type == 1) {
            ans.join(a, b);
        }
        if (type == 2) {
            int i = a;
            while (i < b) {
                ans.join(i, b);
                int j = place.emp[place.get_(i)] + 1;
                place.join(i, b);
                i = j;
            }
        }
        if (type == 3) {
            if (ans.get_(a) == ans.get_(b))
                s += "YES\n";
            else
                s += "NO\n";
        }
    }
    cout << s << endl;
    return 0;
}
