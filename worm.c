//#include <stdio.h>

#define patientZero 1001
#define networkOmega 100000
#define scanRate 3
#define simulationN 3
#define simulationTime 1200
#define t 1

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
