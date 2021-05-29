[![Build Status](https://travis-ci.org/GolubDobra/lab06.svg?branch=master)](https://travis-ci.org/GolubDobra/lab06)

## Laboratory work VII

Данная лабораторная работа посвещена изучению систем документирования исходного кода на примере **Doxygen**

```ShellSession
$ open https://www.stack.nl/~dimitri/doxygen/manual/index.html
```

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab08** на сервисе **GitHub**
- [X] 2. Выполнить инструкцию учебного материала
- [X] 3. Ознакомиться со ссылками учебного материала
- [X] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial
Устанавливание значение для сервиса **GitHub** и выбираем редактор  
```ShellSession
$ export GITHUB_USERNAME=<имя_пользователя> #Устанавливаем значение переменной окружения GITHUB_USERNAME
$ alias edit=subl # Выбираем текстовый редактор 
```
Инициализация директории **lab08**
```ShellSession
$ git clone https://github.com/${GITHUB_USERNAME}/lab06 lab08
Клонирование в «lab08»…
$ cd lab06 # Переходим в каталог lab08
$ git remote remove origin #Удалить старый репозиторий
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab08 # Добавляем новый удаленный репозиторий
```
Работа с системой документирования **Doxygen**
```ShellSession
$ mkdir docs #Создаем каталог docs
$ doxygen -g docs/doxygen.conf #Создаем файл doxygen.conf
$ cat docs/doxygen.conf #Редактирование файла doxygen.conf
```
Работаем с конфигурационным файлом doxygen.conf
```ShellSession
#Изменение файла doxygen.conf
$ sed -i '' 's/\(PROJECT_NAME.*=\).*$/\1 print/g' docs/doxygen.conf
$ sed -i '' 's/\(EXAMPLE_PATH.*=\).*$/\1 examples/g' docs/doxygen.conf
$ sed -i '' 's/\(INCLUDE_PATH.*=\).*$/\1 examples/g' docs/doxygen.conf
$ sed -i '' 's/\(INPUT *=\).*$/\1 README.md include/g' docs/doxygen.conf
$ sed -i '' 's/\(USE_MDFILE_AS_MAINPAGE.*=\).*$/\1 README.md/g' docs/doxygen.conf
$ sed -i '' 's/\(OUTPUT_DIRECTORY.*=\).*$/\1 docs/g' docs/doxygen.conf
```
Изменение файла README.md
```ShellSession
$ sed -i '' 's/lab06/lab08/g' README.md
```
Документирование и редактирование print.hpp
```ShellSession
# документируем функции print
$ edit include/print.hpp
```
Отправляем последние изменения на **GitHub** сервер
```ShellSession
$ git add . # Отследить изменения всех файлов
$ git commit -m"added doxygen.conf" # Сохранить изменения с комментарием
$ git push origin master # Загрузка файлов на сервер
```
Работаем с сервисом **Travis**
```ShellSession
$ travis login --auto # Авторизация через GitHub
$ travis enable # Включение проекта
```
Работа с файлом документации и отправление последни изменений на **GitHub** сервер
```ShellSession
$ doxygen docs/doxygen.conf # Создание конфигурационного файла документации
$ ls | grep "[^docs]" | xargs rm -rf
$ mv docs/html/* . && rm -rf docs # Перемещение и удаление файлов кроме файла docs
$ git checkout -b gh-pages #Перемещаемся на ветку gh-pages,где хранится документация html
#Добавляем все отредактированные файлы в подтвержденные
$ git add . # Отследить изменения всех файлов
$ git commit -m"added documentation" # Сохранить изменения с комментарием
$ git push origin gh-pages
$ git checkout master  #Перемещаемся на ветку master
```
Делаем Screenshot терминала и загружаем на сервис **Google Drive**
```ShellSession
$ mkdir artifacts && cd artifacts #Создаем каталог artifacts и перемещаемся в него
$ screencapture -T 10 screenshot.jpg #Делаем снимок экрана и помещаем его в каталог artifacts
<Command>-T
$ open https://${GITHUB_USERNAME}.github.io/lab08/print_8hpp_source.html #Открываем ссылку
$ gdrive upload screenshot.jpg #Загружаем скриншот
$ SCREENSHOT_ID=`gdrive list | grep screenshot | awk '{ print $1; }'` # Задаем значения переменной SCREENSHOT_ID
$ gdrive share ${SCREENSHOT_ID} --role reader --type user --email rusdevops@gmail.com # Даем права на просмотр для пользователя rusdevops@gmail.com
$ echo https://drive.google.com/open?id=${SCREENSHOT_ID} #Выводим ссылку на наше изображение
https://drive.google.com/file/d/0Bw35q7PD8b3lNkFPb1IwRWtvdlU/view
```

## Report

```ShellSession
$ cd ~/workspace/labs/
$ export LAB_NUMBER=07
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gistup -m "lab${LAB_NUMBER}"
```

## Links

- [HTML](https://ru.wikipedia.org/wiki/HTML)
- [LAΤΕΧ](https://ru.wikipedia.org/wiki/LaTeX)
- [man](https://ru.wikipedia.org/wiki/Man_(%D0%BA%D0%BE%D0%BC%D0%B0%D0%BD%D0%B4%D0%B0_Unix))
- [CHM](https://ru.wikipedia.org/wiki/HTMLHelp)
- [PostScript](https://ru.wikipedia.org/wiki/PostScript)

```
Copyright (c) 2017 Братья Вершинины
