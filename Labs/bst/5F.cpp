#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Node {
    ll y, x, sz;
    Node *left, *right;
    Node() {}
    Node(ll x) {
        this->x = x;
        this->y = ((rand() << 15)^rand());
        this->left = (this->right) = nullptr;
        this->sz = 1;
    }
    Node(ll x, ll y) {
        this->x = x;
        this->y = y;
        this->left = (this->right) = nullptr;
        this->sz = 1;
    }
};
typedef pair <Node*, Node*> treap_pair;

int get_size(Node *t) {
    if (t == nullptr)
        return 0;
    else
        return (int)(t->sz);
}

Node* update(Node *t) {
    if (t == nullptr)
        return t;
    t->sz = 1 + get_size(t->left) + get_size(t->right);
    return t;
}

treap_pair treap_split(Node *t, ll k) {
    if (t == nullptr)
        return {nullptr, nullptr};
    treap_pair p;
    int leftSz = get_size(t->left);
    if (leftSz < k) {
        p = treap_split(t->right, k - leftSz - 1);
        t->right = p.first;
        t = update(t); p.second = update(p.second);
        return {t, p.second};
    } else {
        p = treap_split(t->left, k);
        t->left = p.second;
        t = update(t); p.first = update(p.first);
        return {p.first, t};
    }
}

Node* treap_merge(Node *L, Node *R) {
    if (L == nullptr)
        return R;
    if (R == nullptr)
        return L;
    if (L->y < R->y) {
        L->right = (treap_merge(L->right, R));
        L = update(L);
        return L;
    } else {
        R->left = (treap_merge(L, R->left));
        R = update(R);
        return R;
    }
}

vector<ll> tree;

void print_tree(Node *t) {
    if (t != nullptr) {
        print_tree(t->left);
        tree.push_back(t->x);
        // cout << t->x << " ";
        print_tree(t->right);
    }
}

Node* treap_insert(Node* treap, ll x) {
    treap_pair p = treap_split(treap, x);
    Node* t = treap_merge(treap_merge(p.first, new Node(x)), p.second);
    t = update(t);
    return t;
}

Node* insertTo(Node* t, ll pnt, ll x) {
    Node *t1, *t2;
    treap_pair p = treap_split(t, pnt);
    t1 = p.first;
    t2 = p.second;
    t = treap_merge(treap_merge(t1, new Node(x)), t2);
    t = update(t);
    return t;
}

Node* eraseFrom(Node* t, ll pnt) {
    Node *t1, *t3;
    treap_pair p = treap_split(t, pnt + 1);
    t1 = p.first;
    t3 = p.second;
    p = treap_split(t1, pnt);
    t1 = p.first;
    t = treap_merge(t1, t3);
    t = update(t);
    return t;
}

int p[300001];
int sz[300001];
int emp[300001];

int get_(int x) {
    if (x != p[x])
        x = get_(p[x]);
    return x;
}

void join(int x, int y) {
    x = get_(x);
    y = get_(y);
    emp[x] = emp[y];
    if (x == y) return;
    if (sz[y] < sz[x])
        swap(x, y);
    p[x] = y;
    sz[y] += sz[x];
}

void superPrint(Node *r) {
    print_tree(r);
    int W = -1;
    int s = (int)r->sz;
    for (int i = 0; i < s; ++i) {
        if (tree[i] != -1) {
            W = i;
        }
    }
    cout << W + 1 << endl;
    for (int i = 0; i <= W; ++i) {
        if (tree[i] == -1)
            cout << "0 ";
        else
            cout << tree[i] << " ";
    }
    cout << endl;
    tree.clear();
}


int main() {
    // freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    Node *ROOT = nullptr;
    int N, n, c, m, old;
    n = 300000;
    cin >> N >> m;
    for (int i = 0; i < n; ++i) {
        p[i] = i; sz[i] = 1; emp[i] = i;
        ROOT = treap_insert(ROOT, -1);
    }
    // superPrint(ROOT);
    // cout << endl;
    for (int i = 0; i < N; ++i) {
        cin >> c; c--;
        old = c;
        c = emp[get_(c)];
        ROOT = eraseFrom(ROOT, c);  // удалить с-ый
        // cout << "erased from " << c << ": \n";
        // superPrint(ROOT);
        join(c, c + 1);
        ROOT = insertTo(ROOT, old, i + 1);  // добавить на позицию old
        // superPrint(ROOT);
        // cout << endl;
    }
    superPrint(ROOT);
    return 0;
}
