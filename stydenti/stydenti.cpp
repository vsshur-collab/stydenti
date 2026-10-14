#include <iostream>
#include <string>
#include <iomanip> // - для setprecision(2) — вывода среднего балла с двумя знаками после запятой.
#include <cstdlib>
#include <Windows.h>


using namespace std;

const int MAX_STUDENTOV = 30;
const int MAX_GRUPP = 5;
const int MAX_OCENOK = 10;

struct Student
{ 
    string fio;
    string gruppa;
    int ocenki[MAX_OCENOK] = {}; // {} - заполняет изначально нулями
    int kolOcenok = 0; // кол-во оценок изначально 
};

Student studenti[MAX_STUDENTOV]; // Создаёт массив из 30 карточек студентов.
string gruppi[MAX_GRUPP]; // Создаёт массив из 5 строк для названий групп. 
int kolStudentov = 0; // Хранит количество добавленных студентов.
int kolGrupp = 0;

int vvodChisla(string soobshenie, int minimum, int maximum); // int перед vvodChisla — функция вернёт целое число. vvodChisla — название функции. string soobshenie — функция получает текст. int maximum — получает максимальное допустимое число.
string vvodTexta(string soobshenie); // Получает сообщение для пользователя, возвращает введённый текст. 
void pokazGrupp();
int viborGruppi();
void pokazStudentov(); 
int viborStudenta();
bool estGruppa(string nazvanie); // Проверяет существование группы. Возвращает bool: true — да, false — нет.
void dobavitStudenta();
void izmenitStudenta();
void udalitStudenta();
void dobavitGruppu();
void izmenitGruppu();
void udalitGruppu();
void dobavitOcenku();
void sredneeStudenta();
void sredneeGruppi();
void statistikaGruppi();
void nachalnieDannie();

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 
    nachalnieDannie(); // Вызывает функцию, которая добавляет заранее подготовленные данные.
    int vibor; 
    do
    {
        cout << "\n Учебная группа \n";
        cout << "1. Список студентов\n";
        cout << "2. Список групп\n";
        cout << "3. Добавить студента\n";
        cout << "4. Изменить студента\n";
        cout << "5.Удалить студента\n";
        cout << "6. Добавить группу\n";
        cout << "7. Изменить группу\n";
        cout << "8. Удалить группу\n";
        cout << "9. Добавить оценку\n";
        cout << "10. Средний балл студента\n";
        cout << "11. Средний балл группы\n";
        cout << "12. Статистика группы\n";
        cout << "0. Выход\n";
        vibor = vvodChisla("Выберите пункт: ", 0, 12);
        switch (vibor)
        {
        case 1:
            pokazStudentov();
            break;
        case 2:
            pokazGrupp();
            break;
        case 3:
            dobavitStudenta();
            break;
        case 4:
            izmenitStudenta();
            break;
        case 5:
            udalitStudenta();
            break;
        case 6:
            dobavitGruppu();
            break;
        case 7:
            izmenitGruppu();
            break;
        case 8:
            udalitGruppu();
            break;
        case 9:
            dobavitOcenku();
            break;
        case 10:
            sredneeStudenta();
            break;
        case 11:
            sredneeGruppi();
            break;
        case 12:
            statistikaGruppi();
            break;
        case 0:
            cout << "Программа завершена.\n";
            break;
        }
    } while (vibor != 0); // выпролняет меню пока ен убдет введное чилсо равно 0
    return 0;
}

