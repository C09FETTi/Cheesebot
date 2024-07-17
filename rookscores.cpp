
/* PART A */
/* Stacks using Fixed Size Arrays */
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;
int RookScore(int i , int j){
    int  opium[8][8] = {
        {2,3,3,4,4,3,3,2},
        {2,2,3,4,4,3,2,2},
        {1,2,3,4,4,3,2,1},
        {1,2,2,3,3,2,2,1},
        {1,1,2,3,3,2,1,1},
        {1,2,2,4,4,2,2,1},
        {2,2,3,4,4,3,2,2},
        {2,3,3,4,4,3,3,2}
    };
    return opium[i][j];
}
