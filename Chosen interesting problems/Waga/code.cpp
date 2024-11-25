#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxi=62500;

int n,l,p;
int granica;
int dol;

stack<int>lewo[26];
stack<int>prawo[26];

int maxl=maxi;
int maxp=maxi;

int top;

//POCZATEK LEWEGO PLECAKA
int plecak_lewy[2*maxi+7];
/////////////////////////

//POCZATEK PRAWEGO PLECAKA
int plecak_prawy[2*maxi+7];
////////////////////////////

//POCZATEK NOWEGO PLECAKA
int plecak_nowy[2*maxi+7];
////////////////////

void wczytaj()//WCZYTANIE DANYCH
{
    cin>>n>>l>>p;

    for(int i=0;i<l;++i)
    {
        for(int j=0;j<n;++j)
        {
            int x;
            cin>>x;
            maxl+=x;
            lewo[i].push(x);
        }
    }

    for(int i=0;i<p;++i)
    {
        for(int j=0;j<n;++j)
        {
            int x;
            cin>>x;
            maxp+=x;
            prawo[i].push(x);
        }
    }
}

void preproces_lewo()
{
    // for(int i=0;i<=2*maxi;++i) plecak_lewy[i]=1e9;
    fill(&plecak_lewy[0],&plecak_lewy[2*maxi+1],1e9);
    plecak_lewy[maxl]=0;
    granica=maxl;
    dol=maxl;
}

void preproces_prawo()
{
    // for(int i=0;i<=2*maxi;++i) plecak_prawy[i]=1e9;
    fill(&plecak_prawy[0],&plecak_prawy[2*maxi+1],1e9);
    plecak_prawy[maxp]=0;
    granica=maxp;
    dol=maxp;
}

void przepisz_lewa()
{
    for(int iter=dol;iter<=granica;++iter)
    {
        if(plecak_lewy[iter]>plecak_nowy[iter]) 
        {
            plecak_lewy[iter]=plecak_nowy[iter];
        }
    }
}

void przepisz_prawa()
{
    for(int iter=dol;iter<=granica;++iter)
    {
        if(plecak_prawy[iter]>plecak_nowy[iter]) 
        {
            plecak_prawy[iter]=plecak_nowy[iter];
        }
    }
}

void preproces_nowy()
{
    // for(int i=dol;i<=granica;++i) plecak_nowy[i]=1e9;
    fill(&plecak_nowy[dol],&plecak_nowy[granica+1],1e9);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    wczytaj();

    preproces_lewo();
    fill(&plecak_nowy[0],&plecak_nowy[2*maxi+1],1e9);
    for(int i=0;i<l;++i)
    {
        top=0;

        for(int j=1;j<=n;++j)
        {
            top+=lewo[i].top();
            lewo[i].pop();

            for(int iter=max(0,dol-top);iter<=min(2*maxi,granica-top);++iter)
            {
                if(plecak_lewy[iter+top]+j<plecak_nowy[iter])
                {
                    plecak_nowy[iter]=plecak_lewy[iter+top]+j;
                    if(iter>granica)
                        granica=iter;
                    if(iter<dol)
                        dol=iter;
                }
            }
        }
        przepisz_lewa();
        preproces_nowy();
    }

    preproces_prawo();
    fill(&plecak_nowy[0],&plecak_nowy[2*maxi+1],1e9);
    for(int i=0;i<p;++i)
    {
        top=0;

        for(int j=1;j<=n;++j)
        {
            top+=prawo[i].top();
            prawo[i].pop();

            for(int iter=max(0,dol-top);iter<=min(2*maxi,granica-top);++iter)
            {
                if(plecak_prawy[iter+top]+j<plecak_nowy[iter])
                {
                    plecak_nowy[iter]=plecak_prawy[iter+top]+j;
                    if(iter>granica)
                        granica=iter;
                    if(iter<dol)
                        dol=iter;
                }
            }
        }
        przepisz_prawa();
        preproces_nowy();
    }

    int odp=2e9;
    for(int i=0;i<=2*maxi;++i)
    {
        if(odp>plecak_lewy[i]+plecak_prawy[i])
            odp=plecak_lewy[i]+plecak_prawy[i];
    }
    cout<<odp;

    return 0;
}