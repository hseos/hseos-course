# Ассемблер x86, часть 4

## Компиляция программ без стандартной библиотеки Си

При компиляции программ с помощью драйвера gcc по умолчанию при компоновке программы подключается стандартная библиотека
языка Си libc. Частью стандартной библиотеки является код инициализации (start-up code), который
выполняет необходимую инициализацию стандартной библиотеки (например, создает стандартные потоки stdin, stdout, stderr),
а затем вызывает функцию `main`. Поэтому, если используется стандартная библиотека Си, точкой входа в программу
является функция `main`.

Чтобы отключить стандартную библиотеку можно использовать опцию `-nostdlib`. В этом случае к программе не подключается
код инициализации и код функций стандартной библиотеки. Программа остается "один на один" с операционной системой.
В этом случае точка входа в программу называется `_start` (на Linux). Ядро передает управление на точку `_start` не
как вызов подпрограммы, то есть для завершения программы нельзя использовать инструкцию `ret`. Для завершения
программы нужно использовать системный вызов `exit`.

Таким образом, чтобы скомпилировать 32-битную программу без стандартной библиотеки потребуется командная строка:
```
gcc -m32 -nostdlib prog.S -o prog
```

## Аргументы командной строки и переменные окружения

Перед передачей управления на точку входа `_start` ядро ОС размещает аргументы командной строки и переменные окружения в области памяти, отведенной под стек.
Если, например, верхняя граница адресного пространства, отведенного под стек, равна `0xc0000000`, то непосредственно ниже этой верхней границы будут размещены аргументы
командной строки и переменные окружения. В регистре `%esp` при входе в программу будет находиться текущая верхушка стека, растущего вниз. Начиная от значения `%esp`
на момент старта программы и до верхней границы адресного пространства, отведенного под стек, и будут располагаться аргументы командной строки и переменные окружения.

Так как адрес возврата на стеке отсутствует, по адресу `(%esp)` находится параметр `argc` --- 32-битное целое число, равное числу аргументов командной строки, включая имя программы.
По адресу `%esp + 4` начинается массив `argv` аргументов командной строки, который завершается нулевым указателем. Таким образом, `4(%esp)` --- это `argv[0]`, `8(%esp)` --- это `argv[1]`
`12(%esp)` --- это `argv[2]` и так далее. Если в регистр `%eax` поместить параметр `argc`, то по адресу `4(%esp, %eax, 4)` всегда будет находится нулевой указатель, обозначающий
конец аргументов командной строки. Следующий после него элемент --- это первая строка из массива переменных окружения. Массив переменных окружения завершается нулевым указателем.

Таким образом, в точке входа в программу значения указателей `argv` и `envp` могут быть вычислены следующим образом:

```
        mov     (%esp), %eax            // помещаем параметр argc в %eax
        lea     4(%esp), %ecx           // в регистре %ecx будет находиться адрес начала массива аргументов командной строки
        lea     8(%esp, %eax, 4), %edx  // в регистре %edx будет находиться адрес налала массива переменных окружения
```

Передать управление функции `main`, принимающей параметры argc, argv и envp можно будет следующим образом:

```
        and     $-16, %esp              // выравнивание стека
        push    %eax                    // для выравнивания области параметров по 16 байт
        push    %edx                    // envp
        push    %ecx                    // argv
        push    %eax                    // argc
        call    main
        add     $16, %esp
```

## Интерфейс системных вызовов

Способ выполнения системного вызова сильно отличается на разных платформах. На платформе x86 системный вызов
выполняется следующим образом:
* номер системного вызова помещается в регистр `%eax`
* параметры системного вызова помещаются в регистры `%ebx`, `%ecx`, `%edx`, `%esi`, `%edi` (в зависимости от их количества)
* выполняется инструкция `int $0x80`

Номера системных вызовов находятся в заголовочном файле `<asm/unistd_32.h>`. Например, чтобы считать один символ со стандартного
потока ввода нужно выполнить системный вызов:
```c
char c;
int val = read(0, &c, sizeof(c));
```

