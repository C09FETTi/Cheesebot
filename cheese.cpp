#include <bits/stdc++.h>
#include "headers/bishopscores.cpp"
#include "headers/knightscores.cpp"
#include "headers/rookscores.cpp"
#include "headers/pawnscores.cpp"
#include "headers/check.cpp"
using namespace std;
#define all(a) a.begin(), a.end()
#define pb(t) push_back(t)
#define sz() size()
#define forr(i, n) for (int i = 0; i < n; i++)
#define vi vector<int>
#define vd vector<double>
#define vs vector<string>
#define vll vector<long long>
#define vc vector<char>
#define vld vector<long double>
#define vf vector<float>
using ll = long long int;
const ll inf = 1e17;
const int MOD = 1e9 + 9;
const int MAXM = 300300;
const int MAXN = 1e6;
const int BoardSize = 8;
string cut = "\n";
const int dept = 5;
enum Piece
{
    None = 0,
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 7,
};
int PieceScore(Piece p)
{
    if (p == None)
    {
        return 0;
    }
    if (p == Pawn)
    {
        return 1;
    }
    if (p == Bishop)
    {
        return 3;
    }
    if (p == Knight)
    {
        return 3;
    }
    if (p == Rook)
    {
        return 5;
    }
    if (p == Queen)
    {
        return 9;
    }
    if (p == King)
    {
        return 25;
    }
}
enum Player
{
    nuun = -1,
    White = 0,
    Black = 1,
};
struct gamepiece
{
    pair<Piece, Player> p;
};
// Piece board[8][8];
//  using
vector<vector<gamepiece>> ChessBoard;
int movenumber = 0;
map<Piece, int> BlackTroops;
map<Piece, int> WhiteTroops;
double CurrentEval = 0; // + ve favours black negative favours white

