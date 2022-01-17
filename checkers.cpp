#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <stdio.h>

using namespace std;


class Board
{
    public:
    char PBoard[8][8];
    int ix;
    int iy;
    int fx;
    int fy;
    int Heuristic;
};

class Piece
{
    public:
    int x;
    int y;
    bool A;
    bool King;
    char symbol;

};

int getHeuristic(int bsize, Board BoardState);
void GetAPieces(char InBoard[][8], int bsize, Board &BoardState, Piece &APiece, deque<Piece> &APieces);
void GetAPieces(Board CurrentBoard, int bsize, Board &BoardState, Piece &APiece, deque<Piece> &APieces);
void GetBPieces(Board CurrentBoard, int bsize, Board &BoardState, Piece &BPiece, deque<Piece> &BPieces);
bool MinMaxCheckers(char InBoard[][8], int bsize, int Depth);
bool GetRightForwardJumps(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump);
bool GetLeftForwardJumps(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump);
bool GetLeftBackJumps(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump);
bool GetRightBackJumps(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump);
bool GetRightForwardMoves(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates);
bool GetLeftForwardMoves(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates);
bool GetRightBackMoves(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates);
bool GetLeftBackMoves(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates);

bool GetRightForwardJumpsB(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jumpD1);
bool GetLeftForwardJumpsB(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jumpD1);
bool GetLeftBackJumpsB(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jumpD1);
bool GetRightBackJumpsB(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jumpD1);

int main()
{
    int Depth;
    const int bsize=8;
    char Board[bsize][bsize];
    cout << "Enter each symbol for the board, starting from the top left going to the right, pressing enter after each line:"<<endl;
    for(int y = 0; y < bsize; y++)
    {
        for(int x = 0; x < bsize; x++)
        {
            cin>>Board[y][x];
        }
    }

    cin>>Depth;
    while(!(Depth<5 && Depth>0))
    {
        cout<<"Please enter a depth from 1 to 4: ";
        cin>>Depth;
    }
    MinMaxCheckers(Board, bsize, Depth);


    return 0;
}



