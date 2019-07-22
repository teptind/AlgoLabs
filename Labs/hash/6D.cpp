#include <bits/stdc++.h>

using namespace std;

#define ll long long

const uint32_t MOD = 4294967291;
const uint32_t BASE = 53;

void print(vector<string> &t) {
    for (const string &s : t) {
        cout << s << " ";
    }
    cout << "\n";
}

class hashSet {
    uint32_t cnt;
    uint32_t sz;
    vector<list<pair<string, unordered_set<string> > > > table;
    vector<list<pair<string, unordered_set<string> > > > newTable;

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
            for (const list<pair<string, unordered_set<string> > > &L : table) {
                for (const pair<string, unordered_set<string>> &elem : L) {
                    uint32_t key = getHash(elem.first);
                    newTable[key].push_back(elem);
                }
            }
            table.swap(newTable);
        }
    }

    void insert(const string &x, string &y) {
        expand();
        int t = getHash(x);
        for (auto &p : table[t]) {
            if (p.first == x) {
                p.second.insert(y);
                return;
            }
        }
        table[t].push_front({x, unordered_set<string>()});
        table[t].begin()->second.insert(y);
        cnt++;
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
    void erasePair(const string &x, string &y) {
        int t = getHash(x);
        for (auto &p : table[t]) {
            if (p.first == x) {
                p.second.erase(y);
                return;
            }
        }
    }

    void get(const string &x, vector<string> &v) {
        int t = getHash(x);
        for (auto &p : table[t]) {
            if (p.first == x) {
                for (const string &s : p.second)
                v.push_back(s);
            }
        }
    }
};

int main() {
    // freopen("file.in", "r", stdin);
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    hashSet H;
    string key, val;
    string act, ans = "";
    vector<string> curr;
    while (cin >> act) {
        if (act == "put") {
            cin >> key >> val;
            H.insert(key, val);
        } else if (act == "delete") {
            cin >> key >> val;
            H.erasePair(key, val);
        } else if (act == "deleteall") {
            cin >> key;
            H.erase(key);
        } else if (act == "get") {
            cin >> key;
            curr.clear();
            H.get(key, curr);
            cout << curr.size() << " ";
            print(curr);
        }
    }

    cout << ans << endl;
    return 0;
}
