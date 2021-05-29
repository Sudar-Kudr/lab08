## Laboratory work VIII

Данная лабораторная работа посвещена изучению систем автоматизации развёртывания и управления приложениями на примере **Docker**

```sh
$ open https://docs.docker.com/get-started/
```

## Tasks

- [ok] 1. Создать публичный репозиторий с названием **lab08** на сервисе **GitHub**
- [ok] 2. Ознакомиться со ссылками учебного материала
- [ok] 3. Выполнить инструкцию учебного материала
- [ok] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

```sh
$ export GITHUB_USERNAME=<имя_пользователя>     #присваиваем имя пользователя GitHub в переменную GITHUB_USERNAME
```

```
cd ${GITHUB_USERNAME}/workspace    #спускаемся в workspace
pushd .                           #добавляем в стек текущий каталог
source scripts/activate          #выполняем скрипт

```

```sh
$ git clone https://github.com/${GITHUB_USERNAME}/lab07 lab08             #клонируем репозиторий из lab07 в директорию lab08
$ cd lab08                                                               #переходим директорию lab08
$ git submodule update --init                                           #
$ git remote remove origin                                             #удаляем старую ссылку репозитория
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab08   #добавляем ссылку репозитория в управление репозиториями
```

```sh
$ cat > Dockerfile <<EOF         #создаем файл Dockerfile и пишем операционную систему, где будем работать
FROM ubuntu:18.04
EOF
```

```sh
$ cat >> Dockerfile <<EOF         #дозапысиваем команды (обновляем и устанавливаем пакеты)

RUN apt update
RUN apt install -yy gcc g++ cmake
EOF
```

```sh
$ cat >> Dockerfile <<EOF         #дозапысиваем команды который копирует то что есть в print/ и спускаемся в print

COPY . print/
WORKDIR print
EOF
```

```sh
$ cat >> Dockerfile <<EOF         #дозапысиваем команды для тестирования сборки и инсталляции проекта

RUN cmake -H. -B_build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=_install
RUN cmake --build _build
RUN cmake --build _build --target install
EOF
```

```sh 
$ cat >> Dockerfile <<EOF         #дозапысиваем команды установки значения переменной LOG_PATH

ENV LOG_PATH /home/logs/log.txt
EOF
```

```sh
$ cat >> Dockerfile <<EOF         #дозапысиваем команды указываем в какой директории будут храниться файлы после работы

VOLUME /home/logs
EOF
```

```sh
$ cat >> Dockerfile <<EOF         #дозапысиваем команды спуска в _install/bin

WORKDIR _install/bin
EOF
```

```sh
$ cat >> Dockerfile <<EOF         #дозапысиваем команды вызова утилиты demo

ENTRYPOINT ./demo
EOF
```

```sh
$ docker build -t logger .              #cборка образа
[+] Building 38.5s (15/15) FINISHED                                 
=> [internal] load build definition from Dockerfile           0.0s
=> => transferring dockerfile: 384B                           0.0s
=> [internal] load .dockerignore                              0.0s
=> => transferring context: 2B                                0.0s
=> [internal] load metadata for docker.io/library/ubuntu:18.  3.7s
=> [auth] library/ubuntu:pull token for registry-1.docker.io  0.0s
=> [internal] load build context                              0.1s
=> => transferring context: 1.14MB                            0.1s
=> [1/9] FROM docker.io/library/ubuntu:18.04@sha256:04919776  5.8s
=> => resolve docker.io/library/ubuntu:18.04@sha256:04919776  0.0s
=> => sha256:04919776d30640ce4ed24442d5f7c1a 1.41kB / 1.41kB  0.0s
=> => sha256:ceed028aae0eac7db9dd33bd89c14d5a999 943B / 943B  0.0s
=> => sha256:81bcf752ac3dc8a12d54908ecdfe98a 3.32kB / 3.32kB  0.0s
=> => sha256:4bbfd2c87b7524455f144a03bf387 26.70MB / 26.70MB  4.2s
=> => sha256:d2e110be24e168b42c1a2ddbc4a476a217b 857B / 857B  0.2s
=> => sha256:889a7173dcfeb409f9d88054a97ab2445f5 189B / 189B  0.5s
=> => extracting sha256:4bbfd2c87b7524455f144a03bf387c88b6d4  1.0s
=> => extracting sha256:d2e110be24e168b42c1a2ddbc4a476a217b7  0.0s
=> => extracting sha256:889a7173dcfeb409f9d88054a97ab2445f5a  0.0s
=> [2/9] RUN apt update                                       6.3s
=> [3/9] RUN apt install -yy gcc g++ cmake                   19.2s 
=> [4/9] COPY . print/                                        0.0s 
=> [5/9] WORKDIR print                                        0.0s
=> [6/9] RUN cmake -H. -B_build -DCMAKE_BUILD_TYPE=Release -  1.2s
=> [7/9] RUN cmake --build _build                             0.5s
=> [8/9] RUN cmake --build _build --target install            0.3s
=> [9/9] WORKDIR _install/bin                                 0.0s
=> exporting to image                                         1.3s
=> => exporting layers                                        1.3s
=> => writing image sha256:3c1db7cfd2d60730865473d29db01d55a  0.0s
=> => naming to docker.io/library/logger                      0.0s
```

```sh
$ docker images         #выводим информацию о существующих образах
REPOSITORY                    TAG       IMAGE ID       CREATED          SIZE
logger                        latest    3c1db7cfd2d6   40 seconds ago   326MB
workspace/ubuntu-nodejs       latest    448b5297d2fc   2 weeks ago
..............................................................................
```

```sh
$ mkdir logs                                          #cоздаем директорию logs
$ docker run -it -v "$(pwd)/logs/:/home/logs/" logger  #cоздаем интерактивный процесс logger и передаем текст
text1
text2
text3
<C-D>
```

```sh
$ docker inspect logger             #вывод подробной информации о контейнере
```

```sh
$ cat logs/log.txt                 #вывод информации о вывода утилиты в лог
```

```sh
$ sed -i -e 's/lab07/lab08/g' README.md         #заменяем README.md
```

```sh
$ vim .travis.yml        #измененим .travis.yml для сборки в контейнере
/lang<CR>o
services:
- docker<ESC>
jVGdo
script:
- docker build -t logger .<ESC>
:wq
```

```sh
$ git add Dockerfile                  #добавляем Dockerfile
$ git add .travis.yml                #добавляем .travis.yml
$ git commit -m"adding Dockerfile"  #закомментируем их
$ git push origin main             #отправляем данные на сервер, в удаленный репозиторий main
```

```sh
$ travis login --auto         #авторизируемся на travis
$ travis enable             #делаем проект доступным
```

## Report

```sh
$ popd                                                                           #удаляем из стека текущий каталог
$ export LAB_NUMBER=08                                                          #присваиваем 08 в переменную LAB_NUMBER
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER} #клонируем из ссылки в директорию (в нашем случае-tasks/lab08)
$ mkdir reports/lab${LAB_NUMBER}                                              #создаем в директории reports папку (в нашем случае- lab08) 
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md     #копируем из одной директории в другую
$ cd reports/lab${LAB_NUMBER}                                               #спускаемся в директорию (в наше случае- lab08)
$ edit REPORT.md                                                           #редактируем REPORT.md
$ gist REPORT.md                                                          #сохраняем REPORT.md
```

## Links

- [Book](https://www.dockerbook.com)
- [Instructions](https://docs.docker.com/engine/reference/builder/)

```
Copyright (c) 2015-2021 The ISC Authors
```
