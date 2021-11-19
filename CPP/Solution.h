#include <vector>
#include <stack>
#include <string>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};
class Solution {
private:
    ListNode* recur(ListNode* cur, ListNode* pre){
        if(cur== nullptr) return pre;
        ListNode* res = recur(cur->next, cur);
        cur->next = pre;
        return res;
    }
public:
    std::vector<int> reversePrint(ListNode* head) {
        std::stack<int> valStack;
        while (head != nullptr){
            valStack.push(head->val);
            head = head->next;
        }
        std::vector<int> ans;
        while (!valStack.empty()) {
            ans.push_back(valStack.top());
            valStack.pop();
        }
        return ans;
    }

    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while (cur != nullptr){
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }

    ListNode* reverseListRecur(ListNode* head) {
        return recur(head, nullptr);
    }

    Node* copyRandomList(Node* head) {

        if (head == nullptr) return nullptr;
        // create the copy of cur node than cur->next = new node
        Node* cur = head;
        while (cur != nullptr){
            Node* newNode = new Node(cur->val);
            newNode->next = cur->next;
            cur->next = newNode;
            cur = newNode->next;
        }

        //update random
        cur = head;
        while (cur != nullptr){
            Node* newNode = cur->next;
            newNode->random = (cur->random != nullptr) ? cur->random->next : nullptr;
            cur = newNode->next;
        }

        //delete connection between cur and newNode
        Node* newNodeHead=head->next;
        cur = head;
        while (cur != nullptr ){
            Node* newNode = cur->next;
            cur->next = newNode->next;
            newNode->next = (newNode->next != nullptr) ? newNode->next->next : nullptr;
            cur = cur->next;
        }

        return newNodeHead;
    }

    std::string replaceSpace(std::string s) {
        std::string res;
        for(char& a : s){
            if( a == ' '){
                res += "%20";
            }else{
                res += a;
            }
        }
        return res;
    }

    std::string reverseLeftWords(std::string s, int n) {
        std::string res;
        for(int i = n; i < s.size(); i++){
            res += s[i];
        }
        for(int i = 0; i < n; i++){
            res += s[i];
        }
        return res;
    }
};