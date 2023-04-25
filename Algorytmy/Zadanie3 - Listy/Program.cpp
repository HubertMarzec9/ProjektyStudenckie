#include <iostream>

using namespace std;

struct Person
{
    int name;
    bool lp;
    Person* next;
    Person* prev;

    Person(){}

    Person(int name){
        this->name = name;
        this->next = nullptr;
        this->prev = nullptr;
    }

    Person(int name, bool lp)
    {
        this->name = name;
        this->lp = lp;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

int clamp(int i, int n) {
    if (i >= 0 && i < n) {
        return i;
    }
    return (i < 0) ? (i == -1) ? n-1 : n-2 : (i == n) ? 0 : 1;
}

struct StackOfPairs
{
    Person *first;
    Person *last;

    int size;

    StackOfPairs() {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    void addPairs(Person *p)
    {
        Person* pom = new Person(p->name);
        if(this->size >= 2)
        {
            this->last->next = pom;
            this->last = pom;
        }
        else if(this->size == 0)
        {
            this->first = pom;
            this->last = pom;
            this->first->next = pom;
        }else if(this->size == 1)
        {
            this->first->next = pom;
            this->last = pom;
        }
        size++;
    }

    void delPairs()
    {
        size--;
        if(size == 0)
            first = nullptr;
        else
            first = first->next;
    }
};

struct List {
    Person *first;
    Person *last;

    int *stack;
    StackOfPairs* stackOfPairs;

    int k;
    int size;

    List(int n, int p, int k)
    {
        this->stack = new int[n]{0};
        this->stackOfPairs = new StackOfPairs();
        this->k = k;
        this->size = n * 2;
        add(n, p);
    }

    void setK(int k)
    {
        this->k = k;
        if(k == 1)
        {
            last = first->prev;
        }
        else
        {
            last = first->next;
        }
    }

    void add(int n, int p) {
        first = new Person(p, true);
        first->next = first;
        first->prev = first;
        last = first;

        int i = clamp(p, n);

        for (int j = 0; j < n - 1; j++) {
            Person *p1 = new Person(clamp(i - 2, n), false);
            Person *p2 = new Person(clamp(i - 1, n), true);

            if (j == 0) {
                first->next = p1;
            }

            last->next = p1;

            p1->prev = last;
            p1->next = p2;
            p2->prev = p1;
            p2->next = first;

            first->prev = p2;
            last = p2;

            i = clamp(i - 1, n);
        }

        Person *p3 = new Person(((p - 1 < 0) ? n-1 : p-1) , false);
        first->prev = p3;
        p3->prev = last;
        p3->next = first;
        last->next = p3;
        last = p3;
    }

    void del()
    {
        size--;
        if(++this->stack[first->name] == 2)
        {
            this->stack[first->name] = 0;
            this->stackOfPairs->addPairs(this->first);
        }

        if(this->k == 1)
        {
            last->next = first->next;
            last->next->prev = last;
            first = last;
        }
        else
        {
            last->prev = first->prev;
            last->prev->next = last;
            first = last;
        }

    }

};

void show(List *list)
{
    Person* f = list->first;

    if(list->k == 1)
    {
        while (list->first != list->last)
        {
            cout<<list->first->name<<" ";
            list->first = list->first->next;
        }
        cout<<list->last->name<<" ";
    }else
    {
        while (list->first != f->next)
        {
            cout<<list->first->name<<" ";
            list->first = list->first->prev;
        }
        cout<<f->next->name<<" ";
    }

    list->first = f;
    cout<<"\n";
}

void operations(int op, int x, List *list)
{

    if(list->k == 1)
        for(int i = 0;i < x-1;i++)
        {
            list->first = list->first->next;
            list->last = list->first->prev;
        }
    else
        for(int i = 0;i < x-1;i++)
        {
            list->first = list->first->prev;
            list->last = list->first->next;
        }

    if(op == 2)
        list->setK((list->k == 0)? 1 : 0);

    else if(op == 0)
        show(list);

    else if(op == 1)
    {
        int flag;
        cin>>flag;

        list->del();
        list->setK((list->k == 0)? 1 : 0);

        if(list->stackOfPairs->size > 0 && (flag == 1 || (flag == 0 && (list->size <= 3)) ) ) {

            Person *pom1 = new Person(list->stackOfPairs->first->name, false);
            Person *pom2 = new Person(list->stackOfPairs->first->name, true);

            list->stackOfPairs->delPairs();
            list->size = list->size +  2;

            if(list->k == 0)
            {
                pom2->next = list->first;
                pom2->prev = list->first->prev;

                list->first->prev->next = pom2;
                list->first->prev = pom2;

                ////
                pom1->next = list->last->next;
                pom1->prev = list->last ;

                list->last->next->prev = pom1;
                list->last->next = pom1;
            }else
            {
                pom2->next = list->last;
                pom2->prev = list->last->prev;

                list->last->prev->next = pom2;
                list->last->prev = pom2;

                ////
                pom1->next = list->first->next;
                pom1->prev = list->first ;

                list->first->next->prev = pom1;
                list->first->next = pom1;
            }
        }
    }
}

int main()
{
    int n, p, k, m;
    cin >> n >> p >> k >> m;

    List *list = new List(n, p, 1);
    
    if(k == 0)
        list->setK(0);

    int op, x;
    for(int i=0 ;i < m; ++i)
    {
        cin>> op >> x;
        operations(op,x,list);
    }

    return 0;
}