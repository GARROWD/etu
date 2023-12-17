package org.example;

class Stack<T>
{
    private class Node
    {
        T values;
        Node next;

        Node(T values)
        {
            this.values = values;
        }
    }

    Node nullNode;
    Node head;
    int size;

    public Stack(T nullNode)
    {
        this.nullNode = new Node(nullNode);
        this.head = null;
        this.size = 0;
    }

    boolean isEmpty()
    {
        return head == null;
    }

    public void push(T values)
    {
        Node tmp = new Node(values);
        tmp.next = head;
        head = tmp;
        size++;
    }

    void pop()
    {
        if (!isEmpty())
        {
            Node tmp = head;
            head = head.next;
            size--;
        }
    }

    public T peek(int index)
    {
        if (!isEmpty() && index < size)
        {
            Node tmp = head;
            for (int i = 0; i < index; i++)
            {
                tmp = tmp.next;
            }

            return tmp.values;
        } else
        {
            return nullNode.values;
        }
    }

    public void edit(T values, int index)
    {
        if (!isEmpty() && index < size)
        {
            Node tmp = head;
            tmp.values = values;
        }
    }
}