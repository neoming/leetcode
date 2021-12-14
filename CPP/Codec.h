#include <string>
#include <queue>
//#include "Solution.h"
#include <strings.h>

using namespace std;
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans;
        queue<TreeNode*> treeNodeQueue;
        if(root == nullptr)return "";
        vector<string> treeNodeString;
        treeNodeQueue.push(root);
        while (!treeNodeQueue.empty()){
            TreeNode* tmp = treeNodeQueue.front();
            if( tmp == nullptr){
                treeNodeString.emplace_back("null");
            }else{
                treeNodeQueue.push(tmp->left);
                treeNodeQueue.push(tmp->right);
                treeNodeString.emplace_back(to_string(tmp->val));
            }
            treeNodeQueue.pop();
        }
        for(int i = 0;i<treeNodeString.size();i++){
            ans += treeNodeString[i]+',';
        }
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.size() == 0)return nullptr;
        vector<string> treeNodeString;
        string tmp;
        for(auto c : data){
            if(c==','){
                treeNodeString.emplace_back(tmp);
                tmp.clear();
            }else{
                tmp.push_back(c);
            }
        }
        queue<TreeNode* > treeQueue;
        TreeNode *root = new TreeNode(atoi(treeNodeString[0].c_str()));
        int index = 1;

        treeQueue.push(root);
        while (!treeQueue.empty()){
            TreeNode* treeNode = treeQueue.front();
            treeQueue.pop();
            if(treeNodeString[index] != "null" && treeNode != nullptr){
                treeNode->left = new TreeNode(atoi(treeNodeString[index].c_str()));
                treeQueue.push(treeNode->left);
            }
            index++;
            if(treeNodeString[index] != "null" && treeNode != nullptr){
                treeNode->right = new TreeNode(atoi(treeNodeString[index].c_str()));
                treeQueue.push(treeNode->right);
            }
            index++;
        }
        return root;
    }
};