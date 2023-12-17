#define stack_var char

struct node
{
    stack_var val;
    node *next;
};

class stack
{
public:
    node null_node;
    node *head;
    int size = 0;

    stack()
    {
        head = nullptr;
    }

    bool is_empty()
    {
        return head == nullptr;
    }

    void push(stack_var val)
    {
        node *tmp = new node;
        tmp->val = val;
        tmp->next = head;
        head = tmp;
        size++;
    }

    void pop()
    {
        if (!is_empty())
        {
            node *tmp = head;
            head = head->next;
            size--;
            delete tmp;
        }
    }

    node peek(int index = 0)
    {
        if (!is_empty() && index < size)
        {
            node *tmp = head;
            for (int i = 0; i < index && index < size; i++)
            {
                tmp = tmp->next;
            }

            return *tmp;
        }
        else
        {
            return null_node;
        }
    }

    void edit(stack_var val, int index = 0)
    {
        if (!is_empty() && index < size)
        {
            node *tmp = head;
            for (int i = 0; i < index && index < size; i++)
            {
                tmp = tmp->next;
            }
            tmp->val = val;
        }
    }

    ~stack()
    {
        while (!is_empty())
        {
            pop();
        }
    }
};