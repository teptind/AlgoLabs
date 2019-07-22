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
        void popb()
        {
            elem *curr = tail->prev;
            delete tail;
            tail = curr;
        }
        int top()
        {
            if (tail == nullptr)
                return -1;
            int ans = tail->x;
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
    string s;
    bool f = true;
    MyList st;
    while (cin >> s)
    {
        f = true;
        for (char x : s)
        {
            if (x == '(')
                st.pushb(1);
            if (x == '[')
                st.pushb(2);
            if (x == ')')
            {
                if (st.top() != 1)
                {
                    f = false;
                    break;
                }
                st.popb();
            }
            if (x == ']')
            {
                if (st.top() != 2)
                {
                    f = false;
                    break;
                }
                st.popb();
            }
        }
        if (f && st.top() == -1)
            cout << "YES\n";
        else
            cout << "NO\n";
        st.clr();
    }
    return 0;
}
