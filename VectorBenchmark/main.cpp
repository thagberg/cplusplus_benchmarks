#include <iostream>
#include <vector>
#include <sys/time.h>

using namespace std;

const int NUM_CREATE = 1000000;

class TestObject
{
public:
    TestObject(int x, int y);
    //TestObject(const TestObject &obj);
private:
    int mX;
    int mY;
};

TestObject::TestObject(int x, int y)
{
    mX = x;
    mY = y;
}

//TestObject::TestObject(const TestObject &obj)
//{
//    mX = obj.mX;
//    mY = obj.mY;
//}

int main() {
    cout << "Comparing vector::push_back and vector::emplace_back performance" << std::endl << std::endl;

    timeval startTime;
    timeval endTime;
    int seconds;
    int uSeconds;
    vector<TestObject> pushVector;
    vector<TestObject> emplaceVector;
    vector<TestObject> weirdEmplaceVector;
    vector<TestObject> reservedPush;
    vector<TestObject> reservedEmplace;
    vector<pair<int, int>> pairPush;
    vector<pair<int, int>> pairEmplace;
    vector<pair<int, int>> reservedPairPush;
    vector<pair<int, int>> reservedPairEmplace;

    // get prepared
    reservedPush.reserve(NUM_CREATE);
    reservedEmplace.reserve(NUM_CREATE);
    reservedPairPush.reserve(NUM_CREATE);
    reservedPairEmplace.reserve(NUM_CREATE);


    cout << "Creating " << NUM_CREATE << " objects" << endl;

    /* Vectors without reserved size */
    cout << "\n\nNon-reserved Vectors:" << std::endl;

    // do regular push
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        pushVector.push_back(TestObject(1, 2));
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tPush:\n\t\t" << seconds << " : " << uSeconds << std::endl;

    // do regular emplace
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        emplaceVector.emplace_back(1, 2);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tEmplace:\n\t\t" << seconds << " : " << uSeconds << std::endl;

    // do weird emplace
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        weirdEmplaceVector.emplace_back(TestObject(1, 2));
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tWeird:\n\t\t" << seconds << " : " << uSeconds << std::endl;

    /* Reserved Vectors */
    cout << "\n\nReserved Vectors:" << std::endl;

    // do regular push
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        reservedPush.push_back(TestObject(1, 2));
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tPush:\n\t\t" << seconds << " : " << uSeconds << std::endl;

    // do regular emplace
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        reservedEmplace.emplace_back(1, 2);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tEmplace:\n\t\t" << seconds << " : " << uSeconds << std::endl;

    /* Pairs */
    cout << "\n\nCreating " << NUM_CREATE << " pairs" << endl;
    /* Non-reserved */
    cout << "\n\nNon-reserved Vectors" << endl;

    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        pairPush.push_back(make_pair(1, 2));
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tPush:\n\t\t" << seconds << " : " << uSeconds << std::endl;

    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        pairEmplace.emplace_back(1, 2);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tEmplace:\n\t\t" << seconds << " : " << uSeconds << std::endl;

    /* Reserved */
    cout << "\n\nReserved Vectors" << endl;

    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        reservedPairPush.push_back(make_pair(1, 2));
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tPush:\n\t\t" << seconds << " : " << uSeconds << std::endl;

    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        reservedPairEmplace.emplace_back(1, 2);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tEmplace:\n\t\t" << seconds << " : " << uSeconds << std::endl;

    return 0;
}