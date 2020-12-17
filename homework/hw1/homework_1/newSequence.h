#ifndef newSequence_h
#define newSequence_h

#include <string>
#include <iostream>

using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 250;

class Sequence
{
private:
    ItemType* m_arr;
    int m_size;
    int m_maxSize;
public:
    Sequence(int val = DEFAULT_MAX_ITEMS);//constructor
    Sequence(const Sequence& other);//copy constructor
    Sequence& operator = (const Sequence& other);//=operator overload
    ~Sequence();//deconstructor
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
//    void dump() const;
};

#endif
