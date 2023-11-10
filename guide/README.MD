# Гайд по созданию кастомного syscall для linux v6.x (VirtualBox)

## Слёту переходим в режим sudo, чтобы по сто раз не вводить пароль

```console
sudo -s
```

## Открываем терминал

Для сборки выбирайте версию ядра чуть выше версии вашего ядра. Это позволит при ребуте сразу поставить последнюю версию. 

Для того, чтобы посмотреть вашу версию:

```console
uname -r
```

Далее:

```console
wget https://www.kernel.org/pub/linux/kernel/v6.x/linux-6.2.1.tar.xz
```

## Извлекаем сорцы

```console
sudo tar -xvf linux-6.2.1.tar.xz -C/usr/src/
```

## Идем определять syscall

```console
cd /usr/src/linux-6.2.1/
mkdir hello
cd hello
touch hello.c
touch Makefile
```

[hello.c](guide/hello/hello.c) - файл для системного вызова
[Makefile](guide/hello/Makefile) - файл сборки

## Оповещаем ядро о наших приколах

```console
cd /usr/src/linux-6.2.1/
```

1. В файле
```console
vim include/linux/syscalls.h
```
В самом конце **перед endif** размещаем сигнатуру:
```c
asmlinkage long sys_hello(void)
```

1. В файле
```console
vim kernel/sys_ni.c
```
Выставляем заглушку (там, где находятся прочие заглушки):
```c
COND_SYSCALL(hello);
```
1. В файле 
```console
vim Makefile
```
Выполняем поиск по строке `core-y`, добавляем путь до системного вызова:
```Makefile
core-y  := hello/
```

1. В файле 
```console
vim arch/x86/entry/syscalls/syscall_64.tbl
```
Вставляем в самый конец наш системный вызов (запоминаем его номер):
```tbl
548     common      hello       sys_hello
```

## Собираем ядро

n - количество ядер:
```console
cd /usr/src/linux-6.2.1/
make -jn
```

## Инсталлируем модули

```console
cd /usr/src/linux-6.2.1/
make modules_install install
```

## Выполняем перезагрузку

```console
shutdown -r now
```

После перезагрузки проверяем версию 
```console
uname -r
```
Должна быть 6.2.1

## Тестируем системный вызов

```console
cd ~
touch test.c
gcc test.c
./a.out
```
где [test.c](guide/userspace/test.c) - файл пространства пользователя с системным вызовом

После исполнения (если вернулось значение 0), проверяем буфер ядра:
```console
dmesg
```
(Внизу будет ваше сообщение)

# Приложение

- [Пример syscall'ов с различным числом параметров](https://elixir.bootlin.com/linux/v6.2.1/source/include/linux/syscalls.h#L314)
- [Пример создания syscall согласно макросу](https://elixir.bootlin.com/linux/v6.2.1/source/fs/splice.c#L1292) (см. [пример]((guide/hello/hello.c)))
- [Официальный гайд](https://www.kernel.org/doc/html/latest/process/adding-syscalls.html?highlight=syscall_define)
    - chapter: Adding a New System Call
- [Гайд от 2018 года для linux v4.x](https://medium.com/anubhav-shrimal/adding-a-hello-world-system-call-to-linux-kernel-dad32875872)
- [Гайд от 2014 года для linux v3.x](https://tssurya.wordpress.com/2014/08/19/adding-a-hello-world-system-call-to-linux-kernel-3-16-0/)

# FAQ

- [Что делать, чтобы вернуть старое ядро?](https://askubuntu.com/questions/621393/how-to-change-kernel-at-boot)
- Что делать, если ядро не собирается? - поворотить конфиг файл согласно вашим ошибкам, попробовать гайд сначала
- Сколько собирается ядро? - до 3 часов
- Сколько весит скомпиленое ядро - **20 Гб !!!**

# Благодарности

- Сергей Клименков
- Иван Соколов
- Иван Скрябин

> by Тучков Максим Русланович
