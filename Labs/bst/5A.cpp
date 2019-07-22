#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <set>
#include <time.h>
#include <stdlib.h>

using namespace std;

#define ll long long

const int INF = (int) (-2e9);

struct Node {
    ll val;
    Node *left, *right, *par;

    Node() {}

    Node(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
        par = nullptr;
    }
};

typedef Node *pNode;

pNode updPar(pNode p) {
    if (p->left != nullptr)
        p->left->par = p;
    if (p->right != nullptr)
        p->right->par = p;
    return p;
}

pNode eraseParent(pNode r) {
    if (r->left != nullptr)
        r->left->par = nullptr;
    if (r->right != nullptr)
        r->right->par = nullptr;
    return r;
}

pair<pNode, pNode> rot(pNode p, pNode ch) {
    Node *gp = p->par;
    if (gp != nullptr) {
        if (p == gp->left) {
            gp->left = ch;
        } else if (p == gp->right) {
            gp->right = ch;
        }
    }


    if (ch == p->left) {
        p->left = ch->right;
        ch->right = p;
    } else if (ch == p->right) {
        p->right = ch->left;
        ch->left = p;
    }

    p = updPar(p);
    ch = updPar(ch);
    ch->par = gp;
    return {p, ch};
}

pNode splay(pNode u) {
    if (u == nullptr)
        return u;
    pair<pNode, pNode> tree;
    if (u->par == nullptr)
        return u;
    Node *p = u->par, *gp = u->par->par;
    if (gp == nullptr) {   // zig
        tree = rot(p, u);
        return u;
    }
    if ((p == gp->left && u == p->left) || (p == gp->right && u == p->right)) {   // zigzig
        tree = rot(gp, p);
        p = tree.second;
        rot(p, u);
    } else {   // zigzag
        tree = rot(p, u);
        u = tree.second;
        rot(gp, u);
    }
    return splay(u);
}

pNode find(pNode r, int x) {
    if (r == nullptr)
        return r;
    if (x == r->val) {
        return splay(r);
    }
    if (x < r->val && r->left != nullptr)
        return find(r->left, x);
    if (x > r->val && r->right != nullptr)
        return find(r->right, x);
    return splay(r);
}

pair<pNode, pNode> split(pNode r, int x) {
    if (r == nullptr)
        return {nullptr, nullptr};
    r = find(r, x);
    if (r->val == x) {
        r = eraseParent(r);
        return {r->left, r->right};
    }
    if (r->val < x) {
        pNode right = r->right;
        r->right = nullptr;
        if (right != nullptr)
            right->par = nullptr;
        return {r, right};
    } else {
        pNode left = r->left;
        r->left = nullptr;
        if (left != nullptr)
            left->par = nullptr;
        return {left, r};
    }
}

pNode merge(pNode left, pNode right) {
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;
    right = find(right, (int) (left->val));
    right->left = left;
    right = updPar(right);
    return right;
}

pair<pNode, bool> exists(pNode r, int x) {
    r = find(r, x);
    return {r, (r != nullptr && r->val == x)};
}

pNode delete_(pNode r, int x) {
    if (r == nullptr)
        return r;
    r = find(r, x);
    if (r->val != x)
        return r;
    r = eraseParent(r);
    return merge(r->left, r->right);
}

pNode insert_(pNode r, int x) {
    pair<pNode, pNode> tree = split(r, x);
    r = new Node(x);
    r->left = tree.first;
    r->right = tree.second;
    r = updPar(r);
    return r;
}

pair<pNode, int> next(pNode r, int x) {
    pair<pNode, bool> res = exists(r, x);
    r = res.first;
    bool k = res.second;
    pair<pNode, pNode> tree = split(r, x);
    Node *left = tree.first, *right = tree.second;
    right = find(right, x);
    int ans;
    if (right != nullptr)
        ans = (int) right->val;
    else ans = INF;
    r = merge(left, right);
    if (k) {
        r = insert_(r, x);
    }
    if (r != nullptr)
        r = splay(r);
    return {r, ans};
}

pair<pNode, int> prev(pNode r, int x) {
    pair<pNode, bool> res = exists(r, x);
    r = res.first;
    bool k = res.second;
    pair<pNode, pNode> tree = split(r, x);
    Node *left = tree.first, *right = tree.second;
    left = find(left, x);
    int ans;
    if (left != nullptr)
        ans = (int) left->val;
    else ans = INF;
    r = merge(left, right);
    if (k) {
        r = insert_(r, x);
    }
    if (r != nullptr)
        r = splay(r);
    return {r, ans};
}


int main() {
    // freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie();
    string act;
    int k, ans;
    Node *ROOT = nullptr;
    while (cin >> act) {
        cin >> k;
        if (act == "insert") {
            ROOT = insert_(ROOT, k);
            continue;
        }
        if (act == "delete") {
            ROOT = delete_(ROOT, k);
            continue;
        }
        if (act == "exists") {
            pair<pNode, bool> res = exists(ROOT, k);
            ROOT = res.first;
            bool ex = res.second;
            if (ex)
                cout << "true\n";
            else cout << "false\n";
            continue;
        }
        if (act == "next") {
            pair<pNode, int> res = next(ROOT, k);
            ROOT = res.first;
            ans = res.second;
            if (ans == INF)
                cout << "none\n";
            else cout << ans << "\n";
            continue;
        }
        if (act == "prev") {
            pair<pNode, int> res = prev(ROOT, k);
            ROOT = res.first;
            ans = res.second;
            if (ans == INF)
                cout << "none\n";
            else cout << ans << "\n";
        }
    }
    return 0;
}