bool MinMaxCheckers(char InBoard[][8], int bsize, int Depth)
{
    int CurrentDepth=1;
    int BestHeuristicMax=-1000;
    int BestHeuristicMin=1000;
    int HighestBeta=1000;
    int alpha1=-1000;
    int beta1=1000;
    int alpha2=-1000;
    int beta2=1000;
    int alpha3=-1000;
    int beta3=1000;
    int alpha4=-1000;
    int beta4=1000;
    Board BoardState;
    Board CurrentBoard;
    Board BestMoveMax;
    Board BestMoveMin;
    Board CurrentAMove;
    bool jump=false;

    deque<Board> BoardStatesD1;
    deque<Board> BoardStatesD2;
    deque<Board> BoardStatesD3;
    deque<Board> BoardStatesD4;

    deque<Board>::iterator BoardNumberD1;
    deque<Board>::iterator BoardNumberD2;
    deque<Board>::iterator BoardNumberD3;
    deque<Board>::iterator BoardNumberD4;

    Piece APiece;
    Piece BPiece;
    Piece ThisPiece;
    deque<Piece> APieces;
    deque<Piece> BPieces;
    deque<Piece>::iterator PieceNumber;


//////////GET A's PIECES AT START
    GetAPieces(InBoard,bsize,BoardState,APiece,APieces);
/////////GET ALL POSSIBLE MOVES AND CORRESPONDING BOARD STATES FOR A's FIRST MOVE
    for(PieceNumber=APieces.begin();PieceNumber < APieces.end(); PieceNumber++)
    {
    ThisPiece=*PieceNumber;
    GetRightForwardJumps(BoardState,ThisPiece,BoardStatesD1,jump);
    GetLeftForwardJumps(BoardState,ThisPiece,BoardStatesD1,jump);
    if(ThisPiece.King==true)
    {
    GetLeftBackJumps(BoardState,ThisPiece,BoardStatesD1,jump);
    GetRightBackJumps(BoardState,ThisPiece,BoardStatesD1,jump);
    }
    if(jump==false)
    {
    GetRightForwardMoves(BoardState,ThisPiece,BoardStatesD1);
    GetLeftForwardMoves(BoardState,ThisPiece,BoardStatesD1);
        if(ThisPiece.King==true)
        {
            GetRightBackMoves(BoardState,ThisPiece,BoardStatesD1);
            GetLeftBackMoves(BoardState,ThisPiece,BoardStatesD1);
        }
    }
    }
    /////IF PLAYER A HAS NO MOVES
    if(BoardStatesD1.empty())
    {
        cout<<"There are no moves for A."<<endl;
        return 0;
    }

    ////CYCLE THROUGH PLAYER A's POSSIBLE MOVES, IF THIS IS THE DEPTH LIMIT - IT WILL OUTPUT HEURISTIC AND PICK BEST MOVE
    BoardNumberD1=BoardStatesD1.begin();
    while(BoardNumberD1 < BoardStatesD1.end())
    {
    if(CurrentDepth>1)
    {
        if(alpha1<beta2)
        {alpha1=beta2;
        BestMoveMax=CurrentAMove;
        }
    }
    CurrentBoard=*BoardNumberD1;
    CurrentAMove=CurrentBoard;

    if(CurrentDepth==1 && CurrentDepth!=Depth)
    {
    BestMoveMax=CurrentBoard;
    }
    CurrentDepth=1;

    if(alpha1>=beta1)
    {
        cout<<"Depth 0: Pruning Player A's Moves: ("<<CurrentBoard.iy+1<<","<<CurrentBoard.ix+1<<") to ("<<CurrentBoard.fy+1<<","<<CurrentBoard.fx+1<<")."<<endl;
        if(BoardNumberD1==BoardStatesD1.end()-1)
        {
        cout<<"Alpha = "<<alpha1<<"; Beta = "<<beta1<<endl;
        }
    }
    else
    {
    cout<<"Depth 0: Player A moves the piece at ("<<CurrentBoard.iy+1<<","<<CurrentBoard.ix+1<<") to ("<<CurrentBoard.fy+1<<","<<CurrentBoard.fx+1<<")."<<endl;
    if(CurrentDepth==Depth)
    {
    CurrentBoard.Heuristic=getHeuristic(bsize, CurrentBoard);
    cout<<"     Depth 1: Heuristic Value of the Current Board = "<<CurrentBoard.Heuristic<<endl;
    if(CurrentBoard.Heuristic>=BestHeuristicMax)
    {
        BestHeuristicMax=CurrentBoard.Heuristic;
        BestMoveMax=CurrentBoard;
    }
    }

    //////////////PLAYER B's MOVES IF DEPTH > 1;
    else
    {
    CurrentDepth=2;
    alpha2=alpha1;
    beta2=beta1;
    BestHeuristicMin=1000;
    BPieces.clear();
    BoardStatesD2.clear();
    bool jumpD1=false;     /////this variable checks if there are jumps available, since the player has to jump, regular moves are ignored
    GetBPieces(CurrentBoard,bsize,BoardState,BPiece,BPieces);
    for(PieceNumber=BPieces.begin(); PieceNumber < BPieces.end(); PieceNumber++)
    {
    ThisPiece=*PieceNumber;
    GetLeftBackJumpsB(BoardState,ThisPiece,BoardStatesD2,jumpD1);
    GetRightBackJumpsB(BoardState,ThisPiece,BoardStatesD2,jumpD1);
        if(ThisPiece.King==true)
        {
        GetRightForwardJumpsB(BoardState,ThisPiece,BoardStatesD2,jumpD1);
        GetLeftForwardJumpsB(BoardState,ThisPiece,BoardStatesD2,jumpD1);
        }
        if(jumpD1==false)
        {
        GetRightBackMoves(BoardState,ThisPiece,BoardStatesD2);
        GetLeftBackMoves(BoardState,ThisPiece,BoardStatesD2);
            if(ThisPiece.King==true)
            {
            GetRightForwardMoves(BoardState,ThisPiece,BoardStatesD2);
            GetLeftForwardMoves(BoardState,ThisPiece,BoardStatesD2);
            }
        }
    }

    /////IF PLAYER B HAS NO MOVES
    if(BoardStatesD2.empty())
    {
        beta2=1000;
        cout<<"     Depth 1: Player B has no moves"<<endl;
        cout<<"         Depth 2: Heuristic Value of the Current Board = 1000"<<endl;
        BestMoveMax=CurrentAMove;
    }
//    if(alpha>beta)
//    cout<<"     Depth 1: Pruning Player B's Moves "


    BoardNumberD2=BoardStatesD2.begin();
    /////CYCLE THROUGH ALL OF PLAYER B's MOVES OBTAINING HEURISTIC VALUES IF AT DEPTH LIMIT
    while(BoardNumberD2 < BoardStatesD2.end())
    {

    if(CurrentDepth>2)
    {
        if(beta2>alpha3)
        {beta2=alpha3;
        }
    }
    CurrentDepth=2;
    CurrentBoard=*BoardNumberD2;
    if(alpha2>=beta2)
    {
        cout<<"     Depth 1: Pruning Player B's Moves: ("<<CurrentBoard.iy+1<<","<<CurrentBoard.ix+1<<") to ("<<CurrentBoard.fy+1<<","<<CurrentBoard.fx+1<<")."<<endl;
        if(BoardNumberD2==BoardStatesD2.end()-1)
        {
        cout<<"     Alpha = "<<alpha2<<"; Beta = "<<beta2<<endl;

        if(alpha1<beta2)
        {alpha1=beta2;
        BestMoveMax=CurrentAMove;
        }

        }
    }
    else
    {
    cout<<"     Depth 1: Player B moves the piece at ("<<CurrentBoard.iy+1<<","<<CurrentBoard.ix+1<<") to ("<<CurrentBoard.fy+1<<","<<CurrentBoard.fx+1<<")."<<endl;
    if(CurrentDepth==Depth)
    {
    CurrentBoard.Heuristic=getHeuristic(bsize, CurrentBoard);

    cout<<"         Depth 2: Heuristic Value of the Current Board = "<<CurrentBoard.Heuristic<<endl;
    if(CurrentBoard.Heuristic<=BestHeuristicMin)
    {
        beta2=CurrentBoard.Heuristic;
        BestHeuristicMin=beta2;

    }
    if(BoardNumberD2==BoardStatesD2.end()-1)
    {
        if(alpha1<beta2)
        {alpha1=beta2;
        BestMoveMax=CurrentAMove;
        }
    }
    }
    ////PLAYER A's SECOND MOVE IF DEPTH > 2
    else
    {
    alpha3=alpha2;
    beta3=beta2;
    BestHeuristicMax=-1000;
    BoardStatesD3.clear();
    APieces.clear();
    bool jumpD2=false;     /////this variable checks if there are jumps available, since the player has to jump, regular moves are ignored
    GetAPieces(CurrentBoard,bsize,BoardState,APiece,APieces);
    for(PieceNumber=APieces.begin();PieceNumber < APieces.end(); PieceNumber++)
    {
    ThisPiece=*PieceNumber;
    GetRightForwardJumps(BoardState,ThisPiece,BoardStatesD3,jumpD2);
    GetLeftForwardJumps(BoardState,ThisPiece,BoardStatesD3,jumpD2);
    if(ThisPiece.King==true)
    {
    GetLeftBackJumps(BoardState,ThisPiece,BoardStatesD3,jumpD2);
    GetRightBackJumps(BoardState,ThisPiece,BoardStatesD3,jumpD2);
    }
    if(jumpD2==false)
    {
    GetRightForwardMoves(BoardState,ThisPiece,BoardStatesD3);
    GetLeftForwardMoves(BoardState,ThisPiece,BoardStatesD3);
        if(ThisPiece.King==true)
        {
            GetRightBackMoves(BoardState,ThisPiece,BoardStatesD3);
            GetLeftBackMoves(BoardState,ThisPiece,BoardStatesD3);
        }
    }
    }
    /////IF PLAYER A HAS NO MOVES
    if(BoardStatesD3.empty())
    {
        alpha3=-1000;
        cout<<"         Depth 2: Player A has no moves"<<endl;
        cout<<"             Depth 3: Heuristic Value of the Current Board = -1000"<<endl;

    }
//    if(alpha>beta)
//    cout<<"     Depth 1: Pruning Player B's Moves "


    BoardNumberD3=BoardStatesD3.begin();
    /////CYCLE THROUGH ALL OF PLAYER B's MOVES OBTAINING HEURISTIC VALUES IF AT DEPTH LIMIT
    while(BoardNumberD3 < BoardStatesD3.end())
    {
    if(CurrentDepth>3)
    {
        if(alpha3<beta4)
        {alpha3=beta4;
        }
    }
    CurrentDepth=3;
    CurrentBoard=*BoardNumberD3;
    if(alpha3>=beta3)
    {
        cout<<"         Depth 2: Pruning Player A's Moves: ("<<CurrentBoard.iy+1<<","<<CurrentBoard.ix+1<<") to ("<<CurrentBoard.fy+1<<","<<CurrentBoard.fx+1<<")."<<endl;
        if(BoardNumberD3==BoardStatesD3.end()-1)
        {
        cout<<"         Alpha = "<<alpha3<<"; Beta = "<<beta3<<endl;
        if(beta2>alpha3)
        {
            beta2=alpha3;

        }
        }
    }
    else
    {
    cout<<"         Depth 2: Player A moves the piece at ("<<CurrentBoard.iy+1<<","<<CurrentBoard.ix+1<<") to ("<<CurrentBoard.fy+1<<","<<CurrentBoard.fx+1<<")."<<endl;
    if(CurrentDepth==Depth)
    {
    CurrentBoard.Heuristic=getHeuristic(bsize, CurrentBoard);
    cout<<"             Depth 3: Heuristic Value of the Current Board = "<<CurrentBoard.Heuristic<<endl;
    if(CurrentBoard.Heuristic>=BestHeuristicMax)
    {
        BestHeuristicMax=CurrentBoard.Heuristic;
        alpha3=BestHeuristicMax;


//        if(beta2>alpha3)
//        {beta2=alpha3;
//        }
//        if(alpha1<beta2)
//        {alpha1=beta2;
//        BestMoveMax=CurrentAMove;
//        }
    }
    if(BoardNumberD3==BoardStatesD3.end()-1)
    {
        if(beta2>alpha3)
        {
            beta2=alpha3;

        }

    }
    }
    else
    {
    CurrentDepth=4;
    alpha4=alpha3;
    BestHeuristicMin=1000;
    beta4=beta3;
    BPieces.clear();
    BoardStatesD4.clear();
    bool jumpD3=false;     /////this variable checks if there are jumps available, since the player has to jump, regular moves are ignored
    GetBPieces(CurrentBoard,bsize,BoardState,BPiece,BPieces);
    for(PieceNumber=BPieces.begin(); PieceNumber < BPieces.end(); PieceNumber++)
    {
    ThisPiece=*PieceNumber;
    GetLeftBackJumpsB(BoardState,ThisPiece,BoardStatesD4,jumpD3);
    GetRightBackJumpsB(BoardState,ThisPiece,BoardStatesD4,jumpD3);
        if(ThisPiece.King==true)
        {
        GetRightForwardJumpsB(BoardState,ThisPiece,BoardStatesD4,jumpD3);
        GetLeftForwardJumpsB(BoardState,ThisPiece,BoardStatesD4,jumpD3);
        }
        if(jumpD3==false)
        {
        GetRightBackMoves(BoardState,ThisPiece,BoardStatesD4);
        GetLeftBackMoves(BoardState,ThisPiece,BoardStatesD4);
            if(ThisPiece.King==true)
            {
            GetRightForwardMoves(BoardState,ThisPiece,BoardStatesD4);
            GetLeftForwardMoves(BoardState,ThisPiece,BoardStatesD4);
            }
        }
    }

    /////IF PLAYER B HAS NO MOVES
    if(BoardStatesD4.empty())
    {
        beta4=1000;
        cout<<"             Depth 3: Player B has no moves"<<endl;
        cout<<"                 Depth 4: Heuristic Value of the Current Board = 1000";

    }
//    if(alpha>beta)
//    cout<<"     Depth 1: Pruning Player B's Moves "


    BoardNumberD4=BoardStatesD4.begin();
    /////CYCLE THROUGH ALL OF PLAYER B's MOVES OBTAINING HEURISTIC VALUES IF AT DEPTH LIMIT
    while(BoardNumberD4 < BoardStatesD4.end())
    {
    CurrentDepth=4;
    CurrentBoard=*BoardNumberD4;
    if(alpha4>=beta4)
    {
        cout<<"             Depth 3: Pruning Player B's Moves: ("<<CurrentBoard.iy+1<<","<<CurrentBoard.ix+1<<") to ("<<CurrentBoard.fy+1<<","<<CurrentBoard.fx+1<<")."<<endl;
        if(BoardNumberD4==BoardStatesD4.end()-1)
        {
        cout<<"             Alpha = "<<alpha4<<"; Beta = "<<beta4<<endl;
        }
    }
    else
    {
    cout<<"             Depth 3: Player B moves the piece at ("<<CurrentBoard.iy+1<<","<<CurrentBoard.ix+1<<") to ("<<CurrentBoard.fy+1<<","<<CurrentBoard.fx+1<<")."<<endl;
    if(CurrentDepth==Depth)
    {
    CurrentBoard.Heuristic=getHeuristic(bsize, CurrentBoard);

    cout<<"                 Depth 4: Heuristic Value of the Current Board = "<<CurrentBoard.Heuristic<<endl;
    if(CurrentBoard.Heuristic<=BestHeuristicMin)
    {
        BestHeuristicMin=CurrentBoard.Heuristic;
        beta4=BestHeuristicMin;

    }
    if(BoardNumberD4==BoardStatesD4.end()-1)
    {
        if(alpha3<beta4)
        {alpha3=beta4;
        }
    }
    }
    }
    BoardNumberD4++;

    }/////END OF WHILE LOOP FOR B's SECOND MOVE
    }////END OF ELSE LOOP FOR B's SECOND MOVE

    }
    BoardNumberD3++;

    }/////END OF WHILE LOOP FOR A's SECOND MOVE

    }////END OF ELSE LOOP TO GET A's SECOND MOVE

    }
    BoardNumberD2++; //BOARD NUMBER TO ITERATE THROUGH B's FIRST MOVE

    } /////END OF WHILE LOOP FOR B's FIRST MOVE

    }////END OF ELSE LOOP TO GET TO B's FIRST MOVE

    }////END OF ELSE LOOP THAT CHECKS FOR PRUNING OR NOT PLAYER A's FIRST MOVE
    BoardNumberD1++; /////BOARDNUMBER TO ITERATE THROUGH A's FIRST MOVE

    }////END OF WHILE LOOP FOR A's FIRST MOVE
    cout<<"Expansions Completed"<<endl<<endl<<"Answer: Player A moves the piece at ("<<BestMoveMax.iy+1<<","<<BestMoveMax.ix+1<<") to ("<<BestMoveMax.fy+1<<","<<BestMoveMax.fx+1<<")."<<endl;

    return 0;
}


