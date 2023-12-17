package org.example;

public class TimSortForEdges<T>
{
    private class Node
    {
        int startIndex;
        int length;

        Node(int startIndex, int length)
        {
            this.startIndex = startIndex;
            this.length = length;
        }
    }

    private Stack<Node> runs;
    private DynamicArray<Edge> array;

    private int getMinRunLength()
    {
        int otherBitsDet = 0, arrayLength = array.size();
        while (arrayLength >= 64)
        {
            otherBitsDet |= arrayLength & 1;
            arrayLength >>= 1;
        }

        return arrayLength + otherBitsDet;
    }

    private void binInsSort(int arrayStartIndex, int arrayLength)
    {
        int left = 0, right = 0, middle = 0;

        for (int i = arrayStartIndex; i - arrayStartIndex < arrayLength - 1; i++)
        {
            if (array.get(i).weight > array.get(i + 1).weight)
            {
                Edge insertValue = array.get(i + 1);
                left = arrayStartIndex;
                right = i;

                do
                {
                    middle = (left + right) / 2;

                    if (array.get(middle).weight < insertValue.weight)
                    {
                        left = middle + 1;
                    } else
                    {
                        right = middle - 1;
                    }
                } while (left <= right);

                for (int j = i; j >= left; j--)
                {
                    array.set(array.get(j), j + 1);
                }
                array.set(insertValue, left);
            }
        }
    }

    private void binMergeSort(Node firstRun, Node secondRun)
    {
        int runsLength = firstRun.length + secondRun.length, firstP = firstRun.startIndex, secondP = secondRun.startIndex;
        int firstRunEnd = firstRun.length + firstRun.startIndex, secondRunEnd = secondRun.length + secondRun.startIndex;

        DynamicArray<Edge> tmp = new DynamicArray<Edge>();

        for (int i = 0; i < runsLength; i++)
        {

            if (firstP >= firstRunEnd)
            {
                tmp.add(array.get(secondP));
                secondP++;
            } else if (secondP >= secondRunEnd)
            {
                tmp.add(array.get(firstP));
                firstP++;
            } else if (array.get(firstP).weight < array.get(secondP).weight)
            {
                tmp.add(array.get(firstP));
                firstP++;

            } else
            {
                tmp.add(array.get(secondP));
                secondP++;
            }

        }

        int arrayStartIndex = Math.min(firstRun.startIndex, secondRun.startIndex);
        for (int i = 0; i < runsLength; i++)
        {
            array.set(tmp.get(i), i + arrayStartIndex);
        }
    }

    private void mergeRuns()
    {
        Node z = runs.peek(2);
        Node y = runs.peek(1);
        Node x = runs.peek(0);
        boolean isXGreater = z.length > y.length + x.length || runs.size < 3, isYGreater = y.length > x.length || runs.size < 2;

        while (!isXGreater || !isYGreater)
        {
            runs.pop();
            if (z.length != 0)
            {
                runs.pop();
                if (z.length < x.length)
                {
                    binMergeSort(y, z);

                    runs.edit(new Node(Math.min(y.startIndex, z.startIndex), y.length + z.length), 0);
                    runs.push(new Node(x.startIndex, x.length));
                } else
                {
                    binMergeSort(y, x);
                    runs.push(new Node(Math.min(y.startIndex, x.startIndex), y.length + x.length));
                }
            } else
            {
                binMergeSort(y, x);

                runs.edit(new Node(Math.min(y.startIndex, x.startIndex), y.length + x.length), 0);
            }

            z = runs.peek(2);
            y = runs.peek(1);
            x = runs.peek(0);
            isXGreater = z.length > y.length + x.length || runs.size < 3;
            isYGreater = y.length > x.length || runs.size < 2;
        }
        ;
    }

    private void finalMerge()
    {
        while (!runs.isEmpty())
        {
            Node firstRun = runs.peek(1), secondRun = runs.peek(0);
            binMergeSort(firstRun, secondRun);
            runs.pop();
            runs.edit(new Node(Math.min(firstRun.startIndex, secondRun.startIndex), firstRun.length + secondRun.length), 0);
        }
    }

    private void divideToRuns()
    {
        int i = 0, minRunLength = getMinRunLength();
        while (i < array.size())
        {
            int runStartIndex = i, runLength = minRunLength;

            if (i + minRunLength < array.size())
            {
                binInsSort(i, minRunLength);
                i += minRunLength;

                while (array.get(i - 1).weight <= array.get(i).weight)
                {
                    runLength++;
                    i++;
                }
            } else
            {
                binInsSort(i, array.size() - i);
                runLength = array.size() - i;
                i = array.size();
            }

            runs.push(new Node(runStartIndex, runLength));
        }
    }

    public DynamicArray<Edge> algorithm(DynamicArray<Edge> array)
    {
        this.runs = new Stack<>(new Node(0, 0));
        this.array = array;
        divideToRuns();
        mergeRuns();
        finalMerge();
        return array;
    }
}
