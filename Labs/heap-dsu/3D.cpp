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

int p[300001];
int sz[300001];
int emp[300001];

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

int main() {
    // freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, c;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        p[i] = i; sz[i] = 1; emp[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        cin >> c; c--;
        c = emp[get_(c)];
        cout << c + 1 << " ";
        join(c, (c + 1) % n);
    }
    cout << endl;
    return 0;
}
