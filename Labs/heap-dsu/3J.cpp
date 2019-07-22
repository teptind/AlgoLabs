#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

void print(vector<int> &t) {
    for (int i : t)
        cout << i << " ";
    cout << endl;
}

struct dsu {
    vector<int> p;
    vector<int> value;
    vector<int> readAlready;
    dsu() {}
    dsu(int n) {
        p = vector<int>(n);
        value = vector<int>(n);
        readAlready = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            p[i] = i;
            value[i] = 0;
            readAlready[i] = 0;
        }
    }
    pair<int, int> getUnion(int x) {
        if (x != p[x]) {
            pair<int, int> c = getUnion(p[x]);
            value[x] += c.second;
            p[x] = c.first;
            return {p[x], value[x]};
        }
        return {x, 0};
    }

    bool join(int x, int y) {
        pair<int, int> cx = getUnion(x); x = cx.first;
        pair<int, int> cy = getUnion(y); y = cy.first;
        if (x == y) return false;
        int V = (int)p.size();
        p.push_back(V);
        value.push_back(0);
        readAlready.push_back(0);
        p[x] = V;
        p[y] = V;
        return true;
    }

    int getAns(int x) {
        int ans;
        if (x == p[x]) {
            ans = value[x] + readAlready[x];
            readAlready[x] -= ans;
            return ans;
        }
        pair<int, int> c = getUnion(x);
        ans = value[x] + value[c.first] + readAlready[x];
        readAlready[x] -= ans;
        return ans;
    }

    void sendMessage(int x) {
        pair<int, int> cx = getUnion(x); x = cx.first;
        value[x]++;
    }

    void printAll() {
        cout << "------//------\n";
        print(p);
        print(value);
        print(readAlready);
        cout << "------//------\n";
    }
};

int main() {
    // freopen("file.in", "r", stdin);
    // freopen("restructure.in", "r", stdin);
    // freopen("restructure.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie();
    int zerg = 0;
    int n, m, a, b, type, mod = (int)(1e6 + 3);
    cin >> n >> m;
    dsu D = dsu(n);
    for (int i = 0; i < m; ++i) {
        cin >> type;
        // cout << type << " ";
        if (type == 1) {
            cin >> a;
            // cout << (a + zerg) % n << endl;
            D.sendMessage((a + zerg) % n);
            zerg = (zerg * 30 + 239) % mod;
        }
        if (type == 2) {
            cin >> a >> b;
            // cout << (a + zerg) % n << " " << (b + zerg) % n << endl;
            if (D.join((a + zerg) % n, (b + zerg) % n))
                zerg = (zerg * 13 + 11) % mod;
        }
        if (type == 3) {
            cin >> a;
            // cout << (a + zerg) % n << endl;
            int ANS = D.getAns((a + zerg) % n);
            cout << ANS << "\n";
            zerg = (int)((100500LL * zerg + ANS) % mod);
        }
        // cout << "zerg =" << " " << zerg % 2 << endl;
        // D.printAll();
    }
    return 0;
}
