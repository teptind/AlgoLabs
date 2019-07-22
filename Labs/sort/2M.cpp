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

vector<pair<int, int> > comp;
vector<int> bt;

int n, m, k;

bool ok() {
    for (pair<int, int> p : comp) {
        if (bt[p.first] > bt[p.second])
            swap(bt[p.first], bt[p.second]);
    }
    for (int i = 1; i < n; ++i) {
        if (bt[i - 1] > bt[i])
            return false;
    }
    return true;
}

int main() {
    // freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    comp.clear();
    bt.clear();
    int r, a, b;
    cin >> n >> m >> k;
    for (int i = 0; i < k; ++i) {
        cin >> r;
        for (int j = 0; j < r; ++j) {
            cin >> a >> b; a--; b--;
            comp.push_back({min(a, b), max(a, b)});
        }
    }
    int sz = (1 << n);
    bt.resize(n);
    for (int c = 0; c < sz; ++c) {
        for (int i = n - 1; i > -1; --i) {
            if ((c & (1 << i)) == 0)
                bt[n - 1 - i] = 0;
            else
                bt[n - 1 - i] = 1;
        }
        // print(bt);
        if (!ok()) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}
