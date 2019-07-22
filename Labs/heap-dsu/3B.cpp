#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

void print(vector<int> t) {
    for (int a : t)
        cout << a << " ";
    cout << endl;
}

vector<int> sz;
vector<int> mn;
vector<int> mx;
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
    mn[y] = min(mn[x], mn[y]);
    mx[y] = max(mx[x], mx[y]);
}

int main() {
    // freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    int n, a, b;
    cin >> n;
    sz.resize(n + 1);
    mn.resize(n + 1);
    mx.resize(n + 1);
    p.resize(n + 1);
    string act;
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
        mn[i] = i; mx[i] = i; sz[i] = 1;
    }
    while (cin >> act) {
        if (act == "union") {
            cin >> a >> b;
            join(a, b);
            /*cout << "united " << a << " " << b << ":\n";
            print(p);
            print(mn);
            print(mx);
            print(sz);*/
        }
        if (act == "get") {
            cin >> a;
            a = get_(a);
            cout << mn[a] << " " << mx[a] << " " << sz[a] << "\n";
        }
    }
    return 0;
}
