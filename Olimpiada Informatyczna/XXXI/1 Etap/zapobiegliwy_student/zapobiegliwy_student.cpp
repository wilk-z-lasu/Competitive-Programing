// XXXI Olimpiada Informatyczna - 1 Etap
// Mateusz Woloszyk
// Solution for 100/100 pkt

#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second
constexpr int maxn=500000+7;
constexpr int inf=1e9+7;

int n;
int a,b;

vector<pair<int,pair<int,int>>>vec;
vector<pair<int,pair<int,int>>>vec2;

vector<int> lis(maxn);
vector<int> obc(maxn);//index obecnego
vector<int> ans(maxn);//przodkowie

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>a>>b;
        vec.push_back({a,{b,i}});
    }
    sort(vec.begin(),vec.end());

    for(int i=0;i<maxn;i++)
        lis[i]=inf;
        
    for(int i=0;i<maxn;i++)
        ans[i]=inf;

    for(int i=0;i<vec.size();i++)
    {
        // cout<<vec[i].f<<" "<<vec[i].s.f<<" "<<vec[i].s.s<<endl;
        auto wzk=upper_bound(lis.begin(),lis.end(),vec[i].f);
        if(vec[i].s.f<*wzk)
        {
            *wzk=vec[i].s.f;
            obc[(wzk-lis.begin())]=i+1;//vec[i].s.s
            if((wzk-lis.begin())>0)
                ans[i+1]=obc[(wzk-lis.begin())-1];
        }
    }
    int v;
    for(int i=maxn-1;i>=0;--i)
    {
        if(lis[i]!=inf)
        {
            v=i;
            break;
        }
    }
    v=obc[v];

    stack<int>solv1;
    while(v!=inf)
    {
        solv1.push(vec[v-1].s.s);//push odpowiedzi
        int lv=v;
        v=ans[v];
        ans[lv]=inf;
    }

    for(int i=0;i<vec.size();i++)
        vec2.push_back({vec[i].s.f,{vec[i].f,vec[i].s.s}});
    sort(vec2.begin(),vec2.end());

    int koniec=0;//koniec elementu
    int koniec_r=0;//koniec rozszerzenia
    int tmp_koniec=0;//koniec elementu
    int tmp_koniec_r=0;//koniec rozszerzenia
    int gosc=0;
    int rozszerzenie=0;
    int solv2=0;
    queue<int>goscie;
    queue<int>rozszerzenia;
    
    for(int i=0;i<vec2.size();i++)
    {
        if(gosc==0 && vec2[i].s.f>=koniec_r)
        {
            goscie.push(vec2[i].s.s);
            gosc++;
            tmp_koniec=vec2[i].f;
        }
        else if(rozszerzenie==0 && vec2[i].s.f>=koniec)
        {
            rozszerzenia.push(vec2[i].s.s);
            rozszerzenie++;
            tmp_koniec_r=vec2[i].f;
        }
        if(gosc==1 && rozszerzenie==1)
        {
            koniec=tmp_koniec;
            gosc=0;
            koniec_r=tmp_koniec_r;
            if(koniec_r<koniec)
                koniec_r=koniec;
            rozszerzenie=0;
            solv2++;
        }
    }
    if((int)solv1.size()-1>=solv2)
    {
        cout<<(int)solv1.size()-1<<'\n';
        //aby uzyskac odpowiedz wypisuje wszystkei polaczone do ostatniego
        int lacznik=solv1.top();
        solv1.pop();
        while(!solv1.empty())
        {
            cout<<solv1.top()<<' '<<lacznik<<'\n';
            solv1.pop();
        }
    }
    else
    {
        cout<<solv2<<'\n';
        for(int i=0;i<solv2;i++)
        {
            cout<<goscie.front()<<' '<<rozszerzenia.front()<<'\n';
            goscie.pop();
            rozszerzenia.pop();
        }
    }
    return 0;
}