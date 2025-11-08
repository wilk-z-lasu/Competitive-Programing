#include <bits/stdc++.h>
using namespace std;

#define sz(A) (int)A.size()
#define f first
#define s second
#define pb push_back
#define pi pair<int,int>

constexpr int maxn = 200+7;
constexpr int maxk = 2500+7;
constexpr int maxi = 107*107;

constexpr int inf = 1e9+7;

int N,K;
int Start[maxn][maxn];//initial configuration
int End[maxn][maxn];//final configuration
vector<pair<int,pi>> moves;
pi Rep[maxn][maxn];
pi main_in_Rep[maxn][maxn];
int n;//n for 15 puzzle
int KingtoTile[maxi];
int TiletoKing[maxi];
int Ending_TiletoKing[maxi];
int fake_king_id;
int IDtoKing[maxi];
int tiletoID[maxi];

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
    void move_to_ending_position() //moves king to his ending position in a big tile
    {
        if(real_x == ending_x && real_y == ending_y)
            return;
        else if(real_x == ending_x - 1 && real_y == ending_y)
            real_move('R');
        else if(real_x == ending_x && real_y == ending_y - 1)
            real_move('D');
        else if(real_x == ending_x - 1 && real_y == ending_y - 1)
        {
            real_move('D');
            real_move('R');
        }    
    }
    void move(char c)//moves king in 15 puzzle
    {
        if(c=='U')
        {
            real_move('U');
            real_move('U');
            y--;
        }
        if(c=='D')
        {
            real_move('D');
            real_move('D');
            y++;
        }
        if(c=='L')
        {
            real_move('L');
            real_move('L');
            x--;
        }
        if(c=='R')
        {
            real_move('R');
            real_move('R');
            x++;
        }
    }
} Kings[maxi];//first k kings are real

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
            Kings[End[i][j]].id = (Rep[i][j].f-1)*n + (Rep[i][j].s-1);
        }
}
void move_kings_to_starting_positions()
{
    for(int i=1;i<=K;++i)
        Kings[i].move_to_starting_position();
}
void move_kings_to_ending_positions()
{
    for(int i=1;i<=K;++i)
        Kings[i].move_to_ending_position();
}
void not_possible()
{
    cout<<"NIE\n";
    exit(0);
}
void calculate_tile_mappings()//calculate TiletoKing and KingtoTile
{
    for(int i=1;i<=K;++i)
    {
        TiletoKing[Kings[i].y*n + Kings[i].x] = i;
        KingtoTile[i] = Kings[i].y*n + Kings[i].x;
        Ending_TiletoKing[Kings[i].ending_y*n + Kings[i].ending_x] = i;
    }
}
void add_fake_Kings()//make fake kings to fill 15 puzzle
{
    fake_king_id = K;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(TiletoKing[i*n + j] != 0) continue;
            ++fake_king_id;
            Kings[fake_king_id].x = j;
            Kings[fake_king_id].y = i;
            Kings[fake_king_id].real_x = main_in_Rep[i][j].s;
            Kings[fake_king_id].real_y = main_in_Rep[i][j].f;
            Kings[fake_king_id].real_id = -1;
            TiletoKing[i*n + j] = fake_king_id;
        }
    }

    for(int i=1;i<=K;++i)
        Ending_TiletoKing[Kings[i].ending_y*n + Kings[i].ending_x] = i;
    int fake_king_it = K;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(Ending_TiletoKing[i*n + j] != 0) continue;
            ++fake_king_it;
            Kings[fake_king_it].ending_x = j;
            Kings[fake_king_it].ending_y = i;
            Kings[fake_king_it].real_ending_x = main_in_Rep[i][j].s;
            Kings[fake_king_it].real_ending_y = main_in_Rep[i][j].f;
            Kings[fake_king_it].id = (i-1)*n + (j-1);
            Ending_TiletoKing[i*n + j] = fake_king_it;
        }
    }
}
bool check_if_no_blank_configuration_is_solved()
{
    for(int i=1;i<=K;++i)
    {
        if(Kings[i].x != Kings[i].ending_x || Kings[i].y != Kings[i].ending_y)
            return false;
    }
    return true;
}
void one_move_in_ending_configuration(int y, int x, char c)
{
    int k1,k2;
    int poz2;
    k1 = Ending_TiletoKing[y*n+x];
    if(c == 'L')
        poz2 = (y)*n+(x-1);
    if(c == 'R')
        poz2 = (y)*n+(x+1);
    if(c == 'U')
        poz2 = (y-1)*n+x;
    if(c == 'D')
        poz2 = (y+1)*n+x;

    k2 = Ending_TiletoKing[poz2];

    swap(Kings[k1].ending_y, Kings[k2].ending_y);
    swap(Kings[k1].ending_x, Kings[k2].ending_x);
    swap(Kings[k1].real_ending_y, Kings[k2].real_ending_y);
    swap(Kings[k1].real_ending_x, Kings[k2].real_ending_x);
    swap(Kings[k1].id, Kings[k2].id);
    swap(Ending_TiletoKing[y*n+x], Ending_TiletoKing[poz2]);
}
void move_in_ending_configuration(int id, int y, int x, vector<char>& record_path)
{
    //move empty tiles to last two positions in ending configuration
    int akt_y = Kings[id].ending_y;
    int akt_x = Kings[id].ending_x;
    while(akt_x<x)
    {
        record_path.pb('R');
        one_move_in_ending_configuration(akt_y, akt_x, 'R');
        ++akt_x;
    }
    while(akt_x>x)
    {
        record_path.pb('L');
        one_move_in_ending_configuration(akt_y, akt_x, 'L');
        --akt_x;
    }
    while(akt_y<y)
    {
        record_path.pb('D');
        one_move_in_ending_configuration(akt_y, akt_x, 'D');
        ++akt_y;
    }
    while(akt_y>y)
    {
        record_path.pb('U');
        one_move_in_ending_configuration(akt_y, akt_x, 'U');
        --akt_y;
    }
}
int locationtoID(int y, int x)
{
    return (y-1)*n + (x-1);
}
void Print_solution()
{
    cout<<"TAK\n";
    cout<<sz(moves)<<'\n';
    for(auto &u: moves)
        cout<<u.f<<' '<<u.s.f<<' '<<u.s.s<<'\n';
    exit(0);
}

