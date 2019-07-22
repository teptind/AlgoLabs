#include <bits/stdc++.h>
#include <time.h>

using namespace std;
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long

const ll INF = 2e18;

struct pnt {
    int place;
    ll val;
    pnt() {}
    pnt(int p, ll v) {
        place = p;
        val = v;
    }
};

void printPnt(vector<pnt> t) {
    for (pnt x : t)
        cout << "(" << x.val << " " << x.place << ") ";
    cout << endl;
}

void print(vector<ll> t) {
    for (ll x : t)
        cout << x << " ";
    cout << endl;
}

vector<int> segPlace;

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

    void push(ll x) {
        acts.push_back((int)heap.size());
        heap.push_back(pnt((int)acts.size() - 1, x));
        siftUp((int)heap.size() - 1);
    }

    void extractMin() {
        // acts.push_back(-1);
        if (heap.empty())
            return;
        sw(0, (int)heap.size() - 1);
        heap.pop_back();
        siftDown(0);
    }

    void decreaseKey(int x, ll new_val) {
        // acts.push_back(-1);
        if (heap[acts[x]].val <= new_val)
            return;
        heap[acts[x]].val = new_val;
        siftUp(acts[x]);
    }

    bool isEmpty() {
        return ((int)heap.size() == 0);
    }

    ll get_min() {
        if (heap.empty())
            return 2e18;
        pnt ans = heap[0];
        return ans.val;
    }
};

int main() {
    // freopen("file.in", "r", stdin);
    // freopen("priorityqueue2.in", "r", stdin);
    // freopen("priorityqueue2.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie();
    int n, m;
    cin >> n >> m;
    int a, b;
    ll q;
    vector<tuple<int, int, ll> > seg;
    segPlace.assign(m, -1);
    vector<ll> ans(n);
    vector<vector<int> > open(n);
    vector<vector<int> > close(n);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> q; a--; b--;
        seg.push_back(make_tuple(a, b, q));
        open[a].push_back(i);
        close[b].push_back(i);
    }
    Heap h;
    int p = 0;
    for (int i = 0; i < n; ++i) {
        for (int j : open[i]) {
            segPlace[j] = p; p++;
            h.push(-get<2>(seg[j]));
            // cout << "pushed " << -get<2>(seg[j]) << endl;
            // printPnt(h.heap);
        }
        while (h.get_min() == -INF) {
            h.extractMin();
            // cout << "extracted " << h.get_min() << endl;
            // printPnt(h.heap);
        }
        if (h.isEmpty()) {
            ans[i] = 123LL;
        } else {
            ans[i] = -h.get_min();
            // cout << "curr min is " << h.get_min() << " " << -INF << endl;
            // printPnt(h.heap);
        }
        for (int j : close[i]) {
            // cout << "decreased " << j << endl;
            h.decreaseKey(segPlace[j], -INF);
            // printPnt(h.heap);
        }
    }
    print(ans);
    return 0;
}