соответствующий фрагмент программы на ассемблере будет выглядеть следующим образом:
```gas
#include <asm/unistd_32.h>
        .data                   // размещаем данные
c:      .byte   0               // c - это глобальная переменная размера один байт (char)
        .text                   // начинаем секцию кода
        // ...
        movl    $__NR_read, %eax // или $3, %eax, если заголовочный файл не найден
        movl    $0, %ebx        // первый аргумент (0 - стандартный поток ввода) в %ebx
        movl    $c, %ecx        // второй аргумент (адрес переменной c) в %ecx
        movl    $1, %edx        // третий аргумент (размер переменной c) в %edx
        int     $0x80
        // в %eax будет возвращаемое значение read
```

системный вызов `exit(0);` на ассемблере запишется следующим образом:
```gas
        movl    $__NR_exit, %eax
        xorl    %ebx, %ebx
        int     $0x80
```

если файл `<asm/unistd_32.h>` недоступен, можно использовать численные значения:
```c
#define __NR_exit 1
#define __NR_read 3
#define __NR_write 4
#define __NR_brk 45
```

## Некоторые системные вызовы

Для написания программ нам потребуются следующие простейшие системные вызовы. Ниже будет дано краткое описание, полностью
эти системные вызовы будут рассмотрены далее в соответствующих разделах курса.

```
ssize_t read(int fd, void *ptr, size_t size);
```

Чтение из потока. Для чтения со стандартного потока ввода значение `fd` указывается равным 0. `ptr` - адрес, по которому
будут размещены считанные данные, `size` - размер буфера для чтения. `read` возвращает:
* -1 в случае ошибки чтения;
* 0 в случае достижения конца файла;
* число действительно считанных байт данных (оно не больше чем размер `size`, но не обязано быть ему равным).

Обратите внимание, что собственно системный вызов `__NR_read` на Linux при ошибке возвращает из ядра ОС отрицательное значение, равное по модулю коду ошибки
из `errno.h`. Стандартная библиотека glibc проверяет результат на отрицательное значение и в случае ошибки устанавливает переменную `errno` в код ошибки,
то есть результат системного вызова, взятый с обратным знаком.

```
ssize_t write(int fd, const void *ptr, size_t size);
```

Запись в поток. Для записи на стандартный поток вывода значение `fd` указывается равным 1. `ptr` - адрес, по которому
размещаются данные для записи, `size` - размер записываемых данных. `write` возвращает:
* -1 в случае ошибки записи;
* число записанных байт данных (не больше чем `size`, но не обязано быть ему равным).
Пока мы будем предполагать, что успешно записываются все данные из буфера `ptr`.

Обратите внимание, что собственно системный вызов `__NR_write` на Linux при ошибке возвращает из ядра ОС отрицательное значение, равное по модулю коду ошибки
из `errno.h`. Стандартная библиотека glibc проверяет результат на отрицательное значение и в случае ошибки устанавливает переменную `errno` в код ошибки,
то есть результат системного вызова, взятый с обратным знаком.

```
void exit(int code);
```

Завершение программы с кодом возврата `code`. Обратите внимание, что в стандартной библиотеке Си функция-обертка для
системного вызова exit называется `_exit`. Тем не менее, константа номера системного вызова называется `__NR_exit`.

```
void *brk(void *newbrk);
```

Установить новый адрес конца кучи в программе. `newbrk` - новый адрес. Системный вызов возвращает новый адрес конца кучи.
Чтобы получить текущий адрес конца кучи нужно задать параметр `newbrk` равным `NULL`.
Обратите внимание, что функция-обертка стандартной библиотеки Си имеет другой прототип.

## Управление динамической памятью (кучей)

При загрузке программы на выполнение перед передачей ей управления ядро ОС размещает в адресном пространстве секции исполняемого
файла, в частности, `.text`, содержащую код программы, `.data`, содержащую глобальные инициализированные данные,
и `.bss`, содержащую глобальные обнуляемые данные. Ядро ОС выделяет память под стек и копирует в него аргументы командной строки и переменные
окружения. Но управление областью динамической памяти (кучей) полностью возлагается на саму программу.

