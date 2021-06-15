cmake_minimum_required(VERSION 3.19)
project(bd C)

#status = сделано - можно копипастить, написал для себя
#status = было - нельзя копипастить, взял из лабы

set(CMAKE_C_STANDARD 99)
#1 (3/3)
#status = сделано
add_executable(deck 1/deck/tests.c 1/deck/deck.c)
#status = сделано
add_executable(queue 1/queue/tests.c 1/queue/queue.c)
#status = сделано
add_executable(stack 1/stack/tests.c 1/stack/stack.c)
#2 (3/3)
#status = сделано
add_executable(hashTable 2/hashTable/tests.c 2/hashTable/hashTable.c)
#status = сделано
add_executable(viewTable 2/viewTable/tests.c 2/viewTable/viewTable.c)
#status = сделано
add_executable(sortTable 2/sortTable/tests.c 2/sortTable/sortTable.c)
#3 (2/5)
#status = было
add_executable(avlTree 3/avlTree/main4b.c 3/avlTree/AVLtree.c)
#status = было
add_executable(binaryTree 3/binaryTree/main4.c 3/binaryTree/Tree.c)
#4 (1/2)
#status = было
add_executable(Heap 4/heap/main6.c 4/heap/Heap.c)
#status = сделано
add_executable(skipList 4/skipList/tests.c 4/skipList/skipList.c)
#5 (1/1)
#status = было
add_executable(graph 5/graph/main5.c 5/graph/Graph.c)

