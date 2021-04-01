#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum 
{
    immune,
    susceptible,
    infectious
} nodeType;

#define patientZero 1001 // Where the infection starts!
#define networkOmega 100000 // The number of systems in the network
#define scanRate 3  // The number of scans an infected computer can do
#define simulationN 3 // The number of simulations we want to run
#define simulationTime 3333  // How many times the simulation might run to infect all nodes

/**
 * This will default all of the computers in the network to the predefined states
 * 
 * @param nodeType[] NodeStatus array of the current network status
 */
void build_network(nodeType NodeStatus[]);

/**
 * Depending on if the type of scan, random or local,
 * infect computers until the network is fully infected.
 *
 * @param int n - simulation run count
 * @param int type - 1 for random scan, 2 for local scan
 * @return int - time taken to fully infect the network
 */
int run_scan(int n, int type);

/**
 * Checks the number of infections found against what is expected in the simulation
 * 
 * @param int infectedComputers - current count of infected computers.
 * @return 1 if the network is full, otherwise 0.
 */
int network_is_fully_infected(int infectedComputers);

/**
 * Runs a random scan to find a computer in the network to infect
 *
 * @param nodeType[] NodeeStatus - array of the current network
 * @param int attackerIp - the IP address of the computer initiating the attack.
 * @param int nextIpLocation - index to place a newly infected computer in the infectdList
 * @param int[] InfectedList - container to whole the IP addresses of the infected computers.
 * @return int - number of newly infected computers
 */
int random_scan(nodeType NodeStatus[], int attackerIp, int nextIpLocation, int infectedList[]);

/**
 * Runs a random scan to find a computer in the network to infect
 *
 * @param nodeType[] NodeeStatus - array of the current network
 * @param int attackerIp - the IP address of the computer initiating the attack.
 * @param int nextIpLocation - index to place a newly infected computer in the infectdList
 * @param int[] InfectedList - container to whole the IP addresses of the infected computers.
 * @return int - number of newly infected computers
 */
int local_scan(nodeType NodeStatus[], int atttackerIp, int nextIpLocation, int infectedList[]);

/**
 * Gets a random IP address between 1 and networkOmega.
 *
 * @return int - the random IP address to try and infect.
 */
int get_random_ip();

/**
 * This is just a utility fuction to display the current infections in the network

 * @param nodeType[] NodeeStatus - array of the current network
 */
void display_infections(nodeType NodeStatus[]);

/**
 * Get a probablity value between 1 and 10.
 * 
 * @return double value between 1 and 10 to use for probabliity purposes.
 */
double rand01();

/**
 * This saves a tab delimneted file of time \t infection count:
 *
 * 1    1
 * 2    1
 * 3    2
 *
 * @param int n - the current simulation count
 * @param int type - the type of simulation ran
 * @param int[][simulationTime] lt - vector of results
 * @param int t - the total time it took to complete the current simulation.
 */
void save_file(int n, int type, int lt[][simulationTime], int t);

// Create an array of the node types so you can model the network.
nodeType NodeStatus[networkOmega + 1];
//nodeType PriorNodeStatus[networkOmega + 1];

int lt[simulationN][simulationTime];

int main(void)
{
    int t; 
    // Make sure the IPs are randomized each time.
    time_t t_time;
    srand((unsigned) time(&t_time));

    // Build the network
    build_network(NodeStatus);

    for(int n = 0; n<simulationN; n++)
    {        
        // Run run random-scan
        t = run_scan(n, 1);
        build_network(NodeStatus);
        save_file(n, 1, lt, t);     

        // Run local-preferecne
        t = run_scan(n, 2);
        build_network(NodeStatus);
        save_file(n, 2, lt, t);     

    }

    return 0;
}

