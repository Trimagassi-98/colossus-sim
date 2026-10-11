#include "network.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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
vector<string> Network::findShortestPath(string source, string destination) {
    unordered_map<string, int> distances;
    unordered_map<string, string> previous;
    unordered_set<string> visited;

    for(auto& [id, node] : nodes){
        distances[id] = INT_MAX;
    }
    distances[source] = 0;

    while(true){
        string current = "";
        int smallest = INT_MAX;

        for(auto& [id, dist] : distances){
            if(visited.count(id) == 0 && dist < smallest){
                smallest = dist;
                current = id;
            }
        }

        if(current == "") break;
        
        if(current == destination) break;

        visited.insert(current);

        for(auto& edge : adjacencyList[current]){
            int newDist = distances[current] + edge.latency;
            if(newDist < distances[edge.destination]){
                distances[edge.destination] = newDist;
                previous[edge.destination] = current;
            }
        }
    }

    vector<string> path;
    string current = destination;

    while(current != source){
        if(previous.count(current) == 0){
            return {};
        }
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(source);

    reverse(path.begin(), path.end());

    return path;
}
void Network::sendPacket(string source, string destination) {
    Packet packet;
    packet.source = source;
    packet.destination = destination;   
    packet.size = rand() % 100 + 1;

    packet.path = findShortestPath(source, destination);
    if(packet.path.empty()){
        cout << "No path found from " << source << " to " << destination << endl;
        return;
    }

    packet.totalLatency = 0;
    for(int i = 0; i < packet.path.size() - 1; i++){
        string current = packet.path[i];
        string to = packet.path[i + 1];

        for(auto& edge : adjacencyList[current]){
            if(edge.destination == to){
                edge.currentTraffic += packet.size;
                packet.totalLatency += edge.latency;
                break;
            }
        }
    }

    cout << "\nPacket sent !" << endl;
    cout << "Size: " << packet.size << " MB" << endl;
    cout << "Route: ";
    for(int i = 0; i < packet.path.size(); i++){
        cout << packet.path[i];
        if(i < packet.path.size() - 1) cout << " → ";
    }
    cout << endl;
    cout << "Total Latency: " << packet.totalLatency << " ms" << endl;
}

bool Network::isEdgeCongested(Edge& edge) {
    int threshold = edge.capacity * 0.8;
    return edge.currentTraffic > threshold;
}

void Network::checkNetworkCongestion(){
    cout << "\n --- Congestion Report ---" << endl;
    bool anyCongestion = false;

    for(auto& [nodeName, edges] : adjacencyList){
        for(auto& edge : edges){
            if(isEdgeCongested(edge)){
                anyCongestion = true;
                cout << "CONGESTION: " << nodeName
                     << " -> " << edge.destination << endl;
                cout << " Traffic: " << edge.currentTraffic
                        << " MB / " << edge.capacity << " MB capacity" << endl;

                nodes[nodeName].isCongested = true;
            }
        }
    }

    if(!anyCongestion){
        cout << "Network clear - no congestion detected." << endl;
    }
}