/// \file Solver.cpp
/// Code file for the Solver class CSolver.

#include <bits/stdc++.h>
using namespace std;

/// \file Solver.h
/// Header file for the Solver class CSolver.

const int MAX_SIDE = 51; ///< Maximum side length of the puzzle.
const int MAX_SIZE = MAX_SIDE*MAX_SIDE; ///< Maximum number of tiles including the blank.

/// The Solver class is responsible for generating random solvable instances
/// of the puzzle and solving them using the greedy algorithm.

class CSolver{
  private:
    
    int m_nMoveCount; ///< Number of moves used in the current solution.
    int m_nSize; ///< Size of current sub-puzzle.
    int m_nTileToPosition[MAX_SIZE]; ///< Map from number on tile to its position.
    int m_nPositionToTile[MAX_SIZE]; ///< Map from position to number on tile.
    bool m_bLocked[MAX_SIZE]; /// < For each position, whether the tile in that position is locked.

    int m_nCurrentTile; ///< The current tile being moved to its home position.

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
    std::cout<<m[j];
    int nBlank = m_nBlankPosition;
    int nTile = nBlank;
    switch(m[j]){
      case 'L': nTile -= 1; break;
      case 'R': nTile += 1; break;
      case 'U': nTile -= m_nSize; break;
      case 'D': nTile += m_nSize; break;
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

int CSolver::Solve(int sizeN, std::vector<int> input){
  //initialize
  g_nPuzzleSize = sizeN;
  int sq = g_nPuzzleSize*g_nPuzzleSize - 1; //number of tiles
  for(int i=0; i<=sq; ++i)
  {
    int x = input[i];
    if(x==0) x = sq;
    else --x;
    m_nTileToPosition[x] = i;
    m_nPositionToTile[i] = x;
  }
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

  // //move the blank to lower right
  // switch(m_nBlankPosition){
  //   case 0: SimulateMove("RD"); break;
  //   case 1: SimulateMove("D"); break; 
  //   case 2: SimulateMove("R"); break;
  //   case 3: break; //do nothing     
  // } //switch

  // //one cycle left or right as appropriate to finish
  // switch(m_nTileToPosition[2]){
  //   case 0: SimulateMove("LURD"); break;
  //   case 1: SimulateMove("ULDR");  break;  
  //   case 2: //do nothing 
  //   case 3: //not possible
  //     break;
  // } //switch

  //cout n=2
  std::cout<<std::endl;
  for(int I=0; I<4; I++)
    {
      std::cout<<m_nPositionToTile[I]<<" ";
      if((I+1)%2==0)
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
  //cout n=2

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

int main()
{
  CSolver solver;

  int n,x;
  std::vector<int> vec;

  std::cin>>n;
  for(int i=1;i<=n*n;++i)
  {
      std::cin>>x;
      vec.push_back(x);
  }
  int result = solver.Solve(n, vec);
  std::cout<<result<<std::endl;
  return 0;
}