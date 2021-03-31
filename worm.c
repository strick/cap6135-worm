#include <stdio.h>

#define patientZero 1001 // Where the infection starts!
#define networkOmega 100000 // The number of systems in the network
#define scanRate 3  // The number of scans an infected computer can do
#define simulationN 3 // The number of simulations we want to run
#define simulationTime 3000  // How many times the simulation might run to infect all nodes

enum nodeType
{
    immune,
    susceptible,
    infectious
};

// Create an array of the node types so you can model the network.
enum nodeType NodeStatus[networkOmega + 1];
enum nodeType PriorNodeStatus[networkOmega + 1];

int lt[simulationN][simulationTime];

int main(void)
{
    // The number of infected computers.
    int infectedComputers = 1;

    // While there are still susceptible computers in the network, try to infect more.
    while(!network_is_fully_infected())
    {

    }

    return 0;
}

// Build a network  of 100,000 network nodes with IP addresses from 1 - 100,000
void build_network()
{

}

// Initialize the network node types
void initialize_network()
{
    return;
}


void scan_network()
{

}

void infect_computer()
{

}

bool network_is_fully_infected()
{
    return false;
}
