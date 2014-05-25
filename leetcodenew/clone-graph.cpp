/**
 * clone-graph.cpp
 * https://oj.leetcode.com/problems/clone-graph/
 *
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 *
 * the key is to establish a mapping from node in original graph
 * to node in clone graph
 */
class Solution {
public:
    void dfs(UndirectedGraphNode *node, map<UndirectedGraphNode*, UndirectedGraphNode*> &nodemap) {
        if (nodemap.count(node)) return;
        UndirectedGraphNode *cloneNode = new UndirectedGraphNode(node->label);
        nodemap[node] = cloneNode;
        for (int i = 0; i < node->neighbors.size(); ++i) {
            UndirectedGraphNode *neighbor = node->neighbors[i];
            if (nodemap.count(neighbor)) {
                // do nothing
            } else {
                dfs(neighbor, nodemap);
            }
            cloneNode->neighbors.push_back(nodemap[neighbor]);
        }
    }
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL) return NULL;
        map<UndirectedGraphNode*, UndirectedGraphNode*> nodemap;
        dfs(node, nodemap);
        return nodemap[node];
    }
};
