//
// Created by Tom on 20/09/2021.
//

#ifndef TD3_NODE_IPP
#define TD3_NODE_IPP


#include <vector>
#include <ostream>
#include <stack>

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

    Node(T value, Node<T>* leftChild, Node<T>* rightChild);

    void remove_all_children();

    std::vector<Node<T>*> iterate_left_hand();

    T getValue() const
    {
        return value;
    }

    void setValue(T val)
    {
        Node::value = val;
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

    ssize_t height();

    ssize_t countNodes();

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Node<U>& node);

    template<typename U>
    friend void remove_rec(U value, Node<U>** node);

private:
    T value;
    Node<T>* left_child = nullptr;
    Node<T>* right_child = nullptr;
};

template <typename T>
void Node<T>::remove_all_children()
{
    remove_child(&this->left_child);
    remove_child(&this->right_child);
}

template <typename T>
ssize_t Node<T>::height()
{
    if (left_child && right_child)
        return std::max(left_child->height(), right_child->height()) + 1;
    else if (left_child)
        return left_child->height() + 1;
    else if (right_child)
        return right_child->height() + 1;
    else
        return 0;
}

template <typename T>
std::vector<Node<T>*> Node<T>::iterate_left_hand()
{
    std::vector<Node<T>*> vec{};

    std::stack<Node<T>*> s;
    Node<T>* curr = this;

    while (curr != nullptr || !s.empty())
    {
        while (curr != nullptr)
        {
            s.push(curr);
            curr = curr->getLeftChild();
        }
        curr = s.top();
        s.pop();
        vec.push_back(curr);
        curr = curr->getRightChild();
    }

    return vec;
}

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
