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

void testFindRepeatNumber(){
    std::cout<<"test FindRepeatNumber"<<std::endl;
    Solution s = Solution();
    std::vector<int> ans{2,3,1,0,2,5,3};
    std::cout<<s.findRepeatNumber(ans)<<std::endl;
}

void testSearch(){
    std::cout<<"test Search"<<std::endl;
    Solution s = Solution();
    std::vector<int> ans{5,7,7,8,8,10};
    std::cout<<s.search(ans,4)<<std::endl;
}

void testMissingNumber(){
    std::cout<<"test Missing Number"<<std::endl;
    Solution s = Solution();
//    std::vector<int> ans{0,1,2,3,4,5,6,7,9};
    std::vector<int> ans{0,1,3};
    std::cout<<s.missingNumber(ans)<<std::endl;
}

int main() {
    testCQueue();
    testMinStack();
    testReversePrint();
    testReverseListNode();
    testReplaceSpace();
    testReverseLeftWords();
    testFindRepeatNumber();
    testSearch();
    testMissingNumber();
    return 0;
}