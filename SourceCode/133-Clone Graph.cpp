//	133. Clone Graph
//------------------------------------------------------------------------------//
//	Clone an undirected graph. Each node in the graph contains a label and a	//
//	list of its neighbors.														//
//	OJ's undirected graph serialization:										//
//	Nodes are labeled uniquely.													//
//	We use # as a separator for each node, and, as a separator for node label	//
//	and each neighbor of the node.												//
//	As an example, consider the serialized graph{ 0,1,2#1,2#2,2 }.				//
//	The graph has a total of three nodes, and therefore contains three parts as //
//	separated by #.																//
//	First node is labeled as 0. Connect node 0 to both nodes 1 and 2.			//
//	Second node is labeled as 1. Connect node 1 to node 2.						//
//	Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming //
//	a self - cycle.																//
//	Visually, the graph looks like the following :								//
//			1																	//
//		   / \																	//
//		  /   \																	//
//		 0 -- - 2																//
//			   / \																//
//			   \_/																//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<queue>
// constants
// function prototype
using namespace std;

 struct UndirectedGraphNode {     
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};
 //深度优先搜索，利用哈希表来记录是否访问节点
class Solution {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (node == nullptr) return nullptr;
		if (hashtable.find(node) == hashtable.end()) {
			hashtable[node] = new UndirectedGraphNode(node->label);
			for (auto x : node->neighbors)
				hashtable[node]->neighbors.push_back(cloneGraph(x));
		}
		return hashtable[node];
	}
private:
	unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> hashtable;
};
//广度优先搜索，利用一个哈希表记录是否访问过
class Solution2 {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (node == nullptr) return nullptr;
		queue<UndirectedGraphNode*> q;
		q.push(node);
		hashtable[node] = new UndirectedGraphNode(node->label);
		while (!q.empty()) {
			UndirectedGraphNode* cur = q.front();
			q.pop();
			for (auto x : cur->neighbors) {
				if (hashtable.find(x) == hashtable.end()) {
					hashtable[x] = new UndirectedGraphNode(x->label);
					q.push(x);
				}
				hashtable[cur]->neighbors.push_back(hashtable[x]);
			}
		}
		return hashtable[node];
	}
private:
	unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> hashtable;
};
//int main(void)
//{
//	Solution2 test;
//	UndirectedGraphNode *p0, *p1, *p2;
//	p0 = new UndirectedGraphNode(0);
//	p1 = new UndirectedGraphNode(1);
//	p2 = new UndirectedGraphNode(2);
//	p0->neighbors.push_back(p1);
//	p0->neighbors.push_back(p2);
//	p1->neighbors.push_back(p2);
//	p2->neighbors.push_back(p2);
//	auto newp0 = test.cloneGraph(p0);
//	delete p0, p1, p2;
//	delete newp0->neighbors[0], newp0->neighbors[1], newp0;
//	auto res = test;
//	
//	cout << endl;
//
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}