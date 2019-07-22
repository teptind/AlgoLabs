#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

void print(vector<int> &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        cout << t[i] << " ";
    cout << "\n";
}

void print2(vector<vector<int> > &t, int n) {
    cout << n << " " << t.size() << endl;
    for (int i = 0; i < (int)t.size(); ++i)
        print(t[i]);
    cout << "\n";
}

int INF = 2e9;

int main() {
    // freopen("file.in", "r", stdin);
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> e(n + 1, INF);
    vector<int> eplace(n + 1, -1);
    vector<int> prev(n, -1);
    vector<int> ans;
    e[0] = -INF;
    eplace[0] = -1;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) {
        // print(e);
        int c = (int)(lower_bound(e.begin(), e.end(), a[i]) - e.begin()) - 1;
        // cout << a[i] << " " << c << endl;
        if (a[i] < e[c + 1]) {
            e[c + 1] = a[i];
            eplace[c + 1] = i;
            prev[i] = eplace[c];
        }
    }
    // print(e);
    // print(eplace);
    int mx = 0;
    for (int i = 1; i < n + 1; ++i) {
        if (e[i] != INF)
            mx = eplace[i];
    }
    // print(prev);
    int p = mx;
    // cout << p << endl;
    while (p != -1) {
        ans.push_back(a[p]);
        p = prev[p];
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    print(ans);
    return 0;
}
