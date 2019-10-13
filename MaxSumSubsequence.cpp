#include <iostream>

//  最大连续子序列和 算法
// 暴力求解 O(n^3)
int Sum1(int* head, int count)
{
	if (!head || count <= 0)
		return 0;
	int maxSum = head[0];
	for (int i = 0; i < count; ++i)
	{
		for (int j = i; j < count; ++j)
		{
			int curSum = 0;
			for (int k = i; k <= j; ++k)
			{
				curSum += head[k];
				if (curSum > maxSum)
					maxSum = curSum;
			}
		}
	}

	return maxSum;
}

// 暴力求解的优化 O(n^2)
int Sum2(int* head, int count)
{
	if (!head || count <= 0)
		return 0;
	int maxSum = head[0];
	for (int i = 0; i < count; ++i)
	{
		int curSum = 0;
		for (int j = i; j < count; ++j)
		{
			curSum += head[j];
			if (curSum > maxSum)
				maxSum = curSum;
		}
	}

	return maxSum;
}

// 分治法 O(nlogn)
int Sum3(int* head, int count)
{
	if (!head || count <= 0)
		return 0;

	if (count <= 1)
		return head[0];

	int size = count / 2;
	int leftMax = Sum3(head, size);	// 左最大子序列
	int rightMax = Sum3(&head[size], count - size);	// 右最大子序列

	// 跨越左右的最大子序列
	int left = head[size - 1];
	int curSum = 0;
	for (int i = size - 1; i >= 0; --i)
	{
		curSum += head[i];
		if (curSum > left)
			left = curSum;
	}
	int right = head[size];
	curSum = 0;
	for (int i = size; i < count; ++i)
	{
		curSum += head[i];
		if (curSum > right)
			right = curSum;
	}
	int middleMax = left + right;

	int maxSum = leftMax;
	if (maxSum < rightMax)
	{
		maxSum = rightMax;
	}
	if (maxSum < middleMax)
	{
		maxSum = middleMax;
	}

	return maxSum;
}

// 在线求解算法 O(n)
int Sum4(int* head, int count)
{
	if (!head || count <= 0)
		return 0;
	int maxSum = head[0];
	int curSum = 0;
	for (int i = 0; i < count; ++i)
	{
		curSum += head[i];
		if (curSum <= 0)
			curSum = 0;
		else if (curSum > maxSum)
			maxSum = curSum;
	}

	return maxSum;
}

int main()
{
	int test[10] = {10, -8, -2, -8, 15, 2, 6, -5, 8, -15};
	int sum = Sum3(test, 10);
	std::cout << sum << std::endl;
	return 0;
}
