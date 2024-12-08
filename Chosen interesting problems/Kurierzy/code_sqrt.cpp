//O(n*sqrt(n))
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int max_n=500000;

pair<pair<int,int>,pair<int,int>> check[2*max_n + 1];//.f.f=indeks akcji .f.s=typ akcji: 0->poczatek 1->koniec .s.f=numer zapytania akcji .s.s=kandydat

int n,m;
int pierwiastek;
int podloga_pierwiastek;
int tab[max_n+7];

int pytania[max_n+7];//pomocnicze do liczenia i przechowywania odpoiedzi na pytania
int kandydat[max_n+7];
pair<int,int> przedzialy[max_n+7];

int licz[max_n+7];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=1;i<=n;i++)
    {
        cin>>tab[i];
    }

    pierwiastek=ceil(sqrt(n));
    podloga_pierwiastek=floor(sqrt(n));

    pair<int,int> slides[pierwiastek];//.f=wartosc .s=ile wartosci

    for(int i=1;i<=pierwiastek*podloga_pierwiastek;i+=pierwiastek)
    {
        int val=0;
        int number=0;
        for(int j=0;j<pierwiastek;j++)
        {
            if(number==0)
            {
                val=tab[i+j];
                number++;
            }
            else if(tab[i+j]==val) number++;
            else number--;
        }
        slides[int(ceil(float(i)/pierwiastek))]={val,number};
    }


    for(int i=1;i<=m;i++)
    {
        int a,b;cin>>a>>b;
        if(b<a) swap(a,b);
        przedzialy[i-1]={a,b};

        int val=0;
        int number=0;
        for(int j=a;j<=b;j++)
        {
            if(j%pierwiastek==1 && j+pierwiastek-1<=b)
            {
                // cout<<"pierwiastek: "<<int(ceil(float(j)/pierwiastek))<<" -> ";
                int numer_slides=int(ceil(float(j)/pierwiastek));
                if(number==0)
                {
                    val=slides[numer_slides].f;
                    number=slides[numer_slides].s;
                }
                else if(slides[numer_slides].f==val)
                {
                    number+=slides[numer_slides].s;
                }
                else
                {
                    if(slides[numer_slides].s < number)
                    {
                        number-=slides[numer_slides].s;
                    }
                    else
                    {
                        number=slides[numer_slides].s - number;
                        val=slides[numer_slides].f;
                    }
                }
                j += pierwiastek-1;
            }
            else
            {
                // cout<<"j: "<<j<<" -> ";
                if(number==0)
                {
                    val=tab[j];
                    number++;
                }
                else if(tab[j]==val) number++;
                else number--;
            }
            // cout<<val<<endl;
        }
        check[i-1]={{a,0},{i-1,val}};
        check[m+i-1]={{b,1},{i-1,val}};
        // cout<<"a: "<<a<<" b: "<<b<<" val: "<<val<<endl;
        kandydat[i-1]=val;
    }
    sort(check,check+2*m);


    // // TU NAPISAC ALGORYTM SPRAWDZAJACY KANDYDATOW
    int iter=0;
    for(int i=1;i<=n;i++)
    {
        // cout<<"pozycja: "<<i<<endl;
        while(check[iter].f.f==i && check[iter].f.s==0 && iter<2*m)
        {
            // cout<<"pytania["<<check[iter].s.f<<"]="<<licz[check[iter].s.s]<<endl;
            pytania[check[iter].s.f]=licz[check[iter].s.s];
            kandydat[check[iter].s.f]=check[iter].s.s;
            iter++;
        }
        licz[tab[i]]++;
        while(check[iter].f.f==i && check[iter].f.s==1 && iter<2*m)
        {
            pytania[check[iter].s.f]=licz[check[iter].s.s]-pytania[check[iter].s.f];
            iter++;
        }
    }
    for(int i=0;i<m;i++)
    {
        // cout<<pytania[i]<<endl;
        if(pytania[i] > (przedzialy[i].s-przedzialy[i].f+1)/2) cout<<kandydat[i]<<"\n";
        else cout<<0<<"\n";
    }
    return 0;
}