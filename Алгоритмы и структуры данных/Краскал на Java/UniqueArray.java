package org.example;

public class UniqueArray<K, V>
{
    private class Node<K, V>
    {
        K key;
        V value;

        Node(K key, V value)
        {
            this.key = key;
            this.value = value;
        }
    }

    DynamicArray<Node> array = new DynamicArray<Node>();

    public boolean isEmpty()
    {
        return array.size() == 0;
    }

    public boolean containsKey(K key)
    {
        for (int i = 0; i < array.size(); i++)
        {
            if (array.get(i).key == key)
            {
                return true;
            }
        }

        return false;
    }

    public boolean containsValue(V value)
    {
        for (int i = 0; i < array.size(); i++)
        {
            if (array.get(i).value == value)
            {
                return true;
            }
        }

        return false;
    }

    public boolean put(K key, V value)
    {
        for (int i = 0; i < array.size(); i++)
        {
            if (key == array.get(i).key)
            {
                array.set(new Node<>(key, value), i);
                return true;
            }
        }

        array.add(new Node<>(key, value));
        return true;
    }

    public void remove(K key)
    {
        for (int i = 0; i < array.size(); i++)
        {
            if (array.get(i).key == key)
            {
                array.remove(i);
                break;
            }
        }
    }

    public void remove(K key, V value)
    {
        for (int i = 0; i < array.size(); i++)
        {
            if (array.get(i).key == key && array.get(i).value == value)
            {
                array.remove(i);
                break;
            }
        }
    }

    public void clear()
    {
        array.clear();
    }

    public int size()
    {
        return array.size();
    }

    public V get(K key)
    {
        for (int i = 0; i < array.size(); i++)
        {
            if (array.get(i).key == key)
            {
                return (V) array.get(i).value;
            }
        }

        return null;
    }
}