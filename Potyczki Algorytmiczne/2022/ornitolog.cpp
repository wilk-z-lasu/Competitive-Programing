#include <bits/stdc++.h>
using namespace std;
int spr(int a,int b)
{
    if(a<b) return 1;
    if(a>b) return 0;
    if(a==b) return 2;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin>>n;

    int tab[n];
    for(int i = 0;i<n;i++)
    {
        cin>>tab[i];
    }

    int odp[n];
    for(int i = 0; i<n-1;i++)
    {
        odp[i]=spr(tab[i],tab[i+1]);
    }


//ROBIE CIAGI OD 0 I OD 1
    //tworze 1 ciag zaczynajacy sie strzalki w gore
    int ciag_1[n+7];
    for(int i = 0; i<n;i+=2)
    {
        ciag_1[i]=1;
        ciag_1[i+1]=0;
    }

    //tworze 2 ciag zaczynajacy sie strzalk w dol
    int ciag_2[n+7];
    for(int i = 0; i<n;i+=2)
    {
        ciag_2[i]=0;
        ciag_2[i+1]=1;
    }

    int l_1=0;
    int l_2=0;
    for(int i = 0; i<n-1;i++)
    {
        if(odp[i]!=ciag_1[i])
        {
            l_1++;
            i++;
        }
    }
    for(int i = 0; i<n-1;i++)
    {
        if(odp[i]!=ciag_2[i])
        {
            l_2++;
            i++;
        }
    }
    cout<<min(l_1,l_2);
    return 0;
}