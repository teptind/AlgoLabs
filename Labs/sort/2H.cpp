#include <bits/stdc++.h>

using namespace std;
#define ll long long

void print(vector<int> t) {
    for (int a : t)
        cout << a << " ";
    cout << endl;
}

ll ans = 0LL;

void merge_(vector<int> &a, int l, int m, int r) {
    int t1 = l, t2 = m;
    int* x = new int[r - l];
    for (int t = 0; t < r - l; ++t) {
        if (t1 < m && t2 < r) {
            if (a[t1] <= a[t2]) {
                x[t] = a[t1];
                t1++;
                ans += t2 - m;
            } else {
                x[t] = a[t2];
                t2++;
            }
            continue;
        }
        if (t1 == m) {
            x[t] = a[t2];
            t2++;
            continue;
        }
        if (t2 == r) {
            x[t] = a[t1];
            t1++;
            ans += t2 - m;
            continue;
        }
    }
    for (int i = l; i < r; ++i) {
        a[i] = x[i - l];
    }
}

vector<int> a;

void my_sort(int l, int r) {
    if (r - l < 2)
        return;
    // cout << r << " " << l << endl;
    int m = (r + l) / 2;
    my_sort(l, m);
    my_sort(m, r);
    // inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r);
    merge_(a, l, m, r);
}

unsigned int cur = 0, a1, b1, mod;

unsigned int nextRand24() {
    cur = cur * a1 + b1;
    return cur >> 8;
}

int main() {
    // freopen("file.in", "r", stdin);
    int n;
    cin >> n >> mod >> a1 >> b1;
    a.resize(n);
    for (int i = 0; i < n; ++i)
        a[i] = (int)(nextRand24() % mod);
    // print(a);
    my_sort(0, n);
    // print(a);
    cout << ans << endl;
    return 0;
}
