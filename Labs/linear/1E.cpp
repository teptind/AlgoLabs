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
};

int main()
{
    ios_base::sync_with_stdio(0);
    //freopen("file.in", "r", stdin);
    string s;
    int res = 0, x, y;
    MyList st;
    while (cin >> s)
    {
        //cout << s << endl;
        if (s != "*" && s != "-" && s != "+")
        {
            st.pushb((int)strtoll(s.c_str(), 0, 10));
            //cout << "pushed\n";
            continue;
        }
        x = st.top(); st.popb();
        y = st.top(); st.popb();
        if (s == "*")
            res = x * y;
        if (s == "-")
            res = y - x;
        if (s == "+")
            res = x + y;
        st.pushb(res);
    }
    cout << st.top() << endl;
    return 0;
}
