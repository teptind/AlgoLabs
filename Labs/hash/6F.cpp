#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<string> ans;
string curr = "";

void gen(int i) {
    if (i == 20) {
        ans.push_back(curr);
    } else {
        curr += "Aa";
        gen(i + 2);
        curr.pop_back();
        curr.pop_back();
        curr += "BB";
        gen(i + 2);
        curr.pop_back();
        curr.pop_back();
    }
}


int main() {
    // freopen("file.in", "r", stdin);
    int k;
    cin >> k;
    gen(0);
    for (int i = 0; i < k; ++i) {
        cout << ans[i] << "\n";
    }
    // cout << ans.size() << endl;
    return 0;
}