int vvodChisla(string soobshenie, int minimum, int maximum) { // Функция принимает текст приглашения, минимальное и максимальное допустимые числа. 
    string stroka;
    while (true) { // выполняет пока не введет подходящее число 
        cout << soobshenie;
        if (!getline(cin, stroka)) exit(0); 
        int chislo = 0; // в которой из цифр будет собираться число. 
        bool pravilno = stroka != ""; // сли строка не пустая, записывает true. Если пустая — false.
        for (int i = 0; i < (int)stroka.length(); i++) { // int i = 0 — начать с первого символа.  i < (int)stroka.length() — работать, пока не дошли до конца.   i++ — переходить к следующему символу.  (int)— преобразовать длину строки в тип int.
            if (stroka[i] >= '0' && stroka[i] <= '9') { // Проверяет, является ли текущий символ цифрой от 0 до 9. && означает «и» : должны выполняться оба условия.
                if (pravilno) {
                    chislo = chislo * 10 + (stroka[i] - '0'); // Добавляет очередную цифру к числу. Например, ввели "12" -Первая цифра : 0 * 10 + 1 = 12.  - Вторая цифра : 1 * 10 + 2 = 12. stroka[i] - '0' превращает символ цифры в число : '2' → 2.
                    if (chislo > maximum) pravilno = false;
                }
            }
            else pravilno = false; // Если символ оказался не цифрой, ввод тоже считается неправильным. 
        }
        if (pravilno && chislo >= minimum)
            return chislo; // Если ошибок нет и число не меньше минимума, возвращает его и завершает функцию. 
        cout << "Введите целое число от " << minimum << " до " << maximum << ".\n";
    }
}

string vvodTexta(string soobshenie) { // Функция получает приглашение и возвращает введённую строку. 
    string text;
    while (true) {
        cout << soobshenie;
        if (!getline(cin, text)) exit(0); // читает строку и если не читается то завершает рабоут программу
        bool estText = false; // Пока считаем, что содержательного текста нет. 
        for (int i = 0; i < (int)text.length(); i++) {
            if (text[i] != ' ' && text[i] != '\t' && text[i] != '\r') // Если нашёл символ, который не является пробелом, табуляцией или возвратом каретки, отмечает, что текст есть. 
                estText = true; // к той строчке !
        }
        if (estText) return text; // сли нашёл содержательный символ, возвращает строку. 
        cout << "Поле не должно быть пустым.\n";
    }
}

void pokazGrupp() {
    cout << "\nГруппы\n";
    for (int i = 0; i < kolGrupp; i++)
        cout << i + 1 << ". " << gruppi[i] << '\n';
    if (kolGrupp == 0) cout << "Групп нет.\n";
}

int viborGruppi() {
    pokazGrupp();
    if (kolGrupp == 0) return -1; // возращает -1, -1 = групп нет
    return vvodChisla("Номер группы (0 - отмена): ", 0, kolGrupp) - 1; // Запрашивает номер и вычитает 1, чтобы получить индекс массива:
}

void pokazStudentov() {
    cout << "\nСтуденты\n";
    for (int i = 0; i < kolStudentov; i++) { // Перебирает добавленных студентов. 
        cout << i + 1 << ". " << studenti[i].fio << " | " << studenti[i].gruppa << " | Оценки: "; // dыводит номер, ФИО и группу текущего студента.
        for (int j = 0; j < studenti[i].kolOcenok; j++) // перебирает оценки студента 
            cout << studenti[i].ocenki[j] << ' '; // Выводит очередную оценку и пробел. 
        if (studenti[i].kolOcenok == 0)
            cout << "нет";
        cout << '\n';
    }
    if (kolStudentov == 0)
        cout << '\n';
}

int viborStudenta() {
    pokazStudentov();
    if (kolStudentov == 0) return -1;
    return vvodChisla("Номер студента (0 - отмена): ", 0, kolStudentov) - 1; // Запрашивает номер и переводит его в индекс массива. Работает так же, как выбор группы : 1 → индекс 0, отмена 0 → - 1.
}

bool estGruppa(string nazvanie) { // Получает название и возвращает ответ: есть такая группа или нет. 
    for (int i = 0; i < kolGrupp; i++)
        if (gruppi[i] == nazvanie) return true; // Если нашёл совпадение, сразу возвращает true 
    return false; // Если перебрал все группы и совпадений нет, возвращает false. 
}

