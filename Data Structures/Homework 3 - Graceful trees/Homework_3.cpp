#include <iostream>
#include "Uneven_Tree.h"
#include "Permutation_Generator.h"

/*
Structure: node <number of children>

"null" or nothing is file -> does not write in output file // Tree without a root. Use only when the tree has no root.
node 4 node 0 node 0 node 0 node 0 -> 9 4 7 0 5 0 3 0 1 0 // The tree from the first example. 9 is the root and has 4 children: 7, 5, 3, 1 which have 0 children.
node 1 node 1 node 2 node 1 node 0 node 0 -> 7 1 5 1 9 2 3 0 1 0  // The tree from the second example, but filled correctly.
*/

int main(int argc, char** argv)
{
    Uneven_Tree t;
    t.deserialize(argv[1]);

    if (t.size() == 0)
    {
        std::cout << "No tree was constructed.\n";
        return 0;
    }

    Permutation_Generator p(t.size());
    do
    {
        if (t.is_gracious(p.current()))
        {
            t.serialize("output.txt");

            std::cout << "Gracious tree successfully created!\n";
            return 0;
        }
    } while (p() != std::vector<unsigned>{});

    std::cout << "The tree is not gracious.\n";

    return 0;
}