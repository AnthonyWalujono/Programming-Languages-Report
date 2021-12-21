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
void InsertionSort(double arr[], int numbersSize);
int Partition(double arr[], int lowIndex, int highIndex);
void Quicksort(double arr[], int lowIndex, int highIndex);

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
        cout << "Quicksort Start Time: " << startTime << " seconds since Jan 1, 1970" << endl;
        Quicksort(copy, 0, (int)size - 1);
        time(&endTime);
        cout << "Quicksort End Time: " << endTime << " seconds since Jan 1, 1970" << endl;
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


int Partition(double arr[], int lowIndex, int highIndex) {
    // Pick middle element as pivot
    int midpoint = lowIndex + (highIndex - lowIndex) / 2;
    double pivot = arr[midpoint];
    double temp = 0;
    bool done = false;
    while (!done) {
        // Increment lowIndex while numbers[lowIndex] < pivot
        while (arr[lowIndex] < pivot) {
            lowIndex += 1;
        }

        // Decrement highIndex while pivot < numbers[highIndex]
        while (pivot < arr[highIndex]) {
            highIndex -= 1;
        }

        // If zero or one elements remain, then all numbers are
        // partitioned. Return highIndex.
        if (lowIndex >= highIndex) {
            done = true;
        }
        else {
            // Swap numbers[lowIndex] and numbers[highIndex]
            temp = arr[lowIndex];
            arr[lowIndex] = arr[highIndex];
            arr[highIndex] = temp;

            // Update lowIndex and highIndex
            lowIndex += 1;
            highIndex -= 1;
        }
    }

    return highIndex;
}

void Quicksort(double arr[], int lowIndex, int highIndex) {
    // Base case: If the partition size is 1 or zero
    // elements, then the partition is already sorted
    if (lowIndex >= highIndex) {
        return;
    }

    // Partition the data within the array. Value lowEndIndex
    // returned from partitioning is the index of the low
    // partition's last element.
    int lowEndIndex = Partition(arr, lowIndex, highIndex);

    // Recursively sort low partition (lowIndex to lowEndIndex)
    // and high partition (lowEndIndex + 1 to highIndex)
    Quicksort(arr, lowIndex, lowEndIndex);
    Quicksort(arr, lowEndIndex + 1, highIndex);
}

/**
Compile: g++ quicksort.cpp -o quicksort
Run: ./quicksort input.txt
**/
