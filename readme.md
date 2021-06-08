<<<<<<< HEAD
# Нотатник

Нотатник — це додаток для написання нотаток різного типу.

## Зміст
- [Використання](#використання)
- [Приклад використання:](#приклад-використання)
- [Опис файлів](#опис-файлів)
- [Опис методів](#опис-методів)
- [Опис полів](#опис-полів)
- [Внески](#внески)
- [Ліцензія](#ліцензія)
## Використання
Після запуску у вас з’явиться вікно з кнопкою **+**, яка додає нотатку(так само як і натискання клавіші **N**).
Як тільки ви натиснете цю кнопку — перед вами з’явиться вікно з редагуванням *Заголовку*, *Тексту* нотатки та можливість додати групу, фото, авдіо, фон для нотатки.
Після створення вами хоча б однієї, ви зможете використовувати *Додавання дочірньої нотатки*, *Сортування за алфавітом*, *Пошук по назві*, *Архівування* та *Видалення* нотатки.
## Приклад використання:

![WSApp](img/start.png?raw=true "Головне меню")
![WSApp](img/note.png?raw=true "Редагування нотатки")
![WSApp](img/archive.png?raw=true "Попередній перегляд нотатки в архіві")
![WSApp](img/search.png?raw=true "Пошук за вказаними символами")
![WSApp](img/delete.png?raw=true "Видалення нотатки")
![WSApp](img/sortZA.png?raw=true "Сортування за датою створення")
## Опис файлів
 **widget.cpp/h/ui** створення головного вікна.
 **Note.cpp/h/ui**	 створення вікна редагування нотатки, 
## Опис методів
   __createShortcutNote(Note *n)__ створення ярлика для нотатки
   __QString getDate()__ отримання точної дати для подальшого вказання у полі дати створення та останнього відкриття нотатки
## Опис полів
__QListWidgetItem *shc__ ярлик нотатки
## Внески
Pull request’и вітаються. Для великих змін, спочатку відкрийте дискусію і обговоріть, що саме ви хочете змінити.

## Ліцензія
[MIT](https://choosealicense.com/licenses/mit/)
=======
# Нотатник

Нотатник — це додаток для написання нотаток різного типу.

## Зміст
- [Використання](#використання)
- [Приклад використання:](#приклад-використання)
- [Опис файлів](#опис-файлів)
- [Опис методів](#опис-методів)
- [Опис полів](#опис-полів)
- [Внески](#внески)
- [Ліцензія](#ліцензія)
## Використання
Після запуску у вас з’явиться вікно з кнопкою "+", яка додає нотатку.
Як тільки ви натиснете цю кнопку — перед вами з’явиться вікно з редагуванням *Заголовку*, *Тексту* нотатки та можливість додати групу, фото, авдіо для нотатки.
Після створення вами хоча б однієї, ви зможете використовувати *Сортування за алфавітом*, *Пошук по назві*, *Архівування* та *Видалення* нотатки.
## Приклад використання:

![WSApp](img/start.png?raw=true "Головне меню")
![WSApp](img/note.png?raw=true "Редагування нотатки")
![WSApp](img/archive.png?raw=true "Попередній перегляд нотатки в архіві")
![WSApp](img/delete.png?raw=true "Видалення нотатки")
![WSApp](img/search.png?raw=true "Пошук за вказаними символами")
![WSApp](img/sortZA.png?raw=true "Пошук за алфавітом")
## Опис файлів
 **widget.cpp/h/ui** створення головного вікна.
 **Note.cpp/h/ui**	 створення вікна редагування нотатки, 
## Опис методів
   __createShortcutNote(Note *n)__ створення ярлика для нотатки
   __QString getDate()__ отримання точної дати для подальшого вказання у полі останнього редагування нотатки
## Опис полів
__QListWidgetItem *sc__ ярлик нотатки
## Внески
Pull request’и вітаються. Для великих змін, спочатку відкрийте дискусію і обговоріть, що саме ви хочете змінити.

## Ліцензія
[MIT](https://choosealicense.com/licenses/mit/)
>>>>>>> 0165f09955f0ac46e867c7510b656950b06022f0
