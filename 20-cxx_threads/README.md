# Нити C++ 2011

## Пререквезиты

Материал данного семинара подразумевает углубленным владением материала
по языку C++ в рамках следующих тем:

 1. [Move-семантика](cxx11_move.md)
 2. [Вызываемые объекты](cxx11_callable.md)
 3. [Анонимные функции](cxx11_lambda.md)


## Класс std::thread

Класс [std::thread](http://www.cplusplus.com/reference/thread/thread/),
объявленный в заголовочном файле `<thread>` реализует нить выполнения.

Конструктор класса принимает переменное количество аргументов, первым из
которых является [вызываемый объект](cxx11_callable.md), остальные аргументы
передаются в качестве аргументов вызова.

Вызов конструктора `std::thread` эквивалентен вызову функции `pthread_create`,
то запуск новой нити происходит **при создании переменной класса std::thread**.

Ожидание завершения работы нити осуществляется вызовом метода `.join()`.

```cpp
#include <iostream>
#include <thread>

void threadFunction()
{
  std::cout << "I'm a function from other thread" << std::endl;
  std::cout.flush();
}

int main()
{
  std::thread thr(threadFunction);
  thr.join();
  return 0;
}
```

Передавать аргументы в вызываемую функцию можно тремя способами:

 1. Передачей аргументов в конструктор `std::thread(...)`
 2. Созданием связанной с помощью `std::bind()` функции. См.
 [дополнительный материал](cxx11_callable.md)
 3. Использованием анонимных функций. См.
 [дополнительный материал](cxx11_lambda.md).

Пример передачи аргументов через конструктор:

```cpp
#include <functional>
#include <iostream>
#include <string>
#include <thread>

void hello(const std::string & name, int & result)
{
  const std::string message = "Hello, " + name + "!";
  std::cout << message << std::endl;
  std::cout.flush();
  result = message.length();
}

int main()
{
  static const std::string name = "World";
  int message_length;
  std::thread thr(hello, name, std::ref(message_length));
  thr.join();
  std::cout << "Message length: " << message_length << std::endl;
  return 0;
}
```
