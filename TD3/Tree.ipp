//
// Created by Tom on 20/09/2021.
//

#ifndef TD3_TREE_IPP
#define TD3_TREE_IPP

#include "Node.ipp"
#include <iostream>

/**
 * Container for pretty-print std::ostream handler
 * @tparam T value type
 */
template<typename T>
struct pretty_print_s;

/**
 * Binary tree with BST operations.
 * @tparam T value type
 */
template<typename T>
class Tree final
{
public:
    Tree() = delete;

    explicit Tree(Node<T> rootNode) : root_node(rootNode)
    {
    }

    Tree(const Tree& tree) : Tree(tree.root_node)
    {
    }

    /**
     * Adds a value to the binary search tree.
     * @tparam T value type
     * @param value value to add
     */
    void add(T value);

    /**
     * Removes a value from the binary search tree.
     * @tparam T value type
     * @param value value to remove
     */
    void remove(T value);

    /**
     * @return the height of the root node, i.e. the largest number of edges between the root and the deepest leaf node
     */
    ssize_t height();

    /**
     * @return the total number of nodes in the tree
     */
    ssize_t count_nodes();

    /**
     * Prints the tree in horizontal tree notation.
     *
     * Usage: std::cout << tree.pretty() << std::endl
     *
     * Example output:
     * └──26
     *     ├──23
     *     │   ├──16
     *     │   │   ├──7
     *     │   │   └──20
     *     │   └──
     *     └──49
     *         ├──42
     *         │   ├──40
     *         │   └──44
     *         └──
     * @tparam U value type
     * @param os output stream
     * @param tree tree
     * @return output stream
     */
    pretty_print_s<T> pretty()
    {
        return {*this};
    }

    /**
     * Prints the tree in linear notation.
     *
     * Example:
     * └──26
     *     ├──23
     *     │   ├──16
     *     │   │   ├──7
     *     │   │   └──20
     *     │   └──
     *     └──49
     *         ├──42
     *         │   ├──40
     *         │   └──44
     *         └──
     * is printed as: 26(23(16(7()())(20()()))())(49(42(40()())(44()()))())
     * @tparam U value type
     * @param os output stream
     * @param tree tree
     * @return output stream
     */
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Tree<U>& tree);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const pretty_print_s<U>& tree);

public:
    Node<T> root_node;
};

template<typename U>
std::ostream& operator<<(std::ostream& os, const Tree<U>& tree)
{
    return os << tree.root_node;
}

template<typename T>
struct pretty_print_s
{
    Tree<T>& ref;
};

template<typename U>
std::ostream& operator<<(std::ostream& os, const pretty_print_s<U>& tree)
{
    pretty_print(os, "", &tree.ref.root_node, false);
    return os;
}

template<typename T>
void pretty_print(std::ostream& os, const std::string& prefix, const Node<T>* node, bool isLeft)
{
    os << prefix;
    os << (isLeft ? "├──" : "└──");

    if (node != nullptr)
    {
        os << node->get_value() << std::endl;
        if (node->get_left_child() || node->get_right_child())
        {
            pretty_print(os, prefix + (isLeft ? "│   " : "    "), node->get_left_child(), true);
            pretty_print(os, prefix + (isLeft ? "│   " : "    "), node->get_right_child(), false);
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
    return 1 + root_node.height();
}

template<typename T>
ssize_t Tree<T>::count_nodes()
{
    return root_node.count_nodes();
}

template<typename T>
void Tree<T>::add(T value)
{
    add_rec(value, &root_node);
}

template<typename T>
void Tree<T>::remove(T value)
{
    remove_rec(value, &root_node.left_child);
    remove_rec(value, &root_node.right_child);
}

template<typename T>
void add_rec(T value, Node<T>* node)
{
    if (value < node->get_value())
    {
        if (node->get_left_child() == nullptr)
        {
            node->set_left_child(new Node<T>(value));
        }
        else
        {
            add_rec(value, node->get_left_child());
        }
    }
    else if (value > node->get_value())
    {
        if (node->get_right_child() == nullptr)
        {
            node->set_right_child(new Node<T>(value));
        }
        else
        {
            add_rec(value, node->get_right_child());
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
    if (*node == nullptr)
    {
        return;
    }

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
