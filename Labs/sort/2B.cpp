#include <bits/stdc++.h>

using namespace std;
#define ll long long

void print(vector<int> t) {
    for (int a : t)
        cout << a << " ";
    cout << endl;
}

int findR(vector<int> &a, int k) {
    int l = 0, r = (int)a.size(), m;
    while (r - l > 1) {
        m = (r + l) / 2;
        if (a[m] <= k)
            l = m;
        else
            r = m;
    }
    if (a[l] == k)
        return l + 1;
    else
        return -1;
}

int findL(vector<int> &a, int k) {
    int l = -1, r = (int)(a.size() - 1), m;
    while (r - l > 1) {
        m = (r + l) / 2;
        if (a[m] < k)
            l = m;
        else
            r = m;
    }
    if (a[r] == k)
        return r + 1;
    else
        return -1;
}

int main() {
    // freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    int n, m, y;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> y;
        cout << findL(a, y) << " " << findR(a, y) << endl;
    }
    return 0;
}
