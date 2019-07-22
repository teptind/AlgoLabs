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
            curr->next = nullptr;
            if (head != nullptr)
            {
                curr->prev = tail;
                tail->next = curr;
                tail = curr;
            }
            else
            {
                curr->prev = nullptr;
                tail = curr;
                head = curr;
            }
        }
        void popb()
        {
            elem *curr = tail->prev;
            delete tail;
            tail = curr;
            if (tail == nullptr)
                head = tail;
        }
        void popf()
        {
            elem *curr = head->next;
            delete head;
            head = curr;
            if (head == nullptr)
                tail = head;
        }
        int top()
        {
            if (head == nullptr)
                return -1;
            int ans = head->x;
            return ans;
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
        void clr()
        {
            while (tail != nullptr)
                popb();
        }
};

int main()
{
    ios_base::sync_with_stdio(0);
    //freopen("file.in", "r", stdin);
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
            t = st.top(); st.popf();
            cout << t << endl;
        }
    }
    return 0;
}
