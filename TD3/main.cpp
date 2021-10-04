#include <iostream>
#include <random>
#include "Tree.ipp"

void truc(Tree<int> tree)
{

}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 50);

    Tree<int> tree{};
    for (int i = 0; i < 10; i++)
    {
        tree.add(dis(gen));
    }

    std::cout << tree << std::endl;
    std::cout << tree.pretty() << std::endl;
    truc(tree);

    std::cout << "Noeuds : " << tree.count_nodes() << std::endl;
    std::cout << "Hauteur : " << tree.height() << std::endl;

    for (int i = 1; i <= 50; i++)
    {
        tree.remove(i);
        std::cout << "After remove " << i << " : " << tree << std::endl;
    }

    Tree<char> tree2(
            Node<char>('A',
                     new Node<char>('B',
                                    new Node<char>('C',
                                                   new Node<char>('D'),
                                                   new Node<char>('E')),
                                    new Node<char>('F')),
                     new Node<char>('G',
                                    new Node<char>('H'),
                                    new Node<char>('I',
                                                   new Node<char>('J'),
                                                   new Node<char>('K')))));
    std::cout << tree2.pretty() << std::endl;
    auto x = tree2.root_node->iterate_left_hand();
    for(auto y : x)
        std::cout << y->get_value() << " ";
    std::cout << std::endl;

    return 0;
}
