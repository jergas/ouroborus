/*esta libreria de bruce eckel genera una lista de numeros ordenados de manera azarosa
de tamaño segun el valor que le des al template (ver funcion main)
*/
#ifndef RandomListGenerator_H
#define RandomListGenerator_H

#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <ctime>

using std::size_t;
using std::bitset;
 
template<size_t UpperBound> class RandomListGenerator{
  bitset<UpperBound> used;
public:
  RandomListGenerator() { 
	  time_t timer;
	  srand(unsigned int(time(&timer))); } // Randomize
  size_t operator()(); // The "generator" function
};

template<size_t UpperBound>
inline size_t RandomListGenerator<UpperBound>::operator()() {
  if(used.count() == UpperBound)
    used.reset();  // Start over (clear bitset)
  size_t newval;
  while(used[newval = rand() % UpperBound])
    ; // Until unique value is found
  used[newval] = true;
  return newval;
} 
#endif // RandomListGenerator_H