void dobavitStudenta() {
    if (kolStudentov == MAX_STUDENTOV) {
        cout << "Достигнут предел студентов.\n";
        return;
    }
    int nomerGruppi = viborGruppi(); // Пользователь выбирает группу. Её индекс сохраняется в nomerGrupp 
    if (nomerGruppi == -1) return; // При отмене или отсутствии групп заканчивает функцию. 
    studenti[kolStudentov].fio = vvodTexta("ФИО: "); // Запрашивает ФИО и записывает его в первую свободную карточку
    studenti[kolStudentov].gruppa = gruppi[nomerGruppi]; // Записывает название выбранной группы. 
    studenti[kolStudentov].kolOcenok = 0; // у нового студента оценок сначало нит 
    kolStudentov++;
    cout << "Студент добавлен.\n"; 
}

void izmenitStudenta() {
    int nomerStudenta = viborStudenta(); // выбор студента для изменения 
    if (nomerStudenta == -1) return; 
    string fio = vvodTexta("Новое ФИО: ");
    int nomerGruppi = viborGruppi(); // Запрашивает группу. 
    if (nomerGruppi == -1) return;
    studenti[nomerStudenta].fio = fio; // Записывает новое ФИО. 
    studenti[nomerStudenta].gruppa = gruppi[nomerGruppi]; // Записывает выбранную группу. 
    cout << "Студент изменён. Оценки сохранены.\n";
}

void udalitStudenta() {
    int nomerStudenta = viborStudenta();
    if (nomerStudenta == -1) return;
    for (int i = nomerStudenta; i < kolStudentov - 1; i++) studenti[i] = studenti[i + 1]; //Сдвигает следующих студентов на одно место влево, закрывая место удалённого 
    kolStudentov--; // Уменьшает число студентов
    cout << "Студент удалён.\n";
}

void dobavitGruppu() {
    if (kolGrupp == MAX_GRUPP) {
        cout << "Достигнут предел групп.\n";
        return;
    }
    string nazvanie = vvodTexta("Название новой группы: ");
    if (estGruppa(nazvanie)) {
        cout << "Такая группа уже есть.\n";
        return;
    }
    gruppi[kolGrupp] = nazvanie;
    kolGrupp++;
    cout << "Группа добавлена.\n";
}

void izmenitGruppu() {
    int nomerGruppi = viborGruppi();
    if (nomerGruppi == -1) return;
    string nazvanie = vvodTexta("Новое название: ");
    if (nazvanie != gruppi[nomerGruppi] && estGruppa(nazvanie)) {
        cout << "Такая группа уже есть.\n";
        return;
    }
    string staroeNazvanie = gruppi[nomerGruppi]; // Запоминает старое название. 
    gruppi[nomerGruppi] = nazvanie;
    for (int i = 0; i < kolStudentov; i++) // Перебирает студентов. 
        if (studenti[i].gruppa == staroeNazvanie) studenti[i].gruppa = nazvanie; // У студентов из переименованной группы тоже меняет название группы. 
    cout << "Группа изменена.\n";
}

void udalitGruppu() {
    int nomerGruppi = viborGruppi();
    if (nomerGruppi == -1) return;
    for (int i = 0; i < kolStudentov; i++) {
        if (studenti[i].gruppa == gruppi[nomerGruppi]) {    // провертяет есть ли этот студент в группе и если есть хоть 1 то незя 
            cout << "Нельзя удалить группу, т.к в ней есть студенты. \n";
            return;
        }
    }
    for (int i = nomerGruppi; i < kolGrupp - 1; i++) gruppi[i] = gruppi[i + 1]; // Если группа пустая, сдвигает следующие названия на одно место влево. 
    kolGrupp--;
    cout << "Группа удалена.\n";
}