Рассмотрим одну из простейших стратегий управления кучей. Куча будет размещаться непосредственно после загруженной программы.
Память будет запрашиваться у ядра ОС по мере необходимости, и куча будет постепенно увеличиваться. Внутри куча будет организована как список
блоков памяти переменного размера, для каждого блока памяти будет храниться его размер и флаг занятости.
Ниже будут показаны примеры для 32-битного процессора, в котором типы size_t и void * имеют размер 4 байта. Для 64-битной платформы потребуется
сделать изменения, исходя из того, что size_t и void * имеют размер 8 байт.

Структура, описывающая блок динамической памяти, может быть определена следующим образом:

```
struct MemBlock
{
    unsigned is_used:1;
    unsigned is_last:1;
    unsigned size:30;
    unsigned char data[0];
};
```

Битовое поле `is_used` равно 1, если данный блок динамической памяти используется, то есть функция `malloc` вернула указатель на него для использования в программе,
и он еще не был освобожден с помощью `free`.
Битовое поле `is_last` равно 1 для последнего блока динамической памяти в списке блоков.
Он может быть как свободен, так и занят.
Мы предполагаем, что динамическая память выделяется блоками размера, кратного 4 байтам, поэтому два младших бита
размера мы используем для хранения дополнительной информации. В итоге поле размера + служебных битов займет ровно 4 байта.

Далее идет поле `data`, которое объявлено как массив нулевого размера. Это означает, что данные располагаются непосредственно после конца этой структуры.
Размер структуры `struct MemBlock` равен 4 байтам. Функция `malloc` будет возвращать в программу не адрес самой структуры, а адрес поля `data`,
то есть собственно начало выделенных данных. В нашей реализации `malloc` всегда возвращает адрес, выровненный по 4 байтам. В других реализациях может
потребоваться большее выравнивание --- 8 или даже 16 байт. Когда указатель на динамическую память будет передаваться в функцию `free`, нам потребуется
получить адрес начала соответствующей `struct MemBlock`, для чего достаточно вычесть 4 из значения адреса.

Для хранения состояния кучи потребуется одна глобальная переменная --- указатель на первый блок динамической памяти. Далее мы можем переходить на следующие блоки,
прибавляя размеры выделенных блоков.

```
static struct MemBlock *heap_head = NULL;
```

Напишем функцию `malloc` для выделения блока динамической памяти.
Во-первых, обработаем входной параметр. Если размер запрошенной области равен 0,
то мы все равно должны вернуть корректный указатель на блок динамической памяти,
поэтому в этом случае сделаем размер запрошенной области равным 1.
Память будем выделять блоками размера, кратного константе HEAP_ALIGN,
которая в нашей 32-битной реализации будет равна 4.

Проинициализировать кучу можно при первом запросе на выделение динамической памяти,

```
void *malloc(size_t size)
{
    if (!heap_head) {
        // initialize the heap here
    }
}
```

Как было сказано выше, куча будет размещаться непосредственно после загруженной в память
программы, поэтому при инициализации нам сначала нужно будет узнать адрес, на котором
заканчивается загруженная программа (так называемый break address). Его можно получить,
передав в системный вызов brk нулевой указатель. Затем следует выровнять возвращенный адрес
по требуемому выравниванию. Зная текущий адрес конца загруженной программы и запрошенный размер памяти
мы можем получить новый адрес конца выделенной для программы памяти, который передадим
в системный вызов. А далее останется только проинициализировать поля структуры в памяти.

