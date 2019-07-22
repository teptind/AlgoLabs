#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct matrix {
    int value[2][2];
    matrix(int a, int b, int c, int d) {
        value[0][0] = a;
        value[0][1] = b;
        value[1][0] = c;
        value[1][1] = d;
    }
    matrix() {}
    void print() {
        cout << value[0][0] << " " << value[0][1] << "\n"
        << value[1][0] << " " << value[1][1] << "\n\n";
    }
};

const matrix E = matrix(1, 0, 0, 1);
const matrix ZERO = matrix(0, 0, 0, 0);
int R;

matrix operator*(const matrix &a, const matrix &b) {
    return {(a.value[0][0] * b.value[0][0] + a.value[0][1] * b.value[1][0]) % R,
                  (a.value[0][0] * b.value[0][1] + a.value[0][1] * b.value[1][1]) % R,
                  (a.value[1][0] * b.value[0][0] + a.value[1][1] * b.value[1][0]) % R,
                  (a.value[1][0] * b.value[0][1] + a.value[1][1] * b.value[1][1]) % R};
}

matrix* DO[1000001];
matrix* X[200001];
void build_tree(size_t a, size_t l, size_t r) {
    if (r - l == 1) {
        DO[a] = new matrix();
        *DO[a] = *X[l];
        return;
    }
    size_t m = (l + r) / 2;
    build_tree(a * 2 + 1, l, m);
    build_tree(a * 2 + 2, m, r);
    DO[a] = new matrix();
    *DO[a] = *DO[a * 2 + 1] * *DO[a * 2 + 2];
}

matrix get_ans(size_t a, size_t l, size_t r, size_t ql, size_t qr) {
    if (qr <= l || r <= ql) {
        return E;
    }
    if (ql <= l && r <= qr) {
        return *DO[a];
    }
    size_t m = (l + r) / 2;
    return get_ans(a * 2 + 1, l, m, ql, qr) *
           get_ans(a * 2 + 2, m, r, ql, qr);
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    // freopen("file.in", "r", stdin);
    size_t n;
    int a, b, c, d, m;
    cin >> R >> n >> m;
    for (size_t i = 0; i < n; ++i) {
        cin >> a >> b >> c >> d;
        X[i] = new matrix(a, b, c, d);
    }
    build_tree(0, 0, n);
    size_t l, r;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r; l--; r--;
        get_ans(0, 0, n, l, r + 1).print();
    }
    return 0;
}