void GetAPieces(char InBoard[][8], int bsize, Board &BoardState, Piece &APiece, deque<Piece> &APieces)
{
for(int y = 0; y < bsize; y++)
    {
        for(int x = 0; x < bsize; x++)
        {
            BoardState.PBoard[y][x]=InBoard[y][x];
            if(InBoard[y][x]=='k')
            {
            APiece.King=true;
            APiece.A=true;
            APiece.x=x;
            APiece.y=y;
            APiece.symbol='k';
            APieces.push_back(APiece);
            }
            if(InBoard[y][x]=='o')
            {
            APiece.King=false;
            APiece.A=true;
            APiece.x=x;
            APiece.y=y;
            APiece.symbol='o';
            APieces.push_back(APiece);
            }
        }
    }
}

void GetAPieces(Board CurrentBoard, int bsize, Board &BoardState, Piece &APiece, deque<Piece> &APieces)
{
for(int y = 0; y < bsize; y++)
    {
        for(int x = 0; x < bsize; x++)
        {
            BoardState.PBoard[y][x]=CurrentBoard.PBoard[y][x];
            if(CurrentBoard.PBoard[y][x]=='k')
            {
            APiece.King=true;
            APiece.A=true;
            APiece.x=x;
            APiece.y=y;
            APiece.symbol='k';
            APieces.push_back(APiece);
            }
            if(CurrentBoard.PBoard[y][x]=='o')
            {
            APiece.King=false;
            APiece.A=true;
            APiece.x=x;
            APiece.y=y;
            APiece.symbol='o';
            APieces.push_back(APiece);
            }
        }
    }
}


