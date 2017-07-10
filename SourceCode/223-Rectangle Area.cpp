//	223. Rectangle Area
//------------------------------------------------------------------------------//
//	Find the total area covered by two rectilinear rectangles in a 2D plane.	//
//	Each rectangle is defined by its bottom left corner and top right corner as //
//	shown in the figure.														//
//	Assume that the total area is never beyond the maximum possible value of	//
//	int.																		//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>

// constants
// function prototype
using namespace std;
//如果两个矩形相交，将对应4个x，4个y坐标分别排序，取中间两个计算
class Solution {
public:
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		int area = (C - A)*(D - B) + (G - E)*(H - F);
		if (C <= E || A >= G || B >= H || D <= F)
			return area;
		else {
			vector<int> h{ A,C,E,G };
			vector<int> v{ B,D,F,H };
			sort(h.begin(), h.end());
			sort(v.begin(), v.end());
			area -= (h[2] - h[1])*(v[2] - v[1]);
			return area;
		}
	}
};
//列举所有覆盖情况，过于复杂
class Solution2 {
public:
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		int area1 = (D - B)*(C - A);
		int area2 = (H - F)*(G - E);
		int area3;
		if (area1 == 0) {
			return area2;
		}
		if (area2 == 0) {
			return area1;
		}
		if ((A == D) && (B == F) && (C == G) && (D == H)) {
			return area1;
		}
		if ((E >= C) | (G <= A) | (H <= B) | (D <= F)) {    //not overlapping
			return (area1 + area2);
		}
		if (((G - E) <= (C - A)) && ((H - F) <= (D - B)) && (E >= A) && (F >= B) && (G <= C) && (D >= H)) {                        //rect2 is inside rect1
			return area1;
		}
		if (((C - A) <= (G - E)) && ((D - B) <= (H - F)) && (E <= A) && (B >= F) && (G >= C) && (H >= D)) {                        //rect1 is inside rect2
			return area2;
		}
		if ((F >= B) && (E >= A) && (G >= C) && (H >= D)) {                       //overlapping upper right corner
			area3 = (C - E)*(D - F);
		}
		else if ((F >= B) && (E <= A) && (G <= C) && (H >= D)) {                       //overlapping upper left corner
			area3 = (G - A)*(D - F);
		}
		else if ((F <= B) && (E <= A) && (G <= C) && (H <= D)) {                       //overlapping bottom left corner
			area3 = (G - A)*(H - B);
		}
		else if ((F <= B) && (E >= A) && (G >= C) && (H <= D)) {                        //overlapping bottom right corner
			area3 = (H - B)*(C - E);
		}
		else if (((C - A) <= (G - E)) && (H <= D) && (G >= C) && (E <= A) && (F <= B)) {               //overlapping bottom side
			area3 = (C - A)*(H - B);
		}
		else if (((C - A) <= (G - E)) && (H >= D) && (G >= C) && (E <= A) && (F >= B)) {               //overlapping top side
			area3 = (C - A)*(D - F);
		}
		else if (((D - B) <= (H - F)) && (E <= A) && (F <= B) && (H >= D) && (G <= C)) {               //overlapping left side
			area3 = (G - A)*(D - B);
		}
		else if (((D - B) <= (H - F)) && (E >= A) && (F <= B) && (H >= D) && (G >= C)) {               //overlapping right side
			area3 = (C - E)*(D - B);
		}
		else if (((C - A) >= (G - E)) && (E >= A) && (F >= B) && (C >= G) && (D <= H)) {      //overlapping part of top side
			area3 = (G - E)*(D - F);
		}
		else if (((C - A) >= (G - E)) && (A <= E) && (B >= F) && (G <= C) && (D >= H)) {       //overlapping part of bottom side
			area3 = (G - E)*(H - B);
		}
		else if (((D - B) >= (H - F)) && (E <= A) && (F >= B) && (G <= C) && (H <= D)) {      //overlapping part of left side
			area3 = (G - A)*(H - F);
		}
		else if (((D - B) >= (H - F)) && (E >= A) && (F >= B) && (G >= C) && (H <= D)) {       //overlapping part of right side
			area3 = (C - E)*(H - F);
		}
		else if (((G - E) <= (C - A)) && (E >= A) && (F <= B) && (G <= C) && (H >= D)) {     //overlapping top and bottom
			area3 = (G - E)*(D - B);
		}
		else if (((H - F) <= (D - B)) && (E <= A) && (F >= B) && (C <= G) && (D >= H)) {     //overlapping left and right
			area3 = (C - A)*(H - F);
		}

		return (area1 + area2 - area3);
	}
};
//方案2优化
class Solution3 {
public:
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		int area1 = (C - A)*(D - B), area2 = (G - E)*(H - F);
		int coverX = C < E ? 0 : C < G ? A < E ? C - E : C - A : A > G ? 0 : A < E ? G - E : G - A;
		int coverY = D < F ? 0 : D < H ? B < F ? D - F : D - B : B > H ? 0 : B < F ? H - F : H - B;
		return area1 + area2 - coverX * coverY;
	}
};
//1的变形
class Solution4 {
public:
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		int left = max(A, E), right = max(min(C, G), left);
		int bottom = max(B, F), top = max(min(D, H), bottom);
		return (C - A)*(D - B) - (right - left)*(top - bottom) + (G - E)*(H - F);
	}
};
//int main(void)
//{
//	Solution4 test;
//	cout << test.computeArea(-3, 0, 3, 4, 0, -1, 9, 2);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}