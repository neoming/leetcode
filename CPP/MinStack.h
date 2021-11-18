#include <stack>

class MinStack {
    std::stack<int> minStack;
    std::stack<int> dataStack;
public:
    /** initialize your data structure here. */
    MinStack() {
        while (!minStack.empty()) minStack.pop();
        while (!dataStack.empty()) dataStack.pop();
    }

    void push(int x) {
        if(minStack.empty() || minStack.top() > x){
            minStack.push(x);
        }else{
            minStack.push(minStack.top());
        }
        dataStack.push(x);
    }

    void pop() {
        minStack.pop();
        dataStack.pop();
    }

    int top() {
        return  dataStack.top();
    }

    int min() {
        return minStack.top();
    }
};