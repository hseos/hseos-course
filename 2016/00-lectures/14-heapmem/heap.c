// x86

struct Block
{
    struct Block *next;
    int used;  // 0 - free, 1 - busy
    char data[0];
}

struct Block *first_free;

void *allocate(size_t size)
{
    // пройтись по свободным блокам,
    // взять первый подходящий блок
    // расщепить при необходимости, пометить как занятый, вернуть
    struct Block *p; // указатель на выделенный блок
    if (success) {
        return &p->data;
    }
    // используем sbrk(), добавляем память, выделяем
}

void deallocate(void *p)
{
    struct Block *b = (struct Block) ((char*) p - 8);
    // пометить как свободный, слить соседние блоки
}

