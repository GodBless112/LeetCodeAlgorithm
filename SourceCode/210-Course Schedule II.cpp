//	210. Course Schedule II
//------------------------------------------------------------------------------//
//	There are a total of n courses you have to take, labeled from 0 to n - 1.	//
//	Some courses may have prerequisites, for example to take course 0 you have	//
//	to first take course 1, which is expressed as a pair : [0, 1]				//
//	Given the total number of courses and a list of prerequisite pairs, return	//
//	the ordering of courses you should take to finish all courses.				//
//	There may be multiple correct orders, you just need to return one of them.	//
//	If it is impossible to finish all courses, return an empty array.			//
//	For example :																//
//	2, [[1, 0]]																	//
//	There are a total of 2 courses to take.To take course 1 you should have		//
//	finished course 0. So the correct course order is[0, 1]						//
//	4, [[1, 0], [2, 0], [3, 1], [3, 2]]											//
//	There are a total of 4 courses to take.To take course 3 you should have		//
//	finished both courses 1 and 2. Both courses 1 and 2 should be taken after	//
//	you finished course 0. So one correct course order is[0, 1, 2, 3].Another	//
//	correct ordering is[0, 2, 1, 3].											//
//	Note:																		//
//	The input prerequisites is a graph represented by a list of edges, not		//
//	adjacency matrices.Read more about how a graph is represented.				//
//	You may assume that there are no duplicate edges in the input prerequisites.//
//	Hints:																		//
//	1.This problem is equivalent to finding the topological order in a directed //
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
#include<queue>
#include<stack>
// constants
// function prototype
using namespace std;
//广度优先搜索的方法
class Solution {
public:
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
		vector<int> degrees = compute_indegree(graph);
		vector<int> result(numCourses);
		//利用队列
		queue<int> zeros;
		for (int i = 0; i < numCourses; i++)
			if (!degrees[i]) zeros.push(i);
		for (int i = 0; i < numCourses; ++i) {
			if (zeros.empty()) return{};
			int zero = zeros.front();
			zeros.pop();
			result[i] = zero;
			for (int neigh : graph[zero]) {
				if (!--degrees[neigh])
					zeros.push(neigh);
			}
		}
		//不用队列
		/*for (int i = 0; i < numCourses; ++i) {
			int j = 0;
			for (; j < numCourses; ++j)
				if (!degrees[j])
					break;
			if (j == numCourses)
				return vector<int>();
			degrees[j] = -1;
			result[i] = j;
			for (auto neigh : graph[j])
				degrees[neigh]--;
		}*/
		return result;
	}
private:
	vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<unordered_set<int>> graph(numCourses);
		for (auto pre : prerequisites)
			graph[pre.second].insert(pre.first);
		return graph;
	}
	vector<int> compute_indegree(vector<unordered_set<int>> &graph) {
		vector<int> degree(graph.size(), 0);
		for (auto node : graph)
			for (auto neigh : node)
				degree[neigh]++;
		return degree;
	}
};
//深度优先搜索
class Solution2 {
public:
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
		vector<int> toposort;
		vector<bool> onpath(numCourses, false), visited(numCourses, false);
		for (int i = 0; i < numCourses; i++)
			if (!visited[i] && DFS(graph, i, onpath, visited, toposort))
				return{};
		reverse(toposort.begin(), toposort.end());
		return toposort;
	}
private:
	vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<unordered_set<int>> graph(numCourses);
		for (auto pre : prerequisites)
			graph[pre.second].insert(pre.first);
		return graph;
	}
	bool DFS(vector<unordered_set<int>> &graph, int node, vector<bool> &onpath, vector<bool> &visited, vector<int> &topsort) {
		if (visited[node])
			return false;
		visited[node] = onpath[node] = true;
		for (auto neigh : graph[node])
			if (onpath[neigh] || DFS(graph, neigh, onpath, visited, topsort))
				return true;
		topsort.push_back(node);
		return onpath[node] = false;
	}
};
//另一种邻接表
class Solution3 {
public:
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<node> graph(numCourses);
		for (int i = 0; i < numCourses; ++i)
			graph[i].index = i;
		for (int i = 0; i < prerequisites.size(); ++i)
			graph[prerequisites[i].second].adjs.push_back(prerequisites[i].first);
		vector<int> toposort;
		vector<bool> onpath(numCourses, false), visited(numCourses, false);
		for (int i = 0; i < numCourses; i++)
			if (!visited[i] && DFS(graph, i, onpath, visited, toposort))
				return{};
		reverse(toposort.begin(), toposort.end());
		return toposort;
	}
private:
	class node {
	public:
		int index;
		vector<int> adjs;
	};
	bool DFS(vector<node> &graph, int node, vector<bool> &onpath, vector<bool> &visited, vector<int> &topsort) {
		if (visited[node])
			return false;
		visited[node] = onpath[node] = true;
		for (auto neigh : graph[node].adjs)
			if (onpath[neigh] || DFS(graph, neigh, onpath, visited, topsort))
				return true;
		topsort.push_back(node);
		return onpath[node] = false;
	}
};
//三色标记法
//Here, i have used 3 colored approach. Here w -> represent white means vertex yet not visited.
//g->gray, it means it is under DFS recursion and we again found the same node.This means cycle exists and return false.
//b->black node when DFS is done visiting the node.
//This method checks cycle as well as keeps storing answer in stack in case cycle doesn't exists.
class Solution4 {
private:
	class Graph {
	public:
		int v;
		list <int> *adj;
		Graph(int v)
		{
			this->v = v;
			adj = new list<int>[v];
		}
		void addedges(int src, int dest)
		{
			adj[dest].push_back(src);
		}
	};
public:
	stack <int> st;
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		Graph g(numCourses);
		for (int i = 0; i < prerequisites.size(); i++)
			g.addedges(prerequisites[i].first, prerequisites[i].second);
		vector <int> ans;
		if (!courseScheduleCheck(g))
			return ans;
		while (!st.empty())
		{
			ans.push_back(st.top());
			st.pop();
		}
		return ans;
	}
	bool courseScheduleCheck(Graph g)
	{
		int v = g.v;
		vector <char> visit(v, 'w');
		for (int i = 0; i<v; i++)
		{
			if (visit[i] == 'w')
				if (iscycle(g, i, visit))
					return false;
		}
		return true;
	}
	bool iscycle(Graph g, int i, vector <char> & visit)
	{
		list <int> ::iterator it;
		for (it = g.adj[i].begin(); it != g.adj[i].end(); it++)
		{
			if (visit[*it] == 'g')
				return true;
			else
			{
				if (visit[*it] != 'b')
				{
					visit[*it] = 'g';
					if (iscycle(g, *it, visit))
						return true;
				}
			}
		}
		visit[i] = 'b';
		st.push(i);
		return false;
	}
};
//int main(void)
//{
//	Solution4 test;
//	vector<pair<int, int>> prerequisites = { { 0,1 },{ 2,0 },{ 3,1 },{ 3,2 } };
//	auto res = test.findOrder(4, prerequisites);
//	for_each(res.begin(), res.end(), [](int x) {cout << x << " "; });
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}