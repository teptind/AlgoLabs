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
}

vector<int> sz;
vector<int> p;

int get_(int x) {
    if (x != p[x])
        x = get_(p[x]);
    return x;
}

void join(int x, int y) {
    x = get_(x);
    y = get_(y);
    if (x == y) return;
    if (sz[y] < sz[x])
        swap(x, y);
    p[x] = y;
    sz[y] += sz[x];
}

int main() {
    // freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    int g1, g2, g3, k;
    int n, a, b;
    cin >> n >> g2 >> k;
    for (int i = 0; i < g2; ++i)
        cin >> g1 >> g3;
    sz.resize(n + 1);
    p.resize(n + 1);
    vector<tuple<string, int, int> > acts;
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
        sz[i] = 1;
    }
    string act;
    while (cin >> act) {
        cin >> a >> b;
        acts.push_back(make_tuple(act, a, b));
    }
    reverse(acts.begin(), acts.end());
    vector<string> ans;
    for (int i = 0; i < k; ++i) {
        act = get<0>(acts[i]);
        a = get<1>(acts[i]);
        b = get<2>(acts[i]);
        if (act == "ask") {
            if (get_(a) == get_(b))
                ans.push_back("YES");
            else
                ans.push_back("NO");
        }
        if (act == "cut") {
            join(a, b);
        }
    }
    reverse(ans.begin(), ans.end());
    print(ans);
    return 0;
}
