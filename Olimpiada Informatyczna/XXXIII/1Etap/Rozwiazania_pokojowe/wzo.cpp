#include <bits/stdc++.h>
using namespace std;

#define sz(A) (int)A.size()
#define f first
#define s second
#define pb push_back
#define pi pair<int,int>

constexpr int maxn = 200+7;
constexpr int maxk = 2500+7;

constexpr int inf = 1e9+7;

int N,K;
int Start[maxn][maxn];//initial configuration
int End[maxn][maxn];//final configuration
vector<pair<int,pi>> moves;
pi Rep[maxn][maxn];
pi main_in_Rep[maxn][maxn];
int n;//n for 15 puzzle

int sufit(int a, int b){
    int odp = a/b;
    if(a%b!=0)
        ++odp;
    return odp;
}

struct King {
    int real_x, real_y;
    int x, y;
    int real_id;
    int real_ending_x, real_ending_y;
    int ending_x, ending_y;
    int id;//id used in 15 puzzle
    bool is_real = 0; //otherwise is originally an empty tile
    void record_real_move() //records real move
    {
        if(is_real)
            moves.pb({real_id,{real_y, real_x}});
    }
    void real_move(char c)//moves king in range of his big tile
    {
        if(c=='U')
            real_y--;
        else if(c=='D')
            real_y++;
        else if(c=='L')
            real_x--;
        else if(c=='R')
            real_x++;
        record_real_move();
    }
    void move_to_starting_position() //moves king to his starting position in his big tile
    {
        // cout<<"Moving king "<<real_id<<" to starting position "<<main_in_Rep[y][x].f<<" "<<main_in_Rep[y][x].s<<"\n";
        if(real_x == main_in_Rep[y][x].s && real_y == main_in_Rep[y][x].f)
        {
            // cout<<"King "<<real_id<<" is already in the correct position\n";
            return;
        }
        else if(real_x == main_in_Rep[y][x].s + 1 && real_y == main_in_Rep[y][x].f)
        {
            // cout<<"King "<<real_id<<" is to the right of his target, moving left\n";
            real_move('L');
        }
        else if(real_x == main_in_Rep[y][x].s && real_y == main_in_Rep[y][x].f + 1)
        {
            // cout<<"King "<<real_id<<" is below his target, moving up\n";
            real_move('U');
        }
        else if(real_x == main_in_Rep[y][x].s + 1 && real_y == main_in_Rep[y][x].f + 1)
        {
            // cout<<"King "<<real_id<<" is diagonally misplaced, moving around\n";
            real_move('U');
            real_move('L');
        }
    }
} Kings[100*100+7];//first k kings are real

void get_input() {
    cin>>N>>K;
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            cin>>Start[i][j];
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            cin>>End[i][j];
}
void calculate_representatives() {
    n = sufit(N,2);
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            Rep[i][j] = {sufit(i,2), sufit(j,2)};
    
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            main_in_Rep[i][j] = {2*i-1, 2*j-1};
}
void map_kings()
{
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
        {
            if(Start[i][j]==0)
                continue;
            Kings[Start[i][j]].real_x = j;
            Kings[Start[i][j]].real_y = i;
            Kings[Start[i][j]].x = Rep[i][j].s;
            Kings[Start[i][j]].y = Rep[i][j].f;
            Kings[Start[i][j]].real_id = Start[i][j];
            Kings[Start[i][j]].is_real = true;
        }
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
        {
            if(End[i][j]==0)
                continue;
            Kings[End[i][j]].real_ending_x = j;
            Kings[End[i][j]].real_ending_y = i;
            Kings[End[i][j]].ending_x = Rep[i][j].s;
            Kings[End[i][j]].ending_y = Rep[i][j].f;
            Kings[End[i][j]].id = Rep[i][j].f*n + Rep[i][j].s;
        }
}
void move_kings_to_starting_positions()
{
    for(int i=1;i<=K;++i)
        Kings[i].move_to_starting_position();
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    get_input();
    calculate_representatives();
    map_kings();
    move_kings_to_starting_positions();
    
    //move kings to their ending big tiles

    // for(int i=1;i<=K;++i)
    //     cout<<Kings[i].real_id<<" "<<Kings[i].real_y<<" "<<Kings[i].real_x<<"\n";
    
    cout<<"TAK\n";
    cout<<sz(moves)<<'\n';
    for(auto &u: moves)
        cout<<u.f<<' '<<u.s.f<<' '<<u.s.s<<'\n';
    return 0;
}