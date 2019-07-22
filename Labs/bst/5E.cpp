#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll MOD = (ll)1e9;

struct Node {
    ll y, sz, x, sum_, num;
    Node *left, *right;
    Node() {}
    Node(ll x) {
        this->x = this->sum_ = x;
        this->y = ((rand() << 15)^rand());
        this->left = (this->right) = nullptr;
        this->sz = 1;
        this->num = -1;
    }
    Node(ll x, ll y, int num) {
        this->x = this->sum_ = x;
        this->y = y;
        this->left = (this->right) = nullptr;
        this->sz = 1;
        this->num = num;
    }
};
typedef pair <Node*, Node*> treap_pair;

int get_size(Node *t) {
    if (t == nullptr)
        return 0;
    else
        return (int)(t->sz);
}

ll get_sum(Node *t) {
    if (t == nullptr)
        return 0LL;
    else
        return t->sum_;
}
Node* update(Node *t) {
    if (t == nullptr)
        return t;
    t->sz = get_size(t->left) + get_size(t->right) + 1;
    t->sum_ = t->x + get_sum(t->left) + get_sum(t->right);
    return t;
}

treap_pair treap_split(Node *t, ll x) {
    if (t == nullptr)
        return {nullptr, nullptr};
    treap_pair p;
    if (t->x < x) {
        p = treap_split(t->right, x);
        t->right = p.first;
        t = update(t); p.second = update(p.second);
        return {t, p.second};
    } else {
        p = treap_split(t->left, x);
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

bool exists(ll x, Node *t) {
    if (t == nullptr)
        return false;
    if (x == t->x)
        return true;
    if (x < t->x)
        return exists(x, t->left);
    else
        return exists(x, t->right);
}

Node* treap_insert(Node* treap, ll x, ll y, int num) {
    treap_pair p = treap_split(treap, x);
    Node* t = treap_merge(treap_merge(p.first, new Node(x, y, num)), p.second);
    t = update(t);
    return t;
}

Node* treap_erase(Node* t, int k) {
    if (t == nullptr)
        return t;
    if (t->x == k) {
        t = treap_merge(t->left, t->right);
    } else {
        if (t->x > k)
            t->left = treap_erase(t->left, k);
        else
            t->right = treap_erase(t->right, k);
    }
    t = update(t);
    return t;
}

int kth(Node* t, int k) {
    int leftSz = 0;
    if (t->left != nullptr)
        leftSz = (int)t->left->sz;

    if (leftSz == k - 1)
        return (int)t->x;
    else if (leftSz >= k)
        return kth(t->left, k);
    else return kth(t->right, k - (leftSz + 1));
}

ll segSum(Node* t, ll l, ll r) {
    Node *t1, *t2, *t3;
    treap_pair p = treap_split(t, l);
    t1 = p.first;
    p = treap_split(p.second, r + 1);
    t2 = p.first; t3 = p.second;
    ll ans = get_sum(t2);
    t = treap_merge(treap_merge(t1, t2), t3);
    return ans;
}

vector<int> l, r, p;

void check_tree(Node *t) {
    if (t != nullptr) {
        check_tree(t->left);
        if (t->left != nullptr) {
            l[(int)t->num] = (int)(t->left->num);
            p[(int)t->left->num] = (int)(t->num);
        }
        check_tree(t->right);
        if (t->right != nullptr) {
            r[(int)t->num] = (int)(t->right->num);
            p[(int)t->right->num] = (int)(t->num);
        }
    }
}

int main() {
    // freopen("file.in", "r", stdin);
    int n;
    ll a, b;
    string act;
    cin >> n;
    Node *ROOT = nullptr;
    queue<Node* > q;
    vector<vector<ll> > pnt;
    for (int i = 0; i < n; ++i) {
       cin >> a >> b;
       pnt.push_back({a, b, i});
    }
    sort(pnt.begin(), pnt.end());
    for (int i = 0; i < n; ++i) {
        q.push(new Node(pnt[i][0], pnt[i][1], (int)pnt[i][2]));
    }
    int k = n, ind = 0;
    while (q.size() > 1) {
        Node *curr1 = q.front();
        q.pop();
        ind++;
        if (ind < k) {
            Node *curr2 = q.front();
            q.pop();
            ind++;
            curr1 = treap_merge(curr1, curr2);
            q.push(curr1);
            if (ind == k) {
                k = (k + 1) / 2;
                ind = 0;
            }
        } else {
            k = (k + 1) / 2;
            ind = 0;
            q.push(curr1);
        }
    }
    ROOT = q.front();
    l.assign(n, -1);
    r.assign(n, -1);
    p.assign(n, -1);
    check_tree(ROOT);
    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        cout << p[i] + 1 << " " << l[i] + 1 << " " << r[i] + 1 << "\n";
    }
}
