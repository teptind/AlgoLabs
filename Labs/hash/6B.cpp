#include <bits/stdc++.h>

using namespace std;

#define ll long long

std::random_device rd;
mt19937 gen(rd());
const uint32_t MOD = 4294967291;
const uint32_t BASE = 53;

class hashSet {
    uint32_t cnt;
    uint32_t sz;
    vector<list<pair<string, string> > > table;
    vector<list<pair<string, string> > > newTable;

 public:
    hashSet() {
        sz = 10;
        table.resize(sz);
        cnt = 0;
    }


    uint32_t getHash(string s) {
        uint32_t hash = 0;
        for (char &i : s) {
            hash = ((hash * BASE) % MOD + (uint32_t) i) % MOD;
        }
        return hash % sz;
    }

    void expand() {
        if (cnt * 3 > ((uint32_t)sz * 4)) {
            sz *= 2;
            newTable.clear();
            newTable.resize(sz);
            for (const list<pair<string, string> > &L : table) {
                for (const pair<string, string> &elem : L) {
                    uint32_t key = getHash(elem.first);
                    newTable[key].push_back(elem);
                }
            }
            table.swap(newTable);
        }
    }

    void insert(string x, string y) {
        erase(x);
        uint32_t k = getHash(x);
        table[k].push_back({x, y});
        cnt++;
        expand();
    }

    void erase(const string &x) {
        int t = getHash(x);
        for (auto it = table[t].begin(); it != table[t].end(); it++) {
            if ((*it).first == x) {
                table[t].erase(it);
                cnt--;
                return;
            }
        }
    }

    string get(const string &x) {
        int t = getHash(x);
        for (pair<string, string> &p : table[t]) {
            if (p.first == x) {
                return p.second;
            }
        }
        return "$";
    }
};

int main() {
    // freopen("file.in", "r", stdin);
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    hashSet H;
    string key, val;
    string act, ans = "", curr;
    while (cin >> act) {
        if (act == "put") {
            cin >> key >> val;
            H.insert(key, val);
        } else if (act == "delete") {
            cin >> key;
            H.erase(key);
        } else if (act == "get") {
            cin >> key;
            curr = H.get(key);
            if (curr != "$") {
                ans += (curr + "\n");
            } else {
                ans += "none\n";
            }
        }
    }

    cout << ans;
    return 0;
}
