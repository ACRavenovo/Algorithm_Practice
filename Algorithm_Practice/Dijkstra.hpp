#include <iostream>
#include <deque>
#include <vector>
#include <map>
static size_t npos = -1;
using namespace std;


// �ȵ���һ��ͼ�ṹ�� �������ܿ�ʼ����
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
	// �±꣺�ڵ��� ���ݣ����ڽڵ㣬 �±�ڵ㵽������ڽڵ�ľ���
};

// ���ҵ���ǰ�ڵ�����·��������·����С���������ڽڵ��·����С

class Dijkstra {
public:
	// ���ĸ��ڵ����ĸ�ͼ�������·��
	// Dijkstra(graph, 0);
	Dijkstra(std::vector<map<int, map<int, int>>> graph, int start)
		:_graph(graph), _start(start)
	{}

	// ������0�����ڽڵ�����·����Ȼ��ȷ�����·�����յ�Ϊ0���Լ����Լ���̣���������յ㿪ʼ��������һ�����ڽڵ�����·��
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
	//std::vector<map<int. int>> Routelist; // �±��ʾ��Ӧ�ڵ㣬������һ��map������ʾ��̾��룬ֵ��ʾ��һ���ڵ���˭
	// ���±��Ԫ��ֵ��Ӧ�������±��ڴ洢������̾���
};
