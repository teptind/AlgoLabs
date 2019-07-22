#include <bits/stdc++.h>

using namespace std;

struct elem
{
    int x;
    elem *next;
    elem *prev;
};

class MyList
{
    elem *head;
    elem *tail;
    public:
        MyList()
        {
            head = nullptr;
            tail = nullptr;
        }
        void pushb(int val)
        {
            elem *curr = new elem;
            curr->x = val;
            curr->prev = tail;
            if (tail != nullptr)
                tail->next = curr;
            tail = curr;
        }
        /*void pushf(int val)
        {
            elem *curr = new elem;
            curr->x = val;
            curr->next = head;
            if (head != nullptr)
                head->prev = curr;
            head = curr;
        }*/
        int popb()
        {
            int ans = tail->x;
            elem *curr = tail->prev;
            delete tail;
            tail = curr;
            return ans;
        }
        /*int popf()
        {
            int ans = head->x;
            elem *curr = head->prev;
            delete head;
            head = curr;
            return ans;
        }*/
        void print()
        {
            elem *it = head;
            while (it != nullptr)
            {
                cout << it->x << " ";
                it = it->next;
            }
            cout << endl;
        }
};

int main()
{
    //freopen("file.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    int n, t;
    cin >> n;
    char act;
    MyList st;
    for (int i = 0; i < n; ++i)
    {
        cin >> act;
        if (act == '+')
        {
            cin >> t;
            st.pushb(t);
        }
        if (act == '-')
        {
            t = st.popb();
            cout << t << endl;
        }
    }
    return 0;
}
