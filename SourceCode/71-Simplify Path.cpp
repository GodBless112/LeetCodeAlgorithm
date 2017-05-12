//	71. Simplify Path
//------------------------------------------------------------------------------//
//	Given an absolute path for a file (Unix-style), simplify it.				//
//	For example,																//
//	path = "/home/", => "/home"													//
//	path = "/a/./b/../../c/", => "/c"											//
//	Corner Cases:																//
//		Did you consider the case where path = "/../" ?							//
//		In this case, you should return "/".									//
//		Another corner case is the path might contain multiple slashes '/'		//
//		together, such as "/home//foo/".										//
//		In this case, you should ignore redundant slashes and return "/home/foo"//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;
//利用栈来做
class Solution
{
public:
	string simplifyPath(string path)
	{
		vector<string> dirs;
		for (auto i = path.begin(); i != path.end();)
		{
			++i;
			auto j = find(i, path.end(), '/');
			auto dir = string(i, j);
			if (!dir.empty() && dir != ".")
			{
				if (dir == "..")
				{
					if (!dirs.empty())
						dirs.pop_back();
				}
				else
					dirs.push_back(dir);
			}
			i = j;
		}
		stringstream ss;
		if (dirs.empty())
			ss << "/";
		else
		{
			for (auto dir : dirs)
				ss << '/' << dir;
		}
		return ss.str();
	}
};

//int main(void)
//{
//	Solution test;
//	string s("///");
//	cout << test.simplifyPath(s);
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