void GetBPieces(Board CurrentBoard, int bsize, Board &BoardState, Piece &BPiece, deque<Piece> &BPieces)
{
for(int y = 0; y < bsize; y++)
    {
        for(int x = 0; x < bsize; x++)
        {
            BoardState.PBoard[y][x]=CurrentBoard.PBoard[y][x];
            if(CurrentBoard.PBoard[y][x]=='K')
            {
            BPiece.King=true;
            BPiece.A=true;
            BPiece.x=x;
            BPiece.y=y;
            BPiece.symbol='K';
            BPieces.push_back(BPiece);
            }
            if(CurrentBoard.PBoard[y][x]=='*')
            {
            BPiece.King=false;
            BPiece.A=true;
            BPiece.x=x;
            BPiece.y=y;
            BPiece.symbol='*';
            BPieces.push_back(BPiece);
            }
        }
    }
}


/////////A's POSSIBLE JUMP FUNCTIONS

bool GetRightForwardJumps(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y >= 2)
    {
        if(CurrentPiece.x<=5)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x+1]=='*' || CurrentBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x+1]=='K')
                {
                if(CurrentBoard.PBoard[CurrentPiece.y-2][CurrentPiece.x+2]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x+1]='.';
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.PBoard[CurrentPiece.y-2][CurrentPiece.x+2]=CurrentPiece.symbol;
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x+2;
                TempBoard.fy=CurrentPiece.y-2;
                BoardStates.push_front(TempBoard);
                jump=true;
                return 0;
                }
                }

        }
    }
}

