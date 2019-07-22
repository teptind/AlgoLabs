#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

int main() {
    // freopen("file.in", "r", stdin);
    // freopen("restructure.in", "r", stdin);
    // freopen("restructure.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie();
    int n, m;
    cin >> n >> m;
    if (m == 1) {
        cout << "0 1 1\n";
        return 0;
    }
    if (m == 2) {
        cout << "1 1 2\n0 1 2\n";
        return 0;
    }
    if (m == 3) {
        cout << "1 1 2\n1 1 3\n0 2 3\n";
        return 0;
    }
    int root = 3; int i = 2;
    cout << "1 3 1\n1 3 2\n";
    while (i < m) {
        cout << "1 " << root + 1 << " " << root << endl;
        i++;
        int j = 1;
        while (j < root - 1) {
            if (i == m)
                return 0;
            cout << "0 " << j << " " << j + 1 << endl;
            j += 2; i++;
        }
        root++;
    }
    return 0;
}
