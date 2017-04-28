//垂直二叉树遍历
//2017阿里面试题，火车调度

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
#include<ctime>
#include<iomanip>
#include<exception>
#include<cstdlib>
#include<fstream>
#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<stack>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<iterator>
#include<unordered_set>
#include<unordered_map>
#include<Windows.h>
#include<mutex>
// constants
using namespace std;
// function prototype
/*
a
/  \
b    c
/ \  /  \
d   e f   g
\  / \
h j   i
\
k
\
l
a:托马斯（Thomas）
b:艾德华（Edward）
c:亨利（Henry）
d:高登（Gordon）
e:詹姆士（James）
f:培西（Percy）
g:托比（Toby）
h:达克（Duke）
i:唐纳德&道格拉斯（Donald&Douglas）
j:奥利佛（Oliver）
k:亚瑟（Arthur）
l:艾蜜莉（Emily）
*/

struct BT
{
	int key;
	BT *l, *r;
};

BT* create_n(int key)
{
	BT *p = new BT;
	p->key = key;
	p->l = nullptr;
	p->r = nullptr;
	return p;

}
//垂直二叉树遍历
class Node
{
public:
	BT * rt;
	int column;
	Node(BT * n, int c) :rt(n), column(c) {}
};
vector<vector<BT*>> verticalOrder(BT *root)
{
	vector<vector<BT*>> result;
	if (root == nullptr)
		return result;
	unordered_map<int, vector<BT*>> orderMap;
	queue<Node> nodelist;
	nodelist.push(Node(root, 0));
	int mincol = INT_MAX, maxcol = INT_MIN;
	while (!nodelist.empty())
	{
		Node curNode = nodelist.front();
		nodelist.pop();
		mincol = min(mincol, curNode.column);
		maxcol = max(maxcol, curNode.column);
		orderMap[curNode.column].push_back(curNode.rt);
		if (curNode.rt->l != nullptr)
			nodelist.push(Node(curNode.rt->l, curNode.column - 1));
		if (curNode.rt->r != nullptr)
			nodelist.push(Node(curNode.rt->r, curNode.column + 1));
	}
	for (int i = mincol; i <= maxcol; i++)
		result.push_back(orderMap[i]);
	return result;
}
//垂直二叉树的一个例子，火车的调度，2017阿里在线笔试
bool train_schedule(BT* rt, int index)
{
	if (!rt)
		return false;

	map<int, string> m_train;
	m_train[0] = "Thomas";
	m_train[1] = "Edward";
	m_train[2] = "Henry";
	m_train[3] = "Gordon";

	m_train[4] = "James";
	m_train[5] = "Percy";
	m_train[6] = "Toby";
	m_train[7] = "Duke";

	m_train[8] = "Donald&Douglas";
	m_train[9] = "Oliver";
	m_train[10] = "Arthur";
	m_train[11] = "Emily";
	//TODO:write the real train schedule code here 
	auto x = verticalOrder(rt);
	auto schedule = x[x.size() - index];
	for (auto itr = schedule.rbegin(); itr != schedule.rend(); itr++)
	{
		cout << m_train[(*itr)->key - 'a'];
		if (itr != schedule.rend() - 1)
			cout << " ";
	}
	return true;
}
int Path[12];

void DFS(BT *rt)
{
	if (rt == nullptr)
		return;
	int p = Path[rt->key - 'a'];
	if (rt->l)
	{
		Path[rt->l->key - 'a'] = p - 1;
		DFS(rt->l);
	}	
	if (rt->r)
	{
		Path[rt->r->key - 'a'] = p + 1;
		DFS(rt->r);
	}
		
}

//int main(int argc, char* argv[])
//{
//	int i = 0;
//	
//	BT *rt = create_n('a');
//	rt->l = create_n('b');
//	rt->r = create_n('c');
//	rt->l->l = create_n('d');
//	rt->l->r = create_n('e');
//	rt->r->l = create_n('f');
//	rt->r->r = create_n('g');
//	rt->r->l->r = create_n('h');
//	rt->r->r->r = create_n('i');
//	rt->r->r->l = create_n('j');
//	rt->r->r->l->r = create_n('k');
//	rt->r->r->l->r->r = create_n('l');
//	std::cin >> i;
//	
//	train_schedule(rt, i);
//	
//	
//	while (std::cin.get() != '\n')
//		continue;
//	std::cin.get();
//	return 0;
//}