bool GetLeftForwardJumps(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y >= 2)
    {
        if(CurrentPiece.x>=2)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x-1]=='*' || CurrentBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x-1]=='K')
                {
                if(CurrentBoard.PBoard[CurrentPiece.y-2][CurrentPiece.x-2]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x-1]='.';
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.PBoard[CurrentPiece.y-2][CurrentPiece.x-2]=CurrentPiece.symbol;
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x-2;
                TempBoard.fy=CurrentPiece.y-2;
                BoardStates.push_front(TempBoard);
                jump=true;
                return 0;
                }
                }
        }
    }
}

bool GetLeftBackJumps(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y <=5)
    {
        if(CurrentPiece.x>=2)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x-1]=='*' || CurrentBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x-1]=='K')
                {
                if(CurrentBoard.PBoard[CurrentPiece.y+2][CurrentPiece.x-2]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x-1]='.';
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.PBoard[CurrentPiece.y+2][CurrentPiece.x-2]=CurrentPiece.symbol;
                BoardStates.push_front(TempBoard);
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x-2;
                TempBoard.fy=CurrentPiece.y+2;
                jump=true;
                return 0;
                }
                }

        }
    }
}

bool GetRightBackJumps(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y <= 5)
    {
        if(CurrentPiece.x<=5)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x+1]=='*' || CurrentBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x+1]=='K')
                {
                if(CurrentBoard.PBoard[CurrentPiece.y+2][CurrentPiece.x+2]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x+1]='.';
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.PBoard[CurrentPiece.y+2][CurrentPiece.x+2]=CurrentPiece.symbol;
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x+2;
                TempBoard.fy=CurrentPiece.y+2;
                BoardStates.push_front(TempBoard);
                jump=true;
                return 0;
                }
                }

        }
    }
}

