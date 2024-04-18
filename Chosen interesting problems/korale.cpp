//Korale O(n*log(n))
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

#define int long long

constexpr int mod = 1e9+9;
constexpr int maxn = 2e5+7;
constexpr int p = 200017;
constexpr int p2 = 200017;


int n;
int tab[maxn];

int pot2[maxn];
int pot[maxn];

int pref_hash[maxn];
int pref_hash_rev[maxn];

vector<int>all_k;

void prepere()
{
    pot[0]=1;
    for(int i=1;i<maxn;++i)
        pot[i]=(pot[i-1]*p)%mod;

    pot2[0]=1;
    for(int i=1;i<maxn;++i)
        pot2[i]=(pot2[i-1]*p2)%mod;

    pref_hash[0]=0;
    for(int i=1;i<=n;++i)
        pref_hash[i]=(pref_hash[i-1] + tab[i]*pot[i])%mod;

    pref_hash_rev[n+1]=0;
    for(int i=n;i>=1;--i)
        pref_hash_rev[i]=(pref_hash_rev[i+1] + tab[i]*pot2[n-i+1])%mod;
}

int get_hash(int a, int b)
{
    return 
    (
        (((pref_hash[b]-pref_hash[a-1]+mod)%mod)*pot[n-a+1])%mod
        +
        (((pref_hash_rev[a]-pref_hash_rev[b+1]+mod)%mod)*pot2[b])%mod
    )%mod;
}

int get_hash_pokaz(int a, int b)
{
    return (((pref_hash[b]-pref_hash[a-1]+mod)%mod)*pot[n-a+1])%mod;
}

int get_hash_rev_pokaz(int a, int b)
{
    return (((pref_hash_rev[a]-pref_hash_rev[b+1]+mod)%mod)*pot2[b])%mod;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>tab[i];

    prepere();

    int max_korale=0;

    for(int k=1;k<=n;++k)
    {
        map<pair<int,int>, bool>have;
        for(int i=1;i+k-1<=n;i+=k)//srednio O(log2(n))
        {
            pair<int,int>akt={get_hash_pokaz(i,i+k-1),get_hash_rev_pokaz(i,i+k-1)};
            if(akt.f>akt.s) swap(akt.f,akt.s);//akt.f<=akt.s
            have[akt]=1;
        }

        if(have.size()>max_korale)
        {
            max_korale=have.size();
            all_k.clear();
            all_k.push_back(k);
        }
        else if(have.size() == max_korale)
            all_k.push_back(k);
    }
    
    cout<<max_korale<<' '<<all_k.size()<<'\n';
    for(auto &u: all_k)
        cout<<u<<' ';
    return 0;
}