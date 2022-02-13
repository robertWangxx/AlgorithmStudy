#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
using namespace std;


struct Node
{
	int i, j;
	int f, g, h;	// h:预估代价 g:当前代价    f = g + h
	Node* parent;

	bool operator<(const Node& node)
	{
		return f < node.f;
	}
};

struct NodeCmp
{
	bool operator()(Node*& left, Node*& right)
	{
		return left->f > right->f;
	}
};

static std::list<Node*> lst;
Node* createNode(int i, int j, int g, Node* pa, const std::pair<int, int>& end)
{
	Node* node = new Node;
	node->i = i;
	node->j = j;
	node->g = g;
	node->h = (abs(end.first - node->i) + abs(end.second - node->j)) * 10;
	node->f = node->g + node->h;
	node->parent = pa;

	lst.push_back(node);
	return node;
}

void destroyNodes()
{
	for (auto it : lst)
	{
		delete it;
	}
	lst.clear();
}

// A* 算法
std::list<std::pair<int, int>> Astar(std::pair<int, int> start, std::pair<int, int> end, const vector<vector<int>>& map)
{
	std::list<std::pair<int, int>> path;
	
	vector<vector<int>> visit = map;
	int row = map.size();
	if (row <= 0)
		return path;
	int col = map[0].size();
	std::priority_queue<Node*, std::vector<Node*>, NodeCmp> q;

	auto startNode = createNode(start.first, start.second, 0, nullptr, end);
	q.push(startNode);
	
	Node* endNode = nullptr;
	while (!q.empty())
	{
		auto node = q.top();
		q.pop();
		if (visit[node->i][node->j] == 1)
			continue;

		visit[node->i][node->j] = 1;
		if (node->i == end.first && node->j == end.second)
		{
			// 找到终点
			endNode = node;
			break;	
		}

		// 周围点
		int left = node->j - 1;
		int right = node->j + 1;
		int up = node->i - 1;
		int low = node->i + 1;

		// 左边
		if (left >= 0)
		{
			if (up >= 0 && visit[up][left] == 0)
			{
				auto n = createNode(up, left, node->g + 14, node, end);
				q.push(n);
			}
			if (visit[node->i][left] == 0)
			{
				auto n = createNode(node->i, left, node->g + 10, node, end);
				q.push(n);
			}
			if (low < row && visit[low][left] == 0)
			{
				auto n = createNode(low, left, node->g + 14, node, end);
				q.push(n);
			}
		}
		{
			if (up >= 0 && visit[up][node->j] == 0)
			{
				auto n = createNode(up, node->j, node->g + 10, node, end);
				q.push(n);
			}
			if (low < row && visit[low][node->j] == 0)
			{
				auto n = createNode(low, node->j, node->g + 10, node, end);
				q.push(n);
			}
		}
		// 右边
		if (right < col)
		{
			if (up >= 0 && visit[up][right] == 0)
			{
				auto n = createNode(up, right, node->g + 14, node, end);
				q.push(n);
			}
			if (visit[node->i][right] == 0)
			{
				auto n = createNode(node->i, right, node->g + 10, node, end);
				q.push(n);
			}
			if (low < row && visit[low][right] == 0)
			{
				auto n = createNode(low, right, node->g + 14, node, end);
				q.push(n);
			}
		}
	}

	if (endNode)
	{
		auto node = endNode;
		while (node)
		{
			path.push_front({ node->i, node->j });
			node = node->parent;
		}
	}

	destroyNodes();
	return path;
}

void testAstar()
{
	std::vector<std::vector<int>> maze = {
		{1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,1,1,0,1,0,0,0,0,1},
		{1,0,0,1,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,1,1,1},
		{1,1,1,0,0,0,0,0,1,1,0,1},
		{1,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,1,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1}
	};

	auto path = Astar({ 1, 1 }, { 6, 10 }, maze);
	for (auto& it : path)
	{
		printf("{%d, %d}\r\n", it.first, it.second);
	}
}

int main()
{
	testAstar();
	return 1;
}
