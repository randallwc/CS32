 #include "newSequence.h"

Sequence::Sequence(int val)
{
    if (val < 0)
    {
        exit(1);
    }
    m_arr = new ItemType[val];
    m_size = 0;
    m_maxSize = val;
}

Sequence::Sequence(const Sequence& other)
{
    m_maxSize = other.m_maxSize;
    m_size = other.m_size;
    
    m_arr = new ItemType[m_maxSize];
    for(int i = 0; i < other.m_size; i++)
    {
        m_arr[i] = other.m_arr[i];
    }
}

Sequence& Sequence::operator= (const Sequence& other)
{
    if (this == &other)
    {
        return *this;
    }
    
    delete [] m_arr;
    
    m_maxSize = other.m_maxSize;
    m_size = other.m_size;
    
    m_arr = new ItemType[other.m_maxSize];
    for(int i = 0; i < other.m_size; i++)
    {
        m_arr[i] = other.m_arr[i];
    }
    
    return *this;
}

Sequence::~Sequence()
{
    delete [] m_arr;
}

bool Sequence::empty() const
{
    if (m_size == 0)
    {
        return true;
    }
    return false;
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0 || pos > this->size())
    {
        return -1;
    }
    
    for(int i = this->size(); i > pos; i--)
    {
        m_arr[i] = m_arr[i-1];
    }
    
    m_arr[pos] = value;
    m_size++;
    return pos;
}

int Sequence::insert(const ItemType& value)
{
    if (this->size() >= m_maxSize)
    {
        return -1;
    }
    
    int pos = 0;
    for(int i = 0; i < this->size(); i++)
    {
        if(value <= m_arr[i])
        {
            break;
        }
        pos++;
    }
    
    //now we have pos
    //pos points to where the <= value is at
    
    for(int i = this->size(); i > pos; i--)
    {
        m_arr[i] = m_arr[i-1];
    }
    
    m_arr[pos] = value;
    m_size++;
    
    return pos;
}

bool Sequence::erase(int pos)
{
    if (pos < 0 || pos >= this->size())
    {
        return false;
    }
    
    for(int i = pos; i < this->size()-1 ; i++)
    {
        m_arr[i] = m_arr[i+1];
    }
    
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value)
{
    int count = 0;
    while(this->find(value) != -1)
    {
        this->erase(this->find(value));
        count++;
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos >= this->size())
    {
        return false;
    }
    
    value = m_arr[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos >= this->size())
    {
        return false;
    }
    
    m_arr[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
    for (int i = 0; i < this->size(); i++)
    {
        if (m_arr[i] == value)
        {
            return i;
        }
    }
    return -1;
}

void Sequence::swap(Sequence& other)
{
    int tempSize;
    tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
    
    int tempMaxSize;
    tempMaxSize = m_maxSize;
    m_maxSize = other.m_maxSize;
    other.m_maxSize = tempMaxSize;
    
    ItemType * tempPtr;
    tempPtr = m_arr;
    m_arr = other.m_arr;
    other.m_arr = tempPtr;
}

//void Sequence::dump() const
//{
//    for (int i = 0; i < m_size; i++)
//    {
//        std::cerr << m_arr[i] << ":";
//    }
//    std::cerr << std::endl;
//}
