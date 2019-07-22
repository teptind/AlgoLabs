#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int

void print(vector<string> t) {
    for (string a : t)
        cout << a << "\n";
    cout << endl;
}

void merge_(vector<ll> &a, int l, int m, int r) {
    int t1 = l, t2 = m;
    // ll* x = new ll[r - l];
    vector<ll> x(r - l);
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
    x.clear();
}

void my_sort(vector<ll> &a, int l, int r) {
    if (r - l < 2)
        return;
    // cout << r << " " << l << endl;
    int m = (r + l) / 2;
    my_sort(a, l, m);
    my_sort(a, m, r);
    // inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r);
    merge_(a, l, m, r);
}


bool ok(ll &mid, vector<int> &a, vector<int> &b, vector<int> &t, int &n, int &p) {
    int sz = (int)a.size();
    vector<ll> ch(sz);
    for (int i = 0; i < sz; ++i) {
        if (mid - t[i] - b[i] < 0) {
            ch[i] = 0;
            continue;
        }
        if (a[i] == 0)
            ch[i] = p;
        else
            ch[i] = (mid - t[i] - b[i]) / a[i];
    }
    my_sort(ch, 0, sz);
    ll x = 0LL;
    for (int i = 1; i <= n; ++i) {
        if (sz - i >= 0)
            x += ch[sz - i];
    }
    if (x >= p)
        return true;
    return false;
}


int main() {
    // freopen("file.in", "r", stdin);
    int m, n, p;
    cin >> m;
    vector<int> a(m);
    vector<int> b(m);
    vector<int> t(m);
    for (int i = 0; i < m; ++i)
        cin >> a[i] >> b[i] >> t[i];
    cin >> n >> p;
    ll l = -1, r = 5e9, mid;
    while (r - l > 1) {
        mid = (r + l) / 2;
        if (ok(mid, a, b, t, n, p))
            r = mid;
        else
            l = mid;
    }
    cout << r << endl;
    return 0;
    // 9133
}
