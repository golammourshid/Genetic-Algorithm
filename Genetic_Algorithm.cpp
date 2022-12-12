// Source File Header
// Genetic_Algorithm.cpp
// Md. Fahim Alam, CISP 400
// 12/13/2022

#include<iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

//This is the main structure class of the Genetic Algorithm.
class Robot
{
public:
    //Declaring the variable for Robot
    //Controlling total number of Robot for each generation and total number of generation
    int totalRobot = 200;
    int totalGeneration = 50;
    int percentageOfMutation = 8;
    int robotWithEnergy;
    int robotWithTurns;
    double robotAvgFitness;
    int Gene[16][5] = {};
    int Grid [12][12] = {};
    int initX, initY, randDir=-1;
    Robot()
    {
        //For preventing repeated sequence of random number
        srand(time(NULL));
    }

    //Function Prototype

    //Program Greeting
    void ProgramGreeting();

    //Can create 16 different gene for each robot
    void geneCreate();

    //Can create a 10x10 grid for each robot
    void gridCreate();

    //Can place each robot randomly
    void placeRobot();

    //Can generate a random direction for any robot
    void robotRandDirection();

    //This is the main function for run the robot in the grid
    void runRobot();

    //Sort all of the robot under with respect to their turns in descending order
    void sortRoboticGene(Robot obj[]);

    //Killing off the lowest 50% Robot. Producing 2 children by combining genes from both parents.
    void Reproduction(Robot obj[]);

    //Mutation for 5% of the children. Just shifting all genes down 1 and the 16th gene moves to the top.
    void Mutation(Robot obj[]);

    //Plotting the graph in the console
    void plot_graph (Robot obj[]);
};


int main ()
{
    //creating Robot type object
    Robot tempRobot;
    Robot robot[tempRobot.totalRobot];
    Robot generationCountRobot[tempRobot.totalGeneration];

    //Greeting of the program
    tempRobot.ProgramGreeting();
    cout<<"Starting Genetic Algorithm Simulation..............."<<endl<<endl;
    int indx, generation;

    //This loop will continue till total generation
    for(generation = 0 ; generation<tempRobot.totalGeneration; generation++)
    {
        //Declaring a variable for count the total turns from all the robot for a specific generation
        int cntTurn = 0;

        //This loop will continue till total robot
        for(indx = 0; indx<tempRobot.totalRobot; indx++)
        {
            //Creating gene for only first generation
            if(generation==0)
            {
                robot[indx].geneCreate();
            }
            //Creating the grid for the robot
            robot[indx].gridCreate();

            //Placing the robot at a random position
            robot[indx].placeRobot();

            //Starting the robot to run
            robot[indx].runRobot();

            //Calculating count turn for the robot
            cntTurn+=robot[indx].robotWithTurns;
        }
        //Sorting robot after all the robots run has ended in a specific generation
        tempRobot.sortRoboticGene(robot);

        //Reproducing robot after all the robots run has ended in a specific generation
        tempRobot.Reproduction(robot);

        //Mutating a specific percentage of robot after all the robots run has ended in a specific generation
        tempRobot.Mutation(robot);

        //Storing the fitness after a generation has ended
        generationCountRobot[generation].robotAvgFitness = (double)cntTurn/(double)tempRobot.totalRobot;
    }

    //Declaring variable for calculating the total average turns for all the generation
    double totalAverageTurns=0.0;
    for(int i=0; i<tempRobot.totalGeneration; i++)
    {
        cout<<"Average fitness of generation "<<i<<": "<<generationCountRobot[i].robotAvgFitness<<endl;

        //Calculating total average turns
        totalAverageTurns+=generationCountRobot[i].robotAvgFitness;
    }
    cout<<"\n\n\nThe fitness graph is given below:\nHere, Generation Number is in X axis and Average Fitness is in Y axis\n"<<endl;

    //Calling the function for plotting the graph
    tempRobot.plot_graph(generationCountRobot);

    cout<<"\nFrom the above fitness graph we see that the robots are getting better and better at navigating the map over time.\n"<<endl;
    cout<<"\n\nTotal average turns over all generation: "<<totalAverageTurns/tempRobot.totalGeneration<<endl<<"That means the average turns for all the single generation is near this average value"<<endl;

    return 0;
}

void  Robot:: ProgramGreeting()
{
    cout<<"********************************************************************************\n                                 ProgramGreetings\n"<<endl;
    cout<<"********************************************************************************"<<endl;
    cout<<"Welcome to our study of Genetic Algorithm. We are going to study the effects of"<<endl;
    cout<<"evolution on a population of robots. The robots will maneuver around a 10 x 10 "<<endl;
    cout<<"grid and collect energy. The robots must collect more energy than they expend to "<<endl;
    cout<<"survive. A battery gives the robot five more power. Moving a square costs 1 power.\nWe placed each robot on a spot on the map randomly. We also gave the space and"<<endl;
    cout<<"battery in the map randomly. Created a population of 200 randomly generated robots\nto start and each robot have 16 genes. Once all the robots in a population have"<<endl;
    cout<<"had a turn, recorded the total energy harvested by the entire generation and breed\nthe robots.Hence here comes the next generation. The robots start with a random"<<endl;
    cout<<"mapping, but over time, the mappings evolve into successful strategies. We also\nsee the plot at the last of the console.\n"<<endl;
    cout<<"Author Name: Md. Fahim Alam"<<endl;
    cout<<"Assignment Due Date: December 13, 2022\n";
    cout<<"********************************************************************************\n                                 ProgramGreetings\n"<<endl;
    cout<<"********************************************************************************"<<endl;
    cout<<""<<endl;
}

