#include "PriorityQueue.h"

void TestProgram(){
    PriorityQueue* pq = initPriorityQueue();

    enqueue(pq, 240, 200);
    enqueue(pq, 34, 10000);
    enqueue(pq, 5, 50);
    enqueue(pq, 255, 205);
    enqueue(pq, 4, 44);

    printf("Dequeue first element: %d\n", dequeue(pq).data);
    printf("Dequeue element with priority 5: %d\n", dequeueWithPriority(pq, 5).data);
    printf("Dequeue element with priority not less than 239: %d\n", dequeueWithPriorityNotLessThan(pq, 239).data);

    free(pq);
}




// Пример тестовой программы
int main() {

    TestProgram();

    return 0;
}
