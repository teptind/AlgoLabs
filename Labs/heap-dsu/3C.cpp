#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

const ll INF = 1e18;

struct pnt {
    int place, val;
    pnt() {}
    pnt(int p, int v) {
        place = p;
        val = v;
    }
};

void print(vector<pnt> t) {
    for (pnt x : t)
        cout << "(" << x.val << " " << x.place << ") ";
    cout << endl;
}

class Heap {
 public:
    vector<pnt> heap;
    vector<int> acts;
    void sw(int x, int y) {
        acts[heap[x].place] = y;
        acts[heap[y].place] = x;
        pnt tx = heap[x], ty = heap[y];
        heap[x] = ty; heap[y] = tx;
    }

    void siftUp(int x) {
        if (heap[x].val < heap[(x - 1) / 2].val) {
            sw(x, (x - 1) / 2);
            siftUp((x - 1) / 2);
        }
    }

    void siftDown(int x) {
        int l = x * 2 + 1, r = x * 2 + 2;
        if ((int)heap.size() <= l)
            return;
        int next_;
        if (r < (int)heap.size() && heap[r].val < heap[l].val)
            next_ = r;
        else
            next_ = l;
        if (heap[next_].val < heap[x].val) {
            sw(x, next_);
            siftDown(next_);
        }
    }

    void push(int x) {
        acts.push_back((int)heap.size());
        heap.push_back(pnt((int)acts.size() - 1, x));
        siftUp((int)heap.size() - 1);
    }

    pnt extractMin() {
        acts.push_back(-1);
        if (heap.empty())
            return pnt(2e9, 2e9);
        pnt ans = heap[0];
        sw(0, (int)heap.size() - 1);
        heap.pop_back();
        siftDown(0);
        return ans;
    }

    void decreaseKey(int x, int new_val) {
        acts.push_back(-1);
        if (heap[acts[x]].val <= new_val)
            return;
        heap[acts[x]].val = new_val;
        siftUp(acts[x]);
    }
};

int main() {
    // freopen("file.in", "r", stdin);
    freopen("priorityqueue2.in", "r", stdin);
    freopen("priorityqueue2.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie();
    int a, b;
    Heap h;
    pnt ans;
    string s;
    while (cin >> s) {
        if (s == "push") {
            cin >> a;
            h.push(a);
        }
        if (s == "extract-min") {
            ans = h.extractMin();
            if (ans.val == 2e9)
                cout << "*\n";
            else
                cout << ans.val << " " << ans.place + 1 << "\n";
        }
        if (s == "decrease-key") {
            cin >> a >> b; a--;
            h.decreaseKey(a, b);
        }
        // print(h.heap);
    }

    return 0;
}
