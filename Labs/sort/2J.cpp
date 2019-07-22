#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define uint unsigned int

void print(vector<int> t) {
    for (int a : t)
        cout << a << " ";
    cout << endl;
}

ll ans = 0LL, k;

void get_ans(vector<ll> &a, int l, int m, int r) {
    int t1 = l, t2 = m;
    for (int t = 0; t < r - l; ++t) {
        if (t1 < m && t2 < r) {
            if (a[t1] + k <= a[t2]) {
                t1++;
                ans += t2 - m;
            } else {
                t2++;
            }
            continue;
        }
        if (t1 == m) {
            t2++;
            continue;
        }
        if (t2 == r) {
            t1++;
            ans += t2 - m;
            continue;
        }
    }
}

void merge_(vector<ll> &a, int l, int m, int r) {
    int t1 = l, t2 = m;
    ll* x = new ll[r - l];
    for (int t = 0; t < r - l; ++t) {
        if (t1 < m && t2 < r) {
            if (a[t1] <= a[t2]) {
                x[t] = a[t1];
                t1++;
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
            continue;
        }
    }
    for (int i = l; i < r; ++i) {
        a[i] = x[i - l];
    }
    delete[] x;
}

void my_sort(vector<ll> &a, int l, int r) {
    if (r - l < 2)
        return;
    // cout << r << " " << l << endl;
    int m = (r + l) / 2;
    my_sort(a, l, m);
    my_sort(a, m, r);
    // inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r);
    get_ans(a, l, m , r);
    merge_(a, l, m, r);
}

unsigned int cur = 0, a1, b1;

uint nextRand24() {
    cur = cur * a1 + b1;
    return cur >> 8;
}

uint nextRand32() {
    uint a = nextRand24(), b = nextRand24();
    return (a << 8) ^ b;
}

int main() {
    // freopen("file.in", "r", stdin);
    int n, cnt = 0;
    cin >> n >> k >> a1 >> b1;
    vector<int> a(n);
    vector<ll> pref(n);
    for (int i = 0; i < n; ++i) {
        a[i] = (int)(nextRand32());
        if (i == 0)
            pref[i] = a[i];
        else
            pref[i] = pref[i - 1] + a[i];
        if (pref[i] >= k)
            ++cnt;
    }
    // print(a);
    // print(pref);
    my_sort(pref, 0, n);
    ans = ((ll)n * (n - 1)) / 2 - ans + cnt;
    cout << ans << endl;
    return 0;
}
