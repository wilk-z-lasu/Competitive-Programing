#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

//esencial values
constexpr short maxn=5e3+7;
short n,k,x;
int solv=1;

//coversion of input
bool know[maxn][maxn];
vector<short> vec[2*maxn];
inline short negativ(short v)
{
    if(v<=n)
        return v+n;
    else
        return v-n;
}

//count post order and stores in stack post_order
stack<short> post_order;
bool vis[2*maxn];
void count_post_order(short v)
{
    vis[v]=1;
    for(auto &u: vec[v])
        if(!vis[u])
            count_post_order(u);
    post_order.push(v);
}
void make_post_order()
{
    for(short i=1;i<=2*n;i++)
        if(!vis[i])
            count_post_order(i);
}

//2-SAT
short cc_number;
short cc[2*maxn];
void dfs(short v)
{
    cc[v]=cc_number;
    for(auto &u: vec[v])
        if(cc[u]==0)
            dfs(u);
}
void solv_2sat()
{
    while(!post_order.empty())
    {
        short top=post_order.top();
        post_order.pop();

        if(cc[top]==0)
        {
            cc_number++;
            dfs(top);
        }
    }
}

//variables to count how many arrangments can we make
bool color[maxn];
short color_number;
short con[maxn];
bool done[maxn];
pair<short,short> black[maxn];
pair<short,short> gray[maxn];
bool i_have_black;
bool i_have_gray;


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(short i=1;i<=n;i++)
    {
        cin>>k;  
        con[i]=k;
        if(k>0) i_have_black=1;
        if(k<n-1) i_have_gray=1;
        while(k--)
        {
            cin>>x;
            know[i][x]=1;
        }
    }
    
    for(short i=1;i<=n;i++)
        for(short j=1;j<=n;j++)
        {
            if(i==j) continue;
            if(know[i][j])
            {
                vec[i].push_back(negativ(j));
            // vec_odw[negativ(j)].push_back(i);
            }
            else
            {
                vec[negativ(i)].push_back(j);
            // vec_odw[j].push_back(negativ(i));
            }
        }

    make_post_order();
    for(short i=1;i<=2*n;i++)
    {
        vec[i].clear();
        vec[i].shrink_to_fit();
    }

    for(short i=1;i<=n;i++)
        for(short j=1;j<=n;j++)
        {
            if(i==j) continue;
            if(know[i][j])
            {
                // vec[i].push_back(negativ(j));
                vec[negativ(j)].push_back(i);
            }
            else
            {
                // vec[negativ(i)].push_back(j);
                vec[j].push_back(negativ(i));
            }
        }

    solv_2sat();

    for(short i=1;i<=n;i++)
    {
        if(cc[i]==cc[negativ(i)])
        {
            cout<<0;
            return 0;
        }
        if(cc[i] < cc[negativ(i)])
        {
            color[i]=1;
            color_number++;
        }
    }

    for(short i=1;i<=n;i++)
        for(short j=1;j<=n;j++)
        {
            if(color[j]==0 && know[i][j]==1)
                gray[i]={gray[i].f+1,j};
            else if(color[j]==1 && know[i][j]==0)
                black[i]={black[i].f+1,j};
        }

    bool flag=1;
    while(flag)
    {
        for(short i=1;i<=n;i++)
        {
            if(done[i]) 
            {
                if(i==n) flag=0;
                continue;
            }
            if(color[i]==1 && con[i]==color_number-1)
            {
                solv++;
                color[i]=0;
                color_number--;
                done[i]=1;
                for(short j=1;j<=n;j++)
                {
                    if(know[i][j]==0)
                        black[j].f--;
                    if(know[i][j]==1)
                        gray[j]={gray[j].f+1,i};
                }
                break;
            }
            else if(color[i]==0 && con[i]==color_number)
            {
                solv++;
                color[i]=1;
                color_number++;
                done[i]=1;
                for(short j=1;j<=n;j++)
                {
                    if(know[i][j]==0)
                        black[j]={black[j].f+1,i};
                    if(know[i][j]==1)
                        gray[j].f--;
                }
                break;
            }
            else if(color[i]==1 && gray[i].f==1 && black[gray[i].s].f==0)
            {
                solv++;
                short next=gray[i].s;

                color[i]=0;
                done[i]=1;
                for(short j=1;j<=n;j++)
                {
                    if(know[i][j]==0)
                        black[j].f--;
                    if(know[i][j]==1)
                        gray[j]={gray[j].f+1,i};
                }
                color[next]=1;
                done[next]=1;
                for(short j=1;j<=n;j++)
                {
                    if(know[next][j]==0)
                        black[j]={black[j].f+1,next};
                    if(know[next][j]==1)
                        gray[j].f--;
                }
                break;
            }
            else if(color[i]==0 && black[i].f==1 && gray[black[i].s].f==0)
            {
                solv++;
                short next=black[i].s;

                color[i]=1;
                done[i]=1;
                for(short j=1;j<=n;j++)
                {
                    if(know[i][j]==0)
                        black[j]={black[j].f+1,i};
                    if(know[i][j]==1)
                        gray[j].f--;
                }
                color[next]=0;
                done[next]=1;
                for(short j=1;j<=n;j++)
                {
                    if(know[next][j]==0)
                        black[j].f--;
                    if(know[next][j]==1)
                        gray[j]={gray[j].f+1,next};
                }
                break;
            }
            if(i==n) flag=0;
        }
    }

    if(!i_have_black || !i_have_gray)
        solv--;
    cout<<solv;

    return 0;
}