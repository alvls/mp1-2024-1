# mp1-2024-1
Центральный репозиторий практики группы 23Б1ФИ1 по курсу МП1

## Задания блока 4

### 4.1. Термометр

* Разработать класс **Термометр**.
* Класс должен хранить историю наблюдений за температурой в течение одного календарного (не високосного) года. Наблюдения описываются датой (день, месяц, год) и временем (в часах). При поступлении нового наблюдения для уже существующих даты и времени старое наблюдение заменяется. Температура задается в градусах Цельсия.
* Класс должен содержать необходимые служебные методы.
* Класс должен предоставлять следующие операции: 1) установить начальные дату и время наблюдений, 2) узнать начальные дату и время наблюдений, 3) задать наблюдение, 4) узнать температуру в выбранном наблюдении, 5) задать серию наблюдений для выбранной даты, 6) найти среднюю температуру для выбранной даты, выбранного месяца, за всю историю наблюдений, 7) найти среднюю дневную или ночную температуру для выбранного месяца, 8) сохранить историю наблюдений в файл, 9) считать историю наблюдений из файла.

### 4.2. Весы напольные

* Разработать класс **Весы напольные**.
* Класс должен хранить историю наблюдений за показаниями веса членов семьи (до пяти человек). Показания описываются датой (день, месяц, год) и именем члена семьи. При поступлении нового наблюдения для уже существующей даты старое наблюдение заменяется. Вес задается в килограммах с точностью до 50 граммов.
* Класс должен содержать необходимые служебные методы.
* Класс должен предоставлять следующие операции: 1) установить начальную дату наблюдений, 2) узнать начальную дату наблюдений, 3) задать наблюдение, 4) узнать вес в выбранном наблюдении, 5) найти средний вес члена семьи в выбранном месяце или за всю историю наблюдений, 6) найти минимальный вес члена семьи в выбранном месяце или за всю историю наблюдений и дату, когда он наблюдался 7) найти максимальный вес члена семьи в выбранном месяце или за всю историю наблюдений и дату, когда он наблюдался, 8) сохранить историю наблюдений в файл, 9) считать историю наблюдений из файла.

### 4.3. Шагомер

* Разработать класс **Шагомер**.
* Класс должен хранить историю подсчета шагов владельца. Каждый подсчет описывается датой (день, месяц, год) и интервалом времени (час, минута начала движения, час, минута окончания движения). Подсчет ведется в шагах с точностью до единицы.
* Класс должен содержать необходимые служебные методы.
* Класс должен предоставлять следующие операции: 1) установить дату начала подсчетов, 2) узнать дату начала подсчетов, 3) задать подсчет, 4) получить информацию о выбранном подсчете, 5) найти среднее число шагов в выбранном месяце или за всю историю наблюдений, 6) найти среднее число шагов в выбранный день недели за всю историю наблюдений, 7) найти максимальное число шагов в день в выбранном месяце или за всю историю наблюдений и дату, когда оно было достигнуто, 8) сохранить историю подсчетов в файл, 9) считать историю подсчетов из файла.

### 4.4. Контакты

* Разработать класс **Контакты**.
* Класс должен хранить информацию о контактах владельца. Каждый контакт содержит следующие данные: фамилия; имя; отчество; телефон; день рождения (день, месяц, год); признак, относится ли контакт к избранным. Контакты хранятся упорядоченно по фамилии, имени, отчеству. Фамилия, имя, отчество (ФИО) являются обязательными полями. Данные вводятся на русском языке.
* Класс должен содержать необходимые служебные методы.
* Класс должен предоставлять следующие операции: 1) создать новый контакт, 2) изменить выбранный контакт, 3) найти контакт по ФИО, 4) найти контакт по телефону, 5) выдать все контакты на заданную букву, 6) узнать текущее число контактов, 7) внести контакт в список избранных, 8) удалить контакт из списка избранных, 9) выдать все избранные контакты, 10) удалить контакт, 11) сохранить контакты в файл, 12) считать контакты из файла.

### 4.5. Песенник

* Разработать класс **Песенник**.
* Класс должен хранить информацию о песенных композициях. Каждая песня описывается следующими данными: название, поэт (автор стихов), композитор (автор музыки), исполнитель, название альбома (если входит в какой-то альбом), дата выпуска (день, месяц, год). Песни хранятся упорядоченно по названию. Данные вводятся на русском языке.
* Класс должен содержать необходимые служебные методы.
* Класс должен предоставлять следующие операции: 1) добавить песню, 2) изменить данные выбранной песни, 3) найти песню по названию и исполнителю, 4) выдать все песни заданного поэта, 5) выдать все песни заданного композитора, 6) выдать все песни заданного исполнителя, 7) узнать текущее число песен, 8) удалить песню, 9) сохранить песенник в файл, 10) считать песенник из файла.

### 4.6. Фильмотека

* Разработать класс **Фильмотека**.
* Класс должен хранить информацию о фильмах. Каждый фильм описывается следующими данными: название, режиссер, сценарист, композитор, дата выхода в прокат (день, месяц, год), сборы (в рублях). Фильмы хранятся упорядоченно по названию и годам. Данные вводятся на русском языке.
* Класс должен содержать необходимые служебные методы.
* Класс должен предоставлять следующие операции: 1) добавить фильм, 2) изменить данные выбранного фильма, 3) найти фильм по названию и году, 4) выдать все фильмы заданного режиссера, 5) выдать все фильмы, вышедшие в прокат в выбранном году, 6) выдать заданное число фильмов с наибольшими сборами, 7) выдать заданное число фильмов с наибольшими сборами в выбранном году, 8) узнать текущее число фильмов, 9) удалить фильм, 10) сохранить фильмотеку в файл, 11) считать фильмотеку из файла.


## Распределение заданий блока 4

В таблице указан номер варианта задания из блока.

| ФИО                            | №    |
| ------------------------------ | ---- |
| Акимов Илья Александрович      | 4    |
| Байков Илья Дмитриевич         | 5    |
| Балдин Андрей Леонидович       | 6    |
| Гонозов Леонид Андреевич       | 1    |
| Гусев Дмитрий Алексеевич       | 2    |
| Гутянский Алексей Сергеевич    | 3    |
| Долов Вячеслав Васильевич      | 4    |
| Дорофеев Иван Денисович        | 5    |
| Завьялов Алексей Алексеевич    | 6    |
| Константинов Семён Анатольевич | 1    |
| Кутергин Валентин Тимофеевич   | 2    |
| Кутузов Иван Арсеньевич        | 3    |
| Левонычев Иван Александрович   | 4    |
| Лузан Егор Андреевич           | 5    |
| Лукин Иван Антонович           | 6    |

