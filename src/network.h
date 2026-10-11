#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <climits>
#include <unordered_set>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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

struct Packet{
    string source;
    string destination;
    int size;
    vector<string> path;
    int totalLatency;
};

class Network {
public:
    void addNode(string id);
    void addEdge(string from, string to, int latency);
    void printNetwork();
    void reroutePacket(string source, string destination);
    bool isPathCongested(vector<string>& path);
    vector<string> findShortestPath(string source, string destination);
    void sendPacket(string source, string destination);
    bool isEdgeCongested(Edge& edge);
    void checkNetworkCongestion();

private:
    unordered_map<string, vector<Edge>> adjacencyList;
    unordered_map<string, Node> nodes;
};