
/* PART A */
/* Stacks using Fixed Size Arrays */
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;
int KnightScore(int i , int j){
    int  opium[8][8] = {
        {3,2,3,2,3,2,3,4},
        {2,3,2,3,2,3,2,3},
        {3,4,1,2,1,4,3,2},
        {2,1,2,3,2,1,2,3},
        {3,2,3,0,3,2,3,2},
        {2,1,2,3,2,1,2,3},
        {3,4,1,2,1,4,3,2},
        {2,3,2,3,2,3,2,3}
    };
    return opium[i][j];
}
