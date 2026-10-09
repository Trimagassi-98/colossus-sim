#include "network.h"
#include <iostream>


void Network::addNode(string id) {
    Node node;
    node.id = id;
    node.isCongested = false;
    nodes[id] = node;
}
void Network::addEdge(string from, string to, int latency) {
    Edge edge;
    edge.destination = to;
    edge.latency = latency;
    edge.currentTraffic = 0;
    edge.capacity = 100;
    adjacencyList[from].push_back(edge);
}
void Network::printNetwork() {
    for(auto& pair : adjacencyList){
        string currentNode = pair.first;
        for(auto& edge : pair.second){
            cout << currentNode << " → " 
                 << edge.destination 
                 << " (latency: " << edge.latency << "ms)" 
                 << endl;
        }
    }
}