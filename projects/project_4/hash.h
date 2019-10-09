#include <vector>
#include <list>
#include <string>
using namespace std;

#ifndef hash_h
#define hash_h

class HashTable
{
public:
    HashTable();
    void insert(string subString, unsigned long offset);
    bool contains(string subString, unsigned long& offset) const;
    int findBestCopyIndex(const string & oldFile,const string& newFile, string subString, unsigned long& bestLength ,size_t initialIndex) const;
private:
    size_t m_size = 100003;
    struct Node
    {
        Node(string s, unsigned long o)
        : m_subString(s), m_offset(o)
        {}
        string m_subString;
        unsigned long m_offset;
    };
    vector<list<Node>> m_hash;
};

#endif
