//
// Created by Tom on 20/09/2021.
//

#ifndef TD3_TREE_IPP
#define TD3_TREE_IPP

#include "Node.ipp"
#include <iostream>

template<typename T>
struct pretty_print_s;

template<typename T>
class Tree final
{
public:
    Tree() = default;

    explicit Tree(Node<T>* rootNode):root_node(rootNode)
    {
    }

    ~Tree()
    {
        delete root_node;
    }

    void add(T value);

    void remove(T value);

    ssize_t height();

    ssize_t countNodes();

    pretty_print_s<T> prettyPrint()
    {
        return {*this};
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Tree<U>& tree);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const pretty_print_s<U>& tree);

public:
    Node<T>* root_node = nullptr;
};

template <typename U>
std::ostream& operator<<(std::ostream& os, const Tree<U>& tree)
{
    if (tree.root_node)
        os << *tree.root_node;
    else
        os << "[EMPTY TREE]";
    return os;
}

template<typename T>
struct pretty_print_s
{
    Tree<T>& ref;
};

template<typename U>
std::ostream& operator<<(std::ostream& os, const pretty_print_s<U>& tree)
{
    printBT(os, "", tree.ref.root_node, false);
    return os;
}

template<typename T>
void printBT(std::ostream& os, const std::string& prefix, const Node<T>* node, bool isLeft)
{
    os << prefix;
    os << (isLeft ? "├──" : "└──");

    if (node != nullptr)
    {
        os << node->getValue() << std::endl;
        if (node->getLeftChild() || node->getRightChild())
        {
            printBT(os, prefix + (isLeft ? "│   " : "    "), node->getLeftChild(), true);
            printBT(os, prefix + (isLeft ? "│   " : "    "), node->getRightChild(), false);
        }
    }
    else
    {
        os << std::endl;
    }
}

template<typename T>
ssize_t Tree<T>::height()
{
    if (root_node)
        return 1 + root_node->height();
    else
        return 0;
}

template<typename T>
ssize_t Tree<T>::countNodes()
{
    if (root_node)
        return root_node->countNodes();
    else
        return 0;
}

template<typename T>
void Tree<T>::add(T value)
{
    if (root_node == nullptr)
    {
        root_node = new Node<T>(value);
    }
    else
    {
        add_rec(value, root_node);
    }
}

template<typename T>
void Tree<T>::remove(T value)
{
    if (root_node != nullptr)
    {
        remove_rec(value, &root_node);
    }
}

template<typename T>
void add_rec(T value, Node<T>* node)
{
    if (value < node->getValue())
    {
        if (node->getLeftChild() == nullptr)
        {
            node->setLeftChild(new Node<T>(value));
        }
        else
        {
            add_rec(value, node->getLeftChild());
        }
    }
    else if (value > node->getValue())
    {
        if (node->getRightChild() == nullptr)
        {
            node->setRightChild(new Node<T>(value));
        }
        else
        {
            add_rec(value, node->getRightChild());
        }
    }
    else // node already in tree
    {
        return;
    }
}

template<typename T>
void remove_rec(T value, Node<T>** node)
{
    if ((*node)->value == value)
    {
        if ((*node)->left_child == nullptr && (*node)->right_child == nullptr)
        {
            delete *node;
            *node = nullptr;
        }
        else if ((*node)->left_child == nullptr)
        {
            Node<T>* temp = *node;
            *node = (*node)->right_child;
            temp->right_child = nullptr;
            delete temp;
        }
        else if ((*node)->right_child == nullptr)
        {
            Node<T>* temp = *node;
            *node = (*node)->left_child;
            temp->left_child = nullptr;
            delete temp;
        }
        else
        {
            Node<T>* temp = (*node)->right_child;
            while (temp->left_child != nullptr)
            {
                temp = temp->left_child;
            }
            (*node)->value = temp->value;
            remove_rec(temp->value, &(*node)->right_child);
        }
    }
    else if (value < (*node)->value && (*node)->left_child)
    {
        remove_rec(value, &(*node)->left_child);
    }
    else if (value > (*node)->value && (*node)->right_child)
    {
        remove_rec(value, &(*node)->right_child);
    }
}

template<typename T>
ssize_t Node<T>::countNodes()
{
    ssize_t result = 1;

    if (left_child)
        result += left_child->countNodes();

    if (right_child)
        result += right_child->countNodes();

    return result;
}

template<typename T>
Node<T>::Node(T value, Node<T>* leftChild, Node<T>* rightChild):value(value), left_child(leftChild),
                                                                right_child(rightChild)
{
}

#endif //TD3_TREE_IPP
