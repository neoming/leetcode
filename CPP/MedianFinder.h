#include <queue>

using namespace std;

class MedianFinder {
    priority_queue<int,vector<int>,less<int>> maxHeap;
    priority_queue<int,vector<int>,greater<int>> minHeap;
public:
    /** initialize your data structure here. */
    MedianFinder() {
    }

    void addNum(int num) {
        if(maxHeap.size() == minHeap.size()){
            minHeap.push(num);
            int top = minHeap.top();
            minHeap.pop();
            maxHeap.push(top);
        }else{
            maxHeap.push(num);
            int top = maxHeap.top();
            maxHeap.pop();
            minHeap.push(top);
        }
    }

    double findMedian() {
        if(maxHeap.size() == minHeap.size()){
            return (maxHeap.top()+minHeap.top())*1.0/2;
        }else{
            return maxHeap.top()*1.0;
        }
    }
};