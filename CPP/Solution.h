#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>
#include <deque>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
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
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
enum Direction{
    Left,Right,Up,Down
};

class Solution {
private:
    unordered_map<int,int> indexMap;
    vector<string> permutationRes;
    vector<int> printNumbersAns;
    vector<char> numberChars = {'0','1','2','3','4','5','6','7','8','9'};

    vector<int> reversePairsTmp;
public:
    // day 31
    int findNthDigit(int n) {
        int digit = 1, start = 1, count = 9;
        while (n > count){
            n -= count;
            digit += 1;
            start *= 10;
            count = 9 * start * digit;
        }
        int num = start + (n - 1)/digit;
        string nums = to_string(num);
        return nums[(n-1)%digit] - '0';
    }

    int cuttingRope(int n) {
        if(n <= 3)return n-1;
        long ans = 1;
        int mod = n % 3;
        int pow = n / 3;
        switch (mod) {
            case 0:
                for(int i = 0; i < pow ; i++){
                    ans = 3 * ans % 1000000007;
                }
                break;
            case 1:
                for(int i = 0; i < pow - 1;i++){
                    ans = 3 * ans % 1000000007;
                }
                ans = 4 * ans % 1000000007;
                break;
            case 2:
                for(int i = 0; i < pow;i++){
                    ans = 3 * ans % 1000000007;
                }
                ans = 2 * ans % 1000000007;
                break;
        }
        return int(ans);
    }

    int countDigitOne(int n) {
        long digit = 1;
        int res = 0;
        int high = n/10, cur = n % 10, low = 0;
        while (high != 0 || cur != 0){
            switch (cur) {
                case 0:
                    res += digit * high;
                    break;
                case 1:
                    res += (digit * high) + low + 1;
                    break;
                default:
                    res += (high + 1) * digit;
            }
            low += digit*cur;
            cur = high % 10;
            high /= 10;
            digit *= 10;
        }
        return res;
    }

