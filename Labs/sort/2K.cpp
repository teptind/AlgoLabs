#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define uint unsigned int

void print(vector<int> t) {
    for (int a : t)
        cout << a << " ";
    cout << endl;
}

ll x, y;

void ret_ans(ll a) {
    cout << "! " << a << endl; cout.flush();
    exit(0);
}

ll to_norm(ll a) {
    a -= (y - 1);
    if (a < 1)
        a += (ll)1e18;
    return a;
}

ll get_(ll a) {
    cout << "? " << a << endl; cout.flush();
    ll b;
    cin >> b;
    return b;
}



int main() {
    // freopen("file.in", "r", stdin);
    ll l, r, mid, curr;
    int m;
    cin >> x >> m;
    y = get_(1LL);
    l = max(1LL, to_norm(x) - m) - 1, r = min(to_norm(x), (ll)1e18 - m) + 1;
    // cout << to_norm(x) << endl;
    while (r - l > 1) {
        mid = (r + l) / 2;
        curr = to_norm(get_(mid));
        if (curr == to_norm(x))
            ret_ans(mid);
        if (curr < to_norm(x))
            l = mid;
        else r = mid;
    }
    cout << "! -1" << endl; cout.flush();
    return 0;
}
