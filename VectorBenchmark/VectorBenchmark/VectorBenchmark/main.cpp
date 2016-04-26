#include <iostream>
#include <vector>
#include <sys/time.h>

using namespace std;

const int NUM_CREATE = 100000;

class TestObject
{
public:
    TestObject();
    TestObject(int x, int y);
    TestObject(const TestObject &obj);
private:
    int mX;
    int mY;
};

TestObject::TestObject(){}

TestObject::TestObject(int x, int y)
{
   // cout << "Creating TestObject" << endl;
    mX = x;
    mY = y;
}

TestObject::TestObject(const TestObject &obj)
{
    //cout << "Copying TestObject" << endl;
    mX = obj.mX;
    mY = obj.mY;
}

class TestComplicated
{
public:
    TestComplicated();
    TestComplicated(vector<int>);
private:
    vector<int> mVec;
};

TestComplicated::TestComplicated(){}

TestComplicated::TestComplicated(vector<int> vec)
{
    mVec = vec;
}

void pushObj(vector<TestObject> &objVec, TestObject &to)
{
    objVec.push_back(to);
}

void emplaceObj(vector<TestObject> &objVec, int i)
{
    objVec.emplace_back(i, i+1);
}

void pushPair(vector<pair<int, int>> &pairVec, int i)
{
    pairVec.push_back(make_pair(i, i+1));
}

void emplacePair(vector<pair<int, int>> &pairVec, int i)
{
    pairVec.emplace_back(i, i+1);
    //pairVec.emplace(pairVec.begin(),1,2);
}

void pushComplicated(vector<TestComplicated> &compVec)
{
    compVec.push_back(TestComplicated(vector<int>()));
}

void emplaceComplicated(vector<TestComplicated> &compVec)
{
    compVec.emplace_back(TestComplicated(vector<int>()));
}

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
    vector<TestComplicated> pushComplicatedVec;
    vector<TestComplicated> emplaceComplicatedVec;
    
    // get prepared
    reservedPush.resize(NUM_CREATE);
    reservedEmplace.resize(NUM_CREATE);
    reservedPairPush.resize(NUM_CREATE);
    reservedPairEmplace.resize(NUM_CREATE);
    pushComplicatedVec.resize(NUM_CREATE);
    emplaceComplicatedVec.resize(NUM_CREATE);
    
    
    cout << "Creating " << NUM_CREATE << " objects" << endl;
    
    /* Vectors without reserved size */
    /*cout << "\n\nNon-reserved Vectors:" << std::endl;
    
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
    cout << "\tWeird:\n\t\t" << seconds << " : " << uSeconds << std::endl;*/
    
    /* Reserved Vectors */
    cout << "\n\nReserved Vectors:" << std::endl;
    
    // do regular push
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        //reservedPush.push_back(TestObject(1, 2));
        TestObject *to = new TestObject(i, i+1);
        pushObj(reservedPush, *to);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tPush:\n\t\t" << seconds << " : " << uSeconds << std::endl;
    
    // do regular emplace
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        //reservedEmplace.emplace_back(1, 2);
        emplaceObj(reservedEmplace, i);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tEmplace:\n\t\t" << seconds << " : " << uSeconds << std::endl;
    
    /* Pairs */
    cout << "\n\nCreating " << NUM_CREATE << " pairs" << endl;
    /* Non-reserved */
    /*cout << "\n\nNon-reserved Vectors" << endl;
    
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
    cout << "\tEmplace:\n\t\t" << seconds << " : " << uSeconds << std::endl;*/
    
    /* Reserved */
    cout << "\n\nReserved Vectors" << endl;
    
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        pushPair(reservedPairPush, i);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tPush:\n\t\t" << seconds << " : " << uSeconds << std::endl;
    
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        emplacePair(reservedPairEmplace, i);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tEmplace:\n\t\t" << seconds << " : " << uSeconds << std::endl;
    
    cout << "\n\nReserved Vectors" << endl;
    
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        pushComplicated(pushComplicatedVec);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tPush:\n\t\t" << seconds << " : " << uSeconds << std::endl;
    
    gettimeofday(&startTime, NULL);
    for (int i = 0; i < NUM_CREATE; i++) {
        emplaceComplicated(emplaceComplicatedVec);
    }
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    uSeconds = endTime.tv_usec - startTime.tv_usec;
    cout << "\tEmplace:\n\t\t" << seconds << " : " << uSeconds << std::endl;
    
    return 0;
}