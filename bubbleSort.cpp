#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <chrono>
#include <cstdint>
#include <cstring>

using namespace std;
typedef double* DblPtr;

void generateInputFile(const char* filename, size_t size);
DblPtr fillArray(ifstream&, size_t & size);
void bubbleSort(double sortArr[], int size);
void InsertionSort(double arr[], int numbersSize);

int main(int argc, const char* argv[]) {
  int userInput;
  cout << "Type how much data you want to sort: ";
  cin >> userInput;
    generateInputFile("input.txt", userInput);

    if (argc != 2) {
        cout << "Invalid number of command line arguments. Usage:" << endl;
        cout << "Argument 1: input_filename" << endl;
        return -1;
    }

    ifstream inputFile;

    inputFile.open(argv[1]);

    if (inputFile.is_open() == false) {
        cout << "Unable to open input file \"" << argv[1] << '"' << endl;
        return -2;
    }

    time_t startTime, endTime;
    double seconds;
    size_t arrSize;
    DblPtr arr = fillArray(inputFile, arrSize);
    DblPtr copy = new double[arrSize];

    for (size_t size = 1000; size <= arrSize; size *= 10) {

        cout << "---------------------------------------------" << endl << endl;
        cout << "Array size: " << size << endl << endl;

        memcpy(copy, arr, size * sizeof(double));
        time(&startTime);
        cout << "bubbleSort Start Time: " << startTime << " seconds since Jan 1, 1970" << endl;
        bubbleSort(copy, (int)size);
        time(&endTime);
        cout << "bubbleSort End Time: " << endTime << " seconds since Jan 1, 1970" << endl;
        seconds = difftime(endTime, startTime);
        cout << seconds << " seconds elapsed." << endl << endl;

    }

    delete[] copy;
    copy = nullptr;
    delete[] arr;
    arr = nullptr;

    return 0;
}

void generateInputFile(const char* filename, size_t size){
    ofstream outputFile(filename);

    outputFile << size << endl;

    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(0.0, 100.0);

    outputFile << setprecision(10);
    for (size_t i = 0; i < size; i++) {
        outputFile << distribution(generator) << endl;
    }

}

DblPtr fillArray(ifstream& fin,  size_t& size) {
    fin >> size;
    DblPtr arr = new double[size];
    for (size_t i = 0; i < size; ++i) {
        fin >> arr[i];
    }
    return arr;
}

void bubbleSort(double sortArr[], int size) {
    while (size-- > 1){
        double temp = 0.0;
        for (int j = 0; j < size; ++j) {
            if (sortArr[j] > sortArr[j + 1]) {
                temp = sortArr[j + 1];
                sortArr[j + 1] = sortArr[j];
                sortArr[j] = temp;
            }
        }
    }
}


/**
Compile: g++ bubbleSort.cpp -o bubbleSort
Run: ./bubbleSort input.txt
**/
