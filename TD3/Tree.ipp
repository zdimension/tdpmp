//
// Created by Tom on 20/09/2021.
//

#ifndef TD3_TREE_IPP
#define TD3_TREE_IPP

#include "Node.ipp"

template <typename T>
class Tree final
{
public:
    ~Tree()
    {
        delete root_node;
    }

    void add(T value)
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

    void remove(T value)
    {
        if (root_node != nullptr)
        {
            remove_rec(value, &root_node);
        }
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Tree<U>& tree)
    {
        if (tree.root_node)
            os << *tree.root_node;
        else
            os << "[EMPTY TREE]";
        return os;
    }
private:
    Node<T>* root_node = nullptr;
};

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
    else
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

#endif //TD3_TREE_IPP
