#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int

void print(vector<int> t) {
    for (int a : t)
        cout << a << " ";
    cout << endl;
}

int n;
ld eps = 1e-7, a;

ld ok(ld a2) {
    ld a1 = a, x;
    for (int i = 2; i < n; ++i) {
        x = a2 * 2 - a1 + 2.0;
        a1 = a2; a2 = x;
        if (x < eps)
            return -1;
    }
    return a2;
}

int main() {
    // freopen("file.in", "r", stdin);
    cin >> n >> a;
    ld l = -1, r = 1e9, m, b;
    for (int i = 0; i < 1000; ++i) {
        m = (r + l) / 2;
        b = ok(m);
        if (b > 0)
            r = m;
        else
            l = m;
    }
    cout.precision(2);
    cout << fixed << ok(r) << endl;
    return 0;
}
