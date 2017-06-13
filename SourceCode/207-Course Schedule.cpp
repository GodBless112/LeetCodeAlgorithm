//	207. Course Schedule
//------------------------------------------------------------------------------//
//	There are a total of n courses you have to take, labeled from 0 to n - 1.	//
//	Some courses may have prerequisites, for example to take course 0 you have	//
//	to first take course 1, which is expressed as a pair : [0, 1]				//
//	Given the total number of courses and a list of prerequisite pairs, is it	//
//	possible for you to finish all courses ?									//
//	For example :																//
//	2, [[1, 0]]																	//
//	There are a total of 2 courses to take.To take course 1 you should have		//
//	finished course 0. So it is possible.										//
//	2, [[1, 0], [0, 1]]															//
//	There are a total of 2 courses to take.To take course 1 you should have		//
//	finished course 0, and to take course 0 you should also have finished		//
//	course 1. So it is impossible.												//
//	Note:																		//
//	The input prerequisites is a graph represented by a list of edges, not		//
//	adjacency matrices.Read more about how a graph is represented.				//
//	You may assume that there are no duplicate edges in the input prerequisites.//
//	Hints:																		//
//	1.This problem is equivalent to finding if a cycle exists in a directed		//
//	graph.If a cycle exists, no topological ordering exists and therefore it	//
//	will be impossible to take all courses.										//
//	2.Topological Sort via DFS - A great video tutorial(21 minutes) on Coursera //
//	explaining the basic concepts of Topological Sort.							//
//	3.Topological sort could also be done via BFS.								//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
// constants
// function prototype
using namespace std;
//可以看成是图，看是否有环路存在，存在则说明无法完成课程，拓扑排序
//利用DFS，将图用邻接表的方法表示
class Solution {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<node> Nodes(numCourses);
		for (int i = 0; i < numCourses; ++i)
			Nodes[i].index = i;
		for (int i = 0; i < prerequisites.size(); ++i)
			Nodes[prerequisites[i].second].adjs.push_back(prerequisites[i].first);
		vector<bool> visited(numCourses, false), onpath(numCourses, false);
		for (int i = 0; i < numCourses; ++i) {
			if(!visited[i] && dfs_cycle(Nodes, i, onpath, visited))
				return false;
		}
		return true;
	}
private:
	class node {
	public:
		int index;
		vector<int> adjs;
	};
	bool dfs_cycle(vector<node> &Nodes, int node, vector<bool>& onpath, vector<bool>& visited) {
		if (visited[node]) return false;
		onpath[node] = visited[node] = true;
		for (int neigh : Nodes[node].adjs)
			if (onpath[neigh] || dfs_cycle(Nodes, neigh, onpath, visited))
				return true;
		return onpath[node] = false;
	}
};
//DFS另一种形式，邻接表的表示不同
class Solution2 {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		auto graph = make_graph(numCourses, prerequisites);
		vector<bool> onpath(numCourses), visited(numCourses);
		for (int i = 0; i < numCourses; ++i)
			if (!visited[i] && DFS(graph, i, onpath, visited))
				return false;
		return true;
	}
private:
	vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<unordered_set<int>> graph(numCourses);
		for (auto pre : prerequisites)
			graph[pre.second].insert(pre.first);
		return graph;
	}
	bool DFS(vector<unordered_set<int>> &graph, int node, vector<bool>& onpath, vector<bool>& visited) {
		if (visited[node])
			return false;
		onpath[node] = visited[node] = true;
		for (auto neigh : graph[node])
			if (onpath[neigh] || DFS(graph, neigh, onpath, visited))
				return true;
		onpath[node] = false;
		return false;
	}
};
//BFS,拓扑排序,计算所有节点的入度，每次找出入度为0的节点，然后使得其邻接的节点的入度减1
class Solution3 {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		auto graph = make_graph(numCourses, prerequisites);
		vector<int> degrees = compute_indegree(graph);
		for (int i = 0; i < numCourses; ++i) {
			int j = 0;
			for (; j < numCourses; ++j)
				if (!degrees[j]) 
					break;
			if (j == numCourses)
				return false;
			degrees[j] = -1;
			for (auto neigh : graph[j])
				degrees[neigh]--;
		}
		return true;
	}
