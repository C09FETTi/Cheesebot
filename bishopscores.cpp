
/* PART A */
/* Stacks using Fixed Size Arrays */
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;
int  BishopScore(int i , int j){
    int  opium[8][8] = {
        {4,3,2,1,3,2,3,4},
        {2,4,3,1,2,3,4,3},
        {3,4,4,3,2,4,3,2},
        {2,2,2,4,4,2,2,3},
        {3,2,3,4,4,3,2,2},
        {2,1,4,3,2,4,3,2},
        {3,4,3,1,1,4,4,3},
        {4,3,2,1,2,3,2,4}
    };
    return opium[i][j];
}
