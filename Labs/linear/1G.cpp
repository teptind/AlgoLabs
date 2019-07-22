#include <bits/stdc++.h>

using namespace std;
#define ll long long


class MyVector
{
    int sz, left, right;
    int* cont;
    public:
        MyVector()
        {
            cont = new int[100];
            sz = 100;
            left = 50; right = 50;

        }
        int size_()
        {
            return right - left;
        }
        void expand()
        {
            sz *= 2;
            int* curr = new int[sz];
            int t = sz / 2 - (right - left) / 2;
            int nleft = t;
            for (int i = left; i < right; ++i)
            {
                curr[t] = cont[i];
                t++;
            }
            left = nleft; right = t;
            delete[] cont;
            cont = curr;
        }
        void squeeze()
        {
            sz /= 4;
            expand();
        }
        void align()
        {
            sz /= 2;
            expand();
        }
        void resize_()
        {
            if (right - left > (sz * 3) / 4)
                expand();
            else if (right - left < sz / 4 && sz > 100)
                squeeze();
            else if (sz - right < 10 || left < 10)
                align();
        }
        bool emp()
        {
            if (left == right)
                return true;
            return false;
        }
        int get_elem(int i)
        {
            return cont[left + i];
        }
        void pushb(int val)
        {
            cont[right] = val;
            right++;
            resize_();
        }
        void popb()
        {
            right--;
            resize_();
        }
        void popf()
        {
            left++;
            resize_();
        }
        int top()
        {
            return cont[right - 1];
        }
        int front_()
        {
            return cont[left];
        }
};

class Quemin
{
    public:
        MyVector fmin;
        MyVector smin;
        MyVector q;
        int get_last()
        {
            return q.top();
        }
        int get_prelast()
        {
            return q.get_elem(q.size_() - 2);
        }
        void change()
        {
            int i = q.size_() - 1;
            while (!smin.emp())
            {
                int x = q.get_elem(i);
                if (!fmin.emp())
                    x = min(x, fmin.top());
                fmin.pushb(x);
                smin.popb();
                i--;
            }
        }
        void push(int val)
        {
            q.pushb(val);
            if (smin.emp())
                smin.pushb(val);
            else
                smin.pushb(min(smin.top(), val));
        }
        void pop()
        {
            if (fmin.emp())
                change();
            fmin.popb();
            q.popf();
        }
        int get_min()
        {
            if (fmin.emp())
                change();
            int ans = fmin.top();
            if (!smin.emp())
                ans = min(ans, smin.top());
            return ans;
        }
};

int f(int prelast, int last, int a1, int b1, int c1)
{
    ll ans = (ll)a1 * prelast + (ll)b1 * last + c1;
    return (int)ans;
}

int main()
{
    //freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    ll res = 0LL;
    int n, m, k, a, b, c, val;
    cin >> n >> m >> k >> a >> b >> c;
    Quemin qm;
    MyVector curr;
    for (int i = 0; i < k; ++i)
    {
        cin >> val;
        curr.pushb(val);
    }
    for (int i = 0; i < m; ++i)
    {
        if (!curr.emp())
        {
           val = curr.front_();
           curr.popf();
        }
        else
            val = f(qm.get_prelast(), qm.get_last(), a, b, c);
        qm.push(val);
    }
    for (int i = 0; i < n - m + 1; ++i)
    {
        if (!curr.emp())
        {
           val = curr.front_();
           curr.popf();
        }
        else
            val = f(qm.get_prelast(), qm.get_last(), a, b, c);

        res += qm.get_min();
        qm.pop();
        qm.push(val);
    }
    cout << res << endl << endl;
    return 0;
}
