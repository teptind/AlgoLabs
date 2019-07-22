#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

void print(vector<pair<int, int> > t) {
    cout << t.size() << "\n";
    for (pair<int, int> a : t)
        cout << a.first + 1 << " " << a.second + 1 << "\n";
    cout << endl;
}

vector<pair<int, int> > comp;
vector<int> a;
bool bad = false;

bool sorted(int l, int r) {
    for (int i = l + 1; i < r; ++i) {
        if (a[i - 1] > a[i])
            return false;
    }
    return true;
}

void solve(int l, int r) {
    if (r - l <= 2)
        return;
    bool sortedSuff = sorted(l + 1, r), sortedPref = sorted(l, r - 1);
    // cout << l << " " << r << " " << sortedSuff << " " << sortedPref << endl;
    if (sortedSuff && sortedPref) {
        bad = true;
        return;
    }

    if ((!sortedPref) && a[r - 1] == 1) {
        solve(l, r - 1);
        for (int i = l; i < r - 1; ++i)
            comp.push_back({i, r - 1});
        return;
    }
    if (!(sortedPref) && a[r - 1] == 0) {
        solve(l, r - 1);
        for (int i = r - 1; i > l; --i)
            comp.push_back({i - 1, i});
        return;
    }

    if (!(sortedSuff) && a[l] == 1) {
        solve(l + 1, r);
        for (int i = l; i < r - 1; ++i)
            comp.push_back({i, i + 1});
        return;
    }
    if (!(sortedSuff) && a[l] == 0) {
        solve(l + 1, r);
        for (int i = r - 1; i > l; --i)
            comp.push_back({l, i});
        return;
    }
}


int main() {
    // freopen("file.in", "r", stdin);
    int n = 1;
    while (true) {
        cin >> n;
        bad = false;
        if (n == 0)
            return 0;
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        if (sorted(0, n)) {
            cout << -1 << endl;
            continue;
        }
        comp.clear();
        solve(0, n);
        print(comp);
    }
    return 0;
}
