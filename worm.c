#include <stdio.h>

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
#define simulationTime 3000  // How many times the simulation might run to infect all nodes

void build_network(nodeType NodeStatus[]);
int network_is_fully_infected();

// Create an array of the node types so you can model the network.
nodeType NodeStatus[networkOmega + 1];
nodeType PriorNodeStatus[networkOmega + 1];

int lt[simulationN][simulationTime];

int main(void)
{
    // The number of infected computers.
    int infectedComputers = 1;

    // Build the network
    build_network(NodeStatus);

    // While there are still susceptible computers in the network, try to infect more.
    while(!network_is_fully_infected())
    {

    }

    return 0;
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
}

void scan_network()
{

}

void infect_computer()
{

}

int network_is_fully_infected()
{
    return 0;
}
