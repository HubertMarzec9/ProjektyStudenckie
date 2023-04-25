#include <iostream>

using namespace std;

struct Person
{
    string s;
    unsigned int u;
    float w;
    unsigned int c;

    Person()
    {

    }

    Person(string s,unsigned int u,float w,unsigned int c)
    {
        this->s = s;
        this->u = u;
        this->w = w;
        this->c = c;
    }

    float uwc(int i,short * tab)
    {
        if(tab[i] == 1)
            return u;
        else if(tab[i] == 2)
            return w;
        else if(tab[i] == 3)
            return c;
        return 0;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
    int n,m;
    cin>>n;
    for(int j=0; j < n ;++j)
    {
        short tab[3];
        cin>>m;
        cin>>tab[0];
        cin>>tab[1];
        cin>>tab[2];
        float u;float w;short c;string s;

        cin >> s >> u >> w >> c;
        Person k = Person(s,u,w,c);

        for(int i=1;i<m;i++) {
            cin >> s >> u >> w >> c;
            Person k2 = Person(s,u,w,c);

            if(k.uwc(0,tab) < k2.uwc(0,tab))
            {
                k = k2;
            }
            else if(k.uwc(0,tab) == k2.uwc(0,tab))
            {
                if(k.uwc(1,tab) < k2.uwc(1,tab))
                {
                    k = k2;
                }
                else if(k.uwc(1,tab) == k2.uwc(1,tab))
                {
                    if(k.uwc(2,tab) < k2.uwc(2,tab))
                    {
                        k = k2;
                    }
                }
            }
        }
        cout<<k.s<<"\n";
    }

    return 0;
}