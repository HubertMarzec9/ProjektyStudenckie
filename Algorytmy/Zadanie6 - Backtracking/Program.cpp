#include <iostream>
#include <cstring>

using namespace std;

int minCost = INT16_MAX;
int **tabMin;

void answer(int n)
{
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(tabMin[i][j] == n*10)
                cout<<j<<" ";
        }
    }
}

void sub(int ** tabPom, int row, int col, int n)
{
    ///Wiersz|Kolumna

    for(int i=0;i<n;++i)
    {
        if(tabPom[row][i] != n*10)
            tabPom[row][i]--;

        if(tabPom[i][col] != n*10)
            tabPom[i][col]--;
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if(tabPom[i][j] != n*10)
            tabPom[i][j]--;
    }

    for (int i = row, j = col; i >= 0 && j < n; i--, j++)
    {
        if(tabPom[i][j] != n*10)
            tabPom[i][j]--;
    }

    for (int i = row, j = col; i < n && j < n; i++, j++)
    {
        if(tabPom[i][j] != n*10)
            tabPom[i][j]--;
    }

    for (int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if(tabPom[i][j] != n*10)
            tabPom[i][j]--;
    }
}

void add(int ** tabPom, int row, int col, int n)
{
    ///Wiersz|Kolumna

    for(int i=0;i<n;++i)
    {
        if(tabPom[row][i] != n*10)
            tabPom[row][i]++;
        if(tabPom[i][col] != n*10)
            tabPom[i][col]++;
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if(tabPom[i][j] != n*10)
            tabPom[i][j]++;
    }

    for (int i = row, j = col; i >= 0 && j < n; i--, j++)
    {
        if(tabPom[i][j] != n*10)
            tabPom[i][j]++;
    }

    for (int i = row, j = col; i < n && j < n; i++, j++)
    {
        if(tabPom[i][j] != n*10)
            tabPom[i][j]++;
    }

    for (int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if(tabPom[i][j] != n*10)
            tabPom[i][j]++;
    }
}

void fun(int n, int ** tab, int ** tabPom, int row = 0, int cost = 0)
{
    if(row == n && cost < minCost)
    {
        minCost = cost;
        for (int i = 0; i < n; i++) {
            memcpy(tabMin[i], tabPom[i], n * sizeof(int));
        }
        return;
    }

    if(row == n)
        return;

    if(cost >= minCost)
        return;

    for (int col = 0; col < n; col++) {
            if(tabPom[row][col] == 0)
            {
                tabPom[row][col] = n*10;
                cost += tab[row][col];
                add(tabPom, row, col, n);

                fun(n, tab, tabPom,row+1, cost);

                sub(tabPom, row, col, n);
                cost -= tab[row][col];
                tabPom[row][col] = 0;
            }
    }
}

int main()
{
    int n;
    cin>>n;

    int **tab; int **tabPom;
    tab = new int *[n];
    tabPom = new int *[n];
    tabMin = new int *[n];
    int x;

    for(int i=0;i<n;++i)
    {
        tab[i] = new int[n];
        tabPom[i] = new int[n];
        tabMin[i] = new int[n];
        for(int j=0;j<n;++j)
        {
            cin>>x;
            tab[i][j] = x;
            tabPom[i][j] = 0;
            tabMin[i][j] = 0;
        }
    }

    fun(n, tab, tabPom);
    answer(n);

    for(int i=0;i<n;++i)
    {
        delete [] tab[i];
        delete [] tabPom[i];
        delete [] tabMin[i];
    }

    delete [] tab;
    delete [] tabPom;
    delete [] tabMin;

    return 0;
}