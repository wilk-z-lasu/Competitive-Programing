// XXXI Olimpiada Informatyczna - 1 Etap
// Mateusz Woloszyk
// Solution for 100/100 pkt
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f first
#define s second

int max_abs;

int n,k;
ll a,b;
char x;
vector<char> tab;

constexpr ll p1_base=31;
constexpr ll p2_base=41;
constexpr ll p3_base=43;

int mod1=1e9+3247;
int mod2=1e9+9;
int mod3=1e9+11767;

vector<int> p1;
vector<int> p2;
vector<int> p3;

vector<int> h1;
vector<int> h2;
vector<int> h3;

int hash1;
int hash2;
int hash3;

map<pair<int,pair<int,int>>,int[27]>nastepca;
//.f=h1 .s.f=h2 .s.s=h2 

map<pair<int,pair<int,int>>,char>gen;
//.f=h1 .s.f=h2 .s.s=h2 

map<pair<int,pair<int,int>>,int>was;//czy juz taki hash rozpatrywalem, a jesli tak to na jakiej pozyjci //jesli tak to mam petle
//.f=h1 .s.f=h2 .s.s=h2 

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n>>k>>a>>b;
    if(n<0)//przyspieszenie modulowania
    {
        mod1=1;mod2=1;mod3=1;
    }
    max_abs=3*n+27;
    tab.push_back(0);
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        tab.push_back(x);
    }

    p1.push_back(1);
    p2.push_back(1);
    p3.push_back(1);
    for(int i=1;i<=max_abs+7;i++)
    {
        p1.push_back(((ll)p1[i-1]*p1_base)%(ll)mod1);
        p2.push_back(((ll)p2[i-1]*p2_base)%(ll)mod2);
        p3.push_back(((ll)p3[i-1]*p3_base)%(ll)mod3);
    }

    h1.push_back(0);
    h2.push_back(0);
    h3.push_back(0);
    for(int i=1;i<=n;i++)
    {
        h1.push_back(((ll)h1[i-1]+(ll)(tab[i]-'a'+1)*(ll)p1[i])%(ll)mod1);
        h2.push_back(((ll)h2[i-1]+(ll)(tab[i]-'a'+1)*(ll)p2[i])%(ll)mod2);
        h3.push_back(((ll)h3[i-1]+(ll)(tab[i]-'a'+1)*(ll)p3[i])%(ll)mod3);
    }

    for(int i=k;i<=n-1;i++)
    {
        //sprawdzam jaka litere generuje hash od i-k+1 do i na pozycji i+1
        hash1=((((ll)(h1[i]-h1[i-k]+mod1)%(ll)mod1)*(ll)p1[max_abs-i])%(ll)mod1);
        hash2=((((ll)(h2[i]-h2[i-k]+mod2)%(ll)mod2)*(ll)p2[max_abs-i])%(ll)mod2);
        hash3=((((ll)(h3[i]-h3[i-k]+mod3)%(ll)mod3)*(ll)p3[max_abs-i])%(ll)mod3);
        nastepca[{hash1,{hash2,hash3}}][tab[i+1]-'a'+1]++;
    }

    for(auto u: nastepca)
    {
        pair<int,int>maxi={0,0};
        //.f=maksymalne uzycie litery .s=litera
        for(int i=1;i<=26;i++)
            if(u.s[i]>maxi.f)
                maxi={u.s[i],i};
        gen[u.f]='a'+maxi.s-1;
    }
    nastepca.clear();

    for(int i=n;i<=b;i++)
    {
        hash1=((((ll)(h1[i]-h1[i-k]+mod1)%(ll)mod1)*(ll)p1[max_abs-i])%(ll)mod1);//hash z jakego tworze nastepna literke na pozycji i+1
        hash2=((((ll)(h2[i]-h2[i-k]+mod2)%(ll)mod2)*(ll)p2[max_abs-i])%(ll)mod2);//hash z jakego tworze nastepna literke na pozycji i+1
        hash3=((((ll)(h3[i]-h3[i-k]+mod3)%(ll)mod3)*(ll)p3[max_abs-i])%(ll)mod3);//hash z jakego tworze nastepna literke na pozycji i+1
        if(was.find({hash1,{hash2,hash3}})!=was.end())
        {
            for(;a<=was[{hash1,{hash2,hash3}}];a++)//wypisuje od a do konca powtorzenia
                cout<<tab[a];
            int dys=b-a+1;

            a=a-was[{hash1,{hash2,hash3}}]-1;//jak dalko od konca powtorzenie zaczynam wypisywac
            a%=(i-was[{hash1,{hash2,hash3}}]);//robie tyle petli ile moge

            for(int j=1;j<=dys;j++)//ide od a wlacznie przez dys krokow
                cout<<tab[was[{hash1,{hash2,hash3}}]+1+(a+j-1)%(i-was[{hash1,{hash2,hash3}}])];
            return 0;
        }
        was[{hash1,{hash2,hash3}}]=i;

        if(gen.find({hash1,{hash2,hash3}})==gen.end())
            tab.push_back('a');
        else
            tab.push_back(gen[{hash1,{hash2,hash3}}]);

        h1.push_back((ll)(h1[i]+(tab[i+1]-'a'+1)*(ll)p1[i+1])%(ll)mod1);
        h2.push_back((ll)(h2[i]+(tab[i+1]-'a'+1)*(ll)p2[i+1])%(ll)mod2);
        h3.push_back((ll)(h3[i]+(tab[i+1]-'a'+1)*(ll)p3[i+1])%(ll)mod3);
    }

    for(ll i=a;i<=b;i++)
        cout<<tab[i];
    return 0;
}