#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//class Node {
//public:
//    int val;
//    Node* next;
//    Node* random;
//
//    Node(int _val) {
//        val = _val;
//        next = nullptr;
//        random = nullptr;
//    }
//};

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // day 18
    int maxDepth(TreeNode* root) {
        queue<TreeNode*> treeQue;
        if(root == nullptr)return 0;
        int depth = 0;
        treeQue.push(root);
        while (!treeQue.empty()){
            depth++;
            int length = treeQue.size();
            for(int i = 0;i<length;i++){
                TreeNode* tmp = treeQue.front();
                treeQue.pop();
                if(tmp->left != nullptr)treeQue.push(tmp->left);
                if(tmp->right != nullptr)treeQue.push(tmp->right);
            }
        }
        return depth;
    }

    int height(TreeNode* root){
        if(root == nullptr)return 0;
        int leftHeight = height(root->left);
        int rightHeight = height((root->right));
        if( rightHeight == -1 || leftHeight == -1 || abs(leftHeight - rightHeight) > 1){
            return -1;
        } else{
            return max(leftHeight,rightHeight) + 1;
        }
    }
    bool isBalanced(TreeNode* root){
        return height(root) >= 0;
    }
    // day 15
    vector<int> path;
    vector<vector<int>> ans;
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        pathSumRecur(root,0,target);
        return ans;
    }
    void pathSumRecur(TreeNode* root, int now, int target){
        if(root == nullptr)return;
        path.emplace_back(root->val);
        if(root->right == nullptr && root->left == nullptr && root->val + now == target ){
            ans.emplace_back(path);
        }else{
            pathSumRecur(root->right, now + root->val, target);
            pathSumRecur(root->left, now + root->val, target);
        }
        path.pop_back();
    }

    Node* pre, *head;
    Node* treeToDoublyList(Node* root) {
        if(root == nullptr) return nullptr;
        treeToDoublyListRecur(root);
        head->left = pre;
        pre->right = head;
        return head;
    }
    void treeToDoublyListRecur(Node* root){
        if(root == nullptr)return;
        treeToDoublyListRecur(root->left);
        if(pre == nullptr){
            head = root;
        }else{
            pre->right = root;
        }
        root->left = pre;
        pre = root;
        treeToDoublyListRecur(root->right);
    }

    vector<int> kthLargestNums;
    int kthLargest(TreeNode* root, int k) {
        kthLargestRecur(root);
        return kthLargestNums[kthLargestNums.size()-k];
    }
    void kthLargestRecur(TreeNode* root){
        if(root == nullptr)return;
        kthLargestRecur(root->left);
        kthLargestNums.emplace_back(root->val);
        kthLargestRecur(root->right);
    }
    // day 14
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty())return false;
        vector<vector<bool>> visited;
        for(int i = 0;i<board.size();i++){
            vector<bool> line;
            for(int j = 0; j< board[0].size();j++){
                line.push_back(false);
            }
            visited.push_back(line);
        }
        for(int i = 0;i<board.size();i++)
            for(int j = 0;j<board[0].size();j++){
                if(board[i][j] == word[0]){
                    bool res = existRecur(board,visited,i,j,0,word);
                    if(res)return true;
                }
            }
        return false;
    }
    bool existRecur(vector<vector<char>>& board,vector<vector<bool>>& visited,int i,int j,int nowIndex, string& word){
        if(i<0 || i >= board.size() || j < 0 || j >= board[0].size())return false;
        if( visited[i][j] )return false;
        if( board[i][j] != word[nowIndex])return false;
        else if(board[i][j] == word[nowIndex] && nowIndex == word.size()-1)return true;
        else{
            visited[i][j] = true;
            bool res =  existRecur(board,visited,i-1,j,nowIndex+1,word)||
                        existRecur(board,visited,i+1,j,nowIndex+1,word)||
                        existRecur(board,visited,i,j-1,nowIndex+1,word)||
                        existRecur(board,visited,i,j+1,nowIndex+1,word);
            visited[i][j] = false;
            return res;
        }
        return false;
    }

    int movingCount(int m, int n, int k) {
        vector<vector<bool>> visited(m,vector<bool>(n, false));
        movingRecur(0,0,k,visited);
        int ans = 0;
        for(auto line : visited)
            for(auto item : line)if(item)ans++;
        return ans;
    }

    void movingRecur(int i,int j, int k, vector<vector<bool>>& visited){
        if(i < 0 || i >= visited.size() || j < 0 || j >= visited[0].size()) return;
        if(canMove(i,j,k) && !visited[i][j]){
            visited[i][j] = true;
            movingRecur(i-1,j,k,visited);
            movingRecur(i+1,j,k,visited);
            movingRecur(i,j+1,k,visited);
            movingRecur(i,j+1,k,visited);
        }
    }

    bool canMove(int i, int j, int k){
        int ans = 0;
        while (i != 0){
            ans += i % 10;
            i /= 10;
        }
        while (j != 0){
            ans += j % 10;
            j /= 10;
        }
        return ans<=k;
    }
    // day 13
    vector<int> exchange(vector<int>& nums) {
        int length = nums.size();
        int odd_index = 0;
        int even_index = length-1;
        vector<int> ans(length);
        for(auto & num : nums){
            if(num%2 == 0){
                ans[even_index--] = num;
            }else{
                ans[odd_index++] = num;
            }
        }
        return ans;
    }
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans(2);
        int left = 0;
        int right = nums.size() - 1;
        while(left < right){
            if(nums[left] + nums[right] > target){
                right--;
            }else if(nums[left] + nums[right] < target){
                left++;
            }else{
                ans[0] = nums[left];
                ans[1] = nums[right];
                break;
            }
        }
        return ans;
    }

    // day 12
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(0);
        ListNode* cur = head;
        while (l1 != nullptr && l2 != nullptr){
            if(l1->val > l2->val){
                cur->next = l2;
                l2 = l2->next;
            }else{
                cur->next = l1;
                l1 = l1->next;
            }
            cur = cur->next;
        }
        while (l1 != nullptr){
            cur->next = l1;
            l1 = l1->next;
            cur = cur->next;
        }
        while (l2 != nullptr){
            cur->next = l2;
            l2 = l2->next;
            cur = cur->next;
        }
        return head->next;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == nullptr) return nullptr;
        if(headB == nullptr) return nullptr;
        ListNode* pa = headA;
        ListNode* pb = headB;
        while (pa != pb){
            pa = pa == nullptr? headB : pa->next;
            pb = pb == nullptr? headA : pb->next;
        }
        return pa;
    }

    // day 11
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* prevNode = nullptr;
        ListNode* nowNode = head;
        while (nowNode != nullptr){
            if(nowNode->val == val){
                if(prevNode != nullptr){
                    prevNode->next = nowNode->next;
                    return head;
                }else{
                    head = nowNode->next;
                    return head;
                }

            }else{
                prevNode = nowNode;
                nowNode = nowNode->next;
            }
        }
        return head;
    }

    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* cur;
        ListNode* next_k;
        cur = head;
        next_k = head;
        for(int i = 0;i<k;i++){
            if(next_k == nullptr)return nullptr;
            next_k = next_k->next;
        }
        while (next_k != nullptr){
            cur = cur->next;
            next_k = next_k->next;
        }
        return cur;
    }

    int translateNum(int num) {
        auto num_string = to_string(num);
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

    int lengthOfLongestSubstring(string s) {
        vector<int> lastPos(256);
        for(int i = 0;i<256;i++)lastPos[i] = -1;
        int left = 0;
        int maxLength = 0;
        for(int i = 0;i<s.size();i++){
            int index = s[i];
            if(lastPos[index] == -1) {
                lastPos[index] = i;
            }else{
                left = max(left,lastPos[index] + 1);
                lastPos[index] = i;
            }
            maxLength = max(i-left + 1, maxLength);
        }
        return maxLength;
    }

    int maxSubArray(vector<int>& nums) {
        int pre = 0;
        int maxRes = INT_MIN;
        for(auto & num : nums){
            pre = max(pre + num, num);
            maxRes = max(maxRes, pre);
        }
        return maxRes;
    }
//
//    int maxValue(vector<vector<int>>& grid) {
//        int m = grid.size();
//        if(m == 0)return 0;
//        int n = grid[0].size();
//        if(n == 0)return 0;
//        int dp[m][n];
//        dp[0][0] = grid[0][0];
//        for(int i = 1;i<m;i++){
//            dp[i][0] = grid[i][0] + dp[i-1][0];
//        }
//        for(int i = 1;i<n;i++){
//            dp[0][i] = grid[0][i] + dp[0][i-1];
//        }
//        for(int i = 1;i<m;i++){
//            for (int j = 1; j<n;j++){
//                dp[i][j] = grid[i][j] + max(dp[i-1][j], dp[i][j-1]);
//            }
//        }
//        return dp[m-1][n-1];
//    }

//    int fib(int n) {
//        int dp [n+1];
//        if(n == 0)return 0;
//        if(n == 1)return 1;
//        dp[0] = 0;
//        dp[1] = 1;
//        for(int i = 2;i<=n;i++){
//            dp[i]  = dp[i-1] + dp[i-2];
//            dp[i] %= 1000000007;
//        }
//        return dp[n];
//    }

//    int numWays(int n) {
//        int dp[n+1];
//        if(n == 0){
//            return 1;
//        }
//        if(n == 1){
//            return 1;
//        }
//        if(n == 2){
//            return 2;
//        }
//        dp[0] = 1;
//        dp[1] = 1;
//        dp[2] = 2;
//
//        for(int i = 3;i<=n;i++){
//            dp[i] = dp[i-1] + dp[i-2];
//            dp[i] %= 1000000007;
//        }
//
//        return dp[n];
//    }

    int maxProfit(vector<int>& prices) {
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

//    Node* copyRandomList(Node* head) {
//
//        if (head == nullptr) return nullptr;
//        // create the copy of cur node than cur->next = new node
//        Node* cur = head;
//        while (cur != nullptr){
//            Node* newNode = new Node(cur->val);
//            newNode->next = cur->next;
//            cur->next = newNode;
//            cur = newNode->next;
//        }
//
//        //update random
//        cur = head;
//        while (cur != nullptr){
//            Node* newNode = cur->next;
//            newNode->random = (cur->random != nullptr) ? cur->random->next : nullptr;
//            cur = newNode->next;
//        }
//
//        //delete connection between cur and newNode
//        Node* newNodeHead=head->next;
//        cur = head;
//        while (cur != nullptr ){
//            Node* newNode = cur->next;
//            cur->next = newNode->next;
//            newNode->next = (newNode->next != nullptr) ? newNode->next->next : nullptr;
//            cur = cur->next;
//        }
//
//        return newNodeHead;
//    }

    string replaceSpace(string s) {
        string res;
        for(char& a : s){
            if( a == ' '){
                res += "%20";
            }else{
                res += a;
            }
        }
        return res;
    }

    string reverseLeftWords(string s, int n) {
        string res;
        for(int i = n; i < s.size(); i++){
            res += s[i];
        }
        for(int i = 0; i < n; i++){
            res += s[i];
        }
        return res;
    }

    int findRepeatNumber(vector<int>& nums) {
        int n = nums.size();
        vector<int> count(n);
        for(int data : nums){
            if(count[data]==0){
                count[data]++;
            }else{
                return data;
            }
        }
        return -1;
    }

    int search(vector<int>& nums, int target) {
        return upper_bound(nums.begin(),nums.end(),target) - lower_bound(nums.begin(),nums.end(),target);
    }

    int missingNumber(vector<int>& nums){
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

    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
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

    char firstUniqChar(string s){
        unordered_map<char, int> frequency;
        for(char ch : s){
            ++frequency[ch];
        }
        for(char ch : s){
            if(frequency[ch] == 1)return ch;
        }
        return ' ';
    }

    string reverseWords(string s) {
        vector<pair<int,int>> word_index;
        int index = 0;
        while (index < s.size()){
            while (index<s.size() && s[index++] == ' ' );
            int left = index;
            while (index<s.size() && s[index++] != ' ' );
            int length = 0;
            if(index == s.size()){
                length = index-left;
            }else{
                length = index-left-1;
            }
            word_index.emplace_back(left,length);
        }
        int length = word_index.size();
        string ans = "";
        for(int i = length - 1;i>=0;i--){
            auto word = s.substr(word_index[i].first,word_index[i].second);
            ans += word;
            if(i != 0)ans+=' ';
        }
        return ans;
    }

    std::vector<int> levelOrder(TreeNode* root) {
        std::queue<TreeNode*> tree_queue;
        std::vector<int> ans;
        if(root == nullptr) return ans;
        tree_queue.push(root);
        while (!tree_queue.empty()){
            int length = tree_queue.size();
            for(int i = 0;i< length;i++){
                TreeNode* tmp = tree_queue.front();
                ans.push_back(tmp->val);
                if(tmp->left != nullptr){
                    tree_queue.push(tmp->left);
                }
                if(tmp->right != nullptr){
                    tree_queue.push(tmp->right);
                }
                tree_queue.pop();
            }
        }
        return ans;
    }

    vector<vector<int>> levelOrder1(TreeNode* root) {
        std::queue<TreeNode*> tree_queue;
        std::vector<std::vector<int>> ans;
        if(root == nullptr) return ans;
        tree_queue.push(root);
        while (!tree_queue.empty()){
            std::vector<int> ans_tmp;
            int length = tree_queue.size();
            for(int i = 0;i< length;i++){
                TreeNode* tmp = tree_queue.front();
                ans_tmp.push_back(tmp->val);
                if(tmp->left != nullptr){
                    tree_queue.push(tmp->left);
                }
                if(tmp->right != nullptr){
                    tree_queue.push(tmp->right);
                }
                tree_queue.pop();
            }
            ans.push_back(ans_tmp);
        }
        return ans;
    }

    vector<vector<int>> levelOrder2(TreeNode* root) {
        std::queue<TreeNode*> tree_queue;
        std::vector<vector<int>> ans;
        if(root == nullptr) return ans;
        tree_queue.push(root);
        bool inverse = false;
        while (!tree_queue.empty()){
            std::vector<int> ans_tmp;
            int length = tree_queue.size();
            for(int i = 0;i< length;i++){
                TreeNode* tmp = tree_queue.front();
                ans_tmp.push_back(tmp->val);
                if(tmp->left != nullptr){
                    tree_queue.push(tmp->left);
                }
                if(tmp->right != nullptr){
                    tree_queue.push(tmp->right);
                }
                tree_queue.pop();
            }
            if(inverse){
                std::reverse(ans_tmp.begin(),ans_tmp.end());
            }
            ans.push_back(ans_tmp);
            inverse = !inverse;
        }
        return ans;
    }
};