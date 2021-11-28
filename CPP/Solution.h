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

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:

    int translateNum(int num) {
        auto num_string = std::to_string(num);
        int q = 0;
        int k = 1;
        int v = 0;
        for(int i = 1; i < num_string.size(); i++){
            v += k;
            auto pre = num_string.substr(i-1,2);
            if( pre >= "10" && pre <= "25"){
                v += q;
            }
            q = k;
            k = v;
        }
        return v;
    }

    int lengthOfLongestSubstring(std::string s) {
        std::vector<int> lastPos(256);
        for(int i = 0;i<256;i++)lastPos[i] = -1;
        int left = 0;
        int maxLength = 0;
        for(int i = 0;i<s.size();i++){
            int index = s[i];
            if(lastPos[index] == -1) {
                lastPos[index] = i;
            }else{
                left = std::max(left,lastPos[index] + 1);
                lastPos[index] = i;
            }
            maxLength = std::max(i-left + 1, maxLength);
        }
        return maxLength;
    }

    int maxSubArray(std::vector<int>& nums) {
        int pre = 0;
        int maxRes = INT_MIN;
        for(auto & num : nums){
            pre = std::max(pre + num, num);
            maxRes = std::max(maxRes, pre);
        }
        return maxRes;
    }

    int maxValue(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        if(m == 0)return 0;
        int n = grid[0].size();
        if(n == 0)return 0;
        int dp[m][n];
        dp[0][0] = grid[0][0];
        for(int i = 1;i<m;i++){
            dp[i][0] = grid[i][0] + dp[i-1][0];
        }
        for(int i = 1;i<n;i++){
            dp[0][i] = grid[0][i] + dp[0][i-1];
        }
        for(int i = 1;i<m;i++){
            for (int j = 1; j<n;j++){
                dp[i][j] = grid[i][j] + std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[m-1][n-1];
    }

    int fib(int n) {
        int dp [n+1];
        if(n == 0)return 0;
        if(n == 1)return 1;
        dp[0] = 0;
        dp[1] = 1;
        for(int i = 2;i<=n;i++){
            dp[i]  = dp[i-1] + dp[i-2];
            dp[i] %= 1000000007;
        }
        return dp[n];
    }

    int numWays(int n) {
        int dp[n+1];
        if(n == 0){
            return 1;
        }
        if(n == 1){
            return 1;
        }
        if(n == 2){
            return 2;
        }
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;

        for(int i = 3;i<=n;i++){
            dp[i] = dp[i-1] + dp[i-2];
            dp[i] %= 1000000007;
        }

        return dp[n];
    }

    int maxProfit(std::vector<int>& prices) {
        int min = INT_MAX;
        int res = 0;
        for(int& price : prices) {
            if(price < min) min = price;
            if(price - min > res) res = price - min;
        }
        return res;
    }

    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if( A == nullptr || B == nullptr) return false;
        if(A->val == B->val && isSub(A->right,B->right) && isSub(A->left,B->left))return true;
        return isSubStructure(A->left,B) || isSubStructure(A->right,B);
    }
    bool isSub(TreeNode* A, TreeNode*B) {
        if(B==nullptr)return true;
        if(A==nullptr)return false;
        if(A->val == B->val){
            return isSub(A->right,B->right) && isSub(A->left,B->left);
        }else{
            return false;
        }
    }

    TreeNode* mirrorTree(TreeNode* root) {
        if(root == nullptr)return nullptr;
        TreeNode* newRoot = new TreeNode(root->val);
        newRoot->right = mirrorTree(root->left);
        newRoot->left = mirrorTree(root->right);
        return newRoot;
    }

    bool isSymmetric(TreeNode* root) {
        if(root== nullptr)return true;
        return isSymmetricHelper(root->left,root->right);
    }

    bool isSymmetricHelper(TreeNode* A, TreeNode* B){
        if(A == nullptr && B == nullptr)return true;
        else if(A != nullptr && B != nullptr) {
            if(A->val == B->val){
                return isSymmetricHelper(A->right,B->left) && isSymmetricHelper(A->left,B->right);
            }else{
                return false;
            }
        }
        return false;
    }
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