//Create random direction of the robot [North, south, east, west]
void Robot::robotRandDirection()
{
    randDir = rand() % 4;
}

//Place each robot randomly
void Robot::placeRobot()
{
    //initial row number
    initX = 1 + rand() % 10;
    //initial column number
    initY = 1 + rand() % 10;
}

//Run the robot in the grid
void Robot::runRobot()
{
    //Giving robot five power as they first emerge on the map.
    robotWithEnergy = 5;

    //The robots start with a random mapping in position (x,y)
    int x=initX, y=initY;
    int turns = 0;

    //Found a battery for the first time when placed the robot
    if(Grid[x][y] == 9)
    {
        //The battery is consuming and set empty in this cell
        Grid[x][y] = 0;

        //Increasing the robots energy
        robotWithEnergy+=5;
    }

    //will continue this loop until the energy of the robot will finish
    while(1)
    {
        //added a flag for detecting the matching gene
        bool flag = false;

        //Setting the randDir value -1 for tracking, whether the random value is used or not
        randDir = -1;

        //Checking the energy of the robot in each iteration
        if(robotWithEnergy<=0)
        {
            //Setting the total turns of the robot
            robotWithTurns = turns;
            return;
        }

        int direction;

        //loop for all 16 genes of a robot
        for(int i=0; i<16; i++)
        {
            //check the match between gene and the grid's north, south, east and west
            if(Gene[i][0] == Grid[x-1][y] && Gene[i][1] == Grid[x+1][y] && Gene[i][2] == Grid[x][y+1] &&  Gene[i][3] == Grid[x][y-1])
            {
                //set true as a match found
                flag = true;

                //taking the direction of this gene
                direction = Gene[i][4];
                break;
            }
        }

        //Check a match found or not
        if(!flag)
        {
            //The robot is executing the last gene as no match found
            direction = Gene[15][4];
        }
        //Check if the direction is random or not
        if(direction == 4)
        {
            //Getting the direction after random move
            robotRandDirection();

            //Keeping the direction
            direction = randDir;
        }
        //Check if the direction is north or not
        if(direction == 0)
        {
            //Moving the robot to North
            x--;
        }
        //Check if the direction is south or not
        else if(direction == 1)
        {
            //Moving the robot to South
            x++;
        }
        //Check if the direction is east or not
        else if(direction == 2)
        {
            //Moving the robot to East
            y++;
        }
        //Check if the direction is west or not
        else if(direction == 3)
        {
            //Moving the robot to West
            y--;
        }

        //Got a battery
        if(Grid[x][y] == 9)
        {
            //Increasing the robots energy
            robotWithEnergy+=5;

            //Increasing the robots turns
            turns++;

            //The battery is consuming and set empty in this cell
            Grid[x][y] = 0;
        }

        //Got a wall
        else if(Grid[x][y] == 1)
        {
            //Got a wall under random direction
            if(randDir != -1)
            {
                //Decreasing the robots energy
                robotWithEnergy--;

                //Increasing the robots turns
                turns++;

                //Restoring previous position if there is a random move and find a wall
                if(direction == 0)
                {
                    x++;
                }
                else if(direction == 1)
                {
                    x--;
                }
                else if(direction == 2)
                {
                    y--;
                }
                else if(direction == 3)
                {
                    y++;
                }
            }

            //Got a wall under a specific direction
            else
            {
                //Increasing the robots turns as found the death knell for that robot
                turns += robotWithEnergy;
                robotWithEnergy = 0;
            }
        }

        //Got a empty space
        else if(Grid[x][y] == 0)
        {
            //Decreasing the robots energy
            robotWithEnergy--;

            //Increasing the robots turns
            turns++;
        }
    }
}

void Robot::sortRoboticGene(Robot obj[])
{
    //Here using the bubble sort algorithm in descending order
    for(int i=0; i<totalRobot-1; i++)
    {
        for(int j=0; j<totalRobot-1-i; j++)
        {
            //Checking the current robot's turn is lower than the next Robot's
            if(obj[j].robotWithTurns < obj[j+1].robotWithTurns)
            {
                //Swapping the gene and turn for these robot
                swap(obj[j].Gene,obj[j+1].Gene);
                swap(obj[j].robotWithTurns,obj[j+1].robotWithTurns);
            }
        }
    }
}

