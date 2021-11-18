#include <stack>

class CQueue {
    std::stack<int> tail;
    std::stack<int> head;
public:
    CQueue() {
        while (!tail.empty()) tail.pop();
        while (!head.empty()) head.pop();
    }

    void appendTail(int value) {
        tail.push(value);
    }

    int deleteHead() {
        if( head.empty() ){
            while (!tail.empty())
            {
                head.push(tail.top());
                tail.pop();
            }
        }
        if( head.empty() )return -1;
        else {
            int res = head.top();
            head.pop();
            return res;
        }
    }
};


