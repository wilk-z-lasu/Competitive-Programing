/// \file mtwist.h
/// Header file for the Mersenne twister class CMersenneTwister.

#pragma once

/// The class CMersenneTwister implements the Mersenne twister random number generator MT19937.

class CMersenneTwister{
  static const int MTSIZE = 624; ///< Size of untempered number table.

private:
  int m_pUntempered[MTSIZE]; ///< Untempered random number table.
  int m_nIndex; ///< Index of next untempered number to be used.
  void GenerateUntempered(); ///< Generate a new table of untempered numbers.

public:
  CMersenneTwister(); ///< Constructor.
  void srand(const int seed); ///< eed the Mersenne twister.
  int rand(); ///< Generate a random number.
}; //CMersenneTwister