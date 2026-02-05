#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
#define li __int128
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=2e5+7;
constexpr int MOD=1e9+7;

int n,k;
string w1,w2;

const int ile_p=2;
const li p[ile_p] = {37, 31};
li mod[ile_p]={1000000000000002137, 1000000000910002139};
li P[ile_p][maxn];
li H1[ile_p]={0,0};
li H2[ile_p]={0,0};

void make_hash()
{
    P[0][0] = 1;
    P[1][0] = 1;
    for(int i=1;i<=n;++i)
    {
        P[0][i] = (P[0][i-1]*p[0])%mod[0];
        P[1][i] = (P[1][i-1]*p[1])%mod[1];
    }
    for(int i=1;i<=n;++i)
    {
        H1[0] = (H1[0] + ((li)(w1[i]-'a'+1)*P[0][i])%mod[0])%mod[0];
        H1[1] = (H1[1] + ((li)(w1[i]-'a'+1)*P[1][i])%mod[1])%mod[1];

        H2[0] = (H2[0] + ((li)(w2[i]-'a'+1)*P[0][i])%mod[0])%mod[0];
        H2[1] = (H2[1] + ((li)(w2[i]-'a'+1)*P[1][i])%mod[1])%mod[1];
    }
}

void print_li(li x)
{
    if(x==0)
    {
        cout<<"0";
        return;
    }
    string s;
    while(x>0)
    {
        s.pb((char)(x%10+'0'));
        x/=10;
    }
    reverse(s.begin(),s.end());
    cout<<s;
}


int get_special=0;
int get_common=0;
int skip = 0;
int special = 0;
int common = 1;

void get_odp()
{
    cout<<((get_special*special)%MOD + (get_common*common)%MOD)%MOD; 
    exit(0);
}

vector<vector<int>> multiply(vector<vector<int>>& a, vector<vector<int>>& b)
{
    vector<vector<int>> wyn={{0,0},{0,0}};
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
            for(int z=0;z<2;++z)
                wyn[i][j] = (wyn[i][j] + (a[i][z]*b[z][j])%MOD)%MOD;
    return wyn;
}

vector<vector<int>> pot(vector<vector<int>> &a, int b)
{
    vector<vector<int>> wyn={{1,0},{0,1}};
    while(b>0)
    {
        if(b%2==1)
        {
            wyn = multiply(wyn,a);
        }
        a = multiply(a,a);
        b /= 2;
    }
    return wyn;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k;
    cin>>w1;
    cin>>w2;
    w1 = '#' + w1;
    w2 = '#' + w2;

    if(k==0)
    {
        if(w1==w2)
            cout<<1;
        else
            cout<<0;
        return 0;
    }
    if(n==1)
    {
        cout<<0;
        return 0;
    }
    
    make_hash();

    if(H1[0] == H2[0] && H1[1] == H2[1])
        get_special=1;
    for(int i=1;i<=n-1;++i)
    {
        
        H2[0] = (H2[0] - ((li)(w2.back()-'a'+1)*P[0][n])%mod[0] + mod[0]) % mod[0];
        H2[1] = (H2[1] - ((li)(w2.back()-'a'+1)*P[1][n])%mod[1] + mod[1]) % mod[1];

        H2[0] = (H2[0]*p[0]) % mod[0];
        H2[1] = (H2[1]*p[1]) % mod[1];

        H2[0] = (H2[0] + ((li)(w2.back()-'a'+1)*p[0]) % mod[0]) % mod[0];
        H2[1] = (H2[1] + ((li)(w2.back()-'a'+1)*p[1]) % mod[1]) % mod[1];
        w2.pop_back();

        if(H1[0] == H2[0] && H1[1] == H2[1])
            get_common++;
    }

    vector<vector<int>>matrix={{0,n-1},{1,n-2}};
    vector<vector<int>>result=pot(matrix,k);

    special = result[0][0];
    common = result[1][0];

    get_odp();
    return 0;
}