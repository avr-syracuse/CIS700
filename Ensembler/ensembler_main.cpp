#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>

struct element {
    float classificationValue;
    float voteWeight;
};

bool elementVoteWeight = false;
std::vector<std::ifstream*> inputVector;

void vote() {

    // Create output file stream
    std::ofstream outputStream("ensambleOutput.csv");
    outputStream << "index, class, voteweight" << std::endl;


    uint8_t fileCount = inputVector.size();


    // Assume all files are the same length... good enough for now
    uint32_t rowIndex = 0;
    while(!inputVector[0]->eof()) {

        // list of votes
        std::map<int32_t, float> votes;
        std::map<int32_t, float>::iterator voteIterator;

        for (int index = 0; index < fileCount; index++) {
            std::string line;
            getline(*inputVector[index], line);

            // ignore the header
            if (rowIndex != 0 && line.length() >= 1) {

                // Read in information from csv file
                // CSV file format must be: classification, weight, <other stuff>
                std::string strLabel;
                std::stringstream ssline(line);
                getline(ssline, strLabel, ','); // first value label;
                int32_t classLable = std::stoi(strLabel);

                std::string strVoteWeight;
                float voteWeight = 1.0 / (float) fileCount; // average;
                getline(ssline, strVoteWeight, ','); // second value vote weight
                if (elementVoteWeight) {
                    voteWeight = std::stof(strVoteWeight);
                }

                // Add info to vote map
                voteIterator = votes.find(classLable);
                if (voteIterator == votes.end()) {    // New class!
                    std::cout << "new vote" << classLable << std::endl;
                    votes[classLable] = voteWeight;
                } else {    // existing class
                    votes[classLable] += voteWeight;
                }

            }
        }



        // Write as vote results
        // Find label with highest vote count
        if (rowIndex != 0 && votes.size() > 0) {
            uint32_t maxLabel;
            float maxVoteWeight = 0.0;
            for (auto vote : votes) {
                if (maxVoteWeight < vote.second) {
                    maxLabel = vote.first;
                    maxVoteWeight = vote.second;
                }
            }

            outputStream << rowIndex << ", " << maxLabel << ", " << maxVoteWeight
                         << std::endl;
        }

        rowIndex++;

    }

}


int main(int argc, char* argv[]) {

    if(argc <= 1) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }


    for(int index = 1; index < argc; index++){
        std::string argument(argv[index]);

        // Increment the index to get the argument's parameter value
        if(argc > index + 1) {
            index++;
        } else{
            std::cerr << "Argument value not provided for "
                      << argument << std::endl;
            return 1;
        }

        if(argument.compare("-i") == 0) {

            std::ifstream* ifs = new std::ifstream();
            ifs->open(argv[index]);

            if(!ifs->is_open()) {
                std::cerr << "Failed to open file: " << argv[index] << std::endl;
                return 1;
            }

            std::cout << "Inserting Path: " << argv[index] << std::endl;

            inputVector.push_back(ifs);
        } else if(argument.compare("-w") == 0) {
            std::cout << "Element Vote Weight ON" << std::endl;
            elementVoteWeight = true;
        }
    }

    // check if we have input files
    if(inputVector.size() <= 1) {
        std::cerr << "Need multiple files for ensembeling" << std::endl;
        return 1;
    }



    vote();


    return 0;
}