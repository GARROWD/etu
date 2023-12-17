#define dynamic_array_var int

class dynamic_array
{
public:
    dynamic_array_var *head = nullptr;
    int size = 0;

    dynamic_array(int array_size = 0)
    {
        if (array_size > 0)
        {
            head = new dynamic_array_var[array_size];
            size = array_size;
        }
    }

    void resize(int array_size)
    {
        if (array_size > 0)
        {
            dynamic_array_var *tmp = new dynamic_array_var[array_size];

            for (int i = 0; i < array_size; i++)
            {
                if (i < size)
                {
                    tmp[i] = head[i];
                }
            }

            delete[] head;
            head = tmp;
            size = array_size;
        }
    }

    ~dynamic_array()
    {
        delete[] head;
    }

    dynamic_array_var &operator[](int i)
    {
        return head[i];
    }
};