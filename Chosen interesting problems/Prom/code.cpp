#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1e5+7;
constexpr int inf=1e18+7;
constexpr int G=15;

int n;
string w;
char s;

vector<int>combi[G][G];

int dp[(1<<G)];

void calculate_combi()
{
    for(int i=0;i<G;i++)
    {
        for(int j=0;j<G;j++)
        {
            if(i==j || combi[i][i].empty() || combi[j][j].empty()) continue;
            vector<int>front;
            vector<int>back;
            int it=0;
            for(auto &v: combi[i][i])
            {
                while(it < combi[j][j].size() && combi[j][j][it] < v)
                    it++;
                front.push_back(it);
                back.push_back(combi[j][j].size() - it);
            }
            for(int idx=1;idx<front.size();idx++)
                front[idx]+=front[idx-1];
            for(int idx=back.size()-2;idx>=0;idx--)
                back[idx]+=back[idx+1];

            combi[i][j].push_back(back[0]);
            for(int idx=0;idx+1<front.size();idx++)
                combi[i][j].push_back(front[idx]+back[idx+1]);
            combi[i][j].push_back(front.back());
        }
    }
}

void wypisz(int mask, int ADD)
{
    cout<<"mask: "<<mask/2<<mask%2<<" add: "<<ADD<<endl;
    for(int pref=0; pref<=combi[ADD][ADD].size(); pref++)
    {
        int grup1=pref;
        int grup2=combi[ADD][ADD].size()-grup1;
        
        if(grup1>0) grup1--;
        if(grup2>0) grup2--;

        int add=0;
        for(int others=0; others<G; others++)
        {
            if(others==ADD) continue;
            if(((1<<others) & mask) == 0) continue;
            if(combi[others][others].empty()) continue; 
            add+=combi[ADD][others][pref];
        }
        cout<<(2*add + grup1*(grup1+1)/2 + grup2*(grup2+1)/2)<<' ';
    }
    cout<<endl;
}

int cost(int mask, int ADD)
{
    // wypisz(mask, ADD);

    int solv=inf;
    int l=0, r=combi[ADD][ADD].size()-1;

    int mid, solv1, solv2;
    while(l<r)
    {
        mid = (l+r)/2;
        solv1=0;
        {
            int grup1=mid;
            int grup2=combi[ADD][ADD].size()-grup1;
        
            if(grup1>0) grup1--;
            if(grup2>0) grup2--;

            for(int others=0; others<G; others++)
            {
                if(others==ADD) continue;
                if(((1<<others) & mask) == 0) continue;
                if(combi[others][others].empty()) continue; 
                solv1 += 2*combi[ADD][others][mid];
            }
            solv1 +=  grup1*(grup1+1)/2 + grup2*(grup2+1)/2;
        }
        solv2=0;
        {
            int grup1=mid+1;
            int grup2=combi[ADD][ADD].size()-grup1;
        
            if(grup1>0) grup1--;
            if(grup2>0) grup2--;

            for(int others=0; others<G; others++)
            {
                if(others==ADD) continue;
                if(((1<<others) & mask) == 0) continue;
                if(combi[others][others].empty()) continue; 
                solv2 += 2*combi[ADD][others][mid+1];
            }
            solv2 +=  grup1*(grup1+1)/2 + grup2*(grup2+1)/2;
        }
        // cout<<"mid: "<<mid<<" solv1: "<<solv1<<" solv2: "<<solv2<<endl;
        if(solv1 >= solv2)
            l=mid+1;
        else
            r=mid;
    }
    solv1=0;
    {
        int grup1=l;
        int grup2=combi[ADD][ADD].size()-grup1;
        
        if(grup1>0) grup1--;
        if(grup2>0) grup2--;

        for(int others=0; others<G; others++)
        {
            if(others==ADD) continue;
            if(((1<<others) & mask) == 0) continue;
            if(combi[others][others].empty()) continue; 
            solv1 += 2*combi[ADD][others][l];
        }
        solv1 +=  grup1*(grup1+1)/2 + grup2*(grup2+1)/2;
    }
    solv2=0;
    {
        int grup1=combi[ADD][ADD].size();
        int grup2=0;
        
        if(grup1>0) grup1--;
        if(grup2>0) grup2--;

        for(int others=0; others<G; others++)
        {
            if(others==ADD) continue;
            if(((1<<others) & mask) == 0) continue;
            if(combi[others][others].empty()) continue; 
            solv2 += 2*combi[ADD][others][combi[ADD][ADD].size()];
        }
        solv2 +=  grup1*(grup1+1)/2 + grup2*(grup2+1)/2;
    }
    // cout<<min(solv1,solv2)<<endl;
    return min(solv1,solv2);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>w;
    n=w.size();

    for(int i=1;i<=n;i++)
    {
        s=w[i-1];
        combi[s-'A'][s-'A'].push_back(i);
    }
    
    calculate_combi();

    for(int i=1;i<(1<<G);i++)
        dp[i]=inf;

    for(int mask=0;mask<(1<<G);mask++)
    {
        for(int ADD=0;ADD<G;ADD++)
        {
            if((1<<ADD) & mask) continue;

            if(combi[ADD][ADD].empty())
            {
                dp[mask | (1<<ADD)] = min(dp[mask | (1<<ADD)], dp[mask]);
                continue;
            }
            
            dp[mask | (1<<ADD)] = min(dp[mask | (1<<ADD)], dp[mask] + cost(mask, ADD));
        }
    }
    int solution=dp[(1<<G)-1];
    cout<<solution/2;
    if(solution%2!=0)
        cout<<".5";
    return 0;
}