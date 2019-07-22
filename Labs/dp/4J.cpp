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

void print2(vector<vector<int > > &t) {
    for (int i = 0; i < (int)t.size(); ++i)
        print(t[i]);
    cout << "\n";
}

string s1, s2;

vector<int> makeDP(string a, string b) {
    vector<int> dp(b.size() + 1, 0), p;
    for (int ai = 0; ai < (int)a.size(); ++ai) {
        p = dp;
        for (int bi = 0; bi < (int)b.size(); ++bi) {
            if (a[ai] == b[bi])
                dp[bi + 1] = p[bi] + 1;
            else
                dp[bi + 1] = max(p[bi + 1], dp[bi]);
        }
    }
    return dp;
}

string solve(string a, string b) {
    if (a == "" || b == "") {
        return "";
    }

    int la = (int)a.size();
    if (la == 1) {
        for (char t : b) {
            if (a[0] == t) {
                return (a.substr(0, 1));
            }
        }
        return "";
    }
    int mid = la / 2;
    string aL = a.substr(0, mid), aR = a.substr(mid, a.size() - mid);

    vector<int> dp1 = makeDP(aL, b);

    string aRRev = aR; reverse(aRRev.begin(), aRRev.end());
    string bRev = b; reverse(bRev.begin(), bRev.end());

    vector<int> dp2 = makeDP(aRRev, bRev);
    reverse(dp2.begin(), dp2.end());

    int n = min((int)dp1.size(), (int)dp2.size());
    int mx = -1, ind = -1;
    for (int i = 0; i < n; ++i) {
        if (dp1[i] + dp2[i] > mx) {
            mx = dp1[i] + dp2[i];
            ind = i;
        }
    }
    // print(dp1);
    // print(dp2);
    string bL = b.substr(0, ind), bR = b.substr(ind, b.size() - ind);
    /*cout << "aL: " << aL << endl;
    cout << "bL: " << bL << endl;
    cout << "aR: " << aR << endl;
    cout << "bR: " << bR << endl;*/
    string solve1 = solve(aL, bL);
    string solve2 = solve(aR, bR);
    string S = solve1 + solve2;
    return S;
}

int main() {
    // freopen("file.in", "r", stdin);
    cin >> s1 >> s2;
    if (s1.size() > s2.size())
        swap(s1, s2);
    cout << solve(s1, s2) << endl;
    return 0;
}
