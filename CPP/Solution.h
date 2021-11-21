#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_map>

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

    int findRepeatNumber(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> count(n);
        for(int data : nums){
            if(count[data]==0){
                count[data]++;
            }else{
                return data;
            }
        }
        return -1;
    }

    int search(std::vector<int>& nums, int target) {
        return std::upper_bound(nums.begin(),nums.end(),target) - std::lower_bound(nums.begin(),nums.end(),target);
    }

    int missingNumber(std::vector<int>& nums){
        int length = nums.size();
        int left = 0;
        int right = length-1;
        int ans = length;
        while (left <= right){
            int mid = (left + right) / 2;
            if(nums[mid] != mid){
                right = mid-1;
                ans = mid;
            } else{
                left = mid + 1;
            }
        }
        return ans;
    }

    bool findNumberIn2DArray(std::vector<std::vector<int>>& matrix, int target) {
        int n = matrix.size();
        if( n == 0) return false;
        int m = matrix[0].size();
        if( m == 0) return false;
        bool res = false;
        int row = n - 1;
        int col = 0;
        while (row >= 0 && col < m) {
            int val = matrix[row][col];
            if(val == target){
                return true;
            }else if(val < target){
                col++;
            }else if(val > target){
                row--;
            }
        }
        return false;
    }

    int minArray(std::vector<int>& numbers){
        int length = numbers.size();
        int left = 0;
        int right = length - 1;
        while (left < right){
            int mid = (right + left) / 2;
            if( numbers[mid] > numbers[right]) {
                left = mid + 1;
            }else if (numbers[mid] == numbers[right]){
                right--;
            }else if (numbers[mid] < numbers[right]){
                right = mid;
            }
        }
        return numbers[left];
    }

    char firstUniqChar(std::string s){
        std::unordered_map<char, int> frequency;
        for(char ch : s){
            ++frequency[ch];
        }
        for(char ch : s){
            if(frequency[ch] == 1)return ch;
        }
        return ' ';
    }
};