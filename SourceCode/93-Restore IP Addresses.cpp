//	93. Restore IP Addresses
//------------------------------------------------------------------------------//
//	Given a string containing only digits, restore it by returning all possible //
//	valid IP address combinations.												//
//	For example :																//
//	Given "25525511135",														//
//	return["255.255.11.135", "255.255.111.35"]. (Order does not matter)			//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<set>
#include<iterator>
// constants
// function prototype
using namespace std;
//深度优先搜索加回溯
class Solution 
{
public:
	vector<string> restoreIpAddresses(string s) 
	{
		vector<string> result;
		string IPAdress;
		IPAdrDFs(0, s, IPAdress, result);
		return result;
	}
private:
	void IPAdrDFs(int dotcount, string s, string IPAdress, vector<string> &result)
	{
		if (dotcount == 3)
		{
			if (s.size() > 3)
				return;
			int ip = atoi(s.c_str());
			if (s.size() > 1 && s[0] == '0')
				return;
			if (ip >= 0 && ip <= 255)
			{
				IPAdress += s;
				result.push_back(IPAdress);
			}
			return;
		}
		int len = min(3, (int)(s.size() - 3 + dotcount));
		string prev = IPAdress;
		for (int i = 1; i <= len; i++)
		{
			string temp = s.substr(0, i);
			int ip = atoi(temp.c_str());
			if (ip < 0 || ip > 255)
				continue;
			if (i > 1 && s[0] == '0')
				continue;
			IPAdress += temp + ".";
			IPAdrDFs(dotcount + 1, s.substr(i), IPAdress, result);
			IPAdress = prev;
		}
	}
};
//深搜，利用一个string数组来存放IP
class Solution2
{
public:
	vector<string> restoreIpAddresses(string s) {
		vector<string> result;
		vector<string> ip; //存放中间结果
		dfs(s, ip, result, 0);
		return result;
	}
	void dfs(string s, vector<string>& ip, vector<string> &result,
		size_t start) {
		if (ip.size() == 4 && start == s.size()) { //找到一个合法解
			result.push_back(ip[0] + '.' + ip[1] + '.' + ip[2] + '.' + ip[3]);
			return;
		}
		if (s.size() - start > (4 - ip.size()) * 3)
			return; //剪枝
		if (s.size() - start < (4 - ip.size()))
			return; //剪枝
		int num = 0;
		for (size_t i = start; i < start + 3; i++) {
			num = num * 10 + (s[i] - '0');
			if (num < 0 || num > 255) continue; //剪枝
			ip.push_back(s.substr(start, i - start + 1));
			dfs(s, ip, result, i + 1);
			ip.pop_back();
			if (num == 0) break; //不允许前缀0，允许单个0
		}
	}
};
//深搜，不用vector
class Solution3 {
public:
	vector<string> restoreIpAddresses(string s) {
		vector<string> result;
		string ip;
		dfs(s, 0, 0, ip, result); //paras:string s,start index of s,step(from0-3),intermediate ip,final result
		return result;
	}
	void dfs(string s, int start, int step, string ip, vector<string>& result) {
		if (start == s.size() && step == 4) {
			ip.erase(ip.end() - 1); //remove the last '.' from the last decimal number
			result.push_back(ip);
			return;
		}
		if (s.size() - start>(4 - step) * 3) return;
		if (s.size() - start<(4 - step)) return;
		int num = 0;
		for (int i = start; i<start + 3; i++) {
			num = num * 10 + (s[i] - '0');
			if (num <= 255) {
				ip += s[i];
				dfs(s, i + 1, step + 1, ip + '.', result);
			}
			if (num == 0) break;
		}
	}
};
//int main(void)
//{
//	Solution2 test;
//	auto x = test.restoreIpAddresses("000100");
//	for_each(x.begin(), x.end(), [](string &s) {
//		cout << s << endl;
//	});
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