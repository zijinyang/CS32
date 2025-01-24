#include <string>
#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence(){
    m_size = 0;
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
    
    if(m_size == DEFAULT_MAX_ITEMS){
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

    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++){
        ItemType temp = m_sequence[i];
        m_sequence[i] = other.m_sequence[i];
        other.m_sequence[i] = temp;
    }
}