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

void print_tree(Node *t) {
    if (t != nullptr) {
        print_tree(t->left);
        cout << t->x << " ";
        print_tree(t->right);
    }
}

Node* treap_insert(Node* treap, ll x) {
    treap_pair p = treap_split(treap, x);
    Node* t = treap_merge(treap_merge(p.first, new Node(x)), p.second);
    t = update(t);
    return t;
}

Node* moveLeft(Node* t, int l, int r) {
    Node *t1, *t2, *t3;
    treap_pair p = treap_split(t, l - 1);
    t1 = p.first; t1 = update(t1);
    t2 = p.second; t2 = update(t2);
    p = treap_split(t2, r - (l - 1));
    t2 = p.first; t2 = update(t2);
    t3 = p.second; t3 = update(t3);
    t = treap_merge(treap_merge(t2, t1), t3);
    return t;
}

int main() {
    // freopen("file.in", "r", stdin);
    int n, m, a, b;
    cin >> n >> m;
    Node *ROOT = nullptr;
    for (int i = 1; i <= n; ++i) {
        ROOT = treap_merge(ROOT, new Node(i));
    }
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        ROOT = moveLeft(ROOT, a, b);
    }
    print_tree(ROOT);
}
