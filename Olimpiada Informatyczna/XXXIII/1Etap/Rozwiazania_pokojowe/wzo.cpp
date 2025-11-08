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
int n_puzzle;//n for 15 puzzle
int KingtoTile[maxi];
int TiletoKing[maxi];
int Ending_TiletoKing[maxi];
int fake_king_id;
int IDtoKing[maxi];
int tiletoID[maxi];
int Blank;

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
        if(real_x == main_in_Rep[y][x].s && real_y == main_in_Rep[y][x].f)
            return;
        else if(real_x == main_in_Rep[y][x].s + 1 && real_y == main_in_Rep[y][x].f)
            real_move('L');
        else if(real_x == main_in_Rep[y][x].s && real_y == main_in_Rep[y][x].f + 1)
            real_move('U');
        else if(real_x == main_in_Rep[y][x].s + 1 && real_y == main_in_Rep[y][x].f + 1)
        {
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
    n_puzzle = sufit(N,2);
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
            Kings[End[i][j]].id = (Rep[i][j].f-1)*n_puzzle + (Rep[i][j].s-1);
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
        TiletoKing[Kings[i].y*n_puzzle + Kings[i].x] = i;
        KingtoTile[i] = Kings[i].y*n_puzzle + Kings[i].x;
        Ending_TiletoKing[Kings[i].ending_y*n_puzzle + Kings[i].ending_x] = i;
    }
}
void add_fake_Kings()//make fake kings to fill 15 puzzle
{
    fake_king_id = K;
    for(int i=1;i<=n_puzzle;++i)
    {
        for(int j=1;j<=n_puzzle;++j)
        {
            if(TiletoKing[i*n_puzzle + j] != 0) continue;
            ++fake_king_id;
            Kings[fake_king_id].x = j;
            Kings[fake_king_id].y = i;
            Kings[fake_king_id].real_x = main_in_Rep[i][j].s;
            Kings[fake_king_id].real_y = main_in_Rep[i][j].f;
            Kings[fake_king_id].real_id = -1;
            TiletoKing[i*n_puzzle + j] = fake_king_id;
        }
    }

    for(int i=1;i<=K;++i)
        Ending_TiletoKing[Kings[i].ending_y*n_puzzle + Kings[i].ending_x] = i;
    int fake_king_it = K;
    for(int i=1;i<=n_puzzle;++i)
    {
        for(int j=1;j<=n_puzzle;++j)
        {
            if(Ending_TiletoKing[i*n_puzzle + j] != 0) continue;
            ++fake_king_it;
            Kings[fake_king_it].ending_x = j;
            Kings[fake_king_it].ending_y = i;
            Kings[fake_king_it].real_ending_x = main_in_Rep[i][j].s;
            Kings[fake_king_it].real_ending_y = main_in_Rep[i][j].f;
            Kings[fake_king_it].id = (i-1)*n_puzzle + (j-1);
            Ending_TiletoKing[i*n_puzzle + j] = fake_king_it;
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
    k1 = Ending_TiletoKing[y*n_puzzle+x];
    if(c == 'L')
        poz2 = (y)*n_puzzle+(x-1);
    if(c == 'R')
        poz2 = (y)*n_puzzle+(x+1);
    if(c == 'U')
        poz2 = (y-1)*n_puzzle+x;
    if(c == 'D')
        poz2 = (y+1)*n_puzzle+x;

    k2 = Ending_TiletoKing[poz2];

    swap(Kings[k1].ending_y, Kings[k2].ending_y);
    swap(Kings[k1].ending_x, Kings[k2].ending_x);
    swap(Kings[k1].real_ending_y, Kings[k2].real_ending_y);
    swap(Kings[k1].real_ending_x, Kings[k2].real_ending_x);
    swap(Kings[k1].id, Kings[k2].id);
    swap(Ending_TiletoKing[y*n_puzzle+x], Ending_TiletoKing[poz2]);
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
    return (y-1)*n_puzzle + (x-1);
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
    for(int i=1;i<=n_puzzle;++i)
        for(int j=1;j<=n_puzzle;++j)
            tiletoID[i*n_puzzle+j] = locationtoID(i,j);
}
void reverse_Path(vector<char>& path, int akt_y, int akt_x)
{
    for(auto &u: path)
    {
        if(u=='L') //goes 'R'
        {
            Kings[IDtoKing[tiletoID[akt_y*n_puzzle + akt_x+1]]].move('L');
            Kings[IDtoKing[tiletoID[akt_y*n_puzzle + akt_x]]].move('R');
            swap(tiletoID[akt_y*n_puzzle + akt_x+1], tiletoID[akt_y*n_puzzle + akt_x]);
            ++akt_x;
        }
        if(u=='R') //goes 'L'
        {
            Kings[IDtoKing[tiletoID[akt_y*n_puzzle + akt_x-1]]].move('R');
            Kings[IDtoKing[tiletoID[akt_y*n_puzzle + akt_x]]].move('L');
            swap(tiletoID[akt_y*n_puzzle + akt_x-1], tiletoID[akt_y*n_puzzle + akt_x]);
            --akt_x;
        }
        if(u=='U') //goes 'D'
        {
            Kings[IDtoKing[tiletoID[(akt_y+1)*n_puzzle + akt_x]]].move('U');
            Kings[IDtoKing[tiletoID[akt_y*n_puzzle + akt_x]]].move('D');
            swap(tiletoID[(akt_y+1)*n_puzzle + akt_x], tiletoID[akt_y*n_puzzle + akt_x]);
            ++akt_y;
        }
        if(u=='D') //goes 'U'
        {
            Kings[IDtoKing[tiletoID[(akt_y-1)*n_puzzle + akt_x]]].move('D');
            Kings[IDtoKing[tiletoID[akt_y*n_puzzle + akt_x]]].move('U');
            swap(tiletoID[(akt_y-1)*n_puzzle + akt_x], tiletoID[akt_y*n_puzzle + akt_x]);
            --akt_y;
        }
    }
}

vector<char>path1;
vector<char>path2;
void moving_empty_tiles()
{
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
    if(fake_king_id-K==1)
    {
        move_in_ending_configuration(K+1, n_puzzle,n_puzzle, path1);
    }
    if(fake_king_id-K>=2)
    {
        move_in_ending_configuration(K+1, n_puzzle,n_puzzle, path1);
        move_in_ending_configuration(K+2, n_puzzle,n_puzzle-1, path2);
    }
}
void returning_empty_tiles()
{
    calculate_ID_mappings();
    reverse(path1.begin(), path1.end());
    reverse(path2.begin(), path2.end());
    reverse_Path(path2, n_puzzle, n_puzzle-1);
    reverse_Path(path1, n_puzzle, n_puzzle);
}

/// \file Solver.cpp
/// Code file for the Solver class CSolver.

/// \file Solver.h
/// Header file for the Solver class CSolver.

const int MAX_SIDE = 52; ///< Maximum side length of the puzzle.
const int MAX_SIZE = MAX_SIDE*MAX_SIDE; ///< Maximum number of tiles including the blank.

/// The Solver class is responsible for generating random solvable instances
/// of the puzzle and solving them using the greedy algorithm.

class CSolver{
  private:
    
    int m_nMoveCount=0; ///< Number of moves used in the current solution.
    int m_nSize=0; ///< Size of current sub-puzzle.
    int m_nTileToPosition[MAX_SIZE]; ///< Map from number on tile to its position.
    int m_nPositionToTile[MAX_SIZE]; ///< Map from position to number on tile.
    bool m_bLocked[MAX_SIZE]; /// < For each position, whether the tile in that position is locked.

    int m_nCurrentTile=0; ///< The current tile being moved to its home position.

    int m_nTilePosition; ///< The position of the current tile.
    int m_nTileRow; ///< The row that the current tile is in.
    int m_nTileCol; ///< The row that the current tile is in.
  
    int m_nHomePosition; ///< The home position of the current tile.
    int m_nHomeRow; ///< The row that the current tile's home is in.
    int m_nHomeCol; ///< The column that the current tile's home is in.
    
    int m_nBlankPosition; ///< The position of the blank.
    int m_nBlankRow; ///< The row that the blank is in.
    int m_nBlankCol;  ///< The column that the blank is in. 

    void Remap(const int n); ///< Remap the puzzle to the next size down.
    void Reset(); ///< Reset the puzzle to initial conditions.
    void SwapTilesAtPosition(const int i, const int j); /// Swap two tiles.
    void ComputePositions(); ///< Recompute the positions, rows, and columns of the current tile and blank.
    void SimulateMove(const char* m); ///< Simulate a sequence of moves.
    void MoveTileUpTo(const int tile, const int dest); ///< Move a tile to a destination above it.
    void MoveTileLeftTo(const int tile, const int dest); ///< Move a tile to a destination to the left of it.
    void MoveBlankWhileAvoiding(const int dest, const int avoid); ///< Move the blank while avoiding some tiles.
    void MoveBlankWhileAvoiding(const int dest); ///< Move the blank while avoiding locked tiles.

    void SolveFirstRow(const int m);  ///< Solve the first row.
    void SolveFirstCol(const int m);  ///< Solve the first column.

  public:
    int Solve(int sizeN, std::vector<int> input); ///< Find the number of moves needed to solve a random configuration of the puzzle.
}; //CSolver

int g_nPuzzleSize;

/// Compute the position, row, and column of the current tile,
/// its home, and the blank. 

void CSolver::ComputePositions(){ 
    
  //current tile
  m_nTilePosition = m_nTileToPosition[m_nCurrentTile];
  m_nTileRow = m_nTilePosition/m_nSize;
  m_nTileCol = m_nTilePosition%m_nSize;
  
  //home of current tile
  m_nHomePosition = m_nCurrentTile;
  m_nHomeRow = m_nHomePosition/m_nSize;
  m_nHomeCol = m_nHomePosition%m_nSize;

  //blank
  m_nBlankPosition = m_nTileToPosition[m_nSize*m_nSize - 1];
  m_nBlankRow = m_nBlankPosition/m_nSize;
  m_nBlankCol = m_nBlankPosition%m_nSize;
} //ComputePositions

/// Simulate a sequence of moves of the blank entry left, right, up, or down.
/// \param m A string of L, R, U, and D characters.

void CSolver::SimulateMove(const char* m){
  int count = strlen(m);
  for(int j=0; j<count; j++){
    // std::cout<<m[j];
    int nBlank = m_nBlankPosition;
    int nTile = nBlank;
    switch(m[j]){
      case 'L': {
        nTile -= 1; 
        int new_Blank = Blank - 1;
        Kings[TiletoKing[Blank]].move('L');
        Kings[TiletoKing[new_Blank]].move('R');
        swap(TiletoKing[Blank], TiletoKing[new_Blank]);
        Blank = new_Blank;
        break;
      }
      case 'R': {
        nTile += 1; 
        int new_Blank = Blank + 1;
        Kings[TiletoKing[Blank]].move('R');
        Kings[TiletoKing[new_Blank]].move('L');
        swap(TiletoKing[Blank], TiletoKing[new_Blank]);
        Blank = new_Blank;
        break;
      }
      case 'U': {
        nTile -= m_nSize; 
        int new_Blank = Blank - n_puzzle;
        Kings[TiletoKing[Blank]].move('U');
        Kings[TiletoKing[new_Blank]].move('D');
        swap(TiletoKing[Blank], TiletoKing[new_Blank]);
        Blank = new_Blank;
        break;
      }
      case 'D': {
        nTile += m_nSize; 
        int new_Blank = Blank + n_puzzle;
        Kings[TiletoKing[Blank]].move('D');
        Kings[TiletoKing[new_Blank]].move('U');
        swap(TiletoKing[Blank], TiletoKing[new_Blank]);
        Blank = new_Blank;
        break;
      }
    } //switch
    SwapTilesAtPosition(nTile, nBlank);
    ComputePositions();
  } //for
  
  m_nMoveCount += count;
} //SimulateMove

/// Move a tile to some destination that is above it.
/// \param t Tile index.
/// \param dest Destination.

void CSolver::MoveTileUpTo(const int t, const int dest){ 
  m_nCurrentTile = t; 
  ComputePositions();

  const int nDestRow = dest/m_nSize;
  const int nDestCol = dest%m_nSize;
  
  //move horizontally left or right
  int nColCount = abs(nDestCol - m_nTileCol);

  if(nDestCol < m_nTileCol){ //move left
    //move blank to the left of the tile
    MoveBlankWhileAvoiding(m_nTilePosition - 1, m_nTilePosition);
    
    //move tile left
    for(int i=0; i<nColCount-1; i++)
      if(m_nTileRow > 1)
        if(nDestRow < m_nTileRow) //diagonal shortcut
          SimulateMove("RULDLU");
        else SimulateMove("RULLD");
      else 
        SimulateMove("RDLLU");        
    SimulateMove("R");
  } //if

  else if(nDestCol > m_nTileCol){  //move right
    //move blank to the right of the tile
    MoveBlankWhileAvoiding(m_nTilePosition + 1, m_nTilePosition);

    //move tile right
    for(int i=0; i<nColCount-1; i++)
      if(m_nTileRow > 1)
        if(nDestRow < m_nTileRow) //diagonal shortcut
          SimulateMove("LURDRU");
        else SimulateMove("LURRD");
      else 
        SimulateMove("LDRRU");
    SimulateMove("L");
  } //if

  //move up
  bool bInLastCol = m_nTileCol == m_nSize - 1;
  int nRowCount = abs(nDestRow - m_nTileRow);

  if(nDestRow < m_nTileRow){
    //move blank above the tile
    MoveBlankWhileAvoiding(m_nTilePosition - m_nSize, m_nTilePosition);
    
    //move tile up
    for(int i=0; i<nRowCount-1; i++){
      if(bInLastCol)
        SimulateMove("DLUUR");
      else 
        SimulateMove("DRUUL");
    } //for 
    SimulateMove("D");
  } //if
} //MoveTileUpTo

/// Move a tile to a position on its left by first moving it up or down
/// to the correct row, then moving it left.
/// \param t Number on the tile to be moved.
/// \param dest Position of its destination.

void CSolver::MoveTileLeftTo(const int t, const int dest){ 
  m_nCurrentTile = t; 
  ComputePositions();

  const int nDestRow = dest/m_nSize;
  const int nDestCol = dest%m_nSize;
  
  //move vertically up or down
  int nRowCount = abs(nDestRow - m_nTileRow);

  if(nDestRow < m_nTileRow){ //move tile up
    //move blank above the tile
    MoveBlankWhileAvoiding(m_nTilePosition - m_nSize, m_nTilePosition);

    //move tile up
    for(int i=0; i<nRowCount-1; i++){
      if(m_nTileCol > 1)
          if(nDestCol < m_nTileCol) //diagonal shortcut
            SimulateMove("DLURUL");
          else SimulateMove("DLUUR");
      else 
        SimulateMove("DRUUL");
    } //for
    SimulateMove("D");
  } //if

  else if(nDestRow > m_nTileRow){ //move tile down
    //move blank below the tile
    MoveBlankWhileAvoiding(m_nTilePosition + m_nSize, m_nTilePosition);

    //move tile down
    for(int i=0; i<nRowCount-1; i++){
      if(m_nTileCol > 1)
          if(nDestCol < m_nTileCol) //diagonal shortcut
            SimulateMove("ULDRDL");
        else SimulateMove("ULDDR");
      else 
        SimulateMove("URDDL");
    } //for  
    SimulateMove("U");
  } //if

  //move tile left
  bool bInLastRow = m_nTileRow == m_nSize - 1;
  int nColCount = abs(nDestCol - m_nTileCol);

  if(nDestCol < m_nTileCol){
    //move blank to left of tile
    MoveBlankWhileAvoiding(m_nTilePosition - 1, m_nTilePosition);

    //move tile left
    for(int i=0; i<nColCount-1; i++){
      if(bInLastRow)
        SimulateMove("RULLD");
      else 
        SimulateMove("RDLLU");
    } //for 
    SimulateMove("R");
  } //if
} //MoveTileLeftTo

/// Move the blank to a new position while avoiding
/// (that is, not moving) all locked tiles plus an unlocked tile.
/// \param dest Position that the blank is to move to.
/// \param avoid Position of a tile that must not move.

void CSolver::MoveBlankWhileAvoiding(const int dest, const int avoid){ 
  m_bLocked[avoid] = true;  
  MoveBlankWhileAvoiding(dest);
  m_bLocked[avoid] = false;
} //MoveBlankWhileAvoiding

/// Move the blank to a new position while avoiding
/// (that is, not moving) all locked tiles.
/// \param dest Position that the blank is to move to.

void CSolver::MoveBlankWhileAvoiding(const int dest){ 
  const int nDestRow = dest/m_nSize;
  const int nDestCol = dest%m_nSize;

  while(dest != m_nBlankPosition){
    //move vertically
    while(m_nBlankRow != nDestRow){
      if(nDestRow < m_nBlankRow && !m_bLocked[m_nBlankPosition - m_nSize])
        SimulateMove("U");
      else if(nDestRow > m_nBlankRow && !m_bLocked[m_nBlankPosition + m_nSize])
        SimulateMove("D");
      else{
        if(m_nBlankCol == m_nSize - 1){         
          if(m_bLocked[m_nBlankPosition - 1])
            SimulateMove("D");
          SimulateMove("L");
        } //if
        else{  
          if(m_bLocked[m_nBlankPosition + 1])
            SimulateMove("D");
          SimulateMove("R");
        } //else
      } //if
    } //while

    //move horizontally
    while(m_nBlankCol != nDestCol){ 
      if(nDestCol < m_nBlankCol &&!m_bLocked[m_nBlankPosition - 1])
        SimulateMove("L");
      else if(nDestCol > m_nBlankCol && !m_bLocked[m_nBlankPosition + 1])
        SimulateMove("R");
      else{
        if(m_nBlankRow == m_nSize - 1){         
          if(m_bLocked[m_nBlankPosition - m_nSize])
            SimulateMove("R");
          SimulateMove("U");
        } //if
        else{  
          if(m_bLocked[m_nBlankPosition + m_nSize])
            SimulateMove("R");
          SimulateMove("D");
        } //else
      } //if
    } //while
  } //while
} //MoveBlankWhileAvoiding

/// Remap the puzzle to size one smaller by essentially 
/// chopping off and throwing away the first row and column.
/// \param n Size of smaller sub-puzzle.

void CSolver::Remap(const int n){
  for(int i=0; i<n*n; i++){
    int index = (i/n + 1)*(n+1) + i%n + 1;
    int row = m_nPositionToTile[index]/(n+1);
    int col = m_nPositionToTile[index]%(n+1);
    m_nPositionToTile[i] = (row - 1)*n + col - 1;
    m_nTileToPosition[(row - 1)*n + col - 1] = i;
    m_bLocked[i] = false;
  } //for
  
  m_nSize = n;
  ComputePositions();
} //Remap

/// Solve the first row of a sub-puzzle.
/// \param n Size of the sub-puzzle.

void CSolver::SolveFirstRow(const int n){
  const int blank = n*n - 1; //blank tile

  //place all but last 2 tiles in row
  for(int i=0; i<n-2; i++){   
    if(m_nPositionToTile[i] != i)
      MoveTileUpTo(i, i);
    m_bLocked[i] = true;
  } //for

  //use the quad of slots at top right of the board
  const int ul = n - 2;  //upper left
  const int ur = ul + 1; //upper right, this is where tile ul is
  const int ll = ul + n; //lower left
  const int lr = ll + 1; //lower right
  
  //move second to last tile in the first row to last place
  MoveTileUpTo(ul, ur); //put second last tile in the far corner
  
  //last tile in the first row 

  if(m_nTileToPosition[blank] == ul) //move blank out of top row
    SimulateMove("D");

  if(m_nTileToPosition[ur] == ul){ //worst case, tiles ul and ur are reversed
    MoveBlankWhileAvoiding(ll, ul); 
    m_bLocked[ul - 1] = false;
    SimulateMove("ULDDRRULLURRD");
    m_bLocked[ul - 1] = true;
  } //if
  else{ //normal case, drag in last tile from elsewhere
    m_bLocked[ur] = true;
    MoveTileUpTo(ur, lr);
    MoveBlankWhileAvoiding(ul, lr);
    m_bLocked[ur] = false;
    SimulateMove("RD");
  } //else

  m_bLocked[ul] = m_bLocked[ur] = true; //ul and ur are now in place
} //SolveFirstRow

/// Solve the first column of a sub-puzzle, assuming that the first
/// tile is already in place and that the first row is not
/// to be disturbed.
/// \param n Size of the sub-puzzle.

void CSolver::SolveFirstCol(const int n){
  const int blank = n*n - 1; //blank tile

  //place all but last 2 tiles in column
  for(int i=1; i<n-2; i++){ 
    const int tile = i*n;
    if(m_nPositionToTile[tile] != tile){
      MoveTileLeftTo(tile, tile);
    } //if
    m_bLocked[tile] = true;
  } //for

  //use the 2x2 quad at bottom left of the board
  const int ul = n*(n - 2); //upper left
  const int ur = ul + 1;   //upper right
  const int ll = ul + n;  //lower left
  const int lr = ll + 1; //lower right

  //move second to last tile in column to last place
  MoveTileLeftTo(ul, ll);

  //last tile in first column

  if(m_nTileToPosition[blank] == ul) //move blank out of top row
    SimulateMove("R");

  if(m_nTileToPosition[ll] == ul){ //worst case, tiles ul and ll are reversed
    MoveBlankWhileAvoiding(ur, ll); 
    if(n == 3){ //not enough room to use the shorter solution
      m_bLocked[ul - n] = false;
      SimulateMove("LDRRULLDRULDRRULDRULLDR");
      m_bLocked[ul - n] = true;
    } //if
    else{
      m_bLocked[ul - n] = false;
      SimulateMove("LURRDDLUULDDR");
      m_bLocked[ul - n] = true;
    } //else
  } //if

  else{ //normal case, drag in last tile from elsewhere
    m_bLocked[ll] = true;
    MoveTileLeftTo(ll, lr);
    MoveBlankWhileAvoiding(ul, ll);
    m_bLocked[ll] = false;
    SimulateMove("DR");
  } //else

  m_bLocked[ul] = m_bLocked[ll] = true; //ul and ll are now in place
} //SolveFirstCol

/// Randomize the puzzle and measure the number of moves it takes to solve it.
/// \return Number of moves.

int CSolver::Solve(int sizeN, vector<int> input){
  //initialize
  g_nPuzzleSize = sizeN;
  int sq = g_nPuzzleSize*g_nPuzzleSize - 1; //number of tiles
//   cout<<"x: ";
  for(int i=0; i<=sq; ++i)
  {
    int x = input[i];
    // if(x==0) x = sq;
    // else --x;
    // cout<<x<<' ';
    m_nTileToPosition[x] = i;
    m_nPositionToTile[i] = x;
  }
//   cout<<endl;
  m_nMoveCount = 0;

  //all tiles are unlocked
  for(int i=0; i<g_nPuzzleSize*g_nPuzzleSize; i++)
    m_bLocked[i] = false;

  m_nSize = g_nPuzzleSize;
  ComputePositions();

  //solve row and column for all sizes down to and including 3x3
  for(int i=g_nPuzzleSize; i>2; i--){
    SolveFirstRow(i);
    SolveFirstCol(i);
    Remap(i-1);
  } //for
  
  //2x2 solution
//   cout<<endl<<"jestem przed n=2"<<endl;

  //move the blank to lower right
  switch(m_nBlankPosition){
    case 0: SimulateMove("RD"); break;
    case 1: SimulateMove("D"); break; 
    case 2: SimulateMove("R"); break;
    case 3: break; //do nothing     
  } //switch

    //if there is more then 2 fake kings make sure to solv n = 2 diffrently
    if(fake_king_id - K >= 2)
    {
        int k1 = TiletoKing[Blank-n_puzzle-1];
        int k2 = TiletoKing[Blank-n_puzzle];
        int k3 = TiletoKing[Blank-1];
        int k4 = TiletoKing[Blank];

        if(m_nTileToPosition[2]==2)
            int do_nothing=0;
        else if(m_nTileToPosition[2]==0)
        {
            Kings[k1].move('D');
            Kings[k3].move('U');
            swap(TiletoKing[k2], TiletoKing[k4]);
        }
        else if(m_nTileToPosition[2]==1)
        {
            Kings[k2].move('L');
            Kings[k1].move('R');
            swap(TiletoKing[k2], TiletoKing[k1]);

            Kings[k2].move('D');
            Kings[k3].move('U');
            swap(TiletoKing[k2], TiletoKing[k3]);
        }

        k1 = TiletoKing[Blank-n_puzzle-1];
        k2 = TiletoKing[Blank-n_puzzle];
        k3 = TiletoKing[Blank-1];
        k4 = TiletoKing[Blank];
        // cout<<"Blank at: "<<Blank<<endl;
        // solution for n=2 when there are at least 2 empty tiles
        if(m_nTileToPosition[0]==0 && m_nTileToPosition[1]==1)
            int do_nothing=0;
        else if(m_nTileToPosition[0]==1 && m_nTileToPosition[1]==0)
        {
            Kings[k2].move('D');
            Kings[k4].move('U');
            swap(TiletoKing[k2], TiletoKing[k4]);

            Kings[k2].move('L');
            Kings[k3].move('R');
            swap(TiletoKing[k2], TiletoKing[k3]);

            Kings[k1].move('R');
            Kings[k4].move('L');
            swap(TiletoKing[k1], TiletoKing[k4]);

            Kings[k2].move('U');
            Kings[k4].move('D');
            swap(TiletoKing[k2], TiletoKing[k4]);

            Kings[k4].move('R');
            Kings[k3].move('L');
            swap(TiletoKing[k4], TiletoKing[k3]);
        }
        return m_nMoveCount;
    }
//   if(N%2==0)
//   {
//     //parzysta liczba pustych pol w pelnym ukladzie
//     //zawsze da sie rozwiazac idac na krzyz
//   }

  //one cycle left or right as appropriate to finish
  switch(m_nTileToPosition[2]){
    case 0: SimulateMove("LURD"); break;
    case 1: SimulateMove("ULDR");  break;  
    case 2: //do nothing 
    case 3: //not possible
      break;
  } //switch

// //   ----cout n=2
//   std::cout<<std::endl;
//   for(int I=0; I<4; I++)
//     {
//       std::cout<<m_nPositionToTile[I]<<" ";
//       if((I+1)%2==0)
//         std::cout<<std::endl;
//     }
//     std::cout<<std::endl;
// //   ----cout n=2

  if(m_nTileToPosition[0] != 0 || m_nTileToPosition[1] != 1 || m_nTileToPosition[2] != 2 || m_nTileToPosition[3] != 3)
    not_possible();

  return m_nMoveCount;
} //Solve

/// Update the m_nPositionToTile and m_nPositionToTile maps when
/// the tiles at positions i and j are swapped. Note that i and j
/// need not be adjacent to each other.

void CSolver::SwapTilesAtPosition(const int i, const int j){
  int t1 = m_nPositionToTile[i];
  int t2 = m_nPositionToTile[j];
  m_nPositionToTile[i] = t2;
  m_nPositionToTile[j] = t1;

  int temp = m_nTileToPosition[t1];
  m_nTileToPosition[t1] = m_nTileToPosition[t2];
  m_nTileToPosition[t2] = temp;
} //SwapTilesAtPosition

/// Reset the puzzle to the solved state, with the tile marked i
/// in position i.

void CSolver::Reset(){
  for(int i=0; i<g_nPuzzleSize*g_nPuzzleSize; i++)
    m_nTileToPosition[i] = m_nPositionToTile[i] = i;
} //Reset


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

    //move empty tiles to last two positions in ending configuration
    moving_empty_tiles();

    //move kings to their ending big tiles

    // for(int i=1;i<=n_puzzle;++i)
    // {
    //     for(int j=1;j<=n_puzzle;++j)
    //     {
    //         int id = Kings[TiletoKing[i*n_puzzle + j]].id;
    //         cout<<id<<' ';
    //     }
    //     cout<<endl;
    // }
    
    CSolver solver;
    vector<int> vec;
    for(int i=1;i<=n_puzzle;++i)
    {
        for(int j=1;j<=n_puzzle;++j)
        {
            int id = Kings[TiletoKing[i*n_puzzle + j]].id;
            vec.push_back(id);
            if(id == n_puzzle*n_puzzle - 1)
                Blank = i*n_puzzle + j;
        }
    }

    // cout<<"Blank at: "<<Blank<<endl;

    int result = solver.Solve(n_puzzle, vec);
    // cout<<"result: "<<result<<endl;

    returning_empty_tiles();
    move_kings_to_ending_positions();
    Print_solution();
    return 0;
}