void dobavitOcenku() {
    int nomerStudenta = viborStudenta();
    if (nomerStudenta == -1) return;
    if (studenti[nomerStudenta].kolOcenok == MAX_OCENOK) {
        cout << "Достигнут предел оценок.\n";
        return;
    }
    int ocenka = vvodChisla("Оценка (2-5): ", 2, 5);
    studenti[nomerStudenta].ocenki[studenti[nomerStudenta].kolOcenok] = ocenka; // Записывает оценку на первое свободное место в массиве оценок выбранного студента.
    studenti[nomerStudenta].kolOcenok++;
    cout << "Оценка добавлена.\n";
}
void sredneeStudenta() {
    int nomerStudenta = viborStudenta();
    if (nomerStudenta == -1)
        return;
    if (studenti[nomerStudenta].kolOcenok == 0) {
        cout << "У студента нет оценок.\n";
        return;
    }
    int summa = 0; // Создаёт переменную для суммы оценок.
    for (int j = 0; j < studenti[nomerStudenta].kolOcenok; j++) summa += studenti[nomerStudenta].ocenki[j]; // Перебирает оценки и складывает их. 
    cout << "Средний балл студента: " << fixed << setprecision(2)
        << (double)summa / studenti[nomerStudenta].kolOcenok << '\n'; // Делит сумму на количество оценок и выводит результат  (double)нужен для дробного результата
}

void sredneeGruppi() {
    int nomerGruppi = viborGruppi();
    if (nomerGruppi == -1)
        return;
    int summa = 0, kolichestvo = 0;
    for (int i = 0; i < kolStudentov; i++) {
        if (studenti[i].gruppa == gruppi[nomerGruppi]) { // Обрабатывает только студентов выбранной группы.
            for (int j = 0; j < studenti[i].kolOcenok; j++) {
                summa += studenti[i].ocenki[j]; kolichestvo++;  // Прибавляет очередную оценку к сумме и увеличивает общий счётчик оценок. 
            }
        }
    }
    if (kolichestvo == 0)
    {
        cout << "В группе нет оценок.\n"; return;
    }
    cout << "Средний балл группы: " << fixed << setprecision(2) << (double)summa / kolichestvo << '\n'; // Выводит сумму всех оценок, делённую на их количество. Здесь считается среднее по всем оценкам группы, а не среднее из средних баллов студентов.
}

void statistikaGruppi() {
    int nomerGruppi = viborGruppi();
    if (nomerGruppi == -1) return;
    int otlichniki = 0, horoshisti = 0, troechniki = 0, sDvoikami = 0, bezOcenok = 0;
    for (int i = 0; i < kolStudentov; i++) {
        if (studenti[i].gruppa != gruppi[nomerGruppi]) continue;
        if (studenti[i].kolOcenok == 0) { bezOcenok++; continue; }
        int minOcenka = 5;
        for (int j = 0; j < studenti[i].kolOcenok; j++)
            if (studenti[i].ocenki[j] < minOcenka) minOcenka = studenti[i].ocenki[j]; // Если очередная оценка ниже сохранённой, записывает её.  Например, для{ 5, 4, 3 } значение изменяется так : 5 → 4 → 3.
        if (minOcenka == 5) otlichniki++;
        else if (minOcenka == 4) horoshisti++;
        else if (minOcenka == 3) troechniki++;
        else sDvoikami++;
    }
    cout << "\nСтатистика группы " << gruppi[nomerGruppi] << '\n';
    cout << "Отличников: " << otlichniki << "\nХорошистов: " << horoshisti;
    cout << "\nТроечников: " << troechniki << "\nС двойками: " << sDvoikami;
    cout << "\nБез оценок: " << bezOcenok << '\n';
}

void nachalnieDannie() {
    gruppi[0] = "БД-1-25";
    gruppi[1] = "БД-2-25";
    gruppi[2] = "БД-3-25"; 
    kolGrupp = 3;
    studenti[0] = { "Иванов Иван Иванович", "БД-1-25",{ 5, 5, 5 }, 3 };
    studenti[1] = { "Петров Пётр Петрович", "БД-1-25",{ 4, 5, 4 }, 3 };
    studenti[2] = { "Сидоров Алексей Сергеевич", "БД-1-25",{ 3, 4, 3 }, 3 };
    studenti[3] = { "Смирнова Анна Олеговна", "БД-1-25",{ 2, 3, 4 }, 3 };
    studenti[4] = { "Кузнецова Мария Андреевна", "БД-1-25",{}, 0 };
    studenti[5] = { "Орлов Максим Павлович", "БД-2-25",{ 5, 4, 5 }, 3 };
    kolStudentov = 6;
}