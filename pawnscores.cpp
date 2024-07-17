
/* PART A */
/* Stacks using Fixed Size Arrays */
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;
int PawnScore(int i , int j){
    int  opium[8][8] = {
        {5,5,5,5,5,5,5,5},
        {2,3,3,4,4,3,3,2},
        {1,2,3,5,5,3,2,1},
        {1,2,2,6,6,2,2,1},
        {1,2,2,6,6,2,2,1},
        {1,2,3,5,5,3,2,1},
        {2,3,3,4,4,3,3,2},
        {5,5,5,5,5,5,5,5}
    };
    return opium[i][j];
}
