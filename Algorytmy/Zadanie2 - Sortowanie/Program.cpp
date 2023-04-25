#include <iostream>

using namespace std;

struct Tops
{
    string s;
    unsigned int w;

    void setS(string s)
    {
        this->s = s;
    }

    void setW(unsigned int w)
    {
        this->w = w;
    }

    void print()
    {
        cout<<this->s<<"-"<<this->w<<" ";
    }
};

int pow2(int i)
{
    if(i == 1 || i == 0) return 1;
    int x = 2;
    for(int j=2;j<i;j++)
    {
        x *= 2;
    }
    return x;
}

bool czyPotega2(unsigned int w)
{
    for(int i=0;i<=32;i++)
    {
        if( pow2(i) == w)
            return true;
    }
    return false;
}

void sortowanie(int n, Tops *tab)
{
    Tops pom;
    int j;
    for(int i=1; i<n; i++)
    {
        if(tab[i].w < tab[i - 1].w)
        {
            pom = tab[i];

            for (j=i-1; (j>=0) && (tab[j].w > pom.w); j--)
            {
                tab[j+1] = tab[j];
            }
            tab[j+1] = pom;
        }
    }
//Tablica posortowana rosnaco

    for(int i=0; i<n; i++)
    {
        tab[i].print();
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
    unsigned short t,n;
    unsigned int w;
    string s;

    cin>>t;
    for(int i=0;i<t;++i)
    {
        int t1 = 0, t2 = 0;
        cin>>n;
        Tops* tops = new Tops[n];
        Tops* tops2 = new Tops[n];
        for(int j=0;j<n;++j)
        {
            cin>>s>>w;
            if(czyPotega2(w))
            {
                tops[t1].setS(s);
                tops[t1].setW(w);
                t1++;
            }else
            {
                tops2[t2].setS(s);
                tops2[t2].setW(w);
                t2++;
            }
        }
        sortowanie(t1,tops);
        sortowanie(t2,tops2);
        cout<<"\n";
    }

    return 0;
}