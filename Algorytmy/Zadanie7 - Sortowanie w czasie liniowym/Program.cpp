#include <iostream>

using namespace std;

struct Mysliwy{
    string name;
    Mysliwy *next;

    Mysliwy(string name)
    {
        this->name = name;
        this->next = nullptr;
    }
};

struct List
{
    Mysliwy *first;
    Mysliwy *last;

    List()
    {
        first = nullptr;
        last = nullptr;
    }

    void add(string name)
    {
        auto *pom = new Mysliwy(name);
        if(first != nullptr)
        {
            last->next = pom;
            last = pom;
        }else{
            first = pom;
            last = pom;
        }

    }

    void show()
    {
        while (first != last) {
            cout<<first->name<<" ";
            first = first->next;
        }
        cout<<last->name<<" ";
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
    int n, k, p;
    string name;

    List list[100][10];

    cin>>n;

    for(int i=0; i<n; ++i)
    {
        cin>>name>>k>>p;
        list[k][p].add(name);
    }


    for(int i = 99; i >= 0; --i)
    {
        for(int j = 0; j < 10; ++j)
        {
            if(list[i][j].first != nullptr)
                list[i][j].show();
        }
    }

    return 0;
}