void tester()
{
    vector<gamepiece> pi(BoardSize);
    for (auto i = 0; i < BoardSize; i++)
    {
        pi[i].p.first = None;
        pi[i].p.second = nuun;
    }
    for (auto i = 0; i < BoardSize; i++)
    {
        cout << pi[i].p.first << " " << pi[i].p.second << cut;
    }
    forr(i, 8)
    {
        ChessBoard.push_back(pi);
    }
}
void initializeBoard()
{
    forr(i, BoardSize)
    {
        ChessBoard[1][i].p.first = Pawn;
        ChessBoard[1][i].p.second = Black;
    }
    ChessBoard[1][3].p.first = Pawn;
    ChessBoard[1][3].p.second = Black;
    ChessBoard[1][4].p.first = Pawn;
    ChessBoard[1][4].p.second = Black;
    forr(i, BoardSize)
    {   
        // if(i >= 6){
        ChessBoard[6][i].p.first = Pawn;
        ChessBoard[6][i].p.second = White;
        // }
    }
    // PAWN WALL
    
    ChessBoard[0][0].p.first = Rook;
    ChessBoard[0][1].p.first = Knight;
    ChessBoard[0][2].p.first = Bishop;
    ChessBoard[0][3].p.first = Queen;
    ChessBoard[0][4].p.first = King;
    ChessBoard[0][5].p.first = Bishop;
    ChessBoard[0][6].p.first = Knight;
    ChessBoard[0][7].p.first = Rook;

    forr(i, BoardSize)
    {
        ChessBoard[0][i].p.second = Black;
    }
    // Black Pieces
    ChessBoard[7][0].p.first = Rook;
    ChessBoard[7][1].p.first = Knight;
    ChessBoard[7][2].p.first = Bishop;
    ChessBoard[7][3].p.first = Queen;
    ChessBoard[7][4].p.first = King;
    ChessBoard[7][5].p.first = Bishop;
    ChessBoard[7][6].p.first = Knight;
    ChessBoard[7][7].p.first = Rook;
    ChessBoard[7][7].p.second = White;
    // ChessBoard[6][3].p.first = Pawn;
    // ChessBoard[6][3].p.second = White;
    // ChessBoard[0][3].p.first = Bishop;
    // ChessBoard[0][3].p.second = Black;
    forr(i, BoardSize)
    {
        ChessBoard[7][i].p.second = White;
    }
    // White pieces
    // initializing the number of the initial numebr of troops
}
void PicPos(string g1, vector<vector<gamepiece>> Instance){
        char ro1;
        int col1;
        ro1 = g1[0];
        col1 = g1[1] - '0';
        int row1 = ro1 - 'a';
        swap(col1, row1);
    // cout<<Instance[row1][col1].p.first<<endl;
    
}
double BoardEval(vector<vector<gamepiece>> Instance)
{
    double eval = 0;
    forr(ii,BoardSize){
        forr(jj,BoardSize){
        Piece j = Instance[ii][jj].p.first;
        if(Instance[ii][jj].p.second == Black){
        if (j == Pawn)
        {
            eval += 1 + 0.1*PawnScore(ii,jj);
        }
        if (j == Bishop)
        {
            eval += 3 + 0.1*BishopScore(ii,jj);
        }
        if (j == Knight)
        {
            eval += 3 + 0.1*KnightScore(ii,jj);
        }
        if (j == Rook)
        {
            eval += 5 + 0.1*RookScore(ii,jj);
        }
        if (j == Queen)
        {
            eval += 9  + 0.05*RookScore(ii,jj)  + 0.05*BishopScore(ii,jj);
        }
        if (j == King)
        {
            eval += 1000 ;
        }
        }else{
            if (j == Pawn)
        {
            eval -= (1 + 0.1*PawnScore(ii,jj)) ;
        }
        if (j == Bishop)
        {
            eval -= (3 + 0.1*BishopScore(ii,jj)) ;
        }
        if (j == Knight)
        {
            eval -= (3  + 0.1*KnightScore(ii,jj));
        }
        if (j == Rook)
        {
            eval -= (5 + 0.1*RookScore(ii,jj)) ;
        }
        if (j == Queen)
        {
            eval -= (9 + 0.05*BishopScore(ii,jj) + 0.05*RookScore(ii,jj)) ;
        }
        if (j == King)
        {
            eval -= 1000 ;
        }
        }
    }
    }
    return eval;
}
vector<vector<gamepiece>> MovePiece(string g1, string g2, vector<vector<gamepiece>> ChesBoard , int cp)
{
    // cout<<isValidMove(g1,g2)
    if (cp == 1)
    {
        char ro1;
        int col1;
        ro1 = g1[0];
        col1 = g1[1] - '0';
        // cin>>ro1>>col1;
        char ro2;
        int col2;
        ro2 = g2[0];
        col2 = g2[1] - '0';
        int row1 = ro1 - 'a';
        int row2 = ro2 - 'a';
        swap(row1, col1);
        swap(row2, col2);
        gamepiece toMove = ChesBoard[row1][col1];
        gamepiece titties;
        titties.p.first = None;
        titties.p.second = nuun;
        ChesBoard[row1][col1] = titties;
        ChesBoard[row2][col2] = toMove;
    }
    else
    {
        char ro1;
        int col1;
        ro1 = g1[0];
        col1 = g1[1] - '0';
        char ro2;
        int col2;
        ro2 = g2[0];
        col2 = g2[1] - '0';
        int row1 = ro1 - 'a';
        int row2 = ro2 - 'a';
        swap(col1, row1);
        swap(col2, row2);
        // get piece from the first input and move it to the second position
        gamepiece toMove = ChesBoard[7 - row1][col1];
        gamepiece titties;
        titties.p.first = None;
        titties.p.second = nuun;
        ChesBoard[7 - row1][col1] = titties;
        ChesBoard[7 - row2][col2] = toMove;
    }
    return ChesBoard;
}
vector<vector<gamepiece>> PoliticallyCorrectMovePiece(string g1, string g2, vector<vector<gamepiece>> ChesBoard)
{
    // cout<<isValidMove(g1,g2)
    
        char ro1;
        int col1;
        ro1 = g1[0];
        col1 = g1[1] - '0';
        // cin>>ro1>>col1;
        char ro2;
        int col2;
        ro2 = g2[0];
        col2 = g2[1] - '0';
        int row1 = ro1 - 'a';
        int row2 = ro2 - 'a';
        swap(row1, col1);
        swap(row2, col2);
        gamepiece toMove = ChesBoard[row1][col1];
        gamepiece titties;
        titties.p.first = None;
        titties.p.second = nuun;
        ChesBoard[row1][col1] = titties;
        ChesBoard[row2][col2] = toMove;
    
    
    return ChesBoard;
}
void BishopGenerator(int i, int j, set<pair<string, string>> &PosMoves,vector<vector<gamepiece>> ChesBoard)
{
    // forward right diagnol
    string end = "";
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    // cout << start << endl;
    int crow = i;
    int ccol = j;
    int pos = 1;
    // forward right diagnol
    while (crow + pos < 8 && ccol + pos < 8)
    {
        int row = crow + pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == White)
        {
            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow - pos >= 0 && ccol - pos >= 0)
    {
        int row = crow - pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});

            break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow + pos < 8 && ccol - pos >= 0)
    {
        int row = crow + pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow - pos >= 0 && ccol + pos < 8)
    {
        int row = crow - pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});

            break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
        pos++;
    }
}
void KnightGenerator(int i, int j, set<pair<string, string>> &PosMoves,vector<vector<gamepiece>> ChesBoard)
{
    int currentScore = -1;
    // right up
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    string end = "";
    int row = i - 1;
    int col = j + 2;
    if (row >= 0 && col < 8)
    {
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
    }
    // right down
    row = i + 1;
    col = j + 2;
    if (row < 8 && col < 8)
    {
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }

    // left down
    row = i - 1;
    col = j - 2;
    if (row >= 0 && col >= 0)
    {
        if (ChesBoard[row][col].p.second == White)
        {
            PosMoves.insert({start, end});
            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;

            PosMoves.insert({start, end});
        }
    }
    // left up
    row = i + 1;
    col = j - 2;
    if (row < 8 && col >= 0)
    {
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;

            PosMoves.insert({start, end});
        }
    }
    // up right
    row = i - 2;
    col = j + 1;
    if (row >= 0 && col < 8)
    {
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;

            PosMoves.insert({start, end});
        }
    }
    // up left
    row = i - 2;
    col = j - 1;
    if (row >= 0 && col >= 0)
    {
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }
    // down right
    row = i + 2;
    col = j + 1;
    if (row < 8 && col < 8)
    {
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }
    // down left
    row = i + 2;
    col = j - 1;
    if (row < 8 && col >= 0)
    {
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }
    // cout << start << "," << end << " + " << currentScore << endl;
}
void RookGenerator(int i, int j, set<pair<string, string>> &PosMoves,vector<vector<gamepiece>> ChesBoard)
{
    int currentScore = 0;
    // right up
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    string end = "";
    int row = i;
    int col = j;
    int pos = 1;
    while (row + pos < 8)
    {
        if (ChesBoard[row + pos][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row + pos][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (row - pos >= 0)
    {
        if (ChesBoard[row - pos][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row - pos][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (col + pos < 8)
    {
        if (ChesBoard[row][col + pos].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col + pos].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (col - pos >= 0)
    {
        if (ChesBoard[row][col - pos].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col - pos].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
}

void QueenGenerator(int i, int j, set<pair<string, string>> &PosMoves,vector<vector<gamepiece>> ChesBoard)
{
    int currentScore = -1;
    // right up
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    string end = "";
    int row = i;
    int col = j;
    int pos = 1;
    while (row + pos < 8)
    {
        if (ChesBoard[row + pos][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row + pos][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (row - pos >= 0)
    {
        if (ChesBoard[row - pos][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row - pos][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (col + pos < 8)
    {
        if (ChesBoard[row][col + pos].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col + pos].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (col - pos >= 0)
    {
        if (ChesBoard[row][col - pos].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col - pos].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    int crow = i;
    int ccol = j;
    pos = 1;
    // forward right diagnol
    while (crow + pos < 8 && ccol + pos < 8)
    {
        int row = crow + pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow - pos >= 0 && ccol - pos >= 0)
    {
        int row = crow - pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow + pos < 8 && ccol - pos >= 0)
    {
        int row = crow + pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow - pos >= 0 && ccol + pos < 8)
    {
        int row = crow - pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
}

void PawnGenerator(int i, int j, set<pair<string, string>> &PosMoves,vector<vector<gamepiece>> ChesBoard)
{
    int currentScore = -1;
    // right up
    
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    string end = "";
    int row = i;
    int col = j;
    if(row == 1){
        if(ChesBoard[row + 2][col].p.second == nuun){
            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + 2;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }
    // only three possible moves
    // forward
    if (row + 1 < 8)
    {
        if (ChesBoard[row + 1][col].p.second != nuun)
        {
        }
        else
        {
            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + 1;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }
    // left
    if (row + 1 < 8 && col - 1 >= 0)
    {
        if (ChesBoard[row + 1][col - 1].p.second == Black)
        {
        }
        else if (ChesBoard[row + 1][col - 1].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col - 1;
            rw = '0';
            rw += row + 1;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
    }
    // right
    if (row + 1 < 8 && col + 1 < 8)
    {
        if (ChesBoard[row + 1][col + 1].p.second == Black)
        {
        }
        else if (ChesBoard[row + 1][col + 1].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col + 1;
            rw = '0';
            rw += row + 1;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
    }
}

void KingGenerator(int i, int j, set<pair<string, string>> &PosMoves,vector<vector<gamepiece>> ChesBoard)
{
    int currentScore = -1;
    // right up
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    string end = "";
    int row = i;
    int col = j;
    int pos = 1;
    if (row + pos < 8)
    {
        if (ChesBoard[row + pos][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row + pos][col].p.second == Black)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (row - pos >= 0)
    {
        if (ChesBoard[row - pos][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row - pos][col].p.second == Black)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (col + pos < 8)
    {
        if (ChesBoard[row][col + pos].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col + pos].p.second == Black)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (col - pos >= 0)
    {
        if (ChesBoard[row][col - pos].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col - pos].p.second == Black)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    int crow = i;
    int ccol = j;
    pos = 1;
    // forward right diagnol
    if (crow + pos < 8 && ccol + pos < 8)
    {
        int row = crow + pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (crow - pos >= 0 && ccol - pos >= 0)
    {
        int row = crow - pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (crow + pos < 8 && ccol - pos >= 0)
    {
        int row = crow + pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (crow - pos >= 0 && ccol + pos < 8)
    {
        int row = crow - pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == White)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col].p.second == Black)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
}

set<pair<string, string>> moveGenerator(vector<vector<gamepiece>> ChesBoard)
{
    set<pair<string, string>> PosMoves;
    string h;
    string k;
    forr(i, BoardSize)
    {
        forr(j, BoardSize)
        {
            gamepiece current = ChesBoard[i][j];
            if (current.p.second == Black)
            {
                // if its our own piece
                if (current.p.first == Bishop)
                {
                    BishopGenerator(i, j, PosMoves,ChesBoard);
                }
                if (current.p.first == Knight)
                {
                    KnightGenerator(i, j, PosMoves,ChesBoard);
                }
                if (current.p.first == Pawn)
                {
                    PawnGenerator(i, j, PosMoves,ChesBoard);
                }
                if (current.p.first == Rook)
                {
                    RookGenerator(i, j, PosMoves,ChesBoard);
                }
                if (current.p.first == Queen)
                {
                    QueenGenerator(i, j, PosMoves,ChesBoard);
                }
                if (current.p.first == King){
                    KingGenerator(i,j,PosMoves,ChesBoard);
                }
            }
        }
    }
    // cout << PosMoves.size() << endl;
    // pair<string,string> BestMove;
    // BestMove = SelectMove(PosMoves,ChesBoard);
    // ChessBoard = MovePiece(BestMove.first,BestMove.second,ChessBoard);
    return PosMoves;
}

void WhiteBishopGenerator(int i, int j, set<pair<string, string>> &PosMoves,vector<vector<gamepiece>> ChesBoard)
{
    // forward right diagnol
    string end = "";
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    // cout << start << endl;
    int crow = i;
    int ccol = j;
    int pos = 1;
    // forward right diagnol
    while (crow + pos < 8 && ccol + pos < 8)
    {
        int row = crow + pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == Black)
        {
            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow - pos >= 0 && ccol - pos >= 0)
    {
        int row = crow - pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});

            break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow + pos < 8 && ccol - pos >= 0)
    {
        int row = crow + pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow - pos >= 0 && ccol + pos < 8)
    {
        int row = crow - pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});

            break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
        pos++;
    }
    // cout<<"Pso size after bish"<<PosMoves.size()<<endl;
}
void WhiteKnightGenerator(int i, int j, set<pair<string, string>> &PosMoves,vector<vector<gamepiece>> ChesBoard)
{
    int currentScore = -1;
    // right up
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    string end = "";
    int row = i - 1;
    int col = j + 2;
    if (row >= 0 && col < 8)
    {
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
    }
    // right down
    row = i + 1;
    col = j + 2;
    if (row < 8 && col < 8)
    {
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }

    // left down
    row = i - 1;
    col = j - 2;
    if (row >= 0 && col >= 0)
    {
        if (ChesBoard[row][col].p.second == Black)
        {
            PosMoves.insert({start, end});
            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;

            PosMoves.insert({start, end});
        }
    }
    // left up
    row = i + 1;
    col = j - 2;
    if (row < 8 && col >= 0)
    {
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;

            PosMoves.insert({start, end});
        }
    }
    // up right
    row = i - 2;
    col = j + 1;
    if (row >= 0 && col < 8)
    {
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;

            PosMoves.insert({start, end});
        }
    }
    // up left
    row = i - 2;
    col = j - 1;
    if (row >= 0 && col >= 0)
    {
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }
    // down right
    row = i + 2;
    col = j + 1;
    if (row < 8 && col < 8)
    {
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }
    // down left
    row = i + 2;
    col = j - 1;
    if (row < 8 && col >= 0)
    {
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
        else if (ChesBoard[row][col].p.second == nuun)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }
        // cout<<"size afrer nigh "<<PosMoves.size()<<endl;

    // cout << start << "," << end << " + " << currentScore << endl;
}
void WhiteRookGenerator(int i, int j, set<pair<string, string>> &PosMoves, vector<vector<gamepiece>> ChesBoard)
{
    int currentScore = 0;
    // right up
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    string end = "";
    int row = i;
    int col = j;
    int pos = 1;
    while (row + pos < 8)
    {
        if (ChesBoard[row + pos][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row + pos][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (row - pos >= 0)
    {
        if (ChesBoard[row - pos][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row - pos][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (col + pos < 8)
    {
        if (ChesBoard[row][col + pos].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col + pos].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (col - pos >= 0)
    {
        if (ChesBoard[row][col - pos].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col - pos].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    // cout<<"size afrer rick "<<PosMoves.size()<<endl;
}

void WhiteQueenGenerator(int i, int j, set<pair<string, string>> &PosMoves, vector<vector<gamepiece>> ChesBoard)
{
    int currentScore = -1;
    // right up
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    string end = "";
    int row = i;
    int col = j;
    int pos = 1;
    while (row + pos < 8)
    {
        if (ChesBoard[row + pos][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row + pos][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (row - pos >= 0)
    {
        if (ChesBoard[row - pos][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row - pos][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (col + pos < 8)
    {
        if (ChesBoard[row][col + pos].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col + pos].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (col - pos >= 0)
    {
        if (ChesBoard[row][col - pos].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col - pos].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    int crow = i;
    int ccol = j;
    pos = 1;
    // forward right diagnol
    while (crow + pos < 8 && ccol + pos < 8)
    {
        int row = crow + pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow - pos >= 0 && ccol - pos >= 0)
    {
        int row = crow - pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow + pos < 8 && ccol - pos >= 0)
    {
        int row = crow + pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    while (crow - pos >= 0 && ccol + pos < 8)
    {
        int row = crow - pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    //     // cout<<"size afrer queenk "<<PosMoves.size()<<endl;

}

void WhitePawnGenerator(int i, int j, set<pair<string, string>> &PosMoves, vector<vector<gamepiece>> ChesBoard)
{
    // right up
    int currentScore = 0;
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    string end = "";
    int row = i;
    int col = j;
    // only three possible moves
    // forward
    if (row - 1 >= 0)
    {
        if (ChesBoard[row - 1][col].p.second != nuun)
        {
        }
        else
        {
            currentScore = max(currentScore, 0);
            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - 1;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
    }
    // left
    if (row - 1 >= 0 && col - 1 >= 0)
    {
        if (ChesBoard[row - 1][col - 1].p.second == White)
        {
        }
        else if (ChesBoard[row - 1][col - 1].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col - 1;
            rw = '0';
            rw += row - 1;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
    }
    // right
    if (row - 1 >= 0 && col + 1 < 8)
    {
        if (ChesBoard[row - 1][col + 1].p.second == White)
        {
        }
        else if (ChesBoard[row - 1][col + 1].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col + 1;
            rw = '0';
            rw += row - 1;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
        }
    }
}
void WhiteKingGenerator(int i, int j, set<pair<string, string>> &PosMoves, vector<vector<gamepiece>> ChesBoard)
{
    int currentScore = -1;
    // right up
    char cl = 'a';
    cl += j;
    char rw = '0';
    rw += i;
    string start = "";
    start += cl;
    // start += " ";
    start += rw;
    string end = "";
    int row = i;
    int col = j;
    int pos = 1;
    if (row + pos < 8)
    {
        if (ChesBoard[row + pos][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row + pos][col].p.second == White)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row + pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (row - pos >= 0)
    {
        if (ChesBoard[row - pos][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row - pos][col].p.second == White)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row - pos;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (col + pos < 8)
    {
        if (ChesBoard[row][col + pos].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col + pos].p.second == White)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col + pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (col - pos >= 0)
    {
        if (ChesBoard[row][col - pos].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col - pos].p.second == White)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col - pos;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    int crow = i;
    int ccol = j;
    pos = 1;
    // forward right diagnol
    if (crow + pos < 8 && ccol + pos < 8)
    {
        int row = crow + pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (crow - pos >= 0 && ccol - pos >= 0)
    {
        int row = crow - pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (crow + pos < 8 && ccol - pos >= 0)
    {
        int row = crow + pos;
        int col = ccol - pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
    pos = 1;
    if (crow - pos >= 0 && ccol + pos < 8)
    {
        int row = crow - pos;
        int col = ccol + pos;
        if (ChesBoard[row][col].p.second == Black)
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            // end += " ";
            end += rw;
            PosMoves.insert({start, end});
            // break;
        }
        else if (ChesBoard[row][col].p.second == White)
        {
            // break;
        }
        else
        {

            end = "";
            cl = 'a';
            cl += col;
            rw = '0';
            rw += row;
            end += cl;
            end += rw;
            currentScore = max(currentScore, 0);
            PosMoves.insert({start, end});
        }
        pos++;
    }
}

bool BlackinCheck(vector<vector<gamepiece>> ChesBoard){
    set<pair<string, string>> osMoves;
    forr(i, BoardSize)
    {
        forr(j, BoardSize)
        {
            gamepiece current = ChesBoard[i][j];
            if (current.p.second == White)
            {
                // if its our own piece
                if (current.p.first == Bishop)
                {
                    WhiteBishopGenerator(i, j, osMoves,ChesBoard);
                }
                if (current.p.first == Knight)
                {
                    WhiteKnightGenerator(i, j, osMoves,ChesBoard);
                }
                if (current.p.first == Pawn)
                {
                    WhitePawnGenerator(i, j, osMoves,ChesBoard);
                }
                if (current.p.first == Rook)
                {
                    WhiteRookGenerator(i, j, osMoves,ChesBoard);
                }
                if (current.p.first == Queen)
                {
                    WhiteQueenGenerator(i, j, osMoves,ChesBoard);
                }
            }
        }
    }
    for(auto &ii : osMoves){
        string curr = ii.second;
        string g1 = ii.second;
        char ro1;
        int col1;
        ro1 = g1[0];
        col1 = g1[1] - '0';
        int row1 = ro1 - 'a';
        swap(col1, row1);
        if(ChesBoard[row1][col1].p.second == Black && ChesBoard[row1][col1].p.first == King){
            PicPos(ii.first,ChesBoard);
            // cout<<"apparently the king is here "<<row1<<","<<col1<<endl;
            return true;
        }
    }
    return false;
}

set<pair<string, string>> WhitemoveGenerator(vector<vector<gamepiece>> ChesBoard)
{
    set<pair<string, string>> PosMoves;
    string h;
    string k;
    forr(i, BoardSize)
    {
        forr(j, BoardSize)
        {
            gamepiece current = ChesBoard[i][j];
            if (current.p.second == White)
            {
                // if its our own piece
                if (current.p.first == Bishop)
                {
                    WhiteBishopGenerator(i, j, PosMoves,ChesBoard);
                }
                if (current.p.first == Knight)
                {
                    WhiteKnightGenerator(i, j, PosMoves,ChesBoard);
                }
                if (current.p.first == Pawn)
                {
                    WhitePawnGenerator(i, j, PosMoves,ChesBoard);
                }
                if (current.p.first == Rook)
                {
                    WhiteRookGenerator(i, j, PosMoves,ChesBoard);
                }
                if (current.p.first == Queen)
                {
                    WhiteQueenGenerator(i, j, PosMoves,ChesBoard);
                }
                if (current.p.first == King){
                    WhiteKingGenerator(i,j,PosMoves,ChesBoard);
                }
            }
        }
    }
    // cout << PosMoves.size() << endl;
    // pair<string,string> BestMove;
    // BestMove = WhiteSelectMove(PosMoves,ChesBoard);
    // MovePiece(BestMove.first,BestMove.second,ChessBoard);
    return PosMoves;
}
void Prin(vector<vector<gamepiece>> ChesBoard)
{
    forr(i, BoardSize)
    {
        forr(j, BoardSize)
        {
            Piece type = ChesBoard[i][j].p.first;
            bool isBlack = (ChesBoard[i][j].p.second == Black);
            // cout<<isBlack<<",";
            char out;
            switch (type)
            {
            case None:
                cout << " ";
                break;
            case Rook:
                out = 'R';
                if (isBlack)
                {
                    out = tolower(out);
                }
                cout << out;
                break;
            case Knight:
                out = 'N';
                if (isBlack)
                {
                    out = tolower(out);
                }
                cout << out;
                break;
            case Bishop:
                out = 'B';
                if (isBlack)
                {
                    out = tolower(out);
                }
                cout << out;
                break;
            case Queen:
                out = 'Q';
                if (isBlack)
                {
                    out = tolower(out);
                }
                cout << out;
                break;
            case King:
                out = 'K';
                if (isBlack)
                {
                    out = tolower(out);
                }
                cout << out;
                break;
            case Pawn:
                out = 'P';
                if (isBlack)
                {
                    out = tolower(out);
                }
                cout << out;
                break;
            }
        }
        cout << endl;
    }
    CurrentEval = BoardEval(ChesBoard);
    cout<<"Current Evaluation - ";
    if(CurrentEval > 0) cout<<"+";
    cout << CurrentEval << cut;
}
void MiniMax()
{   
    // we generate the moves for black store them then for every state after these moves we generate the moves for white 
    // we see what move would make for the best evaluation 
    pair<string,string> TheMove;
    set<pair<string,string>> AllPossibleMovesForBlack = moveGenerator(ChessBoard);
    vector<vector<gamepiece>> copy = ChessBoard;
    cout<<"adadadadadas"<<AllPossibleMovesForBlack.size()<<endl;
    bool first = true;
    double bestEval = BoardEval(ChessBoard);
    for(auto &ii : AllPossibleMovesForBlack){
        vector<vector<gamepiece>> Instance = copy;
        map<Piece,int> m;
        cout<<"retard"<<endl;
        Instance = MovePiece(ii.first,ii.second,copy,1);
        cout<<"retard 2"<<endl;
        // bool u = false;
        bool u = BlackinCheck(Instance);
        cout<<"retard 3"<<endl;
        if(u){
            cout<<"here"<<endl;
            continue;
        }
        cout<<"ye le bkl ye le"<<endl;
        Prin(Instance);
        set<pair<string,string>> AllPossibleMovesForWhiteForThisInstance = WhitemoveGenerator(Instance);
        cout<<"CRACKER"<<endl;
        for(auto &j : AllPossibleMovesForWhiteForThisInstance){
            cout<<j.first<<","<<j.second<<endl;
        }
        double bestcase = 20000;
        for(auto &jj : AllPossibleMovesForWhiteForThisInstance){
            vector<vector<gamepiece>> SecondInstance = Instance;
            SecondInstance = PoliticallyCorrectMovePiece(jj.first,jj.second,SecondInstance);
            cout<<"Moose aaala "<<endl;
            Prin(SecondInstance);
            double EvalForSecond = BoardEval(SecondInstance);
            bestcase = min(bestcase,EvalForSecond);
        }
        if(first){
            bestEval = bestcase;
            TheMove = ii;
            first = false;
        }
        else if(bestEval < bestcase){
                TheMove = ii;
                bestEval = bestcase;
        }
        cout<<"BestEval-"<<bestEval<<","<<"bescase - "<<bestcase<<endl;
    }
    ChessBoard = MovePiece(TheMove.first,TheMove.second,ChessBoard,1);
}
double MiniMaxVarDepth(int depth,double alpha , double beta,vector<vector<gamepiece>> Instance,int cn){
    // cout<<"depth "<<depth<<"cn"<<cn<<endl;
    if(depth == 0){
        // cout<<"cal eva ";
        // cout<<BoardEval(Instance)<<endl;
        return BoardEval(Instance);
    }
        set<pair<string,string>> Moves;
        if(cn == 1){
             Moves = moveGenerator(Instance);
        }else{
            Moves = WhitemoveGenerator(Instance);
        }
        for(auto &ii : Moves){
            
            vector<vector<gamepiece>> SecondInstance = MovePiece(ii.first,ii.second,Instance,cn);
            cn ++;
            cn %= 2;
            double ev = MiniMaxVarDepth(depth - 1, -beta, -alpha,SecondInstance,cn);
            if(ev >= beta){
                return beta;
            }
            alpha = max(alpha,ev);
        }
        // maximazing
        // black
    return alpha;
}
void makeMove(vector<vector<gamepiece>> ChesBoard){
    set<pair<string,string>> PosMoves = moveGenerator(ChesBoard);
    // bool incheck = BlackinCheck(ChesBoard);
    double eval = -200000;
    pair<string,string> TheMove;
    bool first = true;
    int y = 0;
    for(auto &i : PosMoves){
        vector<vector<gamepiece>> Instance = MovePiece(i.first,i.second,ChesBoard,1);
        if(BlackinCheck(Instance)){
            continue;
        }
        if(first){
            TheMove = i;
            first = false;
        }
        double evaloo = MiniMaxVarDepth(4, -200000 , 200000, Instance,0);
        if(eval < evaloo){
            TheMove = i;
            eval = evaloo;
        }
        // eval = max(eval, MiniMax(dept, , , Instance));
        // cout<<"this is it yo "<<TheMove.first<<" "<<TheMove.second<<endl;
        y ++;
    }
    if(y == 0){
        if(BlackinCheck(ChesBoard)){
            cout<<"YOU Win"<<endl;
            return;
        }
    }
    else{
        cout<<"THis the move yo"<<endl;
        cout<<TheMove.first<<","<<TheMove.second<<endl;
        ChessBoard = MovePiece(TheMove.first,TheMove.second,ChessBoard,1);
    }
}
bool isValidMove(string move, string move1, int cr)
{
    int row = move[1] - '0';
    int col = move[0] - 'a';
    int toRow = move1[1] - '0';
    int toCol = move1[0] - 'a';
    row--;
    toRow--;
    if (cr == 0)
    {
        row = 7 - row;
        toRow = 7 - toRow;
    }
    if (cr == 1)
    {
        // checking the initial condition
        if (ChessBoard[row][col].p.second == White)
        {
            return false;
        }
        // checking the final condition
        if (ChessBoard[toRow][toCol].p.second == Black)
        {
            return false;
        }
    }
    else
    {
        if (ChessBoard[row][col].p.second == Black)
        {
            return false;
        }
        if (ChessBoard[toRow][toCol].p.second == White)
        {
            return false;
        }
    }
    return true;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    tester();
    initializeBoard();
    Prin(ChessBoard);
    ll turns = 0;
    int cn = 0;
    while (true)
    {
        movenumber ++;
        if (cn == 0)
        {
            // cout<<"NUMBER OF POSSIBLE MOVES FOR WHITE"<<WhitemoveGenerator(ChessBoar/d)<<endl;
            cout << "ENTER MOVE" << endl;
            string g1, g2;
            cin >> g1 >> g2;
            if(g1 == "end" ){
                break;
            }
            while (!isValidMove(g1, g2,0))
            {
                cout << "INVALID MOVE! TRY AGAIN" << endl;
                Prin(ChessBoard);
                cin >> g1 >> g2;
            }
            g1[1]--;
            g2[1]--;
            // MiniMax();
            ChessBoard = MovePiece(g1, g2, ChessBoard,0);
            Prin(ChessBoard);
        }
        else
        {
            // ll posM = moveGenerator();
            // cout<<"Number of Possible moves is "<<posM<<endl;
            makeMove(ChessBoard);
            // MiniMax();
            Prin(ChessBoard);
        }

        cn++;
        cn%= 2;
        turns ++;
    }

    return 0;
}
