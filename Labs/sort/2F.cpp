#include <bits/stdc++.h>

using namespace std;
#define ll long long

void print(vector<int> t) {
    for (int a : t)
        cout << a << " ";
    cout << endl;
}

int main() {
    // freopen("huffman.in", "r", stdin);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        a[i] = i + 1;
    for (int i = 1; i < n; ++i)
        swap(a[i], a[i / 2]);
    print(a);
    return 0;
}
