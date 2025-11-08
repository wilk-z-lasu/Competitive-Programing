#include <windows.h>
#include <process.h>

#include <stdio.h>
#include <conio.h>

#include "Solver.h"
#include "mtwist.h"

const int THREADCOUNT = 1;

CSolver g_cSolver[THREADCOUNT];
bool g_bThreadFinished[THREADCOUNT];

int g_nPuzzleSize;

int g_nMax = -1;
int g_nMin = 0x7FFFFFFF;
long long g_nSum = 0;
int g_nCount = 0;

/// Perform length experiments in a single thread.
/// \param pParam Pointer to parameter list.

void __cdecl PerformLengthExperiments(void *pParam){ 
  int index = ((int*)pParam)[0];
  int repeats = ((int*)pParam)[1];

  if(repeats <= 0 || index < 0 || index > THREADCOUNT)return; //bail and fail

  g_bThreadFinished[index] = false;

  g_cSolver[index].srand(timeGetTime());

  int nMax = -1;
  long long nSum = 0;
  int nMin = 0x7FFFFFFF;

  for(int i=0; i<repeats; i++){
    int m;
    m = g_cSolver[index].Solve();
    nMax = max(nMax, m);
    nMin = min(nMin, m);
    nSum += (long long)m;
  } //for
  
  g_nMax = max(g_nMax, nMax);
  g_nMin = min(g_nMin, nMin);
  g_nSum += nSum;
  g_nCount += repeats;
        
  g_bThreadFinished[index] = true;
} //PerformLengthExperiments


int main(int argc, char *argv[]){
  char filename[MAX_PATH];
  FILE* fd;

  //get parameters from user
  int repeats, lower, upper;

  printf("Repeats> ");
  scanf_s("%d", &repeats);

  printf("From> ");
  scanf_s("%d", &lower);

  printf("To> ");
  scanf_s("%d", &upper);

  printf("Save file> ");
  scanf_s("%s", filename);

  printf("\n");

  //initialization
  int k = repeats/THREADCOUNT;
  strcat_s(filename, ".txt");

  static int arglist[THREADCOUNT][2];
  
  for(int i=0; i<THREADCOUNT-1; i++){
    arglist[i][0] = i;
    arglist[i][1] = k;
  } //for
  arglist[THREADCOUNT-1][0] = THREADCOUNT-1;
  arglist[THREADCOUNT-1][1] = repeats - k*(THREADCOUNT - 1);

  //for each problem size
  for(g_nPuzzleSize=lower; g_nPuzzleSize<=upper; g_nPuzzleSize++){
    g_nMax = -1;
    g_nMin = 0x7FFFFFFF;
    g_nSum = 0;
    g_nCount = 0;

    //mark threads as not finished
    for(int i=0; i<THREADCOUNT; i++)
      g_bThreadFinished[i] = false;

    //launch threads
    for(int i=0; i<THREADCOUNT; i++){
      _beginthread(PerformLengthExperiments, 256, arglist[i]); //launch thread i
      Sleep(100); //wait small period
    } //for

    //check for completed threads
    bool bIsAWorkingThread = true; //there is still a thread working
    while(bIsAWorkingThread){ //busy-wait
      Sleep(1000); //don't thrash
      bIsAWorkingThread = false;
      for(int i=0; i<THREADCOUNT; i++)
        if(!g_bThreadFinished[i])
          bIsAWorkingThread = true;
    } //while
  
    //append data for current size to output file
    fopen_s(&fd, filename, "at");
    if(fd){
      fprintf_s(fd, "%d\t%d\t%d\t%0.2f\t%d\n", 
        g_nPuzzleSize, g_nCount, g_nMin, (double)g_nSum/(double)repeats, g_nMax);
      fclose(fd);
    } //if
    printf("%d, ", g_nPuzzleSize);
  } //for

  //append newline to end of output file
  fopen_s(&fd, filename, "at");
  if(fd){
    fprintf_s(fd, "\n");
    fclose(fd);
  } //if

  printf("\nHit Almost Any Key to Exit...\n");

  _getch();
  return 0;
} //main