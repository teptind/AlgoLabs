#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define ld double
#define uint unsigned int

void print(vector<int> t) {
    for (int a : t)
        cout << a << " ";
    cout << endl;
}

pair<ld, int> curr[100001];

void merge_(int l, int m, int r) {
    int t1 = l, t2 = m;
    pair<ld, int>* x = new pair<ld, int>[r - l];
    for (int t = 0; t < r - l; ++t) {
        if (t1 < m && t2 < r) {
            if (curr[t1] <= curr[t2]) {
                x[t] = curr[t1];
                t1++;
            } else {
                x[t] = curr[t2];
                t2++;
            }
            continue;
        }
        if (t1 == m) {
            x[t] = curr[t2];
            t2++;
            continue;
        }
        if (t2 == r) {
            x[t] = curr[t1];
            t1++;
            continue;
        }
    }
    for (int i = l; i < r; ++i) {
        curr[i] = x[i - l];
    }
    delete[] x;
}

void my_sort(int l, int r) {
    if (r - l < 2)
        return;
    // cout << r << " " << l << endl;
    int m = (r + l) / 2;
    my_sort(l, m);
    my_sort(m, r);
    // inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r);
    merge_(l, m, r);
}

int n, k;
int v[100001];
int w[100001];

bool ok(ld x) {
    for (int i = 0; i < n; ++i)
        curr[i] = {(ld)v[i] - (ld)w[i] * x, i};
    my_sort(0, n);
    // sort(curr, curr + n);
    ld s = 0.0;
    for (int i = n - 1; i >= n - k; --i)
        s += curr[i].first;
    if (s >= 0)
        return true;
    else
        return false;
}

void fill_ans(ld x) {
    for (int i = 0; i < n; ++i)
        curr[i] = {(ld)v[i] - (ld)w[i] * x, i};
    my_sort(0, n);
    // sort(curr, curr + n);
    for (int i = 0; i < k; ++i)
        cout << curr[n - 1 - i].second + 1 << " ";
    cout << endl;
}

int main() {
    // freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> v[i] >> w[i];
    }
    ld l = -0.0001, r = 1e7 + 100, mid;
    for (int i = 0; i < 64; ++i) {
        mid = (r + l) / 2;
        if (ok(mid))
            l = mid;
        else
            r = mid;
    }
    fill_ans(l);
    return 0;
}
