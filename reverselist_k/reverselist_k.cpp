struct node
{
	int		ele = 0;
	node*	next = nullptr;
};

/*
单向链表(个数num)按k个元素反转，从后往前，至最前面几个元素不足k个则不反转
支持 num >= k
*/

// ex1: num:10 k:4
// 1 2 3 4 5 6 7 8 9 10
// 1 2 6 5 4 3 7 8 9 10
// 1 2 6 5 4 3 10 9 8 7

// ex1: num:12 k:4
// 1 2 3 4 5 6 7 8 9 10 11 12
// 4 3 2 1 5 6 7 8 9 10 11 12
// 4 3 2 1 8 7 6 5 9 10 11 12
// 4 3 2 1 8 7 6 5 12 11 10 9

void reverse_k(node* &head, int num, int k)
{
	int offset = num % k;
	int count = num / k;
	node* tmphead = head;
	node* tmpprev = nullptr;

	for (int i = 0; i < offset; ++i)
	{
		tmpprev = tmphead;
		tmphead = tmphead->next;
	}

	for (int i = 0; i < count; ++i)
	{
		int num = k;
		node* prev = tmpprev;
		node* cur = tmphead;
		node* nextnode = nullptr;
		// 循环反转链表
		while (cur && num-- > 0)
		{
			nextnode = cur->next;
			cur->next = prev;
			prev = cur;
			cur = nextnode;
		}
		// k个元素链表反转后处理
		if (0 == offset && 0 == i)
			head = prev;				// prev此时成为原来链表的tail  反转后原头节点可能变化
		if (tmpprev)
			tmpprev->next = prev;		// tmpprev指向原k个元素链表的tail节点
		if (tmphead)
			tmphead->next = cur;		// tmphead指向原k个元素链表的tail节点的下一节点
		tmpprev = tmphead;				//
		tmphead = cur;					//
	}

}

void reverselist_K()
{
	int n = 10;
	int k = 4;
	node* head = nullptr;

	node* last = nullptr;
	for (int i = 1; i <= n; ++i)
	{
		node* pnode = new node();
		if (pnode)
		{
			pnode->ele = i;

			if (last)
			{
				last->next = pnode;
			}
			last = pnode;

			if (i == 1)
			{
				head = pnode;
			}
		}
	}

	node* cur = head;
	while (cur)
	{
		std::cout << cur->ele << " ";
		cur = cur->next;
	}
	std::cout << std::endl;

	reverse_k(head, n, k);

	cur = head;
	while (cur)
	{
		std::cout << cur->ele << " ";
		cur = cur->next;
	}
	std::cout << std::endl;
}