#ifndef BSTSET_H
#define BSTSET_H

#include <iostream>

template <typename T>
class BSTSet {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;

        Node(const T& val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void destroy_tree(Node* node) {
        if (node) {
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }
    }

    Node* insert(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value < node->value)
            node->left = insert(node->left, value);
        else if (node->value < value)
            node->right = insert(node->right, value);
        else
            node->value = value; // Replace value if duplicate
        return node;
    }

    Node* find(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value < node->value)
            return find(node->left, value);
        else if (node->value < value)
            return find(node->right, value);
        return node;
    }

    Node* find_first_not_smaller(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value <= node->value) {
            Node* left_res = find_first_not_smaller(node->left, value);
            return left_res ? left_res : node;
        }
        return find_first_not_smaller(node->right, value);
    }

public:
    BSTSet() : root(nullptr) {}

    ~BSTSet() {
        destroy_tree(root);
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    class SetIterator {
    private:
        Node* current;

    public:
        SetIterator(Node* node) : current(node) {}

        const T* get_and_advance() {
            if (!current) return nullptr;
            const T* result = &current->value;
            current = current->right; // Move to the next larger value
            return result;
        }
    };

    SetIterator find(const T& value) const {
        return SetIterator(find(root, value));
    }

    SetIterator find_first_not_smaller(const T& value) const {
        return SetIterator(find_first_not_smaller(root, value));
    }
};

#endif // BSTSET_H
