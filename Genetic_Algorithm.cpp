// Source File Header
// Genetic_Algorithm.cpp
// Md. Fahim Alam, CISP 400
// 12/13/22

#include<iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

//This is the main structure class of the Genetic Algorithm.
class allRobot
{
public:
    int totalRobot = 200, totalGeneration = 50;
    //int robotWithPosition [12][12];
    //int robotWithGenes [16][5];
    int robotWithEnergy;
    int robotWithTurns;
    double robotAvgFitness;
    int Gene[16][5] = {};
    int Grid [12][12] = {};
    int initX, initY, randDir=-1;
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
    void Mutation(allRobot obj[]);
    void plot_point (double y_pos, int screen_width, int yAxis);
    void plot_graph (allRobot obj[]);
};


int main ()
{
    //int totalRobot = 200, totalGeneration = 50;
    allRobot tempRobot;
    allRobot all_robot[tempRobot.totalRobot], generationCountRobot[tempRobot.totalGeneration];
    cout<<"Starting Genetic Algorithm SImulation..............."<<endl<<endl;
    int indx, generation;
    for(generation = 0 ; generation<tempRobot.totalGeneration; generation++)
    {
        //all_robot.robotSeq = 0;
        int cntTurn = 0;

        for(indx = 0; indx<tempRobot.totalRobot; indx++)
        {
            //creating an allRobot type object
            all_robot[indx].robotWithEnergy = 5;
            //cout<<"Initial Energy: "<<all_robot.robotWithEnergy[all_robot.robotSeq][0]<<endl;
            if(generation==0)
            {
                all_robot[indx].geneCreate();
                all_robot[indx].gridCreate();
            }
            //all_robot[indx].gridCreate();
            all_robot[indx].placeRobot();
            //all_robot[indx].robotWithPosition[all_robot[indx].initX][all_robot[indx].initY];
            //all_robot.Grid, all_robot.robotWithGenes, all_robot.robotWithEnergy,all_robot.robotWithPosition
            all_robot[indx].runRobot();
            for(int i=0; i<16; i++)
            {
                for (int j=0; j<5; j++)
                {
                    //cout<<all_robot[indx].Gene[i][j] <<" ";

                }
                //cout<<endl;
            }
            //cout<<endl;
            //cout<<endl;
            //cout<<endl;
            for(int i=0; i<12; i++)
            {
                for (int j=0; j<12; j++)
                {
                    //cout<<all_robot[indx].Grid[i][j] <<" ";

                }
                //cout<<endl;
            }
            cntTurn+=all_robot[indx].robotWithTurns;
            //cout<<"Total Turns: "<<all_robot[indx].robotWithTurns<<endl;
        }
        tempRobot.sortRoboticGene(all_robot);
        tempRobot.Reproduction(all_robot);
        tempRobot.Mutation(all_robot);
        for(int k=0; k<tempRobot.totalRobot; k++)
        {
            for(int i=0; i<16; i++)
            {
                for (int j=0; j<5; j++)
                {
                    //cout<<all_robot[k].Gene[i][j] <<" ";

                }
                //cout<<endl;
            }
            //cout<<endl;
        }
        generationCountRobot[generation].robotAvgFitness = (double)cntTurn/(double)tempRobot.totalRobot;
        //cout<<"Average fitness of generation "<<generation<<": "<<generationCountRobot[generation].robotAvgFitness<<endl;
    }
    int totalAverageTurns=0;
    for(int i=0; i<tempRobot.totalGeneration; i++)
    {
        //generationCountRobot[generation].robotAvgFitness = cntTurn/totalRobot;
        cout<<"Average fitness of generation "<<i<<": "<<generationCountRobot[i].robotAvgFitness<<endl;
        totalAverageTurns+=generationCountRobot[i].robotAvgFitness;
    }
    cout<<"\n\n\nThe fitness graph is given below:\nHere, Average Fitness is in X axis and Generation is in Y axis\n"<<endl;
    tempRobot.plot_graph(generationCountRobot);
    cout<<"\n\nTotal average turns over all generation: "<<(double)totalAverageTurns/(double)tempRobot.totalGeneration<<endl<<"That means the average turns for all the single generation is near this average value"<<endl;
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
    int x=initX, y=initY;
    double turns = 0.0;
    if(Grid[x][y] == 9)
    {
        robotWithEnergy+=5;
        //turns++;
    }
    //cout<<"initial X: "<<x<<", Initial Y: "<<y<<endl;
    //cout<<"initial energy: "<<robotWithEnergy[robotSeq][0]<<endl;
    //added a flag for matching a gene

    while(1)
    {
        bool flag = false;
        if(robotWithEnergy<=0)
        {
            robotWithTurns = turns;
            //cout<<"Turns: "<<robotWithTurns<<endl;
            return;
        }

        int direction;
        for(int i=0; i<16; i++)
        {
            if(Gene[i][0] == Grid[x-1][y] && Gene[i][1] == Grid[x+1][y] && Gene[i][2] == Grid[x][y+1] &&  Gene[i][3] == Grid[x][y-1])
            {
                flag = true;
                direction = Gene[i][4];
                break;
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


        if(Grid[x][y] == 9)
        {
            robotWithEnergy+=5;
            turns++;
        }
        else if(Grid[x][y] == 1)
        {
            if(randDir != -1)
            {
                robotWithEnergy--;
                turns++;
                //Restore previous position if there is a random move and find a wall
                if(direction = 0)
                {
                    x++;
                }
                else if(direction = 1)
                {
                    x--;
                }
                else if(direction = 2)
                {
                    y--;
                }
                else if(direction = 3)
                {
                    y++;
                }
            }
            else
            {
                turns += robotWithEnergy;
                robotWithEnergy = 0;
            }
        }
        else if(Grid[x][y] == 0)
        {
            robotWithEnergy--;
            turns++;
        }
        randDir = -1;
    }
}

void allRobot::sortRoboticGene(allRobot obj[])
{
    for(int i=0; i<totalRobot-1; i++)
    {
        for(int j=0; j<totalRobot-1-i; j++)
        {
            if(obj[j].robotWithTurns < obj[j+1].robotWithTurns)
            {
                //cout<<obj[j].robotWithTurns<<" and "<<obj[j+1].robotWithTurns<<endl;
                swap(obj[j].Gene,obj[j+1].Gene);
                swap(obj[j].robotWithTurns,obj[j+1].robotWithTurns);
            }
        }
    }
}



void allRobot::Reproduction(allRobot obj[])
{
    for(int i=0, k = (totalRobot/2); i<(totalRobot/2); i+=2, k+=2)
    {
        for(int j=0; j<8; j++)
        {
            //cout<<obj[j].robotWithTurns<<" and "<<obj[j+1].robotWithTurns<<endl;
            for(int m = 0; m<5; m++)
            {
                obj[k].Gene[j][m] = obj[i].Gene[j][m];
                obj[k+1].Gene[j][m] = obj[i+1].Gene[j][m];
            }
            //swap(obj[j].robotWithTurns,obj[j+1].robotWithTurns);
        }
        for(int j=8; j<15; j++)
        {
            //cout<<obj[j].robotWithTurns<<" and "<<obj[j+1].robotWithTurns<<endl;
            for(int m = 0; m<5; m++)
            {
                obj[k].Gene[j][m] = obj[i+1].Gene[j][m];
                obj[k+1].Gene[j][m] = obj[i].Gene[j][m];
            }
            //swap(obj[j].robotWithTurns,obj[j+1].robotWithTurns);
        }
    }
}


//Mutation for 5% of the children. Just shifting all genes down 1 and the 16th gene moves to the top.
void allRobot::Mutation(allRobot obj[])
{
    //int robotcnt = 0;
    for(int i=0; i<5; i++)
    {
        int randRobot = (totalRobot/2) + (rand() % (totalRobot/2));
        int tmp = obj[randRobot].Gene[0][4];
        for(int j=0; j<15; j++)
        {
            //cout<<obj[j].robotWithTurns<<" and "<<obj[j+1].robotWithTurns<<endl;

            //tmp = obj[randRobot].Gene[j][4];
            obj[randRobot].Gene[j][4] = obj[randRobot].Gene[j+1][4];
        }
        obj[randRobot].Gene[15][4] = tmp;
    }
}

void allRobot::gridCreate()
{
    //Giving wall for all side of the 10x10 grid and giving space (with value 0) for all inside squares
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
    }
    //Randomly populating 40% of the squares with batteries (with value 9).
    for(int j=0; ;)
    {
        int randomRow = 1 + rand() % 10;
        int randomColumn = 1 + rand() % 10;
        if(Grid[randomRow][randomColumn] != 9)
        {
            Grid[randomRow][randomColumn] = 9;
            j++;
        }
        if(j>=40)
        {
            break;
        }
    }
}


//Here Gene [][0] = North, Gene [][1] = South, Gene [][2] = East, Gene [][3] = West, Gene [][4] = Direction
//direction = 0 means north, 1 means south, 2 means east, 3 means west, 4 means random move
//Here the gene is all time fixed, but the direction under each gene is randomly generated.
void allRobot::geneCreate()
{
    //first gene
    Gene[0][0] = 0;
    Gene[0][1] = 0;
    Gene[0][2] = 0;
    Gene[0][3] = 0;
    Gene[0][4] = rand() % 5;

    //second gene
    Gene[1][0] = 1;
    Gene[1][1] = 1;
    Gene[1][2] = 1;
    Gene[1][3] = 1;
    Gene[1][4] = rand() % 5;

    //third gene
    Gene[2][0] = 9;
    Gene[2][1] = 9;
    Gene[2][2] = 9;
    Gene[2][3] = 9;
    Gene[2][4] = rand() % 5;

    //fourth gene
    Gene[3][0] = 0;
    Gene[3][1] = 1;
    Gene[3][2] = 0;
    Gene[3][3] = 0;
    Gene[3][4] = rand() % 5;

    //fifth gene
    Gene[4][0] = 1;
    Gene[4][1] = 0;
    Gene[4][2] = 0;
    Gene[4][3] = 0;
    Gene[4][4] = rand() % 5;

    //sixth gene
    Gene[5][0] = 9;
    Gene[5][1] = 0;
    Gene[5][2] = 0;
    Gene[5][3] = 0;
    Gene[5][4] = rand() % 5;

    //seventh gene
    Gene[6][0] = 0;
    Gene[6][1] = 9;
    Gene[6][2] = 0;
    Gene[6][3] = 0;
    Gene[6][4] = rand() % 5;

    //eighth gene
    Gene[7][0] = 0;
    Gene[7][1] = 0;
    Gene[7][2] = 1;
    Gene[7][3] = 0;
    Gene[7][4] = rand() % 5;

    //nineth gene
    Gene[8][0] = 0;
    Gene[8][1] = 0;
    Gene[8][2] = 0;
    Gene[8][3] = 9;
    Gene[8][4] = rand() % 5;

    //tenth gene
    Gene[9][0] = 9;
    Gene[9][1] = 0;
    Gene[9][2] = 9;
    Gene[9][3] = 0;
    Gene[9][4] = rand() % 5;

    //eleventh gene
    Gene[10][0] = 0;
    Gene[10][1] = 9;
    Gene[10][2] = 0;
    Gene[10][3] = 9;
    Gene[10][4] = rand() % 5;

    //tewelveth gene
    Gene[11][0] = 1;
    Gene[11][1] = 9;
    Gene[11][2] = 0;
    Gene[11][3] = 0;
    Gene[11][4] = rand() % 5;

    //thirteenth gene
    Gene[12][0] = 0;
    Gene[12][1] = 9;
    Gene[12][2] = 9;
    Gene[12][3] = 0;
    Gene[12][4] = rand() % 5;

    //fourteenth gene
    Gene[13][0] = 9;
    Gene[13][1] = 9;
    Gene[13][2] = 1;
    Gene[13][3] = 0;
    Gene[13][4] = rand() % 5;

    //fifteenth gene
    Gene[14][0] = 1;
    Gene[14][1] = 9;
    Gene[14][2] = 9;
    Gene[14][3] = 0;
    Gene[14][4] = rand() % 5;

    //sixteenth gene
    Gene[15][0] = 9;
    Gene[15][1] = 9;
    Gene[15][2] = 9;
    Gene[15][3] = 1;
    Gene[15][4] = rand() % 5;
}


void allRobot::plot_graph(allRobot obj[])
{
    int i;
    int width_l= 30;	/* Width of the screen */
    int height_c= totalGeneration; /* Height of the screen */
    double x_pos, y_pos; /* x value and y value on our graph */



    printf ("\n");

    /* Now loop round for all our possible y positions */
    for (i= height_c-1; i >= 0; i--)
    {
        x_pos= (double)i/(double)height_c; /* Calculate our x posn */
        y_pos= obj[i].robotAvgFitness/1000;
        plot_point(y_pos, width_l, i);
    }

    /* Last print the "x-axis" of our graph. This is the average turn for each generation  */
    for (i= 0; i < width_l-1; i++)
    {
        if(i<10)
        {
            printf ("0");
        }
        printf ("%d ",i);
    }
    cout<<endl;
}

/* Plot the point at "y_pos" */
void allRobot::plot_point (double y_pos, int screen_width, int yAxis)
{
    int i;
    int y_int;   /* The y_position as an integer position on the screen */
    if(yAxis<10)
    {
        printf ("0");
    }
    printf ("%d",yAxis);  /* Print the "y-axis"*/
    y_int= (int) (y_pos * 1000);

    /* If we cannot print this point then just return */
    if (y_int <= 0 || y_int >= screen_width -1)
    {
        printf ("\n");
        return;
    }

    /* Print a * in the correct place */
    printf ("  ");
    for (i= 1; i < y_int; i++)
    {
        printf ("   ");
    }
    printf ("*\n");

}
