//
// Created by Tom on 20/09/2021.
//

#ifndef TD3_NODE_IPP
#define TD3_NODE_IPP


#include <vector>
#include <ostream>

template <typename T>
class Node final
{
public:
    explicit Node(T value):value(value)
    {

    }

    Node(const Node& node) :
            value(node.value),
            left_child(node.left_child),
            right_child(node.right_child)
    {

    }

    void remove_all_children()
    {
        remove_child(&this->left_child);
        remove_child(&this->right_child);
    }

    std::vector<Node<T>> iterate_left_hand()
    {
        std::vector<Node<T>> res{this};

        if (left_child != nullptr)
        {
            auto left = left_child->iterate_left_hand();
            res.reserve(res.size() + left.size());
            res.insert(res.end(), left.begin(), left.end());
        }

        return res;
    }

    T getValue() const
    {
        return value;
    }

    void setValue(T value)
    {
        Node::value = value;
    }

    Node<T>* getLeftChild() const
    {
        return left_child;
    }

    void setLeftChild(Node<T>* leftChild)
    {
        left_child = leftChild;
    }

    Node<T>* getRightChild() const
    {
        return right_child;
    }

    void setRightChild(Node<T>* rightChild)
    {
        right_child = rightChild;
    }

    ~Node()
    {
        delete left_child;
        delete right_child;
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Node<U>& node);

    template<typename U>
    friend void remove_rec(U value, Node<U>** node);

private:
    T value;
    Node<T>* left_child = nullptr;
    Node<T>* right_child = nullptr;
};

template<typename T>
void remove_child(Node<T>** pointer)
{
    if (*pointer != nullptr)
    {
        (*pointer)->remove_all_children();
        delete *pointer;
        *pointer = nullptr;
    }
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Node<U>& node)
{
    os << node.getValue();
    os << "(";
    if (node.getLeftChild() != nullptr)
    {
        os << *node.getLeftChild();
    }
    os << ")(";
    if (node.getRightChild() != nullptr)
    {
        os << *node.getRightChild();
    }
    os << ")";
    return os;
}

#endif //TD3_NODE_IPP
