#include <iostream>
#include <cmath>
#include <list>

using namespace std;

struct Wojownik
{
    int x, y, w, poz;

    Wojownik(){}

    Wojownik(int x, int y, int w, int poz)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->poz = poz;
    }
};

struct Para
{
    Wojownik w1;
    Wojownik w2;
    double o;

    Para()
    {
        this->o = INT16_MAX;
    }

    Para(Wojownik w1, Wojownik w2, double o)
    {
        this->w1 = w1;
        this->w2 = w2;
        this->o = o;
    }
};

double odleglosc(Wojownik w1, Wojownik w2)
{
    return sqrt(pow(w2.x - w1.x, 2) + pow(w2.y - w1.y, 2));
}

int compareX(Wojownik w1, Wojownik w2)
{
    return (w1.x < w2.x);
}

int compareY(Wojownik w1, Wojownik w2)
{
    return (w1.y < w2.y);
}

Para minPara(Para para1, Para para2)
{
    if (para1.o < para2.o)
    {
        return para1;
    }

    if (para1.o > para2.o)
    {
        return para2;
    }

    int minPoz1 = min(para1.w1.poz, para1.w2.poz);
    int minPoz2 = min(para2.w1.poz, para2.w2.poz);
    if (minPoz1 < minPoz2)
    {
        return para1;
    }
    if (minPoz1 > minPoz2)
    {
        return para2;
    }

    int maxPoz1 = max(para1.w1.poz, para1.w2.poz);
    int maxPoz2 = max(para2.w1.poz, para2.w2.poz);
    return (maxPoz1 < maxPoz2) ? para1 : para2;
}


Para fun(list<Wojownik> listWojownik)
{
    if(listWojownik.size() <= 3)
    {
        ///2 Elementy
        if(listWojownik.size() == 2)
        {
            return {listWojownik.front(), listWojownik.back(), odleglosc(listWojownik.front(), listWojownik.back())};
        }
        ///3 Elementy
        else
        {
            Para paraA = Para( *(listWojownik.begin()), *next(listWojownik.begin()), (odleglosc(*(listWojownik.begin()), *next(listWojownik.begin()))) );
            Para paraB = Para( *(listWojownik.begin()), *next(listWojownik.begin(),2), (odleglosc(*(listWojownik.begin()), *next(listWojownik.begin(),2))));
            Para paraC = Para( *next(listWojownik.begin()), *next(listWojownik.begin(),2), (odleglosc(*next(listWojownik.begin()), *next(listWojownik.begin(),2))) );

            return minPara(paraC, minPara(paraA,paraB));
        }
    }else
    {   ///>3 Elementy
        auto it = listWojownik.begin();
        double minDistance;
        Para paraA;
        Para paraB;
        Para paraCenter;
        list<Wojownik> listWojownikA = {};
        list<Wojownik> listWojownikB(listWojownik.begin(), listWojownik.end());
        list<Wojownik> listWojownikCenter = {};

        for(int i=0; i<listWojownik.size()/2 ;++i)
            it++;

        Wojownik midWoj = (*it);

        ///Rozdzielenie listy
        listWojownikA.splice( listWojownikA.begin(),listWojownikB,listWojownikB.begin(),next( listWojownikB.begin(), listWojownikB.size() / 2 ) );

        paraA = fun(listWojownikA);
        paraB = fun(listWojownikB);

        minDistance = min(paraB.o, paraA.o);

        ///Dodawanie elementów z (centrum+minDistance) listy
        for(auto & itWoj : listWojownik)
        {
            if (abs((double) (itWoj.x - midWoj.x) ) <= minDistance)
            {
                listWojownikCenter.push_back( itWoj );
            }
        }

        ///Sortowanie po Y
        listWojownikCenter.sort(compareY);

        for (auto itWojI = listWojownikCenter.begin(); itWojI != listWojownikCenter.end(); ++itWojI)
        {
            for (auto itWojJ = next(itWojI); itWojJ != listWojownikCenter.end() ; ++itWojJ)
            {
                Para pomParaCenter = Para((*itWojJ), (*itWojI), odleglosc((*itWojJ), (*itWojI)));
                paraCenter = minPara(paraCenter, pomParaCenter);
            }
        }

        return minPara(paraCenter, minPara(paraA,paraB));
    }
}

Wojownik walka(Para p)
{
    if(p.w1.w > p.w2.w)
    {
        cout<<p.w2.x<<" "<<p.w2.y<<"\n";
        return p.w2;
    }else if(p.w1.w < p.w2.w){
        cout<<p.w1.x<<" "<<p.w1.y<<"\n";
        return p.w1;
    }else
    {
        if(p.w1.poz < p.w2.poz)
        {
            cout<<p.w2.x<<" "<<p.w2.y<<"\n";
            return p.w2;
        }else
        {
            cout<<p.w1.x<<" "<<p.w1.y<<"\n";
            return p.w1;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
    Para para;
    int n, t, x, y, w;
    cin>>n>>t;

    list<Wojownik> listWojownik;

    for(int i=0; i<n ;++i)
    {
        cin>>x>>y>>w;
        listWojownik.emplace_back(x,y,w,i);
    }

    ///Sorotwanie po X
    listWojownik.sort(compareX);

    for(int i=0; i<t ;++i)
    {
        para = fun(listWojownik);
        Wojownik ww = walka(para);
        auto toDel = listWojownik.begin();
        while ( ww.poz != toDel->poz )
        {
            toDel++;
        }
        listWojownik.erase(toDel);
    }

    return 0;
}