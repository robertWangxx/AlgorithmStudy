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
	int							m_virtualNodePerReal;			// 每个真实节点对应的虚拟节点个数
	std::set<UINT32>			m_realNodeSet;					// 真实节点列表
	std::map<UINT32, UINT32>	m_allNodesMap;					// key:虚拟节点哈希值 value:真实节点index
};