void Robot::Reproduction(Robot obj[])
{
    //Pairing up the top 2 robots and produce 2 children by combining genes from both parents.
    //This loop will continue for the best half of total robots
    //k is the index of child robot and it will replace the first robot of worst half of total robot
    for(int i=0, k = (totalRobot/2); i<(totalRobot/2); i+=2, k+=2)
    {
        //Taking first 8 gene from the parent and replace the gene with the worst half of total robot
        for(int j=0; j<8; j++)
        {
            //Taking the gene code and direction from the parent and generation the new robot.
            //As replacing the worst half of total robot, so here automatically killing the worst half of total robot
            for(int m = 0; m<5; m++)
            {
                //First child taking the gene from first parent
                obj[k].Gene[j][m] = obj[i].Gene[j][m];
                //Second child taking the gene from second parent
                obj[k+1].Gene[j][m] = obj[i+1].Gene[j][m];
            }
        }
        //Taking last 8 gene from the parent and replace the gene with the worst half of total robot
        for(int j=8; j<15; j++)
        {
            //Taking the gene code and direction from the parent and generation the new robot.
            for(int m = 0; m<5; m++)
            {
                //First child taking the gene from second parent
                obj[k].Gene[j][m] = obj[i+1].Gene[j][m];
                //Second child taking the gene from first parent
                obj[k+1].Gene[j][m] = obj[i].Gene[j][m];
            }
        }
    }
}

void Robot::Mutation(Robot obj[])
{
    int numberOfChildren = totalRobot/2;

    //Finding mutation count for all the children
    int mutationCount = (numberOfChildren*percentageOfMutation)/100;
    for(int i=0; i<mutationCount; i++)
    {
        //Finding a random child robot for doing mutation
        int randRobot = numberOfChildren + (rand() % numberOfChildren);

        //Storing first gene for this robot into tmp
        int tmp = obj[randRobot].Gene[0][4];

        //Shifting all genes down 1
        for(int j=0; j<15; j++)
        {
            obj[randRobot].Gene[j][4] = obj[randRobot].Gene[j+1][4];
        }
        //16th gene moves to the top.
        obj[randRobot].Gene[15][4] = tmp;
    }
}


void Robot::gridCreate()
{
    //Giving wall (with value 1) for all side of the 10x10 grid and giving space (with value 0) for all inside squares
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
        //Finding random row and column between (1,10) for setting the battery
        int randomRow = 1 + rand() % 10;
        int randomColumn = 1 + rand() % 10;

        //Setting the cell with battery if there are no battery in this cell
        if(Grid[randomRow][randomColumn] != 9)
        {
            Grid[randomRow][randomColumn] = 9;

            //increasing the battery count +1
            j++;
        }
        //Checking if the battery is populating 40% of the square or not
        if(j>=40)
        {
            break;
        }
    }
}


//Here Gene [][0] = North, Gene [][1] = South, Gene [][2] = East, Gene [][3] = West, Gene [][4] = Direction
//Direction = 0 means north, 1 means south, 2 means east, 3 means west, 4 means random move
//Here the gene codes are fixed for all the robot, but the direction under each gene is randomly generated.
void Robot::geneCreate()
{
    //first gene
    Gene[0][0] = 0;
    Gene[0][1] = 0;
    Gene[0][2] = 0;
    Gene[0][3] = 0;
    Gene[0][4] = rand() % 5;

    //second gene
    Gene[1][0] = 1;
    Gene[1][1] = 0;
    Gene[1][2] = 1;
    Gene[1][3] = 0;
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

    //twelfth gene
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

void Robot::plot_graph(Robot obj[])
{
    int i;
    double mx = -1.0;
    for(i=0; i<totalGeneration; i++)
    {
        if(obj[i].robotAvgFitness>=mx)
        {
            //Storing the max average fitness from all generation
            mx = obj[i].robotAvgFitness;
        }
    }
    //Height of the screen
    int height = mx + 2;

    //Width of the screen
    int width= totalGeneration+5;


    for(i=height; i>=0; i--)
    {
        //printing y axis
        if(i>=100)
        {
            //Giving leading 0 for 1 digit numbers
            if(i<10)
            {
                cout<<"0";
            }
            //Giving leading 0 for 2 digit numbers
            if(i<100)
            {
                cout<<"0";
            }
            cout<<i<<" ";
        }

        //Operate for 2 or 1 digit numbers
        else
        {
            //Giving leading 0 for 1 digit numbers
            if(i<10)
            {
                cout<<"0";
            }
            cout<<i<<" ";
        }

        for(int j=0; j<totalGeneration; j++)
        {
            int fit = obj[j].robotAvgFitness;

            //give a * at position (fit,i) if there is a match
            if(fit == i)
            {
                cout<<"*";
            }

            //give space at position (fit,i) if there are no match
            else
            {
                cout<<" ";
            }
        }
        cout<<endl;
    }
    cout<<"   ";

    //printing X axis with -
    for (i= 0; i < width; i++)
    {
        cout<<"-";
    }
    cout<<endl;
}
