#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define uint unsigned int

void print(vector<int> t) {
    for (int a : t)
        cout << a << " ";
    cout << endl;
}

vector<int> a;
int n;

int kth(int k, int l, int r) {
    // cout << "need " << k << "th in l = " << l << " r = " << r << " for ";
    // print(a);
    if (r - l == 1)
        return a[l];
    int m = a[l + (int)(rand() % (r - l))];
    // cout << "m = " << m << endl;
    int t = l, less_ = 0, eq = 0;
    for (int i = l; i < r; ++i) {
        if (a[i] < m) {
            swap(a[i], a[t]);
            t++; less_++;
        }
    }
    for (int i = l; i < r; ++i) {
        if (a[i] == m) {
            swap(a[i], a[t]);
            t++; eq++;
        }
    }
    // cout << "t was " << t << endl << endl;
    if (k > less_ + eq) {
        return kth(k - (less_ + eq), t, r);
    }
    if (k > less_)
        return m;
    return kth(k, l, l + less_);
}

int get_next(int A, int B, int C, int a2, int a1) {
    return A * a2 + B * a1 + C;
}


int main() {
    // freopen("file.in", "r", stdin);
    srand((uint)(time(nullptr)));
    ios_base::sync_with_stdio(0);
    int k, A, B, C, a1, a2;
    cin >> n >> k >> A >> B >> C >> a1 >> a2;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        if (i == 0)
            a[i] = a1;
        if (i == 1)
            a[i] = a2;
        if (i > 1)
            a[i] = get_next(A, B, C, a[i - 2], a[i - 1]);
    }
    cout << kth(k, 0, n) << endl;
    return 0;
}
