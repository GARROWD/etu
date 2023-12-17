#define stack_var int

struct node
{
    stack_var start_index = 0;
    stack_var length = 0;
    node *next;
};

class stack
{
private:

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

    void push(stack_var run_start_index, stack_var run_length)
    {
        node *tmp = new node;
        tmp->start_index = run_start_index;
        tmp->length = run_length;
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

    void edit(stack_var run_start_index, stack_var run_length, int index = 0)
    {
        if (!is_empty() /*&& index < size*/)
        {
            node *tmp = head;
            /* Лишнии проверки в данном конкретном случае
            for (int i = 0; i < index && index < size; i++)
            {
                tmp = tmp->next;
            }
            */
            tmp->start_index = run_start_index;
            tmp->length = run_length;
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