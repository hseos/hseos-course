
# RAII

Идиома [RAII](https://ru.wikipedia.org/wiki/%D0%9F%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D0%B5_%D1%80%D0%B5%D1%81%D1%83%D1%80%D1%81%D0%B0_%D0%B5%D1%81%D1%82%D1%8C_%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F)

# Системный вызов `mmap`

[Лекция](https://github.com/hseos/hseos-course/blob/master/00-lectures/os08.pdf)

[Пример](/00-lectures/08-memory/mmap1.c) использования mmap в режиме MAP_SHARED - можно запустить параллельно несколько процессов, и они будут видеть изменения других процессов.

[Пример](/00-lectures/08-memory/mmap2.c) использования mmap в режиме MAP_ANONYMOUS | MAP_SHARED -
можно запустить параллельно несколько процессов, но каждый процесс будет работать со своими данными.

[Пример](/00-lectures/08-memory/mmap3.c) использования mmap в режиме MAP_ANONYMOUS | MAP_SHARED -
будет создан сыновний процесс, и родитель и сын будут читать и модифицировать общие данные.

[Пример](/00-lectures/08-memory/mmap4.c) использования mmap в режиме MAP_ANONYMOUS | MAP_PRIVATE
будет создан сыновний процесс, родитель и сын будут работать со своими данными.

[Пример](/00-lectures/08-memory/mmap5.c) использования mmap в режиме MAP_PRIVATE - изменения в одном процессе не будут видны в других процессах. Обратите внимание, что файл открыт O_RDONLY, а mmap выполняется с правами PROT_READ | PROT_WRITE.

[Пример](/00-lectures/08-memory/mmap6.c) использования mmap в режиме MAP_PRIVATE - изменения в одном процессе не будут видны в других процессах. Обратите внимание, что неспотря на то, что файл открыт O_RDWR, но измененные данные в файл не записываются.

[Пример](/00-lectures/08-memory/mmap7.c) использования mmap в режиме MAP_SHARED - файл открыт в режиме "только для чтения", а mmap пытается подключить его как "чтение-запись", и mmap завершится с ошибкой EPERM - Permission denied.

# Функции работы с разделяемыми библиотеками

[Лекция](https://github.com/hseos/hseos-course/blob/master/00-lectures/os10.pdf)

[Пример](/00-lectures/10-memory/dluser.c) использования функции из загруженной при помощи dlopen динамической библиотеки.

Справка по [dlopen](http://man7.org/linux/man-pages/man3/dlopen.3.html) и [dlsym](http://man7.org/linux/man-pages/man3/dlsym.3.html).

# Виртуальная память

[Лекция](https://github.com/hseos/hseos-course/blob/master/00-lectures/os09.pdf)

[Описание /proc/\[pid\]/maps](http://stackoverflow.com/questions/1401359/understanding-linux-proc-id-maps/1401595#1401595) и [справка по procfs](http://man7.org/linux/man-pages/man5/proc.5.html).
