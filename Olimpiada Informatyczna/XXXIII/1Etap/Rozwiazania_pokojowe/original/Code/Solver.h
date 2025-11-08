/// \file Solver.h
/// Header file for the Solver class CSolver.

#pragma once

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
    void PermuteTiles(); ///< Compute a random even permutation of the tiles.
    void ComputePositions(); ///< Recompute the positions, rows, and columns of the current tile and blank.
    void SimulateMove(const char* m); ///< Simulate a sequence of moves.
    void MoveTileUpTo(const int tile, const int dest); ///< Move a tile to a destination above it.
    void MoveTileLeftTo(const int tile, const int dest); ///< Move a tile to a destination to the left of it.
    void MoveBlankWhileAvoiding(const int dest, const int avoid); ///< Move the blank while avoiding some tiles.
    void MoveBlankWhileAvoiding(const int dest); ///< Move the blank while avoiding locked tiles.

    void SolveFirstRow(const int m);  ///< Solve the first row.
    void SolveFirstCol(const int m);  ///< Solve the first column.

  public:
    int Solve(); ///< Find the number of moves needed to solve a random configuration of the puzzle.
}; //CSolver