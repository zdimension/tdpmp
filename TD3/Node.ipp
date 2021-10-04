//
// Created by Tom on 20/09/2021.
//

#ifndef TD3_NODE_IPP
#define TD3_NODE_IPP


#include <vector>
#include <ostream>
#include <stack>

/**
 * Binary tree node.
 * @tparam T value type
 */
template<typename T>
class Node final
{
public:
    explicit Node(T value) : value(value)
    {
    }

    Node(const Node& node) :
            value(node.value),
            left_child(copy(node.left_child)),
            right_child(copy(node.right_child))
    {
    }

    Node(T value, Node<T>* leftChild, Node<T>* rightChild);

    /**
     * Removes all children from the node.
     */
    void remove_all_children();

    /**
     * Performs an in-order traversal of the tree.
     * @return nodes, in order of traversal
     */
    std::vector<Node<T>*> iterate_left_hand();

    T get_value() const
    {
        return value;
    }

    void set_value(T val)
    {
        Node::value = val;
    }

    Node<T>* get_left_child() const
    {
        return left_child;
    }

    void set_left_child(Node<T>* leftChild)
    {
        left_child = leftChild;
    }

    Node<T>* get_right_child() const
    {
        return right_child;
    }

    void set_right_child(Node<T>* rightChild)
    {
        right_child = rightChild;
    }

    ~Node()
    {
        delete left_child;
        delete right_child;
    }

    /**
     * @return the height of the node, i.e. the largest number of edges between the node and the deepest child node
     */
    ssize_t height();

    /**
     * @return the total number of nodes in the subtree
     */
    ssize_t count_nodes();

    /**
     * @see std::ostream& operator<<(std::ostream& os, const Tree<U>& tree)
     */
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Node<U>& node);

    static Node<T>* copy(Node<T>* ptr)
    {
        if (ptr == nullptr)
            return nullptr;
        return new Node<T>(*ptr);
    }

private:
    template<typename U>
    friend void remove_rec(U value, Node<U>** node);

    T value;
    Node<T>* left_child = nullptr;
    Node<T>* right_child = nullptr;
};

template<typename T>
void Node<T>::remove_all_children()
{
    remove_child(&this->left_child);
    remove_child(&this->right_child);
}

template<typename T>
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

template<typename T>
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
            curr = curr->get_left_child();
        }
        curr = s.top();
        s.pop();
        vec.push_back(curr);
        curr = curr->get_right_child();
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
    os << node.get_value();
    os << "(";
    if (node.get_left_child() != nullptr)
    {
        os << *node.get_left_child();
    }
    os << ")(";
    if (node.get_right_child() != nullptr)
    {
        os << *node.get_right_child();
    }
    os << ")";
    return os;
}

template<typename T>
ssize_t Node<T>::count_nodes()
{
    ssize_t result = 1;

    if (left_child)
        result += left_child->count_nodes();

    if (right_child)
        result += right_child->count_nodes();

    return result;
}

template<typename T>
Node<T>::Node(T value, Node<T>* leftChild, Node<T>* rightChild):value(value), left_child(leftChild),
                                                                right_child(rightChild)
{
}

#endif //TD3_NODE_IPP
