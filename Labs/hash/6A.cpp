#include <bits/stdc++.h>

using namespace std;

#define ll long long

std::random_device rd;
mt19937 gen(rd());
const uint32_t PRIME = 4294967291;

class hashSet {
    uint32_t cnt, a, b, p = PRIME;
    uint32_t sz;
    vector<list<uint32_t> > table;
    vector<list<uint32_t> > newTable;

 public:
    hashSet() {
        sz = 10;
        table.resize(sz);
        rebuildKeys();
        cnt = 0;
    }


    uint32_t getHash(uint32_t x) {
        return static_cast<uint32_t>(a * x + b) % p % sz;
    }

    void rebuildKeys() {
        a = uniform_int_distribution<uint32_t>(1, INT_MAX)(gen);
        b = uniform_int_distribution<uint32_t>(0, INT_MAX)(gen);
    }

    void expand() {
        if (cnt * 3 > ((uint32_t)sz * 4)) {
            sz *= 2;
            newTable.clear();
            vector<list<uint32_t> > newTable(sz);
            rebuildKeys();
            for (const list<uint32_t> &L : table) {
                for (uint32_t elem : L) {
                    newTable[getHash(elem)].push_back(elem);
                }
            }
            table.swap(newTable);
        }
    }

    void insert(uint32_t x) {
        if (exists(x))
            return;
        table[getHash(x)].push_back(x);
        cnt++;
        expand();
    }

    void erase(uint32_t x) {
        int t = getHash(x);
        for (auto it = table[t].begin(); it != table[t].end(); it++) {
            if (*it == x) {
                table[t].erase(it);
                cnt--;
                return;
            }
        }
    }

    bool exists(uint32_t x) {
        int t = getHash(x);
        for (uint32_t &it : table[t]) {
            if (it == x) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    // freopen("file.in", "r", stdin);
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    hashSet H;
    uint32_t k;
    string act, ans = "";
    while (cin >> act) {
        if (act == "insert") {
            cin >> k;
            H.insert(k);
        } else if (act == "exists") {
            cin >> k;
            if (H.exists(k)) {
                 ans += "true\n";
            } else {
                ans += "false\n";
            }
        } else if (act == "delete") {
            cin >> k;
            H.erase(k);
        }
    }

    cout << ans;
    return 0;
}
