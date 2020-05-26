#pragma once

#include <map>
#include <set>

using UINT32 = unsigned int;

class ConsistentHash
{
	ConsistentHash();
	~ConsistentHash();

	void	Init(const std::set<UINT32>& realNodeSet, const int virtualNodePerReal = 0);
	UINT32	getNode(const std::string& str);

	bool	addRealNode(const UINT32 index);
	bool	delRealNode(const UINT32 index);

private:
	int							m_virtualNodePerReal;			// ÿ����ʵ�ڵ��Ӧ������ڵ����
	std::set<UINT32>			m_realNodeSet;					// ��ʵ�ڵ��б�
	std::map<UINT32, UINT32>	m_allNodesMap;					// key:����ڵ��ϣֵ value:��ʵ�ڵ�index
};