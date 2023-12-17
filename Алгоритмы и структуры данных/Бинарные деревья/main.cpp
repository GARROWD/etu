#include <iostream>
#include "tree.cpp"
#include "avl_tree.cpp"

using std::string;
using std::cout;

const unsigned char left_descendant = 195;
const unsigned char right_descendant = 192;
const unsigned char horizontal_line = 196;
const unsigned char vertical_line = 179;

void print_tree(const std::string &prefix, node *a, bool isLeft) {
    if (a) {
        cout << prefix;
        cout << (isLeft ? string(1, left_descendant) : string(1,right_descendant)) << string(1,horizontal_line);
        cout << a->value << std::endl;
        print_tree(prefix + (isLeft ? string(1,vertical_line) + "  " : "  "), a->left, true);
        print_tree(prefix + (isLeft ? string(1,vertical_line) + "  " : "  "), a->right, false);
    }
}

void print_avl_tree(const std::string &prefix, avl_node *a, bool isLeft) {
    if (a) {
        cout << prefix;
        cout << (isLeft ? string(1, left_descendant) : string(1,right_descendant)) << string(1,horizontal_line);
        cout << a->value << std::endl;
        print_avl_tree(prefix + (isLeft ? string(1,vertical_line) + "  " : "  "), a->left, true);
        print_avl_tree(prefix + (isLeft ? string(1,vertical_line) + "  " : "  "), a->right, false);
    }
}

int main() {
    tree tree;
    string s = "9(7(4(100)(10))(8))";
    tree.stot(s);
    avl_tree avl_tree;
    int *tree_nodes = tree.pre_order();

    for (int i = 0; i < tree.node_count; i++) {
        avl_tree.add(tree_nodes[i]);
    }

    cout << " [i] Tree:\n";

    print_tree("", tree.root, false);

    cout << "\n [i] AVL Tree:\n";

    print_avl_tree("", avl_tree.root, false);

    cout << "\n";

    int *avl_tree_nodes = avl_tree.pre_order();
    cout << " [i] Preorder - ";
    for (int i = 0; i < avl_tree.node_count; i++) {
        cout << avl_tree_nodes[i] << " ";
    }

    avl_tree_nodes = avl_tree.in_order();
    cout << "\n [i] Inorder - ";
    for (int i = 0; i < avl_tree.node_count; i++) {
        cout << avl_tree_nodes[i] << " ";
    }

    avl_tree_nodes = avl_tree.post_order();
    cout << "\n [i] Postorder - ";
    for (int i = 0; i < avl_tree.node_count; i++) {
        cout << avl_tree_nodes[i] << " ";
    }

    cout << "\n";
    system("pause");
}
