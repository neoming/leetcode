#include <queue>
#include <deque>

class MaxQueue {
    std::queue<int> q;
    std::deque<int> d;
public:
    MaxQueue() {

    }

    int max_value() {
        if(!d.empty())return d.front();
        else return -1;
    }

    void push_back(int value) {
        while (!d.empty() && value > d.back())d.pop_back();
        d.emplace_back(value);
        q.push(value);
    }

    int pop_front() {
        if(q.empty())return -1;
        int ans = q.front();
        if(ans == d.front())d.pop_front();
        q.pop();
        return ans;
    }
};