    // day 30
    int reversePairs(vector<int>& nums) {
        vector<int> tmp(nums.size());
        return reversePairsRecur(0,nums.size()-1, nums, tmp);
    }
    int reversePairsRecur(int left, int right, vector<int>&nums, vector<int>&tmp){
        if(left >= right)return 0;
        int mid = (right+left)/2;
        int count = reversePairsRecur(left,mid,nums,tmp) + reversePairsRecur(mid+1, right,nums,tmp);
        int i = left, j = mid + 1;
        for(int k = left; k <= right;k++)tmp[k]=nums[k];
        for(int k = left; k <= right;k++){
            if(i == mid + 1){
                nums[k] = tmp[j++];
            }else if( j == right + 1 || tmp[i] <= tmp[j]){
                nums[k] = tmp[i++];
            }else{
                nums[k] = tmp[j++];
                count += mid-i+1;
            }
        }
        return count;
    }
    vector<int> printNumbers(int n) {
        printNumbersAns.clear();
        printNumbersRecur(0,n,"");
        return printNumbersAns;
    }
    void printNumbersRecur(int now, int target, string s){
        if(now == target){
            int index = 0;
            while (s[index] == '0')index++;
            string news = s.substr(index);
            if(news.size() != 0){
                printNumbersAns.emplace_back(atoi(news.c_str()));
            }
            return;
        }
        for(auto c : numberChars){
            string newStr  = s + c;
            printNumbersRecur(now+1,target,newStr);
        }
    }
    // day 29
    vector<double> dicesProbability(int n) {
        vector<double>ans;
        if(n == 0)return ans;
        ans = vector<double>(6,1.0/6.0);
        for(int i = 2;i<=n;i++){
            vector<double> tmp(5*i+1,0.0);
            for(int j = 0;j<ans.size();j++)
                for(int k = 0;k<6;k++){
                    tmp[j+k] += ans[j]*(1.0/6.0);
                }
            ans = tmp;
        }
        return ans;
    }
    int nthUglyNumber(int n) {
        vector<int> dp(n+1);
        dp[0] = 0;
        dp[1] = 1;
        int p2 = 1,p3 = 1,p5 = 1;
        for(int i = 2;i<=n;i++){
            int num2 = dp[p2] * 2;
            int num3 = dp[p3] * 3;
            int num5 = dp[p5] * 5;
            dp[i] = min(min(num2,num3),num5);
            if(dp[i] == num2)p2++;
            if(dp[i] == num3)p3++;
            if(dp[i] == num5)p5++;
        }
        return dp[n];
    }
    bool isMatch(string s, string p) {
        auto m = s.size();
        auto n = p.size();
        auto matches = [&](int x,int y){
            if(x == 0)return false;
            if(p[y-1] == '.')return true;
            return s[x-1] == p[y-1];
        };
        vector<vector<bool>> dp(m+1,vector<bool>(n+1, false));
        dp[0][0]=true;
        for(int i = 0;i<=m;i++){
            for(int j = 1;j<=n;j++){
                if(p[j-1] == '*'){
                    dp[i][j] = dp[i][j-2] || dp[i][j];
                    if(matches(i,j-1)){
                        dp[i][j] = dp[i-1][j] || dp[i][j];
                    }
                }else{
                    if(matches(i,j)){
                        dp[i][j] = dp[i-1][j-1] || dp[i][j];
                    }
                }
            }
        }
        return dp[m][n];
    }
    // day 28
    vector<string> permutation(string s) {
        permutationRes.clear();
        permutationRecur(s,0);
        return permutationRes;
    }
    void permutationRecur(string& s, int i){
        if (i == s.size()-1){
            permutationRes.push_back(s);
            return;
        }
        set<char> st;
        for(int x = i;x<s.size();x++){
            if(st.find(s[x]) != st.end())continue;
            st.insert(s[x]);
            swap(s[i],s[x]);
            permutationRecur(s,i+1);
            swap(s[i],s[x]);
        }
    }
    // day 27
//    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
//        int length = nums.size();
//        vector<int> ans;
//        if(length == 0)return ans;
//        priority_queue<pair<int,int>> q;
//        for(int i = 0;i<k;i++){
//            q.emplace(nums[i],i);
//        }
//        ans.emplace_back(q.top().first);
//        for(int i = k ;i<length;i++){
//            q.emplace(nums[i],i);
//            while (q.top().second <= i-k)q.pop();
//            ans.emplace_back(q.top().first);
//        }
//        return ans;
//    }
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int length = nums.size();
        vector<int> ans;
        if(length == 0)return ans;
        deque<int > q;
        for(int i = 0;i<k;i++){
            while (!q.empty() && nums[i] >= nums[q.back()])q.pop_back();
            q.emplace_back(i);
        }
        ans.emplace_back(nums[q.front()]);
        for(int i = k;i<length;i++){
            while (!q.empty() && nums[i] >= nums[q.back()])q.pop_back();
            q.push_back(i);
            while (q.front() <= i-k)q.pop_front();
            ans.push_back(nums[q.front()]);
        }
        return ans;
    }
    // day 26
    int strToInt(string str) {
        // clear white space
        int i = 0;
        while (i<str.size() && str[i]==' ')i++;
        str = str.substr(i);
        bool neg = false;
        i = 0;
        if(str[0] == '-'){
            neg= true;
            i++;
        }else if(str[0] == '+')i++;
        long ans = 0;
        while (i<str.size()){
            if(str[i]>='0' && str[i]<='9'){
                ans = ans * 10 + (str[i]-'0');
                if(ans >= INT32_MAX)break;
                i++;
            } else break;
        }
        int res = 0;
        if(neg)ans *= -1;
        if(ans >= INT32_MAX){
            res = INT32_MAX;
        }else if(ans <= INT32_MIN){
            res = INT32_MIN;
        }else{
            res = (int)ans;
        }
        return res;
    }
    string clearWhiteSpace(string s){
        // clear white space
        int i = 0;
        while (i<s.size()){
            if(s[i] == ' '){
                i++;
                continue;
            }else{
                break;
            }
        }
        auto j = s.size() - 1;
        while (j > i){
            if(s[j] == ' '){
                j--;
            }else{
                break;
            }
        }
        return s.substr(i,j-i+1);
    }
    bool isNumber(string s) {
        s = clearWhiteSpace(s);
        if(s.find('e')==-1 && s.find('E')==-1){
            return isInteger(s) || isDecimal(s);
        }else{
            auto i = s.find('e')==-1?s.find('E'):s.find('e');
            string preStr = s.substr(0,i);
            string sufStr = s.substr(i+1);
            return (isInteger(preStr) || isDecimal(preStr)) && isInteger(sufStr);
        }
        return false;
    }
    bool isDigital(char c){
        return c>='0' && c <= '9';
    }
    bool isInteger(string s){
        int len = s.size();
        if(len == 0)return false;
        if(s[0] == '+' || s[0] == '-')s = s.substr(1);
        if(s.size()==0)return false;
        for(char i : s){
            if(!isDigital(i))return false;
        }
        return true;
    }

    bool isDecimal(string s){
        int len = s.size();
        if(len == 0)return false;
        if(s[0] == '+' || s[0] == '-')s = s.substr(1);
        auto index = s.find('.');
        if(index == -1)return false;
        if(index != 0){
            if(index == s.size()-1){
                return isInteger(s.substr(0,index));
            }else{
                return isInteger(s.substr(0,index)) && isInteger(s.substr(index+1));
            }
        }else{
            if(s.size() == 1)return false;
            for(char c : s.substr(1)){
                if(!isDigital(c))return false;
            }
            return true;
        }
        return true;
    }
    // day 25
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        if(matrix.size() == 0)return ans;
        vector<vector<bool>> visited(matrix.size(),vector<bool>(matrix[0].size(), false));
        Direction direction = Right;
        int m = matrix.size();
        int n = matrix[0].size();
        int length = m*n;
        int i=0,j=0;
        while (length>0){
            switch (direction) {
                case Right:
                    if(j >= n || visited[i][j]){
                        direction=Down;
                        j--;
                        i++;
                    }
                    else{
                        ans.emplace_back(matrix[i][j]);
                        visited[i][j]= true;
                        length--;
                        j++;
                    }
                    break;
                case Down:
                    if(i >= m || visited[i][j]){
                        direction=Left;
                        i--;
                        j--;
                    }
                    else{
                        ans.emplace_back(matrix[i][j]);
                        visited[i][j]= true;
                        length--;
                        i++;
                    }
                    break;
                case Left:
                    if(j < 0 || visited[i][j]){
                        direction=Up;
                        j++;
                        i--;
                    }
                    else{
                        ans.emplace_back(matrix[i][j]);
                        visited[i][j]= true;
                        j--;
                        length--;
                    }
                    break;
                case Up:
                    if(i < 0 || visited[i][j]){
                        direction=Right;
                        i++;
                        j++;
                    }else{
                        ans.emplace_back(matrix[i][j]);
                        visited[i][j]= true;
                        i--;
                        length--;
                    }
            }
        }
        return ans;
    }

    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        if(pushed.size() != popped.size())return false;
        if(pushed.size() == 0)return true;
        int i = 0,j = 0;
        int len = pushed.size();
        stack<int> stack;
        while (i < len || j <len){
            if(stack.empty()){
                stack.push(pushed[i++]);
                continue;
            }
            if(stack.top() != popped[j]){
                if(i == len)return false;
                stack.push(pushed[i++]);
            }
            else{
                j++;
                stack.pop();
            }
        }

        return i == j && stack.empty();
    }
    // day 24
    int cuttingRope(int n) {
        vector<int> dp(n+1,0);
        for(int i = 2;i<=n;i++){
            int maxValue = 0;
            for(int j = 1; j < i ; j++){
                maxValue = max(maxValue, max(dp[i-j] * j,j*(i-j)));
            }
            dp[i] = maxValue;
        }
        return dp[n];
    }

    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> ans;
        int i = 1;
        int j = 2;
        int sum = 3;
        while (i < j){
            if(sum == target){
                vector<int> tmp;
                for(int k = i;k<=j;k++)tmp.emplace_back(k);
                ans.emplace_back(tmp);
            }
            if(sum >= target){
                sum -= i;
                i++;
            }else{
                j++;
                sum += j;
            }
        }
        return ans;
    }

    int lastRemaining(int n, int m) {
        return lastRemainingRecur(n,m);
    }
    int lastRemainingRecur(int n, int m){
        if(n == 1)return 0;
        int x = lastRemainingRecur(n-1,m);
        return (m+x)%n;
    }

    // day 23
    int majorityElement(vector<int>& nums) {
        int x = 0, votes = 0;
        for(auto num : nums){
            if(votes == 0){
                x = num;
                votes++;
            }else{
                if(num == x)votes++;
                else votes--;
            }
        }
        return x;
    }
    vector<int> constructArr(vector<int>& a) {
        if(a.size() == 0)return {};
        int len = a.size();
        vector<int> ans (len,1);
        for(int i = 1;i<len;i++){
            ans[i] = ans[i-1] * a[i-1];
        }
        int tmp = 1;
        for(int i = len - 2; i >= 0;i--){
            tmp *= a[i+1];
            ans[i] *= tmp;
        }
        return ans;
    }

    // day 22
    vector<int> singleNumbers(vector<int>& nums) {
        int ret = 0;
        for(int num:nums)ret ^= num;
        unsigned int index = 1;
        while ((index & ret) == 0)index <<= 1;
        int a = 0;
        int b = 0;
        for(int num :nums){
            if(index & num){
                a ^= num;
            }else{
                b ^= num;
            }
        }
        return vector<int>{a,b};
    }

    int singleNumber(vector<int>& nums) {
        int bitCount [32] = {0};
        for(int num : nums){
            for(int i = 0;i<32;i++){
                if(num & 1)bitCount[i]++;
                num >>= 1;
            }
        }
        for(int i = 0;i<32;i++){
            bitCount[i] %= 3;
        }
        int ans = 0;
        for(int i = 31;i>=0;i--){
            ans <<= 1;
            ans |= bitCount[i];
        }
        return ans;
    }
    // day 21
    int hammingWeight(uint32_t n){
        int ans = 0;
        while (n != 0){
            if(n&1)ans++;
            n = n >> 1;
        }
        return ans;
    }
    int add(int a, int b) {
        while (b != 0){
            int c = (unsigned int)(a & b) << 1;
            a ^= b;
            b = c;
        }
        return a;
    }
    // day 20
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = inorder.size();
        for(int i = 0;i<inorder.size();i++){
            indexMap[inorder[i]] = i;
        }
        return myBuildTree(preorder,inorder,0,n-1,0,n-1);
    }
    TreeNode* myBuildTree(vector<int>& preorder, vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right){
        if(preorder_left > preorder_right)return nullptr;
        TreeNode* root = new TreeNode(preorder[preorder_left]);
        int inorder_root_index = indexMap[preorder[preorder_left]];
        int left_subtree_size = inorder_root_index-inorder_left;
        root->left = myBuildTree(preorder,inorder,preorder_left+1,preorder_left+left_subtree_size,inorder_left,inorder_root_index-1);
        root->right = myBuildTree(preorder,inorder,preorder_left+left_subtree_size+1,preorder_right,inorder_root_index+1,inorder_right);
        return root;
    }
    double myPow(double x, int n) {
        if(n == 0)return 1.0;
        if(x == 0.0)return 0.0;
        long p = n;
        if(p < 0){
            x = 1/x;
            p = -1*p;
        }
        double ans = 1.0;
        while (p!=0){
            if(p&1)ans *=x;
            p = p>>1;
            x*=x;
        }
        return ans;
    }

    bool verifyPostorder(vector<int>& postorder) {
        return verifyPostorderRecur(postorder,0,postorder.size()-1);
    }
    bool verifyPostorderRecur(vector<int>& postorder, int left, int right){
        if(left>right)return true;
        int rootValue = postorder[right];
        int leftIndex = left;
        while (postorder[leftIndex] < rootValue)leftIndex++;
        int midIndex = left;
        while (postorder[leftIndex] > rootValue)leftIndex++;
        return leftIndex == right && verifyPostorderRecur(postorder,left,midIndex-1) && verifyPostorderRecur(postorder,midIndex,right-1);
    }
    // day 17
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> vec(k,0);
        if(k == 0)return vec;
        priority_queue<int> Q;
        for(int i = 0;i<k;i++)Q.push(arr[i]);
        for(int i = k;i<arr.size();i++){
            if(Q.top() > arr[i]){
                Q.pop();
                Q.push(arr[i]);
            }
        }
        for(int i = 0;i<k;i++){
            vec[i] = Q.top();
            Q.pop();
        }
        return vec;
