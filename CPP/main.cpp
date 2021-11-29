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

void testFindNumberIn2DArray(){
    std::cout<<"test Find Number In 2D Array"<<std::endl;
    Solution s = Solution();
    std::vector<int> row0{1,4,7,11,15};
    std::vector<int> row1{2,   5,  8, 12, 19};
    std::vector<int> row2{3,   6,  9, 16, 22};
    std::vector<int> row3{10, 13, 14, 17, 24};
    std::vector<int> row4{18, 21, 23, 26, 30};
    std::vector<std::vector<int>> data;
    data.push_back(row0);
    data.push_back(row1);
    data.push_back(row2);
    data.push_back(row3);
    data.push_back(row4);
    std::cout<<s.findNumberIn2DArray(data,20)<<std::endl;
}

void testMinArray() {
    std::cout<<"test Min Array"<<std::endl;
    Solution s = Solution();
//    std::vector<int> ans{3,4,5,1,2};
    std::vector<int> ans{2,2,2,0,1};
    std::cout<<s.minArray(ans)<<std::endl;
}

void testFirstUniqChar() {
    std::cout<<"test FirstUniqChar"<<std::endl;
    Solution s = Solution();
    std::string src = "abaccdeff";
    std::cout<<s.firstUniqChar(src)<<std::endl;
}

void testReverseWords() {
    std::cout<<"test ReverseWords"<<std::endl;
    Solution s = Solution();
    std::string src = "the sky is blue";
    std::cout<<s.reverseWords(src)<<std::endl;
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
    testFindNumberIn2DArray();
    testMinArray();
    testFirstUniqChar();
    testReverseWords();
    return 0;
}