void calculate_ID_mappings()
{
    for(int i=1;i<=fake_king_id;++i)
        IDtoKing[Kings[i].id] = i;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            tiletoID[i*n+j] = locationtoID(i,j);
}
void reverse_Path(vector<char>& path, int akt_y, int akt_x)
{
    for(auto &u: path)
    {
        if(u=='L') //goes 'R'
        {
            Kings[IDtoKing[tiletoID[akt_y*n + akt_x+1]]].move('L');
            Kings[IDtoKing[tiletoID[akt_y*n + akt_x]]].move('R');
            swap(tiletoID[akt_y*n + akt_x+1], tiletoID[akt_y*n + akt_x]);
            ++akt_x;
        }
        if(u=='R') //goes 'L'
        {
            Kings[IDtoKing[tiletoID[akt_y*n + akt_x-1]]].move('R');
            Kings[IDtoKing[tiletoID[akt_y*n + akt_x]]].move('L');
            swap(tiletoID[akt_y*n + akt_x-1], tiletoID[akt_y*n + akt_x]);
            --akt_x;
        }
        if(u=='U') //goes 'D'
        {
            Kings[IDtoKing[tiletoID[(akt_y+1)*n + akt_x]]].move('U');
            Kings[IDtoKing[tiletoID[akt_y*n + akt_x]]].move('D');
            swap(tiletoID[(akt_y+1)*n + akt_x], tiletoID[akt_y*n + akt_x]);
            ++akt_y;
        }
        if(u=='D') //goes 'U'
        {
            Kings[IDtoKing[tiletoID[(akt_y-1)*n + akt_x]]].move('D');
            Kings[IDtoKing[tiletoID[akt_y*n + akt_x]]].move('U');
            swap(tiletoID[(akt_y-1)*n + akt_x], tiletoID[akt_y*n + akt_x]);
            --akt_y;
        }
    }
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
    calculate_tile_mappings();
    add_fake_Kings();

    if(fake_king_id-K==0)
    {
        if(check_if_no_blank_configuration_is_solved())
        {
            move_kings_to_ending_positions();
            Print_solution();
        }
        else
            not_possible();
    }
    vector<char>path1;
    vector<char>path2;
    if(fake_king_id-K==1)
    {
        move_in_ending_configuration(K+1, n,n, path1);
    }
    if(fake_king_id-K>=2)
    {
        move_in_ending_configuration(K+1, n,n, path1);
        move_in_ending_configuration(K+2, n,n-1, path2);
    }

    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            cout<<Kings[Ending_TiletoKing[i*n+j]].id<<' ';
        }
        cout<<endl;
    }
    
    //move empty tiles to last two positions in ending configuration

    //move kings to their ending big tiles

    //if there is more then 2 fake kings make sure to solv n = 2 diffrently

    calculate_ID_mappings();
    reverse(path1.begin(), path1.end());
    reverse(path2.begin(), path2.end());
    reverse_Path(path2, n, n-1);
    reverse_Path(path1, n, n);

    move_kings_to_ending_positions();
    Print_solution();
    return 0;
}