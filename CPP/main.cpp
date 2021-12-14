#include <iostream>
#include "CQueue.h"
#include "MinStack.h"
#include "Solution.h"
#include "Codec.h"
using namespace std;

void testCQueue() {
    cout<<"test CQueue"<<endl;
    CQueue cQueue = CQueue();
    cQueue.appendTail(3);
    cout<<cQueue.deleteHead()<< endl;
    cout<<cQueue.deleteHead()<< endl;
}

void testMinStack() {
    cout<<"test MinStack"<<endl;
    MinStack minStack = MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout<<minStack.min()<<endl;
    minStack.pop();
    cout<<minStack.top()<<endl;
    cout<<minStack.min()<<endl;
}

void testReversePrint(){
    cout<<"test reverse print"<<endl;
    Solution s = Solution();
    ListNode* a = new ListNode(1);
    ListNode* b = new ListNode(3);
    ListNode* c = new ListNode(2);
    a->next = b;
    b->next = c;
    for (auto& a : s.reversePrint(a)){
        cout<<a<<",";
    }
    cout<<endl;
}

void testReverseListNode(){
    cout<<"test reverse ListNode"<<endl;
    Solution s = Solution();
    ListNode* a = new ListNode(1);
    ListNode* b = new ListNode(3);
    ListNode* c = new ListNode(2);
    a->next = b;
    b->next = c;
    ListNode* head = a;
    head = s.reverseList(head);
    while(head != nullptr){
        cout<<head->val<<",";
        head = head->next;
    }
    cout<<endl;
    head = c;
    head = s.reverseListRecur(head);
    while(head != nullptr){
        cout<<head->val<<",";
        head = head->next;
    }
    cout<<endl;
}

void testReplaceSpace(){
    cout<<"test replace space"<<endl;
    Solution s = Solution();
    string test = "We are happy.";
    cout<< s.replaceSpace(test) << endl;
}

void testReverseLeftWords(){
    cout<<"test reverse Left Words"<<endl;
    Solution s = Solution();
    string test = "abcdefg";
    cout<< s.reverseLeftWords(test, 2) << endl;
}

void testFindRepeatNumber(){
    cout<<"test FindRepeatNumber"<<endl;
    Solution s = Solution();
    vector<int> ans{2,3,1,0,2,5,3};
    cout<<s.findRepeatNumber(ans)<<endl;
}

void testSearch(){
    cout<<"test Search"<<endl;
    Solution s = Solution();
    vector<int> ans{5,7,7,8,8,10};
    cout<<s.search(ans,4)<<endl;
}

void testMissingNumber(){
    cout<<"test Missing Number"<<endl;
    Solution s = Solution();
//    vector<int> ans{0,1,2,3,4,5,6,7,9};
    vector<int> ans{0,1,3};
    cout<<s.missingNumber(ans)<<endl;
}

void testFindNumberIn2DArray(){
    cout<<"test Find Number In 2D Array"<<endl;
    Solution s = Solution();
    vector<int> row0{1,4,7,11,15};
    vector<int> row1{2,   5,  8, 12, 19};
    vector<int> row2{3,   6,  9, 16, 22};
    vector<int> row3{10, 13, 14, 17, 24};
    vector<int> row4{18, 21, 23, 26, 30};
    vector<vector<int>> data;
    data.push_back(row0);
    data.push_back(row1);
    data.push_back(row2);
    data.push_back(row3);
    data.push_back(row4);
    cout<<s.findNumberIn2DArray(data,20)<<endl;
}

void testMinArray() {
    cout<<"test Min Array"<<endl;
    Solution s = Solution();
//    vector<int> ans{3,4,5,1,2};
    vector<int> ans{2,2,2,0,1};
    cout<<s.minArray(ans)<<endl;
}

void testFirstUniqChar() {
    cout<<"test FirstUniqChar"<<endl;
    Solution s = Solution();
    string src = "abaccdeff";
    cout<<s.firstUniqChar(src)<<endl;
}

void testReverseWords() {
    cout<<"test ReverseWords"<<endl;
    Solution s = Solution();
    string src = "the sky is blue";
    cout<<s.reverseWords(src)<<endl;
}

void testSpiralOrder() {
    cout<<"test SpiralOrder"<<endl;
    Solution s = Solution();
    vector<vector<int>> matrix;
    matrix.emplace_back(vector<int>{1,2,3});
    matrix.emplace_back(vector<int>{4,5,6});
    matrix.emplace_back(vector<int>{7,8,9});
    s.spiralOrder(matrix);
}

void testIsStraight(){
    cout<<"testIsStraight"<<endl;
    Solution s = Solution();
    vector<int> nums{1,2,3,4,5};
    cout<<s.isStraight(nums)<<endl;
}

void testValidateStackSequences(){
    cout<<"testValidateStackSequences"<<endl;
    Solution s = Solution();
    vector<int> pushed{1,2,3,4,5};
    vector<int> popped{4,5,3,2,1};
    cout<<s.validateStackSequences(pushed,popped)<<endl;
}

void testIsNumber(){
    cout<<"testIsNumber"<<endl;
    Solution s = Solution();
    string str = ".-4";
    cout<<s.isNumber(str)<<endl;
}

void testTreeNodeSerialize(){
    cout<<"testTreeNodeSerialize"<<endl;
    Codec c = Codec();
    auto root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    auto s = c.serialize(root);
    cout<<s<<endl;
    TreeNode* newRoot = c.deserialize(s);
    cout<<c.serialize(newRoot)<<endl;
}

void testPermutation(){
    cout<<"testPermutation"<<endl;
    Solution s = Solution();
    string str = "abc";
    s.permutation(str);
}
int main() {
//    testCQueue();
//    testMinStack();
//    testReversePrint();
//    testReverseListNode();
//    testReplaceSpace();
//    testReverseLeftWords();
//    testFindRepeatNumber();
//    testSearch();
//    testMissingNumber();
//    testFindNumberIn2DArray();
//    testMinArray();
//    testFirstUniqChar();
//    testReverseWords();
//    testIsStraight();
//    testSpiralOrder();
//    testValidateStackSequences();
//    testTreeNodeSerialize();
    testPermutation();
    return 0;
}