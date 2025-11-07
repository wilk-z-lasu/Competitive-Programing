#include "mtwist.h"

CMersenneTwister::CMersenneTwister(){
  m_nIndex = 0;
} //constructor

/// Fill the untempered number table with suitable initial values generated from a seed.
/// \param seed The seed.

void CMersenneTwister::srand(const int seed){
  m_pUntempered[0] = seed;
  for(int i=1; i<MTSIZE; i++)
    m_pUntempered[i] = 0xFFFFFFFF & ((long long)1812433253 * (long long)(m_pUntempered[i-1] ^ (m_pUntempered[i-1]>>30) + i));
} //Initialize

///< Generate a table of untempered numbers from its initial seed values.

void CMersenneTwister::GenerateUntempered(){
  for(int i=0; i<MTSIZE; i++){
    int y = (m_pUntempered[i] & 0x80000000) + (m_pUntempered[(i+1)%MTSIZE] & 0x7fffffff);
    m_pUntempered[i] = m_pUntempered[(i + 397)%MTSIZE] ^ (y>>1);
    if(y&1)
      m_pUntempered[i] = m_pUntempered[i] ^ 0x9908b0df;
  } //for
} //GenerateUntempered

/// Generate a pseudorandom integer.
/// \return A pseudorandom integer.

int CMersenneTwister::rand(){
  if(m_nIndex == 0)
    GenerateUntempered();

  int y = m_pUntempered[m_nIndex];
  y ^= y>>11;
  y ^= (y<<7) & 0x9d2c5680;
  y ^= (y<<15) & 0xefc60000; 
  y ^= y>>18;

  m_nIndex = (m_nIndex + 1)%MTSIZE;
  return y;
} //rand