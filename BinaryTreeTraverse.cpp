#include <iostream>
#include <memory.h>
#include <stack>
#include <deque>

typedef struct BinaryTreeNode
{
	int value;
	BinaryTreeNode* lChild;
	BinaryTreeNode* rChild;

	BinaryTreeNode() { memset(this, 0, sizeof(*this)); }
} BTreeNode;

BTreeNode* CreateTree()
{
	BTreeNode* node = new(std::nothrow) BTreeNode[11];
	if (!node)
		return nullptr;

	for (int i = 0; i < 11; ++i)
		node[i].value = i + 1;

	node[0].lChild = &(node[1]);
	node[0].rChild = &(node[2]);
	node[1].lChild = &(node[3]);
	node[2].lChild = &(node[4]);
	node[2].rChild = &(node[5]);
	node[3].rChild = &(node[6]);
	node[4].lChild = &(node[7]);
	node[4].rChild = &(node[8]);
	node[5].lChild = &(node[9]);
	node[7].lChild = &(node[10]);

	return node;
}

void MidTraverse(BTreeNode* root)
{
	if (!root)
		return;

	std::stack<BTreeNode*> s;
	BTreeNode* tmp = root;

	while (tmp || !s.empty())
	{
		if (tmp)
		{
			s.push(tmp);
			tmp = tmp->lChild;
		}
		else
		{
			tmp = s.top();
			s.pop();
			std::cout << tmp->value << std::endl;
			tmp = tmp->rChild;
		}
	}
}

void PreTraverse(BTreeNode* root)
{
	if (!root)
		return;

	std::stack<BTreeNode*> s;
	BTreeNode* tmp = root;

	while (tmp || !s.empty())
	{
		if (tmp)
		{
			std::cout << tmp->value << std::endl;
			s.push(tmp);
			tmp = tmp->lChild;
		}
		else
		{
			tmp = s.top();
			s.pop();
			tmp = tmp->rChild;
		}
	}
}

// 层序 使用队列
void SeqTraverse(BTreeNode* root)
{
	if (!root)
		return;
	std::deque<BTreeNode *> q;
	q.push_back(root);

	while (!q.empty())
	{
		BTreeNode *node = q.front();
		if (node)
		{
			std::cout << node->value << std::endl;
			q.push_back(node->lChild);
			q.push_back(node->rChild);
		}
		q.pop_front();
	}
}

int main()
{
	BTreeNode* root = CreateTree();
	if (!root)
		return 0;

	//PreTraverse(root);
	//MidTraverse(root);
	SeqTraverse(root);

	delete []root;
	return 0;
}


