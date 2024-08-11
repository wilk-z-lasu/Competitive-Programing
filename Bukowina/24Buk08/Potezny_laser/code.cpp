#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=5e5+7;
constexpr int inf=1e9+7;

int n;
int xp, yp, xk, yk;
int xw,yw;
vector<pair<pair<int,int>,int>>vec;

vector<int>graf[2*maxn];

struct point
{
    int x, y, id;
}points[maxn];


int spec1,spec2;

int koszt[2*maxn];
void bfs()
{
    for(int i=1;i<2*maxn;i++)
        koszt[i]=inf;
    queue<int>q;
    koszt[points[n+1].x]=0;
    q.push(points[n+1].x);
    koszt[points[n+1].y+maxn]=0;
    q.push(points[n+1].y+maxn);
    while(!q.empty())
    {
        int top=q.front();
        q.pop();

        for(auto &u: graf[top])
            if(koszt[u]==inf)
            {
                koszt[u]=koszt[top]+1;
                q.push(u);
            }
    }
}

void fastscan(int &number)//z geegs for geeks (chyab)
{ 
    //variable to indicate sign of input number 
    bool negative = false; 
    register int c; 
  
    number = 0; 
  
    // extract current character from buffer 
    c = getchar(); 
    if (c=='-') 
    { 
        // number is negative 
        negative = true; 
  
        // extract the next character from the buffer 
        c = getchar(); 
    } 
  
    // Keep on extracting characters if they are integers 
    // i.e ASCII Value lies from '0'(48) to '9' (57) 
    for (; (c>47 && c<58); c=getchar()) 
        number = number *10 + c - 48; 
  
    // if scanned input has a negative sign, negate the 
    // value of the input number 
    if (negative) 
        number *= -1; 
}

int32_t main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);

    // cin>>n>>xp>>yp>>xk>>yk;
    fastscan(n);
    fastscan(xp);
    fastscan(yp);
    fastscan(xk);
    fastscan(yk);

    for(int i=1;i<=n;i++)
    {
        // cin>>xw>>yw;
        fastscan(xw);
        fastscan(yw);
        vec.push_back({{xw,yw},i});
    }
    vec.push_back({{xp,yp},n+1});
    vec.push_back({{xk,yk},n+2});

    sort(vec.begin(),vec.end());
    int numer=0;
    for(int i=0;i<vec.size();i++)
    {
        ++numer;
        points[vec[i].s].x=numer;
        points[vec[i].s].id=vec[i].s;

        while(i+1<vec.size() && vec[i].f.f==vec[i+1].f.f)
        {
            i++;
            points[vec[i].s].x=numer;
            points[vec[i].s].id=vec[i].s;
        }
    }

    for(int i=0;i<vec.size();i++)
        swap(vec[i].f.f,vec[i].f.s);

    sort(vec.begin(),vec.end());
    numer=0;
    for(int i=0;i<vec.size();i++)
    {
        ++numer;
        points[vec[i].s].y=numer;
        while(i+1<vec.size() && vec[i].f.f==vec[i+1].f.f)
        {
            i++;
            points[vec[i].s].y=numer;
        }
    }

    for(int i=1;i<=n+2;i++)
    {
        graf[points[i].x].push_back(maxn+points[i].y);
        graf[maxn+points[i].y].push_back(points[i].x);
    }

    spec1 = points[n+2].x;
    spec2 = points[n+2].y + maxn;

    bfs();

    if(min(koszt[spec1],koszt[spec2])==inf)
        cout<<-1;
    else
        cout<<min(koszt[spec1],koszt[spec2]);

    return 0;
}