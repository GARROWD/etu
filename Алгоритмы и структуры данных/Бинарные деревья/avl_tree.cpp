struct avl_node {
    int value;
    int height;
    avl_node *left;
    avl_node *right;

    avl_node(int v) {
        value = v;
        left = right = nullptr;
        height = 1;
    }
};

class avl_tree {
private:
    int *nodes;
    int i;

    void order_event(int value) {
        nodes[i] = value;
        i++;
    }

    void pre_order(avl_node *a) {
        if (a) {
            order_event(a->value);
            pre_order(a->left);
            pre_order(a->right);
        }
    }

    void in_order(avl_node *a) {
        if (a) {
            in_order(a->left);
            order_event(a->value);
            in_order(a->right);
        }
    }

    void post_order(avl_node *a) {
        if (a) {
            post_order(a->left);
            post_order(a->right);
            order_event(a->value);
        }
    }

    void edit_height(avl_node *a) {
        int height_left = get_height(a->left);
        int height_right = get_height(a->right);
        a->height = (height_left > height_right ? height_left : height_right) + 1;
    }

    int get_height(avl_node *a) {
        return a ? a->height : 0;
    }

    int get_balance_factor(avl_node *a) {
        return get_height(a->right) - get_height(a->left);
    }

    avl_node *right_rotate(avl_node *a) {
        avl_node *q = a->left;
        a->left = q->right;
        q->right = a;

        edit_height(a);
        edit_height(q);

        return q;
    }

    avl_node *left_rotate(avl_node *a) {
        avl_node *b = a->right;
        a->right = b->left;
        b->left = a;

        edit_height(a);
        edit_height(b);

        return b;
    }

    avl_node *balance(avl_node *a) {
        edit_height(a);

        if (get_balance_factor(a) == 2) {
            if (get_balance_factor(a->right) < 0) {
                a->right = right_rotate(a->right);
            }
            return left_rotate(a);
        }

        if (get_balance_factor(a) == -2) {
            if (get_balance_factor(a->left) > 0) {
                a->left = left_rotate(a->left);
            }
            return right_rotate(a);
        }

        return a;
    }

    avl_node *find_min(avl_node *a) {
        return a->left ? find_min(a->left) : a;
    }

    avl_node *remove_min(avl_node *a) {
        if (a->left == 0) {
            return a->right;
        }
        a->left = remove_min(a->left);

        return balance(a);
    }

    avl_node *insert(avl_node *a, int value) {
        if (!a) {
            return new avl_node(value);
        }

        if (value < a->value) {
            a->left = insert(a->left, value);
        } else {
            a->right = insert(a->right, value);
        }

        return balance(a);
    }

    avl_node *remove(avl_node *a, int value) {
        if (!a) {
            return 0;
        }

        if (value < a->value) {
            a->left = remove(a->left, value);
        } else {
            if (value > a->value) {
                a->right = remove(a->right, value);
            } else {
                avl_node *b = a->left;
                avl_node *c = a->right;
                delete a;
                if (!c) {
                    return b;
                }
                avl_node *min = find_min(c);
                min->right = remove_min(c);
                min->left = b;

                return balance(min);
            }
        }

        return balance(a);
    }

public:
    avl_node *root;
    int node_count;

    avl_tree() {
        root = nullptr;
        nodes = nullptr;
        node_count = 0;
        i = 0;
    }

    void add(int value) {
        root = insert(root, value);
        node_count++;
    }

    void del(int value) {
        root = remove(root, value);
        node_count--;
    }

    int *pre_order() {
        if (root) {
            delete[]nodes;
            nodes = new int[node_count];
            pre_order(root);
            i = 0;
            return nodes;
        }
    }

    int *in_order() {
        if (root) {
            delete[]nodes;
            nodes = new int[node_count];
            in_order(root);
            i = 0;
            return nodes;
        }
    }

    int *post_order() {
        if (root) {
            delete[]nodes;
            nodes = new int[node_count];
            post_order(root);
            i = 0;
            return nodes;
        }
    }
};