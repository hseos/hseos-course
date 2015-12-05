# Нити (threads)

## Мьютексы

[man 3 pthread_mutex_lock](http://linux.die.net/man/3/pthread_mutex_lock)

Если одни и те же данные используются одновременно более, чем в одном потоке, и хотя бы в одном из этих потоков модифицируются, может возникнуть "состояние гонки" (race condition), когда появляется возможность для какого-либо потока обнаружить данные частично модифицированными, т.е. в неконсистентном виде. Операция с данными, при которой невозможно состояние гонки, называется атомарной.

Самый простой (но часто не самый практичный) способ обеспечить атомарность операции - при помощи мьютекса (mutual exclusion, взаимного исключения) гарантировать, что к данным в одно и то же время имеет доступ не больше одного потока.

```c
// хотим гарантировать, что эти два счётчика модифицируются одновременно, 
// то есть никакое чтение не должно увидит эту пару в состоянии, 
// когда один из счётчиков модифицирован, а другой - ещё нет
volatile sig_atomic_t counter0 = 0;
volatile sig_atomic_t counter1 = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

// оба счётчика увеличиваются одновременно
void add_counters(int add0, int add1) {
    pthread_mutex_lock(&counter_mutex);
    counter0 += add0;
    counter1 += add1;
    pthread_mutex_unlock(&counter_mutex);
}

// возвращаем консистентные значения счётчиков
void read_counters(int* cnt0, int* cnt1) {
    pthread_mutex_lock(&counter_mutex);
    *cnt0 = counter0;
    *cnt1 = counter1;
    pthread_mutex_unlock(&counter_mutex);
}
```

