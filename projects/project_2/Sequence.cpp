
#include "Sequence.h"

#include <iostream>
using namespace std;

Sequence::Sequence()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->m_size = 0;
}

Sequence::Sequence(const Sequence& other)
{
    if(other.head == nullptr)
    {
        head = nullptr;
        tail = nullptr;
        m_size = 0;
        return;
    }
    
    this->head = nullptr;
    this->tail = nullptr;
    this->m_size = 0;
    
    int size = other.size();
    for(int i = 0; i < size; i++)
    {
        ItemType x;
        other.get(i, x);
        insert(i, x);
    }
}

Sequence& Sequence::operator= (const Sequence& other)
{
    // if they are the same return *this
    if (this == &other)
    {
        return *this;
    }
    //create a temp with other values
    //swap temp values with this values
    Sequence temp(other);
    this->swap(temp);
    return *this;
    
}

Sequence::~Sequence()
{
    if (!(empty()))
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

bool Sequence::empty() const
{
    if (head == nullptr && tail == nullptr && m_size == 0)
    {
        return true;
    }
    return false;
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert (int pos, const ItemType& value)
{
    if(pos > m_size || pos < 0)
    {
        return -1;
    }
    
    if( pos == 0 && head == nullptr) // initialize a new DLL
    {
        Node* newNode = new Node;
        newNode->data = value;
        head = newNode;
        tail = newNode;
        
        newNode->next = nullptr;
        newNode->prev = nullptr;
    }
    else if (pos == m_size) // insert at the end of a DLL
    {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
//        Node* move = head;
//        while (move->next != nullptr)
//        {
//            move = move->next;
//        }
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    else if(pos == 0 && head != nullptr) // insert at the beginging of a DLL
    {
        Node* newNode = new Node;
        newNode->data = value;
        
        newNode->next = head;
        newNode->prev = nullptr;
        
        head->prev = newNode;
        head = newNode;
    }
    else if (pos > 0 && pos < m_size) // insert inside the DLL
    {
        Node* newNode = new Node;
        newNode->data = value;
        
        int count = 0;
        Node* move = head;
        while (count != pos) //loop until move is at the pos
        {
            move = move->next;
            count++;
        }
        newNode->next = move;
        newNode->prev = move->prev;
        move->prev->next = newNode;
        move->prev = newNode;
    }
    m_size++;
    return pos;
}

int Sequence::insert (const ItemType& value)
{
    Node* move = head;
    int pos = 0;

    //if empty list add at the begining
    if (head == nullptr && m_size == 0)
    {
        return (insert(0, value));
    }
    //if list is not empty loop through and find the first instance where value <= an item
    while(move != nullptr)
    {
        if(value <= move->data)
        {
            break;
        }
        pos++;
        move = move->next;
    }

    insert(pos, value);
    return pos;
}

bool Sequence::erase (int pos)
{
    if(head == nullptr || tail == nullptr || pos >= m_size || pos < 0 || m_size == 0)
    {
        return false;
    }

    if(pos == 0 && m_size == 1)//deleting the only head
    {
        Node* temp = head;
        head = nullptr;
        tail = nullptr;
        delete temp;
        m_size--;
        return true;
    }
    else if(pos == 0 && m_size != 0) // deleting the head ptr
    {
        Node* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
        m_size--;
        return true;
    }
    else if(pos == (m_size - 1) && m_size != 0) // deleting the tail ptr
    {
        Node* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        m_size--;
        return true;
    }

    //delete in middle

    Node* move = head;
    int count = 0;
    while (count != pos)
    {
        move = move->next;
        count++;
    }
    move->prev->next = move->next;
    move->next->prev = move->prev;
    delete move;
    m_size--;
    return true;
}

int Sequence::remove (const ItemType& value)
{
    int count = 0;
    while(find(value) != -1)
    {
        erase(find(value));
        count++;
    }
    return count;
}

bool Sequence::get (int pos, ItemType& value) const
{
    if (pos < 0 || pos >= m_size)
    {
        return false;
    }
    int count;
    Node* move = head;
    for (count = 0; count != pos; count++)
    {
        move = move->next;
    }

    value = move->data;
    return true;
}

bool Sequence::set (int pos, const ItemType& value)
{
    if (pos < 0 || pos >= m_size|| head == nullptr)
    {
        return false;
    }

    Node* move = head;
    int count = 0;
    while (count != pos)
    {
        move = move->next;
        count++;
    }
    move->data = value;
    return true;
}

int Sequence::find (const ItemType& value) const
{
    //if empty return -1
    if (head == nullptr)
    {
        return -1;
    }

    Node* move = head;
    int pos = 0;

    while (move != nullptr)
    {
        if (move->data == value)
        {
            break;
        }
        move = move->next;
        pos++;
    }

    if (pos == m_size)
    {
        return -1;
    }
    return pos;
}

void Sequence::swap (Sequence& other)
{
    //swap head
    Node* tempH = head;
    head = other.head;
    other.head = tempH;

    //swap tail
    Node* tempT = tail;
    tail = other.tail;
    other.tail = tempT;

    //swap size
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

//void Sequence::dump() const
//{
//    Node *p;
//
//    cerr << "forwards" << endl;
//    p = head;
//    while (p != nullptr)
//    {
//        cerr << p->data << ":";
//        p = p->next;
//    }
//    cerr << endl;
//
//    cerr << "backwards" << endl;
//    p = tail;
//    while (p != nullptr)
//    {
//        cerr << p->data << ":";
//        p = p->prev;
//    }
//    cerr << endl;
//}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if(seq2.size() > seq1.size() || seq1.empty() || seq2.empty())
    {
        return -1;
    }
    ItemType val1;
    ItemType val2;
    for(int i = 0; i < seq1.size(); i++)
    {
        // if the size of seq1 - size of seq2 - the pos you are at in seq1 is less than 0 return -1
        if ((seq1.size() - seq2.size() - i) < 0)
        {
            break;
        }
        seq1.get(i,val1);
        seq2.get(0,val2);
        //if a value of seq 1 == value of seq2 then loop through seq to check if they match
        if(val1 == val2)
        {
            for(int k = 0; k < seq2.size(); k++)
            {
                seq1.get(i + k , val1);
                seq2.get(k , val2);

                if(val1 != val2)
                {
                    break;
                }
                else if(k == seq2.size() - 1)
                {
                    return i;
                }

            }
        }
    }
    return -1;

}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    // seq1 is empty return seq 2
    if(seq1.empty())
    {
        result = seq2;
        return;
    }
    // if seq2 is empty and seq1 is not
    else if(seq2.empty())
    {
        result = seq1;
        return;
    }
    
    int size = seq1.size() + seq2.size();
    Sequence temp;
    ItemType val;
    
    int pos = 0;
    for(int i = 0; i < size; i++)
    {
        if(seq1.get(i, val))
        {
            temp.insert(pos, val);
            pos++;
        }
        if(seq2.get(i, val))
        {
            temp.insert(pos, val);
            pos++;
            
        }
    }
    result = temp;
}
