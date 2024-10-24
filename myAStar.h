//#pragma once
//#include <iostream>
//
//typedef struct Node 
//{
//    int puzzle[9];    // 1차원 배열로 퍼즐 상태를 저장
//    int gCost;        // 시작점부터 현재 노드까지의 비용
//    int hCost;        // 목표까지의 휴리스틱 비용 (맨해튼 거리)
//    int fCost() const { return gCost + hCost; }  // fCost 계산
//    int parentIndex;  // 부모 노드 인덱스 (경로 추적용)
//
//    // 퍼즐 상태가 다를 경우 비교
//    bool operator<(const Node& other) const {
//        return fCost() < other.fCost();
//    }
//};
//
//class myPriorityQueue
//{
//private:
//    Node heap[100];  // 최대 100개의 노드를 저장할 수 있는 배열
//    int size;        // 현재 힙에 저장된 노드의 개수
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
//        if (size >= 100) return;  // 큐가 꽉 차면 삽입하지 않음
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
//        if (puzzle[i] != 0) {  // 빈 칸 제외
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
//// A* 알고리즘 구현
//void AStar(int startState[9], const int goalState[9]) {
//    myPriorityQueue openSet;
//    bool closedSet[100] = { false };  // 이미 탐색된 노드를 추적
//
//    Node startNode;
//    for (int i = 0; i < 9; ++i) {
//        startNode.puzzle[i] = startState[i];
//    }
//    startNode.gCost = 0;
//    startNode.hCost = calculateManhattanDistance(startState, goalState);
//    startNode.parentIndex = -1;  // 시작 노드는 부모가 없음
//
//    openSet.push(startNode);
//
//    while (!openSet.isEmpty()) {
//        Node currentNode = openSet.pop();
//
//        // 목표 상태 도달 시 경로 출력
//        if (calculateManhattanDistance(currentNode.puzzle, goalState) == 0) {
//            std::cout << "Puzzle solved!" << std::endl;
//            return;
//        }
//
//        // 이미 방문한 노드는 무시
//        if (closedSet[currentNode.parentIndex]) {
//            continue;
//        }
//
//        closedSet[currentNode.parentIndex] = true;
//
//        // 빈 칸(0)의 위치를 찾음
//        int zeroIndex;
//        for (int i = 0; i < 9; ++i) {
//            if (currentNode.puzzle[i] == 0) {
//                zeroIndex = i;
//                break;
//            }
//        }
//
//        // 네 방향으로 이동 가능한지 체크
//        int directions[4] = { -3, 3, -1, 1 };  // 상하좌우 이동
//        for (int d = 0; d < 4; ++d) {
//            int newIndex = zeroIndex + directions[d];
//
//            // 유효한 이동인지 확인
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