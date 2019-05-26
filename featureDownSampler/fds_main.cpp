#include <iostream>
#include <string>
#include <fstream>



void printHelp() {
    std::cout << std::endl
        << "Feature Down Sampler" << std::endl
        << "Splits large csv file into 2 smaller files with equal weights of target class" << std::endl
        << "  -r          Random number generator seed [Optional]" << std::endl
        << "  -p          Split Percentage as whole number 7% = 7" << std::endl
        << "  -i          Input file path" << std::endl
        << "  -o          Output path" << std::endl
        << std::endl;
}


int main(int argc, char* argv[]) {

    // Collect & Parse Argument
    if(argc < 1) {
        std::cerr << "ERROR: arguments needed" << std::endl;
        printHelp();
        return 1;
    }


    std::string inputFilePath = "";
    std::string outputPath = "";
    uint32_t divisionLine = 0;
    uint32_t splitPercentage = 0;

    for(int argIndex = 1; argIndex < argc; argIndex++) {
        // Get argument as C++ string
        std::string argument(argv[argIndex]);

        // Increment the index to get the argument's parameter value
        if(argc > argIndex + 1) {
            argIndex++;
        } else{
            std::cerr << "Argument value not provided for "
                      << argument << std::endl;
            return 1;
        }

        std::cout << " : " << argument << " = " << argv[argIndex] << std::endl;

        if(argument.compare("-i") == 0){
            inputFilePath = std::string(argv[argIndex]);
        } else if(argument.compare("-d") == 0){
            int seed = std::stoi(argv[argIndex]);
            srand(seed);
        } else if(argument.compare("-p") == 0){
            splitPercentage = std::stoi(argv[argIndex]);
        } else if(argument.compare("-o") == 0){
            outputPath = std::string(argv[argIndex]);
        } else {
            std::cerr << "unkown argument " << argument
                      << ", going to ignore it" << std::endl;
        }
    }


    // Gonna assume all the args have been entered to save time for now
    // Also gonna just drop all the code here, because time savings

    std::ifstream inputFileStream(inputFilePath);
    if(inputFileStream.is_open()){

        std::ofstream outputStream1(outputPath + "/file1.csv");
        std::ofstream outputStream2(outputPath + "/file2.csv");

        // get csv file header
        std::string line;
        std::getline(inputFileStream, line);

        outputStream1 << line;
        outputStream2 << line;


        // reduce body rows/elements
        uint32_t lineCount = 1; // lets assume value provided is counting header
        while(std::getline(inputFileStream, line)) {
            lineCount++;

            int randomNumber = rand() % 100 + 1; // random # from 1 to 100

            if(randomNumber > splitPercentage) {
                outputStream1 << line;
            } else {
                outputStream2 << line;
            }

        }

        outputStream1.close();
        outputStream2.close();
        inputFileStream.close();

    } else {
        std::cerr << "File " << inputFilePath << " could not be open"
                  << std::endl;
        return 1;
    }

    std::cout << "Done!" << std::endl;
    return 0;
}