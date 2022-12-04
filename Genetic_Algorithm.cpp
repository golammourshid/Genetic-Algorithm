// Source File Header
// homework.cpp
// Md. Fahim Alam, CISP 400
// 16/10/21

#include<iostream>
#include <ctime>
#include <windows.h>
#include <unistd.h>
#include <chrono>

using namespace std;




//This is the structure class of the inventory system.
class allRobot
{
public:
    int robotWithPosition [200][12][12];
    int robotWithGenes [200][16][5];
    int robotWithEnergy [200][1];
    int robotWithTurns [200][1]= {0};
    int Gene[16][5];
    int Grid [12][12] = {0};
    int initX, initY, randDir, robotSeq;
    allRobot()
    {
        srand(time(NULL));
        //For preventing repeated sequence of random number
    }
    void geneCreate();
    void gridCreate();
    void placeRobot();
    void robotRandDirection();
    void runRobot();
};


int main ()
{
    allRobot all_robot;
    cout<<"Starting Genetic Algorithm SImulation..............."<<endl<<endl;
    int twoHundred = 200;
    all_robot.robotSeq = 0;
    for(; all_robot.robotSeq<1; all_robot.robotSeq++)
    {
        //creating an Date type object
        allRobot all_robot;
        all_robot.robotWithEnergy[all_robot.robotSeq][0] = 5;
        all_robot.geneCreate();
        all_robot.gridCreate();
        all_robot.placeRobot();
        all_robot.robotWithPosition[all_robot.robotSeq][all_robot.initX][all_robot.initY];
        //all_robot.Grid, all_robot.robotWithGenes, all_robot.robotWithEnergy,all_robot.robotWithPosition
        all_robot.runRobot();
        for(int i=0; i<16; i++)
        {
            for (int j=0; j<5; j++)
            {
                cout<<all_robot.Gene[i][j] <<" ";

            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
        cout<<endl;
        for(int i=0; i<12; i++)
        {
            for (int j=0; j<12; j++)
            {
                cout<<all_robot.Grid[i][j] <<" ";

            }
            cout<<endl;
        }
        cout<<"Total Turns: "<<all_robot.robotWithTurns[all_robot.robotSeq][0]<<endl;
    }
    return 0;
}

void allRobot::robotRandDirection()
{
    randDir = rand() % 4;
}

void allRobot::placeRobot()
{
    initX = 1 + rand() % 10;
    initY = 1 + rand() % 10;
}
//allRobot Grid, allRobot robotWithGenes,allRobot robotWithEnergy,allRobot robotWithPosition
void allRobot::runRobot()
{
    //cout<<"HI Antor "<<Grid[1][2]<<endl;
    int x=initX, y=initY, turns = 0;
    cout<<"initial X: "<<x<<"Initial Y: "<<y<<endl;
    //added a flag for matching a gene
    bool flag = false;
    while(1)
    {
        if(robotWithEnergy[robotSeq][0]<0)
        {
            robotWithTurns[robotSeq][0] = turns;
            cout<<"Turns: "<<robotWithTurns[robotSeq][0]<<endl;
            return;
        }
        if(Grid[x][y] == 9)
        {
            robotWithEnergy[robotSeq][0]+=5;
            turns++;
        }
        else if(Grid[x][y] == 1)
        {
            turns += robotWithEnergy[robotSeq][0];
            robotWithEnergy[robotSeq][0] = 0;
            break;
        }
        else if(Grid[x][y] == 0)
        {
            robotWithEnergy[robotSeq][0]--;
            turns++;
        }
        int direction;
        for(int i=0; i<16; i++)
        {
            if(Gene[i][0] == Grid[x-1][y] && Gene[i][1] == Grid[x+1][y] && Gene[i][2] == Grid[x][y+1] &&  Gene[i][3] == Grid[x][y-1])
            {
                flag = true;
                direction = Gene[i][4];
            }
        }
        if(!flag)
        {
            direction = Gene[15][4];
        }
        if(direction = 4)
        {
            robotRandDirection();
            direction = randDir;
        }
        if(direction = 0)
        {
            x--;
        }
        else if(direction = 1)
        {
            x++;
        }
        else if(direction = 2)
        {
            y++;
        }
        else if(direction = 3)
        {
            y--;
        }
    }
}

void allRobot::gridCreate()
{
    for(int i=0; i<12; i++)
    {
        for(int j=0; j<12; j++)
        {
            if(i==0 || i==11 || j==0 || j==11)
            {
                Grid[i][j]=1;
            }
        }
        if(i!=0 && i!=11)
        {
            for(int j=0; ;)
            {
                int randomColumn = 1 + rand() % 10;
                if(Grid[i][randomColumn] != 9)
                {
                    Grid[i][randomColumn] = 9;
                    j++;
                }
                if(j>=4)
                {
                    break;
                }
            }
        }
    }
}


//Here Gene [][0] = North, Gene [][1] = South, Gene [][2] = East, Gene [][3] = West, Gene [][4] = Direction
void allRobot::geneCreate()
{
    Gene[0][0] = 0;
    Gene[0][1] = 0;
    Gene[0][2] = 0;
    Gene[0][3] = 0;
    Gene[0][4] = rand() % 5;

    Gene[1][0] = 1;
    Gene[1][1] = 1;
    Gene[1][2] = 1;
    Gene[1][3] = 1;
    Gene[1][4] = rand() % 5;

    Gene[2][0] = 9;
    Gene[2][1] = 9;
    Gene[2][2] = 9;
    Gene[2][3] = 9;
    Gene[2][4] = rand() % 5;

    Gene[3][0] = 0;
    Gene[3][1] = 1;
    Gene[3][2] = 0;
    Gene[3][3] = 0;
    Gene[3][4] = rand() % 5;

    Gene[4][0] = 1;
    Gene[4][1] = 0;
    Gene[4][2] = 0;
    Gene[4][3] = 0;
    Gene[4][4] = rand() % 5;

    Gene[5][0] = 9;
    Gene[5][1] = 0;
    Gene[5][2] = 0;
    Gene[5][3] = 0;
    Gene[5][4] = rand() % 5;

    Gene[6][0] = 0;
    Gene[6][1] = 9;
    Gene[6][2] = 0;
    Gene[6][3] = 0;
    Gene[6][4] = rand() % 5;

    Gene[7][0] = 0;
    Gene[7][1] = 0;
    Gene[7][2] = 1;
    Gene[7][3] = 0;
    Gene[7][4] = rand() % 5;

    Gene[8][0] = 0;
    Gene[8][1] = 0;
    Gene[8][2] = 0;
    Gene[8][3] = 9;
    Gene[8][4] = rand() % 5;

    Gene[9][0] = 9;
    Gene[9][1] = 0;
    Gene[9][2] = 9;
    Gene[9][3] = 0;
    Gene[9][4] = rand() % 5;

    Gene[10][0] = 0;
    Gene[10][1] = 9;
    Gene[10][2] = 0;
    Gene[10][3] = 9;
    Gene[10][4] = rand() % 5;

    Gene[11][0] = 1;
    Gene[11][1] = 9;
    Gene[11][2] = 0;
    Gene[11][3] = 0;
    Gene[11][4] = rand() % 5;

    Gene[12][0] = 0;
    Gene[12][1] = 9;
    Gene[12][2] = 9;
    Gene[12][3] = 0;
    Gene[12][4] = rand() % 5;

    Gene[13][0] = 9;
    Gene[13][1] = 9;
    Gene[13][2] = 1;
    Gene[13][3] = 0;
    Gene[13][4] = rand() % 5;

    Gene[14][0] = 1;
    Gene[14][1] = 9;
    Gene[14][2] = 9;
    Gene[14][3] = 0;
    Gene[14][4] = rand() % 5;

    Gene[15][0] = 9;
    Gene[15][1] = 9;
    Gene[15][2] = 9;
    Gene[15][3] = 1;
    Gene[15][4] = rand() % 5;
}
