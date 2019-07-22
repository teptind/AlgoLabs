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

int main() {
    // freopen("file.in", "r", stdin);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    cin >> a[1];
    for (int i = 2; i <= n; ++i) {
        cin >> a[i];
        if (a[i] < a[i / 2]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}
