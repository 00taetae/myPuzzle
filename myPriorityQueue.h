#pragma once
#include <iostream>

typedef struct Node 
{
    int puzzle[9];    // 1���� �迭�� ���� ���¸� ����
    int gCost;        // ���������� ���� �������� ���
    int hCost;        // ��ǥ������ �޸���ƽ ��� (����ư �Ÿ�)
    int fCost() const { return gCost + hCost; }  // fCost ���
    int parentIndex;  // �θ� ��� �ε��� (��� ������)

    // ���� ���°� �ٸ� ��� ��
    bool operator<(const Node& other) const {
        return fCost() < other.fCost();
    }
};

class myPriorityQueue
{
private:
    Node heap[100];  // �ִ� 100���� ��带 ������ �� �ִ� �迭
    int size;        // ���� ���� ����� ����� ����

    void swap(int index1, int index2) 
    {
        Node temp = heap[index1];
        heap[index1] = heap[index2];
        heap[index2] = temp;
    }

    void heapifyUp(int index)
    {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index].fCost() < heap[parentIndex].fCost()) 
            {
                swap(index, parentIndex);
                index = parentIndex;
            }
            else 
            {
                break;
            }
        }
    }

    void heapifyDown(int index) 
    {
        int leftChild, rightChild, smallestChild;
        while ((leftChild = 2 * index + 1) < size) 
        {
            rightChild = leftChild + 1;
            smallestChild = (rightChild < size && heap[rightChild].fCost() < heap[leftChild].fCost()) ? rightChild : leftChild;

            if (heap[index].fCost() > heap[smallestChild].fCost()) 
            {
                swap(index, smallestChild);
                index = smallestChild;
            }
            else 
            {
                break;
            }
        }
    }

public:
    myPriorityQueue() : size(0) {}

    bool isEmpty() const 
    {
        return size == 0;
    }

    void push(const Node& node) 
    {
        if (size >= 100) return;  // ť�� �� ���� �������� ����
        heap[size] = node;
        heapifyUp(size);
        size++;
    }

    Node pop() 
    {
        if (isEmpty()) throw; // 
        Node root = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        return root;
    }
};
