# include <iostream>
# include <cstdlib>
# include <chrono>
# include <filesystem>
# include <fstream>
# include <string>
# include <deque>

struct Bulk {
    std::deque<std::string> commands;
    size_t blockSize = 1;
    int packetsToIgnore = 0;
    int packetTimestamp = 0;
    bool hasOpenPacket = false;

    Bulk(int bSize) { blockSize = bSize; }

    void printCurBlockToFile() {
        std::ofstream outputFile;
        std::string path = "../bulk" + std::to_string(packetTimestamp) + ".log";
        outputFile.open(path);
        outputFile << "bulk:";
        for(auto it = commands.begin(); it != commands.end(); ++it) {
            outputFile << " " << *it;
            if (it != commands.end() - 1) {
               outputFile << ",";
            }
        }
        outputFile << std::endl;
        outputFile.close();
    }
    void printCurBlock() {
        if (commands.empty()) { return; }
        if (hasOpenPacket) {
            printCurBlockToFile();
        }
        std::cout << "bulk:";
        for(auto it = commands.begin(); it != commands.end(); ++it) {
            std::cout << " " << *it;
            if (it != commands.end() - 1) {
               std::cout << ",";
            }
        }
        std::cout << std::endl;
        commands.clear();
    }
    void processCommand(std::string command, int timestamp) {
        if (command == "{"){
            if(!hasOpenPacket) {
                printCurBlock();
                packetTimestamp = timestamp;
                hasOpenPacket = true;
            } else {
                packetsToIgnore ++;
            }
            return;
        }
        if (command == "}") {
            if (packetsToIgnore > 0) {
                packetsToIgnore --;
            } else {
                printCurBlock();
                hasOpenPacket = false;
            }
            return;
        }
        if (hasOpenPacket or commands.size() < blockSize) {
            commands.push_back(command);
        }
        if (!hasOpenPacket and commands.size() == blockSize) {
            printCurBlock();
            return;
        }
    }

};

int main(int argc, char* argv[]) {
    int blockSize = argc > 1 ? atoi(argv[1]) : 3;
    Bulk bulk(blockSize);
    std::ifstream commandsFile;
    commandsFile.open("../commands.txt");
    std::string command;
    auto now = std::chrono::system_clock::now();;
    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
    while(getline(commandsFile, command)) {
        bulk.processCommand(command, timestamp);
        timestamp += 1;
    }
    commandsFile.close();

    if (!bulk.hasOpenPacket and !bulk.commands.empty()) {
        bulk.printCurBlock();
    }

    return 0;
}