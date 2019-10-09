#include "hash.h"
#include <functional>
//#include <cassert>


HashTable::HashTable()
{
    m_hash.resize(m_size);
}

void HashTable::insert(string subString, unsigned long offset)
{
    size_t hashKey = std::hash<string>()(subString);
    size_t index = hashKey % (m_size - 1);
    Node nodeAtBucket(subString, offset);
    m_hash.at(index).push_back(nodeAtBucket);
}

bool HashTable::contains(string subString, unsigned long& offset) const
{
    size_t hashKey = std::hash<string>()(subString);
    size_t index = hashKey % (m_size - 1);
    size_t sizeLL = m_hash.at(index).size();
    if(sizeLL == 0)
    {
        return false;
    }
    // loop through list with iterators
    for(auto itLL = m_hash.at(index).begin(); itLL != m_hash.at(index).end(); itLL++)
    {
//        auto num1 = subString.size();
//        auto num2 = itLL->m_subString.size();
//        assert(num1 == num2);
        //check each value at the string
        if(subString == itLL->m_subString)
        {
            offset = itLL->m_offset;
            return true;
        }
    }
    // no strings matched in the list
    return false;
}

int HashTable::findBestCopyIndex(const string& oldFile,const string& newFile, string subString,
                        unsigned long &bestlen, size_t initialIndex) const
{
    int bestIndex = -1;
    bestlen = 0;
    auto subStringLength = subString.length();
    size_t hashkey = std::hash<string>()(subString);
    size_t index = hashkey % (m_size - 1);
    for(auto itLL = m_hash.at(index).begin();
        itLL != m_hash.at(index).end();
        itLL++)
    {
        if(itLL->m_subString == subString)
        {
            int consecutive = 0;
            while(itLL->m_offset + subStringLength + consecutive < oldFile.length() &&
                  initialIndex + subStringLength + consecutive < newFile.length())
            {
                if(oldFile[itLL->m_offset + subStringLength + consecutive] != newFile[initialIndex + subStringLength + consecutive])
                {
                    break;
                }
                consecutive++;
            }
            if(consecutive >= bestlen)
            {
                bestIndex = static_cast<int>(itLL->m_offset);
                bestlen = consecutive;
            }
        }
    }
//    assert(bestIndex != -1);
    bestlen = subStringLength + bestlen;
    return bestIndex;
}
