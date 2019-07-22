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
        int bot()
        {
            return cont[left];
        }
};

int main()
{
    //freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    MyVector st;
    char act;
    int n, x;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> act;
        if (act == '+')
        {
            cin >> x;
            st.pushb(x);
        }
        if (act == '-')
        {
            cout << st.bot() << endl;
            st.popf();
        }
    }
    return 0;
}