```
void *malloc(size_t size)
{
    if (!size) size = 1;
    size = (size + HEAP_ALIGN - 1) & -HEAP_ALIGN;
    if (!size) {
        // это проверка на то, что при выравнивании размера вверх мы получили 0
        // например, если передать size == 0xfffffffe
        return NULL;
    }
    // добавляем размер служебной структуры
    uintptr_t fullsize = size + sizeof(struct MemBlock);

    if (!heap_head) {
        // получаем текущий адрес конца программы и выравниваем его вверх
        uintptr_t origaddr = sys_brk(0);
        uintptr_t addr = (origaddr + HEAP_ALIGN - 1) & -HEAP_ALIGN;
        // вычисляем новый адрес конца выделенной программе памяти
        // при этом проверяем, что не случилось переполнения
        uintptr_t reqbrk;
        if (__builtin_add_overflow(addr, fullsize, &reqbrk)) {
            return NULL;
        }
        // запрашиваем новый адрес конца памяти
        uintptr_t newbrk = sys_brk(reqbrk);
        if (newbrk != reqbrk) {
            // память нам не дали
            return NULL;
        }
        // инициализируем служебную структуру
        heap_head = (struct MemBlock*) addr;
        heap_head->size = size >> HEAP_ALIGN_SHIFT;
        heap_head->is_used = 1;
        heap_head->is_last = 1;
        // возвращаем пользователю адрес для использования
        return heap_head->data;
    }
    // ...
}

```

Если же куча уже проинициализирована, то нужно просмотреть список блоков кучи. Если найдется свободный блок подходящего размера, можно
его пометить как занятый и вернуть. Если свободного блока не нашлось, то можно запросить увеличение адреса конца памяти, выделенной программе,
аналогично случаю создания нового блока.

```
void *malloc(size_t size)
{
    // начало - см. выше

    struct MemBlock *ptr = heap_head;
    while (1) {
        if (!ptr->is_used && (ptr->size << HEAP_ALIGN_SHIFT) >= size) {
            // найден свободный блок размера, не меньшего, чем запрошенный
            ptr->is_used = 1;
            return ptr->data;
        }
        if (ptr->is_last) {
            // вычисляем текущий адрес конца кучи
            uintptr_t curbrk = (uintptr_t) ptr + (ptr->size << HEAP_ALIGN_SHIFT) + sizeof(*ptr);
            // вычисляем новый адрес конца кучи
            uintptr_t reqbrk;
            if (__builtin_add_overflow(curbrk, fullsize, &reqbrk)) {
                return NULL;
            }
            uintptr_t newbrk = sys_brk(reqbrk);
            if (newbrk != reqbrk) {
                // память нам не дали
                return NULL;
            }
            ptr->is_last = 0; // текущий блок стал не последним
            // создаем новый последний блок
            ptr = (struct MemBlock*) curbrk;
            ptr->size = size >> HEAP_ALIGN_SHIFT;
            ptr->is_used = 1;
            ptr->is_last = 1;
            return ptr->data;
        }
        // переходим к следующему блоку
        ptr = (struct MemBlock*) ((uintptr_t) ptr + (ptr->size << HEAP_ALIGN_SHIFT) + sizeof(*ptr));
    }
}
```

Реализация функции `free` будет очень простой: мы получаем адрес служебной структуры освобождаемого блока
и помечаем его как свободный.

```
void free(void *ptr)
{
    struct MemBlock *ptr = (struct MemBlock*) ((uintptr_t) ptr - sizeof(*ptr));
    ptr->is_used = 0;
}
```

Эта реализация malloc/free обладает рядом недостатков, перечисленных ниже:
* при выделении памяти из списка свободных блоков мы берем первый свободный блок допустимого размера,
следует же найти свободный блок размера, который лучше соответствует запрошенному, чтобы избежать
неэффективного использования памяти или фрагментации кучи;
* при поиске свободного блока мы просматриваем все блоки динамической памяти: и свободные, и занятые.
Если занятых блоков окажется много, выделение памяти будет работать медленно;
* возможна ситуация, когда запрошенный размер памяти меньше, чем размер свободного блока. В этом случае
следует свободный блок разбить на два блока. Первый свободный блок должен иметь требуемый размер, а во
втором свободном блоке будет остаток изначально большого блока. Тогда первый свободный блок будет помечен как занятый,
а остаток останется свободным и будет доступен для последующего использования;
* если последний блок кучи является свободным, то не нужно создавать новый последний свободный блок требуемого размера,
а лучше увеличить размер последнего свободного блока;
* когда память будет освобождаться с помощью `free` в памяти будут возникать несколько последовательных свободных блоков
динамической памяти. Последовательные свободные блоки динамической памяти должны сливаться в один блок. Это можно делать
как в функции `free`, так и в функции `malloc` при поиске свободного блока.

