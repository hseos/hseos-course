

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
// condvar для ждущих писателей
pthread_cond_t cw = PTHREAD_COND_INITIALIZER;
// condvar для ждущих читателей
pthread_cond_t cr = PTHREAD_COND_INITIALIZER;
// число писателей в критической секции (0 или 1)
volatile int nw = 0;
// число писателей в критической секции (>= 0)
volatile int nr = 0;

void rlock()
{
    pthread_mutex_lock(&m);
    while (nw > 0) {
        // ждем, пока не разбудят
        pthread_cond_wait(&cr, &m);
    }
    ++nr; // +1 читатель в критической секции
    pthread_mutex_unlock(&m);
}

void runlock()
{
    pthread_mutex_lock(&m);
    if (!--nr) {
        // будим какого-то одного писателя
        // можно делать и broadcast тоже
        pthread_cond_signal(&cw);
    }
    pthread_mutex_unlock(&m);
}

void wlock()
{
    pthread_mutex_lock(&m);
    // ждем в цикле, пока не станет nw == 0 && nr == 0
    while (nw > 0 || nr > 0) {
        pthread_cond_wait(&cw, &m);
    }
    ++nw; // писатель вошел в критическую секцию
    pthread_mutex_unlock(&m);
    
}

void wunlock()
{
    pthread_mutex_lock(&m);
    --nw;
    // будим какого-то одного писателя
    pthread_cond_signal(&cw);
    // будим всех читателей
    pthread_cond_broadcast(&cr);
    pthread_mutex_unlock(&m);
}

reader()
{
    while (1) {
        rlock();
        //...
        runlock();
    }
}
