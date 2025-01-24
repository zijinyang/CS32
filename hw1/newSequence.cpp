#include <string>
#include "newSequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence(){
    m_size = 0;
    m_maxSize = DEFAULT_MAX_ITEMS;
    m_sequence = new ItemType[DEFAULT_MAX_ITEMS];
}

Sequence::Sequence(int maxSize){
    if(maxSize < 0){
        cerr << "Cannot create a sequence with a negative maximum length" << endl;
        exit(1);
    }
    m_size = 0;
    m_maxSize = maxSize;
    m_sequence = new ItemType[maxSize];
}

Sequence::Sequence(const Sequence& other){
    this->m_size = other.m_size;
    this->m_maxSize = other.m_maxSize;
    this->m_sequence = new ItemType[this->m_maxSize];
    for(int i = 0; i < m_size; i++){
        this->m_sequence[i] = other.m_sequence[i];
    }
}

Sequence::~Sequence(){
    delete [] m_sequence;
}

Sequence& Sequence::operator=(const Sequence& other){
    if(this != &other){
        Sequence temp = other;
        this->swap(temp); 
    }
    return *this;
}

bool Sequence::empty() const{
    return m_size == 0;
}

int Sequence::size() const{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value){
    if(pos < 0 || pos > m_size){
        return -1;
    }
    
    if(m_size == m_maxSize){
        return -1;
    }

    for(int i = m_size; i > pos; i--){
        m_sequence[i] = m_sequence[i-1];
    }
    m_size++;
    m_sequence[pos] = value;
    return pos;
} 

int Sequence::insert(const ItemType& value){
    for(int i = 0; i < m_size; i++){
        if(value <= m_sequence[i]){
            return this->insert(i, value);
        }
    }
    return this->insert(m_size, value);
}

bool Sequence::erase(int pos){
    if(pos < 0 || pos > m_size){
        return false;
    }
    for(int i = pos; i < m_size; i++){
        m_sequence[i] = m_sequence[i+1];
    } 
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value){
    int numRemoved = 0;
    for(int i = 0; i < m_size; i++){
        if(m_sequence[i] == value){
            this->erase(i);
            numRemoved++;
        }
    }
    return numRemoved;
}

bool Sequence::get(int pos, ItemType& value) const{
    if(pos < 0 || pos > m_size){
        return false;
    }
    value = m_sequence[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value ){
    if(pos < 0 || pos > m_size){
        return false;
    }
    m_sequence[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const{
   for(int i = 0; i < m_size; i++){
        if(m_sequence[i] == value){
            return i;
        }
   } 
   return -1;
}

void Sequence::swap(Sequence& other){
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
    
    int tempMaxSize = m_maxSize;
    m_maxSize = other.m_maxSize;
    other.m_maxSize = tempMaxSize;
    
    ItemType* tempSequence = m_sequence;
    m_sequence  = other.m_sequence;
    other.m_sequence = tempSequence;
}