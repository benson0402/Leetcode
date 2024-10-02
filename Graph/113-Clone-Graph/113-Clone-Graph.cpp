/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    vector<Node*> copied;

    Node* cloneGraph(Node* node) {
        if(node == nullptr)
            return nullptr;
        if(copied[node->val] != nullptr)
            return copied[node->val];

        Node* ret = new Node(node->val, node->neighbors);
        copied[ret->val] = ret;
        for(auto& x : ret->neighbors)
            x = cloneGraph(x);
        return ret;
    }

    Solution() { copied = vector<Node*>(200); }
};
