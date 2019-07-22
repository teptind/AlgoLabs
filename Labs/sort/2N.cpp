#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

void print(vector<pair<int, int> > t) {
    cout << t.size() << " ";
    for (pair<int, int> a : t)
        cout << a.first << " " << a.second << " ";
    cout << endl;
}

int n, cnt = 0;
vector<pair<int, int> > comp;
vector<vector<pair<int, int> > > ans;

void add(int a, int b) {
    if (a <= n && b <= n) {
        cnt++;
        comp.push_back({a, b});
    }
}

void next_() {
    if (!comp.empty())
        ans.push_back(comp);
    comp.clear();
}

int main() {
    // freopen("file.in", "r", stdin);

    cin >> n;
    for (int i = 1; i <= 15; i += 2) {  // 1
        add(i, i + 1);
    }
    next_();

    for (int i = 1; i <= 13; i += 4) {  // 2
        add(i, i + 3); add(i + 1, i + 2);
    }
    next_();

    for (int i = 1; i <= 15; i += 2) {  // 1
        add(i, i + 1);
    }
    next_();

    for (int i = 1; i <= 9; i += 8) {  // 4
        add(i, i + 7); add(i + 1, i + 6); add(i + 2, i + 5); add(i + 3, i + 4);
    }
    next_();

    for (int i = 1; i <= 13; i += 4) {  // 5
        add(i, i + 2); add(i + 1, i + 3);
    }
    next_();

    for (int i = 1; i <= 15; i += 2) {  // 1
        add(i, i + 1);
    }
    next_();

    for (int i = 0; i < 8; i++) {  // 7
        add(1 + i, 16 - i);
    }
    next_();

    for (int i = 1; i <= 9; i += 8) {  // 8
        add(i, i + 4); add(i + 1, i + 5); add(i + 2, i + 6); add(i + 3, i + 7);
    }
    next_();

    for (int i = 1; i <= 13; i += 4) {  // 5
        add(i, i + 2); add(i + 1, i + 3);
    }
    next_();

    for (int i = 1; i <= 15; i += 2) {  // 1
        add(i, i + 1);
    }
    next_();

    cout << n << " " << cnt << " " << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i)
        print(ans[i]);

    return 0;
}