//        vector<int> ans(k,0);
//        sort(arr.begin(),arr.end());
//        for(int i = 0;i<k;i++){
//            ans[i] = arr[i];
//        }
//        return ans;
    }

    // day 19
    int sumNums(int n) {
        return addNums(n);
    }
    int addNums(int n){
        if(n == 1)return 1;
        else return n + addNums(n-1);
    }

    TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* ancestor=root;
        while (true){
            if(p->val < ancestor->val && q->val < ancestor->val)ancestor = ancestor->left;
            else if(p->val > ancestor->val && q->val > ancestor->val)ancestor = ancestor->right;
            else{
                break;
            }
        }
        return ancestor;
    }
    //  day 16
    string minNumber(vector<int>& nums) {
        vector<string> strs;
        for(auto & num : nums)strs.emplace_back(to_string(num));
        sort(strs.begin(),strs.end(),[](string& a, string& b){return  a+b < b+a;});
        string res;
        for(auto str : strs)res+=str;
        return res;
    }

    bool isStraight(vector<int>& nums) {
        set<int> numSet;
        int maxNum = -1;
        int minNum = 100;
        for(auto & num : nums){
            if(num == 0)continue;
            else if(numSet.find(num) == numSet.end()){
                numSet.insert(num);
                maxNum = max(num,maxNum);
                minNum = min(num,minNum);
            } else{
                return false;
            }
        }
        return maxNum-minNum < 5;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr || p == root || q == root)return root;
        TreeNode* left = lowestCommonAncestor(root->left,p,q);
        TreeNode* right = lowestCommonAncestor(root->right,p,q);
        if(left == nullptr && right == nullptr)return nullptr;
        else if(left == nullptr)return right;
        else if(right == nullptr)return left;
        return root;
    }
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
        int maxRes = INTMAX_MIN;
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
        int min = INTMAX_MAX;
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