#include <iostream>
#include <deque>
#include <vector>
#include <map>
static size_t npos = -1;
using namespace std;


// 先得有一个图结构， 这样才能开始测试
class Graph {
public:
	Graph() {
		_graph = {
			{ 0 : {1 : 4, 7 : 8} },
			{ 1 : {2 : 8, 7 : 11, 0 : 4} },
			{ 7 : {8 : 7, 6 : 1, 0 : 8, 1 : 11}},
			{ 2 : {3 : 7, 5 : 4, 8 : 2, 1 : 8}},
			{ 8 : {6 : 6, 2 : 2, 7 : 7}},
			{ 6 : {7 : 1, 8 : 6, 5 : 2}},
			{ 3 : {2 : 7, 5 : 14, 4 : 9}},
			{ 5 : {2 : 4, 6 : 2, 3 : 5, 4 : 10}},
			{ 4 : {3 : 9, 5 : 10}}
		};

		//_graph[0] = { 1 : 4, 7 : 8 };
		//_graph[1] = { 2 : 8, 7 : 11, 0 : 4 };
		//... ...
	}
private:
	map<int, map<int, int>> _graph;
	//vector<map<int, int>> _graph;
	// 下标：节点名 内容：相邻节点， 下标节点到这个相邻节点的距离
};

// 先找到当前节点的最短路径，更新路径大小，更新相邻节点的路径大小

class Dijkstra {
public:
	// 找哪个节点在哪个图里的最优路径
	// Dijkstra(graph, 0);
	Dijkstra(std::vector<map<int, map<int, int>>> graph, int start)
		:_graph(graph), _start(start)
	{}

	// 先是找0到相邻节点的最短路径，然后确定最短路径的终点为0（自己找自己最短），从这个终点开始，再找下一个相邻节点的最短路径
	void Get_ShortestRoute() {
		vector<int> PreNode(8, npos);
		vector<int> ShortestRoute(8, npos);
		vector<bool> flag(8, false);
		int min = npos;
		for (auto it = graph[_start].begin(); it != end(); it++)
			if (it->second < min) {
				min = it->second;
				ShortestRoute[it->first] = it->second;
			}
	}

	void CheckShortestRouteFromAllNode() {

	}

	~Dijkstra();
private:
	vector<map<int, map<int, int>>> _graph;
	int _start;
	//std::vector<map<int. int>> Routelist; // 下标表示对应节点，内容是一个map，键表示最短距离，值表示上一个节点是谁
	// 将下标和元素值对应起来，下标内存储的是最短距离
};