bool GetRightForwardMoves(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates)
{
    Board TempBoard;
    TempBoard=CurrentBoard;

    if(CurrentPiece.y >= 1)
    {
        if(CurrentPiece.x<=6)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x+1]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x+1]=CurrentPiece.symbol;
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x+1;
                TempBoard.fy=CurrentPiece.y-1;
                BoardStates.push_front(TempBoard);
                return 0;
                }

        }
    }
}

bool GetLeftForwardMoves(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y >= 1)
    {
        if(CurrentPiece.x>=1)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x-1]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x-1]=CurrentPiece.symbol;
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x-1;
                TempBoard.fy=CurrentPiece.y-1;
                BoardStates.push_front(TempBoard);
                return 0;
                }

        }
    }
}

bool GetLeftBackMoves(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y <= 6)
    {
        if(CurrentPiece.x>=1)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x-1]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x-1]=CurrentPiece.symbol;
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x-1;
                TempBoard.fy=CurrentPiece.y+1;
                BoardStates.push_front(TempBoard);
                return 0;
                }

        }
    }
}

bool GetRightBackMoves(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y <= 6)
    {
        if(CurrentPiece.x<=6)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x+1]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x+1]=CurrentPiece.symbol;
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x+1;
                TempBoard.fy=CurrentPiece.y+1;
                BoardStates.push_front(TempBoard);
                return 0;
                }

        }
    }
}

