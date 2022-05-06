# Прослойка для запуска Winbox кликом по URL в броузере.

Предельно простая утилита, сильно облегчающая жизнь системного администратора.
Позволяет переводить URL вида winbox://user:password@host_ip или winbox://host_ip/user/password в вызов:
winbox.exe host_ip user password , это позволяет сразу залогинится на mikrotik.

## Установка

Просто скопировать куда угодно и зарегистрировать в системе протокол winbox:// .
[В архиве](https://github.com/SerhiiLe/winboxrun/releases) лежит файл winboxrun.reg,
регистрирующий вызов в папку c:\winbox\ . Там же должен лежать winbox.exe . Если надо в другую папке, то надо
подправить этот файл и импортировать в реестр.

## Сборка

Собирал [Dev-C++ / GCC](https://sourceforge.net/projects/orwelldevcpp/). Можно собрать любым компилятором,
но могут понадобится танцы с бубном, собирал Visual Studio, но результат получился хуже.

# A layer to launch Winbox by clicking on a URL in a browser.

An extremely simple utility that greatly simplifies the life of a system administrator.
Allows you to convert a URL like winbox://user:password@host_ip or winbox://host_ip/user/password into a call:
winbox.exe host_ip user password , this allows you to immediately log in to mikrotik.

## Installation

Just copy it anywhere and register the winbox:// protocol in the system. [The archive](https://github.com/SerhiiLe/winboxrun/releases)
contains the winboxrun.reg file, logging call to c:\winbox\ folder. Winbox.exe should also be there.
If you need in another folder, then you need edit this file and import it into the registry.

## Compiling

Compiled by [Dev-C++ / GCC](https://sourceforge.net/projects/orwelldevcpp/). You can compile with any compiler,
but you may need to dance with a tambourine, compiled by Visual Studio, but the result is worse.
