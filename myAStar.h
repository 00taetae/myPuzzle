//#pragma once
//#include <iostream>
//
//typedef struct Node 
//{
//    int puzzle[9];    // 1���� �迭�� ���� ���¸� ����
//    int gCost;        // ���������� ���� �������� ���
//    int hCost;        // ��ǥ������ �޸���ƽ ��� (����ư �Ÿ�)
//    int fCost() const { return gCost + hCost; }  // fCost ���
//    int parentIndex;  // �θ� ��� �ε��� (��� ������)
//
//    // ���� ���°� �ٸ� ��� ��
//    bool operator<(const Node& other) const {
//        return fCost() < other.fCost();
//    }
//};
//
//class myPriorityQueue
//{
//private:
//    Node heap[100];  // �ִ� 100���� ��带 ������ �� �ִ� �迭
//    int size;        // ���� ���� ����� ����� ����
//
//    void swap(int index1, int index2) 
//    {
//        Node temp = heap[index1];
//        heap[index1] = heap[index2];
//        heap[index2] = temp;
//    }
//
//    void heapifyUp(int index)
//    {
//        while (index > 0) {
//            int parentIndex = (index - 1) / 2;
//            if (heap[index].fCost() < heap[parentIndex].fCost()) 
//            {
//                swap(index, parentIndex);
//                index = parentIndex;
//            }
//            else 
//            {
//                break;
//            }
//        }
//    }
//
//    void heapifyDown(int index) 
//    {
//        int leftChild, rightChild, smallestChild;
//        while ((leftChild = 2 * index + 1) < size) 
//        {
//            rightChild = leftChild + 1;
//            smallestChild = (rightChild < size && heap[rightChild].fCost() < heap[leftChild].fCost()) ? rightChild : leftChild;
//
//            if (heap[index].fCost() > heap[smallestChild].fCost()) 
//            {
//                swap(index, smallestChild);
//                index = smallestChild;
//            }
//            else 
//            {
//                break;
//            }
//        }
//    }
//
//public:
//    myPriorityQueue() : size(0) {}
//
//    bool isEmpty() const 
//    {
//        return size == 0;
//    }
//
//    void push(const Node& node) 
//    {
//        if (size >= 100) return;  // ť�� �� ���� �������� ����
//        heap[size] = node;
//        heapifyUp(size);
//        size++;
//    }
//
//    Node pop() 
//    {
//        if (isEmpty()) throw; // std::out_of_range("Queue is empty");
//        Node root = heap[0];
//        heap[0] = heap[--size];
//        heapifyDown(0);
//        return root;
//    }
//};
//
//int calculateManhattanDistance(const int puzzle[9], const int goal[9]) {
//    int distance = 0;
//    for (int i = 0; i < 9; ++i) {
//        if (puzzle[i] != 0) {  // �� ĭ ����
//            for (int j = 0; j < 9; ++j) {
//                if (puzzle[i] == goal[j]) {
//                    distance += std::abs(i / 3 - j / 3) + std::abs(i % 3 - j % 3);
//                    break;
//                }
//            }
//        }
//    }
//    return distance;
//}
//
//// A* �˰��� ����
//void AStar(int startState[9], const int goalState[9]) {
//    myPriorityQueue openSet;
//    bool closedSet[100] = { false };  // �̹� Ž���� ��带 ����
//
//    Node startNode;
//    for (int i = 0; i < 9; ++i) {
//        startNode.puzzle[i] = startState[i];
//    }
//    startNode.gCost = 0;
//    startNode.hCost = calculateManhattanDistance(startState, goalState);
//    startNode.parentIndex = -1;  // ���� ���� �θ� ����
//
//    openSet.push(startNode);
//
//    while (!openSet.isEmpty()) {
//        Node currentNode = openSet.pop();
//
//        // ��ǥ ���� ���� �� ��� ���
//        if (calculateManhattanDistance(currentNode.puzzle, goalState) == 0) {
//            std::cout << "Puzzle solved!" << std::endl;
//            return;
//        }
//
//        // �̹� �湮�� ���� ����
//        if (closedSet[currentNode.parentIndex]) {
//            continue;
//        }
//
//        closedSet[currentNode.parentIndex] = true;
//
//        // �� ĭ(0)�� ��ġ�� ã��
//        int zeroIndex;
//        for (int i = 0; i < 9; ++i) {
//            if (currentNode.puzzle[i] == 0) {
//                zeroIndex = i;
//                break;
//            }
//        }
//
//        // �� �������� �̵� �������� üũ
//        int directions[4] = { -3, 3, -1, 1 };  // �����¿� �̵�
//        for (int d = 0; d < 4; ++d) {
//            int newIndex = zeroIndex + directions[d];
//
//            // ��ȿ�� �̵����� Ȯ��
//            if (newIndex >= 0 && newIndex < 9 &&
//                !(zeroIndex % 3 == 2 && d == 3) &&
//                !(zeroIndex % 3 == 0 && d == 2)) {
//
//                Node neighborNode = currentNode;
//                neighborNode.puzzle[zeroIndex] = currentNode.puzzle[newIndex];
//                neighborNode.puzzle[newIndex] = 0;
//
//                neighborNode.gCost = currentNode.gCost + 1;
//                neighborNode.hCost = calculateManhattanDistance(neighborNode.puzzle, goalState);
//                neighborNode.parentIndex = currentNode.parentIndex + 1;
//
//                openSet.push(neighborNode);
//            }
//        }
//    }
//
//    std::cout << "No solution found." << std::endl;
//}