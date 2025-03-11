#include<iostream> //dbg

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
                T getVal() const {return m_currentNode->value;}
        };

        BSTSet(): m_root(nullptr){}
        ~BSTSet(){deleteRecursive(m_root);}

        void insert(const T& value);
        SetIterator find(const T& value){return SetIterator(findRecursive(value, m_root));}
        SetIterator find_first_not_smaller(const T& value);

    private:
        //helper methods
        void deleteRecursive(Node* root);
        Node* findRecursive(const T& value, Node* current);
        Node* findLocationToInsert(const T& value, Node* current);//should work, TODO check w/ chat
        Node* recursiveFindFirstNotSmaller(const T& value, Node* current);
        
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
typename BSTSet<T>::Node* BSTSet<T>::findRecursive(const T& value, Node* current)
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
        throw std::runtime_error("Insert Failed"); //dbg
    }
    if(location->value == value)
    {
        location->getParentReference() = new Node(value, location->parent);
        delete location;
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
typename BSTSet<T>::Node* BSTSet<T>::recursiveFindFirstNotSmaller(const T& value, Node* current)
{
    if(current->isLeaf)
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
    
    if(current < value)
    {
        if(current->rightptr == nullptr)
            return nullptr;
        else
            return recursiveFindFirstNotSmaller(value, current->rightptr);
    }
}