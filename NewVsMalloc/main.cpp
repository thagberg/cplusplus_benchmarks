#include <iostream>
#include <sys/time.h>
#include <vector>

using namespace std;

const int NUMBER_OBJECTS = 500000;

class Test {
public:
    Test(int x, int y);
    int mX;
    int mY;
};

Test::Test(int x, int y) {
    mX = x;
    mY = y;
}

int main() {
    timeval startTime;
    timeval endTime;
    int seconds;
    int uSeconds;

    Test* newTests[NUMBER_OBJECTS];
    Test* mallocTests[NUMBER_OBJECTS];
    Test* sequentialMallocTests;
//    vector<Test*> newVector;
//    vector<Test*> mallocVector;
//
//    newVector.reserve(NUMBER_OBJECTS);
//    mallocVector.reserve(NUMBER_OBJECTS);

    cout << "New/Delete vs Malloc/Free Benchmark" << endl << endl;


    cout << "New Tests" << endl;
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUMBER_OBJECTS; i++) {
        Test * newTest = new Test(i, i+1);
        newTests[i] = newTest;
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec -  startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tNew: " << seconds << " - " << uSeconds << endl;

    cout << "\nDelete Tests" << endl;
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUMBER_OBJECTS; i++) {
        delete newTests[i];
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec -  startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tDelete: " << seconds << " - " << uSeconds << endl;


    cout << "\nRandom Malloc Tests" << endl;
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUMBER_OBJECTS; i++) {
        Test * mallocTest = (Test *) malloc(sizeof(Test));
        mallocTests[i] = mallocTest;
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec -  startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tRandom Malloc: " << seconds << " - " << uSeconds << endl;

    cout << "\nRandom Free Tests" << endl;
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUMBER_OBJECTS; i++) {
        free(mallocTests[i]);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec -  startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tRandom Free: " << seconds << " - " << uSeconds << endl;

    cout << "\nSequential Malloc Tests" << endl;
    gettimeofday(&startTime, NULL);
    sequentialMallocTests = (Test * ) malloc(sizeof(Test) * NUMBER_OBJECTS);
    for (int i = 0 ; i < NUMBER_OBJECTS; i++) {
        //Test * newTest = new(sequentialMallocTests + i) Test(i, i+1);
        Test newTest = (Test) sequentialMallocTests[i];
        newTest.mX = i;
        newTest.mY = i+1;
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec -  startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tSequential Malloc: " << seconds << " - " << uSeconds << endl;

    cout << "\nSequential Free Tests" << endl;
    gettimeofday(&startTime, NULL);
    free(sequentialMallocTests);
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec -  startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tSequential Free: " << seconds << " - " << uSeconds << endl;


    return 0;
}