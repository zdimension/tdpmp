#include <iostream>
#include <random>
#include "Tree.ipp"

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
    std::cout << tree.prettyPrint() << std::endl;
    std::cout << "Noeuds : " << tree.countNodes() << std::endl;
    std::cout << "Hauteur : " << tree.height() << std::endl;

    for (int i = 1; i <= 50; i++)
    {
        tree.remove(i);
        std::cout << "After remove " << i << " : " << tree << std::endl;
    }

    return 0;
}
