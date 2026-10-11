#include <iostream>
#include "network.h"
#include <vector>

int main() {
    srand(time(0));  // seed random once at start
    
    Network net;

    net.addNode("GPU_1");
    net.addNode("GPU_2");
    net.addNode("GPU_3");
    net.addNode("GPU_4");

    net.addEdge("GPU_1", "GPU_2", 3);
    net.addEdge("GPU_1", "GPU_3", 1);
    net.addEdge("GPU_2", "GPU_4", 2);
    net.addEdge("GPU_3", "GPU_4", 4);

    net.printNetwork();

    // send multiple packets
    cout << "\n--- Sending Packets ---" << endl;
    net.sendPacket("GPU_1", "GPU_4");
    net.sendPacket("GPU_1", "GPU_4");
    net.sendPacket("GPU_1", "GPU_4");
    net.sendPacket("GPU_1", "GPU_4");
    net.sendPacket("GPU_1", "GPU_4");

    net.checkNetworkCongestion();

    cout << "\n--- Rerouting Packet ---" << endl;
    net.reroutePacket("GPU_1", "GPU_4");

    return 0;
}