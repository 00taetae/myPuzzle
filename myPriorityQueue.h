#pragma once
#include <iostream>

typedef struct Node 
{
    int puzzle[9];    // 1차원 배열로 퍼즐 상태를 저장
    int gCost;        // 시작점부터 현재 노드까지의 비용
    int hCost;        // 목표까지의 휴리스틱 비용 (맨해튼 거리)
    int fCost() const { return gCost + hCost; }  // fCost 계산
    int parentIndex;  // 부모 노드 인덱스 (경로 추적용)

    // 퍼즐 상태가 다를 경우 비교
    bool operator<(const Node& other) const {
        return fCost() < other.fCost();
    }
};

class myPriorityQueue
{
private:
    Node heap[100];  // 최대 100개의 노드를 저장할 수 있는 배열
    int size;        // 현재 힙에 저장된 노드의 개수

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
        if (size >= 100) return;  // 큐가 꽉 차면 삽입하지 않음
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
