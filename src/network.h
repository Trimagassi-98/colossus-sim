#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    string id;
    bool isCongested;
};

struct Edge {
    string destination;
    int latency;
    int currentTraffic;
    int capacity;
};

class Network {
public:
    void addNode(string id);
    void addEdge(string from, string to, int latency);
    void printNetwork();

private:
    unordered_map<string, vector<Edge>> adjacencyList;
    unordered_map<string, Node> nodes;
};