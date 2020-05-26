#include "consistent_hash.h"
#include "murmurhash2.h"
#include <sstream>


ConsistentHash::ConsistentHash() :m_virtualNodePerReal(100)
{

}
ConsistentHash::~ConsistentHash()
{

}

void ConsistentHash::Init(const std::set<UINT32>& realNodeSet, const int virtualNodePerReal)
{
	if (virtualNodePerReal < 1 || virtualNodePerReal > 10000)
		return;
	m_realNodeSet = realNodeSet;
	m_virtualNodePerReal = virtualNodePerReal;
	for (auto node : m_realNodeSet)
	{
		for (int i = 0; i < m_virtualNodePerReal; ++i)
		{
			std::stringstream ss;
			ss << "HASHNODE" << node << "VIRTUAL" << i;
			UINT32 hashkey = murMurHash(ss.str().c_str(), ss.str().length());
			m_allNodesMap[hashkey] = node;
		}
	}
}

UINT32 ConsistentHash::getNode(const std::string& str)
{
	UINT32 hashkey = murMurHash(str.c_str(), str.length());
	auto it = m_allNodesMap.lower_bound(hashkey);
	if (it == m_allNodesMap.end())
	{
		if (!m_allNodesMap.empty())
			return m_allNodesMap.begin()->second;
		else
			return 0;
	}
	else
		return it->second;
}

bool ConsistentHash::addRealNode(const UINT32 index)
{
	auto it = m_realNodeSet.find(index);
	if (it != m_realNodeSet.end())
		return false;
	m_realNodeSet.insert(index);
	for (int i = 0; i < m_virtualNodePerReal; ++i)
	{
		std::stringstream ss;
		ss << "HASHNODE" << index << "VIRTUAL" << i;
		UINT32 hashkey = murMurHash(ss.str().c_str(), ss.str().length());
		m_allNodesMap[hashkey] = index;
	}
	return true;
}

bool ConsistentHash::delRealNode(const UINT32 index)
{
	auto it = m_realNodeSet.find(index);
	if (it == m_realNodeSet.end())
		return false;
	m_realNodeSet.erase(it);
	for (int i = 0; i < m_virtualNodePerReal; ++i)
	{
		std::stringstream ss;
		ss << "HASHNODE" << index << "VIRTUAL" << i;
		UINT32 hashkey = murMurHash(ss.str().c_str(), ss.str().length());
		m_allNodesMap.erase(hashkey);
	}
	return true;
}