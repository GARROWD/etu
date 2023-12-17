#include <iostream>
#include <algorithm>

using std::string;

struct node {
    int value;
    node *left;
    node *right;

    node(int v) {
        value = v;
        left = right = nullptr;
    }
};

class tree {
private:
    int *nodes;
    int i = 0;

    void order_event(int value) {
        nodes[i] = value;
        i++;
    }

    void pre_order(node *a) {
        if (a) {
            order_event(a->value);
            pre_order(a->left);
            pre_order(a->right);
        }
    }

    void in_order(node *a) {
        if (a) {
            in_order(a->left);
            order_event(a->value);
            in_order(a->right);
        }
    }

    void post_order(node *a) {
        if (a) {
            post_order(a->left);
            post_order(a->right);
            order_event(a->value);
        }
    }

    bool is_number(char a) {
        return a >= '0' && a <= '9';
    }

    node *parsing(node *a, string s, int &i) {
        // В принципе это повторяющееся нечто можно привести в красивый вид, но мне лень, честно
        if (s[i] == '(') {
            string value_str;
            i++;
            while (is_number(s[i])) {
                value_str += s[i];
                i++;
            }

            if (value_str.size() != 0) {
                int value_tmp = stoi(value_str);
                a->left = new node(value_tmp);
                node_count++;
            } else {
                return nullptr;
            }

            if (s[i] == '(') {
                parsing(a->left, s, i);
            }

            if (s[i] != ')') {
                return nullptr;
            }
            i++;
        }

        if (s[i] == '(') {
            string value_str;
            i++;
            while (is_number(s[i])) {
                value_str += s[i];
                i++;
            }

            if (value_str.size() != 0) {
                int value_tmp = stoi(value_str);
                a->right = new node(value_tmp);
                node_count++;
            } else {
                return nullptr;
            }

            if (s[i] == '(') {
                parsing(a->right, s, i);
            }

            if (s[i] != ')') {
                return nullptr;
            }
            i++;
        }

        return a;
    }

    node *find_min(node *a) {
        return a->left ? find_min(a->left) : a;
    }

    node *remove_min(node *a) {
        if (a->left == 0) {
            return a->right;
        }
        a->left = remove_min(a->left);

        return a;
    }

    node *insert(node *a, int value) {
        if (!a) {
            return new node(value);
        }

        if (value < a->value) {
            a->left = insert(a->left, value);
        } else {
            a->right = insert(a->right, value);
        }

        return a;
    }

    node *remove(node *a, int value) {
        if (!a) {
            return 0;
        }

        if (value < a->value) {
            a->left = remove(a->left, value);
        } else {
            if (value > a->value) {
                a->right = remove(a->right, value);
            } else {
                node *b = a->left;
                node *c = a->right;
                delete a;
                if (!c) {
                    return b;
                }
                node *min = find_min(c);
                min->right = remove_min(c);
                min->left = b;

                return min;
            }
        }

        return a;
    }

public:
    node *root;
    int node_count;

    tree() {
        root = nullptr;
        nodes = nullptr;
        node_count = 0;
    }

    void add(int value) {
        root = insert(root, value);
        node_count++;
    }

    void del(int value) {
        root = remove(root, value);
        node_count--;
    }

    void stot(string s) {
        bool error = 0;
        int brackets = 0;
        s.erase(std::remove(s.begin(), s.end(), ' '), s.end());

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                brackets++;;
            } else if (s[i] == ')') {
                brackets--;
            } else if (!is_number(s[i])) {
                error = 1;
                break;
            }
        }

        if (s.size() != 0 && !error && !brackets) {
            int i = 0;
            string tmp;
            while (is_number(s[i])) {
                tmp += s[i];
                i++;
            }
            add(stoi(tmp));
            root = parsing(root, s, i);
        }
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