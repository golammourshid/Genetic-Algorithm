// Source File Header
// homework.cpp
// Md. Fahim Alam, CISP 400
// 16/10/21

#include<iostream>
#include <ctime>
//#include <unistd.h>
#include <stdlib.h>
//#include <chrono>

using namespace std;




//This is the structure class of the Genetic Algorithm.
class allRobot
{
public:
    int robotWithPosition [12][12];
    int robotWithGenes [16][5];
    int robotWithEnergy;
    int robotWithTurns;
    double robotAvgFitness;
    int Gene[16][5];
    int Grid [12][12];
    int initX, initY, randDir;
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
    void sortRoboticGene(allRobot obj[]);
    void Reproduction(allRobot obj[]);
};


int main ()
{
    int totalRobot = 5, totalGeneration = 10;
    allRobot all_robot[totalRobot], tempRobot, generationCountRobot[totalGeneration];
    cout<<"Starting Genetic Algorithm SImulation..............."<<endl<<endl;
    int indx, generation;
    for(generation = 0 ; generation<totalGeneration; generation++)
    {
        //all_robot.robotSeq = 0;
        int cntTurn = 0;

        for(indx = 0; indx<totalRobot; indx++)
        {
            //creating an allRobot type object
            all_robot[indx].robotWithEnergy = 5;
            //cout<<"Initial Energy: "<<all_robot.robotWithEnergy[all_robot.robotSeq][0]<<endl;
            if(generation==0)
            {
                all_robot[indx].geneCreate();
                all_robot[indx].gridCreate();
            }

            all_robot[indx].placeRobot();
            all_robot[indx].robotWithPosition[all_robot[indx].initX][all_robot[indx].initY];
            //all_robot.Grid, all_robot.robotWithGenes, all_robot.robotWithEnergy,all_robot.robotWithPosition
            all_robot[indx].runRobot();
            for(int i=0; i<16; i++)
            {
                for (int j=0; j<5; j++)
                {
                    cout<<all_robot[indx].Gene[i][j] <<" ";

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
                    cout<<all_robot[indx].Grid[i][j] <<" ";

                }
                cout<<endl;
            }
            cntTurn+=all_robot[indx].robotWithTurns;
            cout<<"Total Turns: "<<all_robot[indx].robotWithTurns<<endl;
        }
        tempRobot.sortRoboticGene(all_robot);
        tempRobot.Reproduction(all_robot);
        for(int k=0; k<totalRobot; k++)
        {
            for(int i=0; i<16; i++)
            {
                for (int j=0; j<5; j++)
                {
                    cout<<all_robot[k].Gene[i][j] <<" ";

                }
                cout<<endl;
            }
            cout<<endl;
        }
        generationCountRobot[generation].robotAvgFitness = cntTurn/totalRobot;
        cout<<"Average fitness of generation "<<generation<<": "<<generationCountRobot[generation].robotAvgFitness<<endl;
    }
    for(int i=0;i<totalGeneration;i++)
    {
        //generationCountRobot[generation].robotAvgFitness = cntTurn/totalRobot;
        cout<<"Average fitness of generation "<<i<<": "<<generationCountRobot[i].robotAvgFitness<<endl;
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
    cout<<"initial X: "<<x<<", Initial Y: "<<y<<endl;
    //cout<<"initial energy: "<<robotWithEnergy[robotSeq][0]<<endl;
    //added a flag for matching a gene
    bool flag = false;
    while(1)
    {
        if(robotWithEnergy<=0)
        {
            robotWithTurns = turns;
            //cout<<"Turns: "<<robotWithTurns<<endl;
            return;
        }
        if(Grid[x][y] == 9)
        {
            robotWithEnergy+=5;
            turns++;
        }
        else if(Grid[x][y] == 1)
        {
            turns += robotWithEnergy;
            robotWithEnergy = 0;
            continue;
        }
        else if(Grid[x][y] == 0)
        {
            robotWithEnergy--;
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

void allRobot::sortRoboticGene(allRobot obj[])
{
    for(int i=0; i<5-1; i++)
    {
        for(int j=0; j<5-1-i; j++)
        {
            if(obj[j].robotWithTurns < obj[j+1].robotWithTurns)
            {
                cout<<obj[j].robotWithTurns<<" and "<<obj[j+1].robotWithTurns<<endl;
                swap(obj[j].Gene,obj[j+1].Gene);
                swap(obj[j].robotWithTurns,obj[j+1].robotWithTurns);
            }
        }
    }
}

void allRobot::Reproduction(allRobot obj[])
{
    for(int i=0; i<4; i+=2)
    {

        for(int j=8; j<16; j++)
        {
            //cout<<obj[j].robotWithTurns<<" and "<<obj[j+1].robotWithTurns<<endl;
            swap(obj[i].Gene[j],obj[i+1].Gene[j]);
            //swap(obj[j].robotWithTurns,obj[j+1].robotWithTurns);
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
            else
            {
                Grid[i][j]=0;
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