int run_scan(int n, int type)
{
     // The number of infected computers.
    int infectedComputers = 1;
    int infectedList[1000];
    for(int i=0;i<1000;i++) infectedList[i] = 0;
    infectedList[0] = patientZero;
    int t = 1;

    // While there are still susceptible computers in the network, try to infect more.
    while(!network_is_fully_infected(infectedComputers))
    {
        // For each infected node, preform a random scan
        for(int i=0; i<infectedComputers; i++)
        {
            int newInfections = 0;

            // Attemp to infect new computrs
            if(type == 1)
                newInfections = random_scan(NodeStatus, infectedList[i], i+1, infectedList);
            else if(type == 2){
                
                // Get the p and if it's 1 or 2
                if(rand01() <= 2)
                {
                    newInfections = random_scan(NodeStatus, infectedList[i], i+1, infectedList);
                }
                else
                {
                    newInfections = local_scan(NodeStatus, infectedList[i], i+1, infectedList);
                }
            }
                

            // Add to the count of the current infections
            infectedComputers += newInfections;            
        }

        //printf("T is %d\n", t);
        lt[n][t] = infectedComputers;
        t++;
    }

    return t;
}

double rand01()
{
    return rand()%10 + 1;
}

// Build a network  of 100,000 network nodes with IP addresses from 1 - 100,000
void build_network(nodeType NodeStatus[])
{
    for(int i = 1; i<=networkOmega; i++)
    {
        NodeStatus[i] = immune;
    }

    for(int j = 0; j<=99; j++)
    {
        for(int i = 0; i<=10; i++)
        {
            // Don't touch teh 1000, 2000, etc
            if((i+j*1000)%1000 != 0)
            {
                NodeStatus[i+j*1000] = susceptible;
                //printf("IP: %d is %d\n", i+j*1000, NodeStatus[i]);
            }            
        }
    }

    // Iniitalie the pateient 0
    NodeStatus[patientZero] = infectious;
}

int local_scan(nodeType NodeStatus[], int attackerIp, int nextIpLocation, int infectedList[])
{
    // TODO:  Refactor local_scan and random_scan into same codebase and just toggle the random ip functionality.
    int newInfections = 0;
    int lower = attackerIp - 10;
    int upper = attackerIp + 10;
    int next = nextIpLocation;

    for(int i=0; i<scanRate; i++){

        // Get a random IP in the network to sca
       int ip = (rand() % (upper - lower + 1)) + lower;

       // If it is susceiptble, then mark it as infected
       if(NodeStatus[ip] == susceptible)
       {
           NodeStatus[ip] = infectious;
           infectedList[next] = ip;
           newInfections++;
           next++;
       }
    }

    return newInfections;
}

int random_scan(nodeType NodeStatus[], int attackerIp, int nextIpLocation, int infectedList[])
{
    // TODO:  Refactor local_scan and random_scan into same codebase and just toggle the random ip functionality.
    int newInfections = 0;
    int next = nextIpLocation;

    for(int i=0; i<scanRate; i++){

        // Get a random IP in the network to sca
       int ip = get_random_ip();

       // If it is susceiptble, then mark it as infected
       if(NodeStatus[ip] == susceptible)
       {
           NodeStatus[ip] = infectious;
           infectedList[next] = ip;
           newInfections++;
           next++;
       }
    }

    return newInfections;
}

int get_random_ip()
{
    return rand()%networkOmega + 1;
}

int network_is_fully_infected(int infectedComputers)
{
    return infectedComputers == 1000;
    //return 0;
}

void display_infections(nodeType NodeStatus[])
{
    for(int i = 1; i<=networkOmega; i++)
    {
        if(NodeStatus[i] == infectious)
        {
            printf("Infected: %d\n", i);
        } 

    }
}

void save_file(int n, int type, int lt[][simulationTime], int t)
{
    FILE *fp;
    char filename[100];
    snprintf(filename, sizeof(filename), "./files/data-%d-%d.txt", type, n);
    fp = fopen(filename, "wt" );
    for(int i=1; i<t; i++){
        fprintf(fp, "%d\t%d\n", i, lt[n][i]);
    }
    
    fclose(fp);
   
    printf("T: %d\n", t);
}