## Позиционно-независимый код

В примере вывода строки на стандартный поток вывода инструкция `push $msg1` заносит в стек **адрес** в памяти,
по которому размещается строка "Hello". При компоновке программы в исполняемый модуль будет получен такой фрагмент исполняемого файла:
```
08048460 <func>:
 8048460:	56                   	push   %esi
 8048461:	68 50 84 04 08       	push   $0x8048450
 8048466:	e8 a5 fe ff ff       	call   8048310 <printf@plt>
 804846b:	83 c4 08             	add    $0x8,%esp
 804846e:	c3                   	ret    
```

(для получения ассемблерного листинга использовалась команда `objdump --disassemble FILE`)

В этом фрагменте в инструкции вызова `call` для получения адреса, на который нужно переходить, испольуется смещение
`0xfffffea5` (байты a5 fe ff ff), а для загрузки в стек адреса строки, используется абсолютный адрес `0x08048450`
(байты 50 84 04 08).

Если мы заходим разместить исполняемый файл в памяти, начиная с другого адреса, а не с адреса `0x08048034`, инструкция `call`
останется без изменений (так как смещение не изменится при перемещении файла по памяти), а инструкция `push` потребует модификации.
Машинный код, настроенный на работу по фиксированным адресам в памяти, называется **неперемещаемым** (или позиционно-зависимым).

Такой код малопригоден для разделяемых библиотек, так как одна и та же библиотека может располагаться по разным адресам
в адресном пространстве разных процессов.

В **позиционно-независимом** (PIC) коде запрещено использование абсолютных адресов. Все адреса глобальных переменных и областей данных
должны вычисляться относительно текущего положения исполняемого кода.

Один из возможных способов реализации PIC-кода описан ниже.

Для получения текущей позиции в коде используется идиома:
```gas
        call    l1
l1:     popl    %eax
```

То есть мы "вызываем" следующую инструкцию программы, помеченную `l1`.
При этом в стек будет занесен адрес возврата (та же самая инструкция, помеченная `l1`), и затем будет
выполнен переход на саму же инструкцию, помеченную `l1`. После этого адрес инструкции достается из стека
с помощью инструкции `popl`.

```gas
        .text
msg1:   .asciz  "Hello, %d!\n"
        .align  16
        .global func
func:
        pushl   %esi            /* сразу заносим в стек второй аргумент printf */
        call    l1              /* получаем адрес, по которому размещаемся в памяти */
l1:     popl    %eax
        addl    $msg1-l1, %eax  /* прибавляем к адресу l1 смещение msg1 относительно l1 */
        pushl   %eax            /* заносим в стек получившийся абсолютный адрес */
        call    printf
        addl    $8, %esp        /* чистим стек */
        ret
```

## Косвенные переходы и вызовы подпрограмм

Для реализации операторов типа `switch`, или для реализации таблиц виртуальных функций, полезна возможность косвенного перехода или вызова подпрограммы.
Например, инструкция
```gas
        jmp     *%eax
```
выполнит переход по адресу, который располагается в регистре `%eax`, а инструкция `call *%eax` выполнит аналогичный вызов подпрограммы.

Предположим, что в регистре `%eax` передано некоторое значение от 0 до 3. Нам нужно перейти на метку `D0`, `D1`, `D2`, `D3` в зависимости о значения `%eax`.
```gas
        movl    jmptab(,%eax,4), %eax   // загружаем адрес из таблицы адресов
        jmp     *%eax                   // косвенный переход
jmptab: .int    D0, D1, D2, D3          // записываем адреса меток
```