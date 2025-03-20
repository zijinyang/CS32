#ifndef BSTSet_Included
#define BSTSet_Included

template <typename T>
class BSTSet
{
    private:
        struct Node
        {
            Node(T value, Node* parent): value(value), parent(parent), leftptr(nullptr), rightptr(nullptr) {}
            Node*& getParentReference() { return parent->leftptr == this ? parent->leftptr : parent->rightptr;}
            bool isLeaf() { return leftptr == nullptr && rightptr == nullptr;}
            T value;
            Node* leftptr;
            Node* rightptr;
            Node* parent;
        };

    public:
        //nested iterator class
        class SetIterator
        {
            private:
                Node* m_currentNode;
            public:
                SetIterator(): m_currentNode(nullptr){}
                SetIterator(Node* node): m_currentNode(node){}

                //not 100% sure if necessary, TODO
                SetIterator(const SetIterator& other): m_currentNode(other.m_currentNode){} 
                SetIterator operator=(const SetIterator& other);
    
                //default destructor should be ok
                const T* get_and_advance();
                Node* recursiveFindFirstGreater(const T& value, Node* current);
        };

        BSTSet(): m_root(nullptr){}
        ~BSTSet(){deleteRecursive(m_root);}

        void insert(const T& value);
        SetIterator find(const T& value) const {return SetIterator(findRecursive(value, m_root));}
        SetIterator find_first_not_smaller(const T& value) const;

    private:
        //helper methods
        void deleteRecursive(Node* root);
        Node* findRecursive(const T& value, Node* current) const;
        Node* findLocationToInsert(const T& value, Node* current);//should work, TODO check w/ chat
        Node* recursiveFindFirstNotSmaller(const T& value, Node* current) const;
        
        Node* m_root;
};

//should work, TODO check w/ chat
template <typename T>
void BSTSet<T>::deleteRecursive(Node* root)
{
    if (root == nullptr) 
        return;
    deleteRecursive(root->leftptr);
    deleteRecursive(root->rightptr);
    delete root;
}

template <typename T>
typename BSTSet<T>::Node* BSTSet<T>::findRecursive(const T& value, Node* current) const
{
    if(current->value == value)
        return current;

    if(current->value > value && current->leftptr != nullptr)
        return findRecursive(value, current->leftptr);

    if(current->value < value && current->rightptr != nullptr)
        return findRecursive(value, current->rightptr);
    
    return nullptr;
}

template <typename T>
void BSTSet<T>::insert(const T& value)
{
    if(m_root == nullptr)
    {
        m_root = new Node(value, nullptr);
        return;
    }
    Node* location = findLocationToInsert(value, m_root);
    if(location == nullptr)
    {
        // throw std::runtime_error("Insert Failed"); //dbg
    }
    if(location->value == value)
    {
        if(location->parent == nullptr)
        {            
            Node* newRoot = new Node(value, location->parent);            
            newRoot->leftptr = location->leftptr;
            newRoot->rightptr = location->rightptr;

            if (location->leftptr) location->leftptr->parent = newRoot;
            if (location->rightptr) location->rightptr->parent = newRoot;

            delete location;

            m_root = newRoot;
        }else
        {
            Node* newNode = new Node(value, location->parent);
            newNode->leftptr = location->leftptr;
            newNode->rightptr = location->rightptr;

            if (location->leftptr) location->leftptr->parent = newNode;
            if (location->rightptr) location->rightptr->parent = newNode;

            location->getParentReference() = newNode;
            delete location;
        }
        return;
    }
    if(location->value > value)
        location->leftptr = new Node(value, location);
    else
        location->rightptr = new Node(value, location);
}

template <typename T>
typename BSTSet<T>::Node* BSTSet<T>::findLocationToInsert(const T& value, Node* current)
{
    if(current->value == value || current->isLeaf())
        return current;
    if(current->value > value)
    {
        if(current->leftptr == nullptr)
            return current;
        else
            return findLocationToInsert(value, current->leftptr);
    }
    if(current->value < value)
    {
        if(current->rightptr == nullptr)
            return current;
        else
            return findLocationToInsert(value, current->rightptr);
    }
    return nullptr; //should never happen
}

template <typename T>
typename BSTSet<T>::SetIterator BSTSet<T>::find_first_not_smaller(const T& value) const
{
    if(m_root == nullptr) //empty tree, checked again in recursiveFindFirstNotSmaller
        return SetIterator();
    Node* location = recursiveFindFirstNotSmaller(value, m_root);
    return SetIterator(location);
}

template <typename T>
typename BSTSet<T>::Node* BSTSet<T>::recursiveFindFirstNotSmaller(const T& value, Node* current) const
{
    if(current == nullptr)
        return nullptr;
    if(current->value == value)
        return current;
    if(current->value > value)
    {
        if(current->leftptr == nullptr)
            return current;
        else
        {
            Node* temp = recursiveFindFirstNotSmaller(value, current->leftptr);
            if(temp == nullptr)
                return current;
            else
                return temp;
        }
    }
    
    if(current->value < value)
    {
        if(current->rightptr == nullptr)
            return nullptr;
        else
            return recursiveFindFirstNotSmaller(value, current->rightptr);
    }
    
    return nullptr; 
}

template <typename T>
const T* BSTSet<T>::SetIterator::get_and_advance()
{
    if (m_currentNode == nullptr)
        return nullptr;

    Node* temp = m_currentNode;
    
    if (m_currentNode->rightptr != nullptr)
    {
        m_currentNode = m_currentNode->rightptr;
        while (m_currentNode->leftptr != nullptr)
            m_currentNode = m_currentNode->leftptr;
    }
    else
    {
    while (m_currentNode->parent != nullptr && m_currentNode == m_currentNode->parent->rightptr)
            m_currentNode = m_currentNode->parent;
        m_currentNode = m_currentNode->parent;
    }

    return &temp->value;
}

template <typename T>
typename BSTSet<T>::Node* BSTSet<T>::SetIterator::recursiveFindFirstGreater(const T& value, Node* current)
{
    if(current == nullptr)
        return nullptr;
    if(current->value > value)
    {
        if(current->leftptr == nullptr)
            return current;
        else
        {
            Node* temp = recursiveFindFirstGreater(value, current->leftptr);
            if(temp == nullptr)
                return current;
            else
                return temp;
        }
    }
    
    if(current->value < value || current->value == value)
    {
        if(current->rightptr == nullptr)
            return nullptr;
        else
            return recursiveFindFirstGreater(value, current->rightptr);
    }
    
    return nullptr; 
}

#endif // BSTSet_Included