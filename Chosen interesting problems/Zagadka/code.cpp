#include "czag.h"
#include <bits/stdc++.h>
using namespace std;

void zagadka()
{
    vector<bool>vec;
    vector<bool>solv;

    int n=inicjuj();

    for(int i=0;i<n;i++)
        vec.push_back(0);

    srand(time(nullptr));

    while(zapytaj(vec)!=n/2)
    {
        for(int i=0;i<n;i++)
            vec[i]=rand()%2;
    }
    
    solv.push_back(vec[0]);
    for(int i=0;i<n-1;i++)
    {
        vec[0]=!vec[0];
        vec[i+1]=!vec[i+1];

        if(zapytaj(vec)==n/2)
            solv.push_back(vec[i+1]);
        else
            solv.push_back(!vec[i+1]);

        vec[0]=!vec[0];
        vec[i+1]=!vec[i+1];
    }
    
    if(zapytaj(solv)!=n)
        for(int i=0;i<solv.size();i++)
            solv[i]=!solv[i];

    odpowiedz(solv);
    return;
}