private:
	vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<unordered_set<int>> graph(numCourses);
		for (auto pre : prerequisites)
			graph[pre.second].insert(pre.first);
		return graph;
	}
	vector<int> compute_indegree(vector<unordered_set<int>> &graph) {
		vector<int> degrees(graph.size(), 0);
		for (auto neighbors : graph)
			for (auto neigh : neighbors)
				degrees[neigh]++;
		return degrees;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<pair<int, int>> prerequisites= { { 6,27 },{ 83,9 },{ 10,95 },{ 48,67 },{ 5,71 },{ 18,72 },
//	{ 7,10 },{ 92,4 },{ 68,84 },{ 6,41 },{ 82,41 },{ 18,54 },{ 0,2 },{ 1,2 },{ 8,65 },{ 47,85 },{ 39,51 },
//	{ 13,78 },{ 77,50 },{ 70,56 },{ 5,61 },{ 26,56 },{ 18,19 },{ 35,49 },{ 79,53 },{ 40,22 },{ 8,19 },
//	{ 60,56 },{ 48,50 },{ 20,70 },{ 35,12 },{ 99,85 },{ 12,75 },{ 2,36 },{ 36,22 },{ 21,15 },{ 98,1 },
//	{ 34,94 },{ 25,41 },{ 65,17 },{ 1,56 },{ 43,96 },{ 74,57 },{ 19,62 },{ 62,78 },{ 50,86 },{ 46,22 },
//	{ 10,13 },{ 47,18 },{ 20,66 },{ 83,66 },{ 51,47 },{ 23,66 },{ 87,42 },{ 25,81 },{ 60,81 },{ 25,93 },
//	{ 35,89 },{ 65,92 },{ 87,39 },{ 12,43 },{ 75,73 },{ 28,96 },{ 47,55 },{ 18,11 },{ 29,58 },{ 78,61 },
//	{ 62,75 },{ 60,77 },{ 13,46 },{ 97,92 },{ 4,64 },{ 91,47 },{ 58,66 },{ 72,74 },{ 28,17 },{ 29,98 },
//	{ 53,66 },{ 37,5 },{ 38,12 },{ 44,98 },{ 24,31 },{ 68,23 },{ 86,52 },{ 79,49 },{ 32,25 },{ 90,18 },
//	{ 16,57 },{ 60,74 },{ 81,73 },{ 26,10 },{ 54,26 },{ 57,58 },{ 46,47 },{ 66,54 },{ 52,25 },{ 62,91 },
//	{ 6,72 },{ 81,72 },{ 50,35 },{ 59,87 },{ 21,3 },{ 4,92 },{ 70,12 },{ 48,4 },{ 9,23 },{ 52,55 },{ 43,59 },
//	{ 49,26 },{ 25,90 },{ 52,0 },{ 55,8 },{ 7,23 },{ 97,41 },{ 0,40 },{ 69,47 },{ 73,68 },{ 10,6 },{ 47,9 },
//	{ 64,24 },{ 95,93 },{ 79,66 },{ 77,21 },{ 80,69 },{ 85,5 },{ 24,48 },{ 74,31 },{ 80,76 },{ 81,27 },{ 71,94 },
//	{ 47,82 },{ 3,24 },{ 66,61 },{ 52,13 },{ 18,38 },{ 1,35 },{ 32,78 },{ 7,58 },{ 26,58 },{ 64,47 },{ 60,6 },
//	{ 62,5 },{ 5,22 },{ 60,54 },{ 49,40 },{ 11,56 },{ 19,85 },{ 65,58 },{ 88,44 },{ 86,58 } };
//	//vector<pair<int, int>> prerequisites = { {1,0},{2,0},{3,1},{3,2} };
//	cout << boolalpha << test.canFinish(100, prerequisites);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}