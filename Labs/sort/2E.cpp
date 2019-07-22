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


int main() {
    // freopen("file.in", "r", stdin);
    int n, m, k;
    vector<string> ans;
    vector<string> curr;
    vector<vector<int> > ind(26);
    cin >> n >> m >> k;
    ans.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> ans[i];
    // print(ans);
    for (int g = 1; g <= k; ++g) {
        ind.clear();
        ind.resize(26);
        curr.clear();
        curr.resize(n);
        for (int i = 0; i < n; ++i) {
            ind[(int)(ans[i][m - g] - 'a')].push_back(i);
        }
        int t = 0;
        for (int i = 0; i < 26; ++i) {
            for (int j : ind[i]) {
                curr[t] = ans[j];
                t++;
            }
        }
        ans.swap(curr);
        // print(ans);
    }
    print(ans);
    return 0;
}