////////// B's POSSIBLE JUMPS FUNCTIONS

bool GetRightForwardJumpsB(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y >= 2)
    {
        if(CurrentPiece.x<=5)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x+1]=='o' || CurrentBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x+1]=='k')
                {
                if(CurrentBoard.PBoard[CurrentPiece.y-2][CurrentPiece.x+2]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x+1]='.';
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.PBoard[CurrentPiece.y-2][CurrentPiece.x+2]=CurrentPiece.symbol;
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x+2;
                TempBoard.fy=CurrentPiece.y-2;
                BoardStates.push_front(TempBoard);
                jump=true;
                return 0;
                }
                }

        }
    }
}

bool GetLeftForwardJumpsB(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y >= 2)
    {
        if(CurrentPiece.x>=2)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x-1]=='o' || CurrentBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x-1]=='k')
                {
                if(CurrentBoard.PBoard[CurrentPiece.y-2][CurrentPiece.x-2]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y-1][CurrentPiece.x-1]='.';
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.PBoard[CurrentPiece.y-2][CurrentPiece.x-2]=CurrentPiece.symbol;
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x-2;
                TempBoard.fy=CurrentPiece.y-2;
                BoardStates.push_front(TempBoard);
                jump=true;
                return 0;
                }
                }
        }
    }
}

bool GetLeftBackJumpsB(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y <=5)
    {
        if(CurrentPiece.x>=2)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x-1]=='o' || CurrentBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x-1]=='k')
                {
                if(CurrentBoard.PBoard[CurrentPiece.y+2][CurrentPiece.x-2]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x-1]='.';
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.PBoard[CurrentPiece.y+2][CurrentPiece.x-2]=CurrentPiece.symbol;
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x-2;
                TempBoard.fy=CurrentPiece.y+2;
                BoardStates.push_front(TempBoard);
                jump=true;
                return 0;
                }
                }

        }
    }
}

bool GetRightBackJumpsB(Board CurrentBoard, Piece CurrentPiece, deque<Board> &BoardStates,bool &jump)
{
    Board TempBoard;
    TempBoard=CurrentBoard;
    if(CurrentPiece.y <= 5)
    {
        if(CurrentPiece.x<=5)
        {
            if(CurrentBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x+1]=='o' || CurrentBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x+1]=='k')
                {
                if(CurrentBoard.PBoard[CurrentPiece.y+2][CurrentPiece.x+2]=='.')
                {
                TempBoard.PBoard[CurrentPiece.y+1][CurrentPiece.x+1]='.';
                TempBoard.PBoard[CurrentPiece.y][CurrentPiece.x]='.';
                TempBoard.PBoard[CurrentPiece.y+2][CurrentPiece.x+2]=CurrentPiece.symbol;
                TempBoard.ix=CurrentPiece.x;
                TempBoard.iy=CurrentPiece.y;
                TempBoard.fx=CurrentPiece.x+2;
                TempBoard.fy=CurrentPiece.y+2;
                BoardStates.push_front(TempBoard);
                jump=true;
                return 0;
                }
                }

        }
    }
}



//////////GET HEURISTIC FUNCTION

int getHeuristic(int bsize, Board BoardState)
{
    int Heuristic=0;
    int A=0;
    int B=0;
    for(int y = 0; y < bsize; y++)
    {
        for(int x = 0; x < bsize; x++)
        {
            if(BoardState.PBoard[y][x]=='o')
            A++;
            if(BoardState.PBoard[y][x]=='k')
            A=A+2;
            if(BoardState.PBoard[y][x]=='*')
            B++;
            if(BoardState.PBoard[y][x]=='K')
            B=B+2;
        }
    }
    Heuristic=A-B;
    if(A==0)
    {
    Heuristic=-1000;
    }
    if(B==0)
    {
    Heuristic=1000;
    }
    return Heuristic;
};


