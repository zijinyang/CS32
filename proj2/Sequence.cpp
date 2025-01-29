#include "Sequence.h"
#include <iostream>

using namespace std;

Sequence::Sequence()
 : m_size(0), m_head(new node())
{
    m_tail = m_head;
}

Sequence::Sequence(const Sequence& other): Sequence() //start with this as empty list
{
    this->m_size = other.m_size;

    //loop starting before the first element of this and at first element of other
    node* currentOther = other.m_head->next;
    node* currentThis = this->m_head;

    /*
    add new node to end
    set previous
    set next 
    increment otherptr 
    */
    for(; currentOther != other.m_head; currentOther = currentOther->next){
        currentThis->next = new node(currentOther->value);
        currentThis->next->prev = currentThis;
        currentThis = currentThis->next;
    }

    //set tail to last node and connect the ends of the list 
    this->m_tail = currentThis;
    m_tail->next = this->m_head;
    m_head->prev = this->m_tail;
}

Sequence::~Sequence()
{
    //only dummy in empty list
    if(empty()){
        delete m_head;
        return;
    }
    //delete dummy and 1st node
    if(m_size == 1){
        delete m_head;
        delete m_tail;
        return;
    }

    //start at first node
    node* current = this->m_head->next;
    
    //delete previous node, first deleted is dummynode
    for(; current != m_tail; current = current->next){
        delete current->prev;
    }
    delete current->prev;
    delete m_tail;
}

Sequence& Sequence::operator=(const Sequence& other){
    if(&other != this){
        Sequence temp = other;
        swap(temp);
    }
    return *this;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0  ||  pos > size())
        return -1;
    node* current = m_head->next;
    for(int i = 0; i < pos; i++){
        current = current->next;
    }
    uncheckedInsert(current, value);
    return pos;
}

int Sequence::insert(const ItemType& value)
{
    int ind = 0;
    node* current = m_head->next;
    //stops at end of list or when value > element value
    for(;current != m_head && value > current->value ; current = current->next)
        ind++;
    uncheckedInsert(current, value);
    return ind;
}
     
bool Sequence::erase(int pos)
{
    if (pos < 0  ||  pos >= size())
        return false;
    node* current = m_head->next;

    for(int i = 0; i < pos; i++){
        current = current->next;
    }
    //set tail if tail is erased
    if(current == m_tail){
        m_tail = current->prev;
    }
    //connect prev and next of current
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current; 
    m_size--;

    return true;
}

int Sequence::remove(const ItemType& value)
{
    int count = 0;
    int ind = 0;
    node* current = m_head->next;
    for(; current != m_head;){
        //if value found call erase (don't increment ind)
        if(current->value == value){
           current = current->next;
           erase(ind); 
           count++;
        }else{
            current = current->next;
            ind++;
        }
    }
    return count;
}
     
bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0  ||  pos >= size())
        return false;
    node* current = m_head->next;
    for(int i = 0; i < pos; i++){
        current = current->next;
    }
    value = current->value;
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0  ||  pos >= size())
        return false;
    node* current = m_head->next;
    for(int i = 0; i < pos; i++){
        current = current->next;
    }
    current->value = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
    int ind = 0;
    node* current = m_head->next;
    for (; current != m_head; current = current->next){
        if (current->value == value)
            return ind;
        ind++;
    }
    return -1;
}

void Sequence::swap(Sequence& other)
{
    //swap head and taiil
    node* temp = m_head;
    this->m_head = other.m_head;
    other.m_head = temp;

    temp = m_tail;
    this->m_tail = other.m_tail;
    other.m_tail = temp; 

      // Swap sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

void Sequence::dump()
{
    if(empty()){
        cerr << "Sequence is Empty" << endl;
        return;
    }
    cerr << "Size: " << m_size << endl;
    node* current = m_head->next;

    for(; current != m_head; current = current->next){
        cerr << current->value << ", ";        
    }
    cerr << endl;
}

void Sequence::uncheckedInsert(node* current, const ItemType& value)
{
    //get ptr to pos in list
    node* newNode = new node(value);
    m_size++;

    //set next and prev of newNode
    newNode->next = current;
    newNode->prev = current->prev;
    //connect next and prev to newNode
    current->prev->next = newNode;
    current->prev = newNode;
    
    //update tail if added to end
    if(newNode->next == m_head){
        m_tail = newNode;
    }
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    //check if seq2 is empty
    if(seq2.empty())
        return -1;
    
    if(seq2.size() > seq1.size())
        return -1;

    ItemType s1;
    int i1 = 0;
    ItemType s2;
    int i2 = 0;

    int start = -1;

    while(i1 < seq1.size()){
        seq1.get(i1,s1);
        seq2.get(i2,s2);
        //if values are equal at indicies
        if(s1 == s2){
            //start of subsequence
            if(i2 == 0){
                start = i1;
            }
            //increment i2 and i1
            i1++;
            i2++;

        }else{ // if not equal
            //reset start of subsequence
            start = -1;
            //restart ptr on seq2;
            i2 = 0; 
            //only increment i1
            i1++;
        }
        //if i2 has iterated past last index
        if(i2 == seq2.size()){
            return start;
        }
    }

    return -1;
}

void zipper(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    //new sequence to write into
    Sequence output;
    //init loop as equal to seq1; 
    output = seq1;
    for(int i = 0; i < seq2.size(); i++){
        ItemType x;
        seq2.get(i, x);
        if(i*2 + 1 > output.size()){
            output.insert(output.size(), x); //insert at end if size is larger
        }else{
            output.insert(i*2 + 1, x); //insert element between elements in output
        }
    }
    
    result = output;
}