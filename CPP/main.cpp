#include <iostream>
#include "CQueue.h"
#include "MinStack.h"
#include "Solution.h"
void testCQueue() {
    std::cout<<"test CQueue"<<std::endl;
    CQueue cQueue = CQueue();
    cQueue.appendTail(3);
    std::cout<<cQueue.deleteHead()<< std::endl;
    std::cout<<cQueue.deleteHead()<< std::endl;
}

void testMinStack() {
    std::cout<<"test MinStack"<<std::endl;
    MinStack minStack = MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    std::cout<<minStack.min()<<std::endl;
    minStack.pop();
    std::cout<<minStack.top()<<std::endl;
    std::cout<<minStack.min()<<std::endl;
}

void testReversePrint(){
    std::cout<<"test reverse print"<<std::endl;
    Solution s = Solution();
    ListNode* a = new ListNode(1);
    ListNode* b = new ListNode(3);
    ListNode* c = new ListNode(2);
    a->next = b;
    b->next = c;
    for (auto& a : s.reversePrint(a)){
        std::cout<<a<<",";
    }
    std::cout<<std::endl;
}

void testReverseListNode(){
    std::cout<<"test reverse ListNode"<<std::endl;
    Solution s = Solution();
    ListNode* a = new ListNode(1);
    ListNode* b = new ListNode(3);
    ListNode* c = new ListNode(2);
    a->next = b;
    b->next = c;
    ListNode* head = a;
    head = s.reverseList(head);
    while(head != nullptr){
        std::cout<<head->val<<",";
        head = head->next;
    }
    std::cout<<std::endl;
    head = c;
    head = s.reverseListRecur(head);
    while(head != nullptr){
        std::cout<<head->val<<",";
        head = head->next;
    }
    std::cout<<std::endl;
}

void testReplaceSpace(){
    std::cout<<"test replace space"<<std::endl;
    Solution s = Solution();
    std::string test = "We are happy.";
    std::cout<< s.replaceSpace(test) << std::endl;
}

void testReverseLeftWords(){
    std::cout<<"test reverse Left Words"<<std::endl;
    Solution s = Solution();
    std::string test = "abcdefg";
    std::cout<< s.reverseLeftWords(test, 2) << std::endl;
}
int main() {
    testCQueue();
    testMinStack();
    testReversePrint();
    testReverseListNode();
    testReplaceSpace();
    testReverseLeftWords();
    return 0;
}