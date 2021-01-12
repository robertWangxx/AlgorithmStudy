#include <stack>
#include <queue>


class stack2queue
{
public:
	void	push(int i);
	void	pop();
	bool	empty();
	int		front();
	int		back();
private:
	std::stack<int> s1;		// 入栈
	std::stack<int> s2;		// 出栈
};

void stack2queue::push(int i)
{
	s1.push(i);
}

void stack2queue::pop()
{
	if (empty())
		return;

	// 出栈为空 把入栈元素弹出并压入出栈
	if (s2.empty())
	{
		while (!s1.empty())
		{
			s2.push(s1.top());
			s1.pop();
		}
	}

	if (!s2.empty())
	{
		int a = s2.top();
		s2.pop();
	}
}

int	stack2queue::front()
{
	// 出栈为空 把入栈元素弹出并压入出栈
	if (s2.empty())
	{
		while (!s1.empty())
		{
			s2.push(s1.top());
			s1.pop();
		}
	}

	if (!s2.empty())
		return s2.top();
	else
		return -111;
}

int	stack2queue::back()
{
	// 入栈为空 把出栈元素弹出并压入入栈
	if (s1.empty())
	{
		while (!s2.empty())
		{
			s1.push(s2.top());
			s2.pop();
		}
	}

	if (!s1.empty())
		return s1.top();
	else
		return -111;
}

bool stack2queue::empty()
{
	return (s1.empty() && s2.empty());
}


class queue2stack
{
public:
	void	push(int i);
	void	pop();
	bool	empty();
	int		top();
private:
	// 有一个队列必为空 作为备用
	std::queue<int> q1;
	std::queue<int> q2;
};

void queue2stack::push(int i)
{
	if (q1.empty() && q2.empty())
	{
		q1.push(i);
	}
	else if (!q1.empty())
	{
		q1.push(i);
	}
	else
	{
		q2.push(i);
	}
}

void queue2stack::pop()
{
	if (q1.empty() && q2.empty())
	{
		return;
	}
	else if (!q1.empty())
	{
		while (!q1.empty())
		{
			int a = q1.front();
			q1.pop();
			if (q1.empty())
			{
				return;
			}
			else
			{
				q2.push(a);
			}
		}
	}
	else
	{
		while (!q2.empty())
		{
			int a = q2.front();
			q2.pop();
			if (q2.empty())
			{
				return;
			}
			else
			{
				q1.push(a);
			}
		}
	}
}

bool queue2stack::empty()
{
	return (q1.empty() && q2.empty());
}

int	queue2stack::top()
{
	if (q1.empty() && q2.empty())
	{
		return -111;
	}
	else if (!q1.empty())
	{
		q1.back();
	}
	else
	{
		q2.back();
	}
}