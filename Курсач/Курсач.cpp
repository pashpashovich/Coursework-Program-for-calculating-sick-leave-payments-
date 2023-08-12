// Выполнил Косович Павел, гр.214303
#include "Check.h" // файл с функциями проверки на ввод
#include "Input.h" // файл с функциями ввода логина и пароля
#include <fstream> // работа с файлами через потоки ввода/вывода
#include <string> // для getline()
#include <Windows.h> // работа с консольным окном
#include <iostream> // ввод/вывод в консоль через потоки
#include <iomanip> // для setw()
#include <algorithm> // для sort()
#include <time.h> // для текущего времени
using namespace std; 

struct Date // структура для текущего месяца и года
{
    int month; // номер месяца
    int year; // год
};

typedef struct // тип Account, представляющий собой структуру
{
    int role; // роль (главный администратор, администратор, пользователь)
    int access; // режим доступа (0 - запрещён, 1 - разрешён)
    string login; // логин
    string password; // пароль
} Account;

typedef struct // тип Lists, представляющий собой структуру
{
    char fio[30]; // ФИО (максимум 30 символов)
    int year; // год больничного листа
    string month; // название месяца
    int series_number; // номер больничного листа
    int days; // кол-во дней 
    double paymentperday; // выплата за 1 день
} Lists;

bool registration(); // прототип функции регистрации нового пользователя, которая возвращает true, если продолжать работу программы, а false, если завершить работу программы 
int authorization(string* login, string* password); // прототип функции авторизации с возвращением роли аккаунта (0,1,2) 
void addAccount(int); // прототип функции добавления нового аккаунта
int displayAccounts(); //прототип функции вывода в консоль информации об учётных записях (возвращает количество учётных записей)
void display_applications(); // прототип функции вывода в консоль заявок на регистрацию
string login(int,int); // прототип функции логина с проверкой на уникальность 
void сhooseDelAccount(); // прототип функции удаления учётной записи
void rewriteAccounts(int); // прототип функции перезаписи учётных записей в файл
void correctMyaccount(string*, string*); // прототип функции корректировки учётной записи действующего пользователя 
void addCorrectAccounts(int*, Account*,int);  // прототип функции перезаписи аккаунта
void correctAccounts(); //  прототип функции корректировки учётных записей
void out(); // прототип функции завершения работы программы
int accountstoStruct(); // прототип функции записи информации об учётных записях в массив структур (возвращает кол-во аккаунтов)
int liststoStruct(); // прототип функции записи больничных листов в массив структур
void createFileLists(); // прототип функции создания нового файла с больничными листами
void createFileAccs(); // прототип функции создания нового файла с учётными записями
void displayLists();  //прототип функции вывода в консоль информации о больничных листах
void addLists(); // прототип функции добавления нового больничного листа
void sortLists(); // прототип функции сортировки больничных листов
void  chooseDelLists(); // прототип функции удаления больничных листов
void correctLists(); // прототип функции корректировки информации о больничных листах
void addCorrectLists(int*, Lists*, int);  // прототип функции перезаписи больничного листа
void searchLists(); // прототип функции поиска больничных листов
Date getCurrentDate(); // прототип функции определения текущей даты
string findmonth(int); // прототип функции поиска названия месяца по номеру
void displayTotalpayments(); // прототип функции индивидуального задания
bool isTheonlyoneNumber(int, int); // прототип функции проверки идентификационного номера больничного листа на уникальность


Account* workers = new Account[1]; // выделение памяти для массива эл-тов workers с типом Account
Lists* lists = new Lists[1];  // выделение памяти для массива эл-тов lists с типом Lists
string FILE_OF_ACCOUNTS = "Accounts.txt"; // название файла с учётными записями
string FILE_OF_LISTS = "SickLists.txt"; // название файла с больничными листами



int main()
{
    system("chcp 1251 > nul"); // поключение кириллицы
     HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);  // для зеленого текста
    int role = -1; // для роли
    bool flag3 = true;  // флаг для выхода из цикла
    while(flag3) 
    { 
    cout << "\t\t\t\tДобро пожаловать в систему учёта больничных листов!\nВыберите действие:\n1.Вход\n2.Регистрация\n3.Выход из программы"<<endl;   
    int a=0; // переменная для выбора действия 
    checkChoice(&a, 1, 3); 
    switch (a) // в зависимости от выбора пользователя либо регистрация, либо вход
    {
    case 3:
    {
        out();
        break;
    }
    case 2: // регистрация
    {
        flag3 = registration();
        break;
    }
    case 1:
    cout << "\t\t\t\tПрограмма расчёта выплат по больничным листам"<<endl;
    bool flag2 = true; // флаг для выхода из цикла
    string login, password; // логин и пароль пользователя, вошедшего в систему
    while (flag2) {
    role=authorization(&login,&password); // авторизация с возвращением роли 
    switch (role)
    {
    case 2:
    {
        cout << "Вы вошли в систему в качестве главного администратора!\n\n------------------------------------------  Главный администратор  ----------------------------------------" << endl;
        bool flag = true;
        while (flag)
        {
            cout << "Выберите действие:\n1.Просмотреть учётные записи\n2.Рассмотреть заявки на регистрацию\n3.Добавить учетную запись\n4.Удалить учётную запись\n5.Корректировать информацию о своей учётной записи\n6.Редактировать информацию об учётных записях\n7.Просмотреть информацию о больничных листах\n8.Сортировать больничные листы\n9.Поиск\n10.Рассчитать выплаты за выбранный месяц и год\n11.Выйти из функционала главного администратора\n12.Выйти из программы\n--------------------------------------------------------------------------------------------------------------\n";
            int b=0; // переменная для выбора дейтствия
            checkChoice(&b, 1, 12);
            switch (b)
            {
            case 1:
                displayAccounts();
                break;
            case 2:
                display_applications();
                break;
            case 3:
                addAccount(0);
                break;
            case 4:
                сhooseDelAccount();
                break;
            case 5:
                correctMyaccount(&login,&password);
                break;
            case 6:
                correctAccounts();
                break;
            case 7:
                displayLists();
                break;
            case 8:
                sortLists();
                break;
            case 9:
                searchLists();
                break;
            case 10:
                displayTotalpayments();
                break;
            case 11:
                flag = false;
                flag2 = false;
                cout << "Выход из функционала главного администратора выполнен успешно!\n----------------------------------------------------------------------------\n";
                break;
            case 12:
                out();
                break;
            }
        }
        break;
    }

    case 1:
    {
        cout << "Вы вошли в систему в качестве администратора!\n\n----------------------------------------------  Администратор  -----------------------------------------" << endl;
        bool flag = true;
        while (flag)
        {
            cout << "Выберите действие:\n1.Просмотреть информацию о больничных листах\n2.Добавить больничный лист\n3.Редактирование информации о больничных листах\n4.Удалить больничный лист\n5.Сортировать больничные листы\n6.Поиск\n7.Рассчитать выплаты за выбранный месяц и год\n8.Корректировать информацию о своём аккаунте\n9.Выйти из функционала администратора\n10.Выйти из программы"<<endl;
            int b = 0; 
            checkChoice(&b, 1,10);
            switch (b)
            {
            case 1:
                displayLists();
                break;
            case 2:
                addLists();
                break;
            case 3:
                correctLists();
                break;
            case 4:
                chooseDelLists();
                break;
            case 5:
                sortLists();
                break;
            case 6:
                searchLists();
                break;
            case 7:
                displayTotalpayments();
                break;
            case 8:
                correctMyaccount(&login,&password);
                break;
            case 9:
                flag = false;
                flag2 = false;
                cout << "Выход из функционала администратора выполнен успешно!\n----------------------------------------------------------------------------\n";
                break;
                break;
            case 10:
                out();
                break;
            }
        }
        break;
    }

    case 0:
    {
        cout << "Вы вошли в систему в качестве пользователя!\n\n----------------------------------------------  Пользователь  -----------------------------------------\n" << endl;
        bool flag = true;
        while (flag)
        {
            cout << "Выберите действие:\n1.Просмотреть информацию о больничных листах\n2.Сортировать больничные листы\n3.Поиск\n4.Корректировать информацию о своём аккаунте\n5.Рассчитать выплаты за выбранный месяц и год\n6.Выйти из функционала пользователя\n7.Выйти из программы"<<endl;
            int b = 0;
            checkChoice(&b, 1, 7);
            switch (b)
            {
            case 1:
                displayLists();
                break;
            case 2:
                sortLists();
                break;
            case 3:
                searchLists();
                break;
            case 4:
                correctMyaccount(&login, &password);
                break;
            case 5:
                displayTotalpayments();
                break;
            case 6:
                flag = false;
                flag2 = false;
                cout << "Выход из функционала пользователя выполнен успешно!\n----------------------------------------------------------------------------\n";
                break;
            case 7:
                out();
                break;
            }
        }
        break;
    }
    default:
    {
        cout << "У вас нет прав доступа..." << endl;
        cout << "1.Продолжить выполнение программы\n2.Выйти из программы"<<endl;
        int choice = 0;
        checkChoice(&choice, 1, 2);
        if (choice == 1)
        {
            flag2 = false;
        }
        else
        {
            out();
        }
        break;
    }
    }
    }
    break;
    }
    }
    delete[] workers;
    delete[] lists;
}


bool registration() // функция регистрации нового пользователя, которая возвращает true, если продолжать работу программы, а false, если завершить работу программы 
{
    char* password = new char[10000]; // для ввода пароля с *
    string newLogin, newPassword; // для логина и пароля нового пользователя 
    ofstream fadd(FILE_OF_ACCOUNTS, ios::app); // открываем файл для дозаписи (старые данные не удаляются) 
    newLogin = login(0,accountstoStruct()); // ввод логина нового пользователя с проверкой на уникальность
    while (true)
    {
        cout << "Введите ваш пароль: ";
        input(password);
        newPassword = password;
        cout << endl;
        if (newPassword.length() < 20) break;
        else cout << "Вы ввели слишком длинный пароль (пароль не должен превышать 20 символов)... Повторите ввод" << endl;
    }
    fadd << 0 << " " << setw(50) << newLogin << setw(50) << newPassword << "          " << 0 << "\n"; // записываем нового пользователя с доступом 0
    fadd.close(); // закрываем файл
    cout << "Заявка принята! Ожидайте одобрения) Желаете продолжить сеанс работы программы?\n1.Да\nЛюбая другая клавиша - нет" << endl;
    if (_getch() == '1') return true; // продолжаем работу программы
    return false; // если нет, то выходим из программы
}

int authorization(string *login,string *password) // функция авторизации с возвращением роли аккаунта (0,1,2) 
{
    int role = -1;
    int number=accountstoStruct(); // количество аккаунтов
    if (number == 0)
    {
        createFileAccs();
        cout << "Нет ни одного пользователя системы...Станьте первым)"<<endl;
        addAccount(1);
        accountstoStruct();
    }
    bool flag = true; 
    int i = 0;
    while(flag)
    { 
    char* password2=new char [10000];
    cout << "Введите Ваш логин: ";
    cin >> *login;
    for (i = 0; i < number; i++) // проверка на совпадение
    {
        if (workers[i].login == *login) break;
    }
    if ((i == number) && (workers[0].login != *login)) cout << "Такого пользователя не существует(" << endl;
    else
    { 
         while (true)
        {
            cout << "Введите Ваш пароль: ";
            input(password2);
            cout << endl;
            if (workers[i].password == password2)
            {
                *password = workers[i].password;
                flag = false;
                role = workers[i].role;
                break;
            }
            else cout << "Неверный пароль( Попробуйте ещё раз" << endl;
        }
    }
    }
    if (workers[i].access == 0) return -1;
    return role;
}

void addAccount(int i) { //функция добавления нового аккаунта
    int role = 0;
    string logins;
    string password;
    ofstream fadd(FILE_OF_ACCOUNTS, ios::app); // открываем файл для дозаписи (старые данные не удаляются) 
    if (fadd.is_open()) { // проверяем, открыт ли файл 
        if (i == 1) role = 2;
        else
        {
            cout << "Введите роль нового пользователя (0-пользователь,1-администратор): ";
            checkChoice(&role, 0, 1);
        }
        logins = login(1,accountstoStruct());
        while (true)
        {
            cout << "Введите пароль нового пользователя (не более 20 символов): ";
            cin >> password;
            if (password.length() < 20) break;
            else cout << "Вы ввели слишком длинный пароль (пароль не должен превышать 20 символов)... Повторите ввод" << endl;
        }
        fadd << role << " " << setw(50) << logins << setw(50) << password << "          " << 1 << "\n";
        cout << "Новая учётная запись успешно добавлена!\n--------------------------------------------------------------------------------------------------------------" << endl;
        fadd.close(); // закрываем файл
    }
}

int displayAccounts() // функция вывода в консоль информации об учётных записях (возвращает количество учётных записей)
{
    int count = accountstoStruct();
    if (count == 0)
        cout << "Информации в файле Accounts.txt не обнаружено" << endl;
    else
    {
        // Выводим данные в консоль
        char roles[3][22] = { "Пользователь","Администратор","Главный администратор" };
        int out = -1;
        cout << "           Роль             |          Логин           |          Пароль         | Режим доступа\n----------------------------|--------------------------|-------------------------|--------------------------------------" << endl;
        for (int i = 0; i < count; i++) {
            switch (workers[i].role)
            {
            case 2:
                out = 2;
                break;
            case 1:
                out = 1;
                break;
            case 0:
                out = 0;
                break;
            }
            cout << (i + 1) << ". " << setw(25) << left << roles[out] << "| " << setw(25) << left << workers[i].login << "|" << setw(25) << left << workers[i].password << "|   " << workers[i].access << "\n";
            cout << "----------------------------|--------------------------|-------------------------|--------------------------------------\n";
        }
    }
    return count;
}

string login(int checkingmark,int count) // ввод логина с проверкой на уникальность 
{
    string newLogin; // строка для ввода логина
    bool isTheOnlyOne = true; // для проверки на уникальность
    while (isTheOnlyOne)
    {
        if (count == 0) isTheOnlyOne = false;
        while (true)
        {
            if (checkingmark == 0) cout << "Введите ваш логин (не более 20 символов): ";
            else cout << "Введите новый логин (не более 20 символов): ";
            cin >> newLogin; // ввод логина
            if (newLogin.length() < 20) break;
            else cout << "Вы ввели слишком длинный логин (логин не должен превышать 20 символов)... Повторите ввод" << endl;
        }
        for (int i = 0; i < count; i++) // перебираем все аккаунты 
        {
            if (workers[i].login == newLogin) // если есть совпадение в логине 
            {
                isTheOnlyOne = true; // продолжаем цикл 
                cout << "Введённый Вами логин уже существует...Повторите попытку" << endl;
                break; // выходим из цикла for
            }
            isTheOnlyOne = false;
        }
    }
    return newLogin; // возвращаем введённый логин 
}

void сhooseDelAccount() // функция удаления информации из файла
{
    displayAccounts();
    int choice = 0, num = 0, rez = 0; // переменные для выбора
    int count = accountstoStruct(); // записываем данные из файла FILE_OF_ACCOUNTS в структуру и это кол-во аккаунтов в файле
    if (count != 0) // если кол-во студентов не равно 0
    {
        if (count == 1) cout << "Удаление невозможно,т. к. существует только аккаунт главного администратора...\n----------------------------------------------------------------------------" << endl;
        else
        {
            cout << "Вы уверены, что хотите удалить какой-либо аккаунт?\n1.Да\n2.Нет\n";
            int choice2 = 0;
            checkChoice(&choice2, 1, 2);
            if (choice2 == 1)
            {
                while (true)
                {
                    cout << "Введите номер аккаунта, данные которого вы хотите удалить: ";
                    checkChoice(&num, 1, count);
                    if (num == 1) {
                        cout << "Аккаунт главного администратора удалить нельзя!" << endl;
                        if (count == 1) break;
                        else
                        {
                            cout << "Хотите удалить какой-нибудь другой аккаунт?\n1.Да\n2.Нет" << endl;
                            int choice = 0;
                            checkChoice(&choice, 1, 2);
                            if (choice == 2)
                            {
                                rewriteAccounts(count);
                                cout << "--------------------------------------------------------------------------------------------------------------\n";
                                break;
                            }
                        }
                    }
                    else
                    {
                        ofstream fout(FILE_OF_ACCOUNTS, ios::out); // открыть файл для записи с очищением
                        cout << "Вы уверены , что хотите удалить аккаунт № "<<num<<" из файла ?\n1.Да\n2.Нет" << endl;
                        checkChoice(&rez, 1, 2);
                        num--; // уменьшаем номер студента, т. к. эл-ты массива начинаются с 0
                        fout << "Роль                                      Логин                                             Пароль         Режим доступа" << endl; // записываем эту строку в файл
                        switch (rez) // в зависимости от выбора пользователя
                        {
                        case 1: // если уверен
                            for (int i = num; i < count; i++)// перемещаем выбранного пользователя за пределы массива
                            {
                                workers[i] = workers[i + 1];
                            }
                            count = count - 1; // уменьшаем размер массива  
                            num++; // возвращаем номер аккаунта к начальному значению
                            cout << "Аккаунт № " << num << " удален успешно\n--------------------------------------------------------------------------------------------------------------" << endl;
                            for (int i = 0; i < count; i++) // записываем данные массива эл-тов Account в файл
                            {
                                fout << workers[i].role << " " << setw(50) << workers[i].login << setw(50) << workers[i].password << "          " << 1 << "\n";
                            }
                            break;
                        case 2: // если нет
                            for (int i = 0; i < count; i++) // записываем без изменений
                            {
                                fout << workers[i].role << " " << setw(50) << workers[i].login << setw(50) << workers[i].password << "          " << 1 << "\n";
                            }
                            cout << "Данные остались в неизмененном состоянии\n--------------------------------------------------------------------------------------------------------------" << endl;
                            break;
                        }
                        fout.close(); // закрываем файл
                        break;
                    }
                }
            }
            else cout << "Ничего не будет удалено!" << endl;
        }
    }
    else
    {
        cout << "Информации в файле FILE_OF_ACCOUNTS не обнаружено" << endl;
    }
}


void rewriteAccounts(int count)
{
    ofstream fout(FILE_OF_ACCOUNTS, ios::out); // открываем файл для записи с очищением
    fout << "Роль                                      Логин                                             Пароль         Режим доступа" << endl; // записываем в файл
    for (int i = 0; i < count; i++) // записываем э-ты массива workers в файл с изменениями
    {
        fout << workers[i].role << " " << setw(50) << workers[i].login << setw(50) << workers[i].password << "          " << workers[i].access << "\n";
    }
    fout.close(); // закрываем файл
}


void correctMyaccount(string* login2, string* password2) // функция корректировки аккаунта действующего пользователя 
{
    string newlogin, newpassword;
    char* password = new char[10000];
    int count = accountstoStruct(); // кол-во аккаунтов в файле
    int nom = 0; // номер пользователя в массиве
    for (int i = 0; i < count; i++)
    {
        if (workers[i].login == *login2 && workers[i].password == *password2)
            nom = i;
    }
    cout << "Что вы хотите откорректировать?\n1.Логин\n2.Пароль\n";
    int choice = 0;
    checkChoice(&choice, 1, 2);
    switch (choice)
    {
    case 1:
    {
        while (true)
        {
            newlogin = login(1,accountstoStruct());
            if (newlogin.length() < 20) break;
            else cout << "Вы ввели слишком длинный логин (логин не должен превышать 20 символов)... Повторите ввод" << endl;
        }
        workers[nom].login = newlogin; // перезаписываем логин аккаунта под номером number
        *login2 = newlogin;
        cout << "Ваш логин откорректирован)\n--------------------------------------------------------------------------------------------------------------\n";
        break;
    }
    case 2:
    {
        while (true)
        {
            cout << "Введите новый пароль (не более 20 символов): ";
            input(password);
            cout << endl;
            newpassword = password;
            if (newpassword.length() < 20) break;
            else cout << "Вы ввели слишком длинный пароль (пароль не должен превышать 20 символов)... Повторите ввод" << endl;
        }
        workers[nom].password = newpassword; // перезаписываем логин аккаунта под номером number
        *password2 = newpassword;
        cout << "Ваш пароль откорректирован)\n--------------------------------------------------------------------------------------------------------------\n";
        break;
    }
    }
    rewriteAccounts(count);
}

void correctAccounts() {
    displayAccounts();
    int num_st = 0; // номер выбранного аккаунта
    int count = accountstoStruct(); // кол-во аккаунтов в файле
    if (count != 0) { // если в файле есть информация
        cout << "Вы уверены, что хотите откорректировать какой-либо аккаунт?\n1.Да\n2.Нет\n";
        int choice = 0;
        checkChoice(&choice, 1, 2);
        if (choice == 1)
        {
            while (true)
            {
                cout << "Введите номер аккаунта, данные которого вы хотите откорректировать:";
                checkChoice(&num_st, 1, count);
                if (num_st == 1) cout << "Вы выбрали свой же аккаунт...Повторите попытку ввода)" << endl;
                else break;
            }
            num_st--; // уменьшаем, т. к. эл-ты массива начинаются с 0
            addCorrectAccounts(&num_st, workers, count); // вызываем ф-цию корректировки данных
            num_st++; // увеличиваем обратно
            ofstream fout(FILE_OF_ACCOUNTS, ios::out); // открываем файл для записи с очищением
            fout << "Роль                                      Логин                                             Пароль         Режим доступа" << endl; // записываем в файл
            cout << "Данные аккаунта № " << num_st << " откорректированы\n--------------------------------------------------------------------------------------------------------------\n";
            for (int i = 0; i < count; i++) // записываем э-ты массива workers в файл с изменениями
            {
                fout << workers[i].role << " " << setw(50) << workers[i].login << setw(50) << workers[i].password << "          " << workers[i].access << "\n";
            }
            fout.close(); // закрываем файл
        }
        else
            cout << "Данные аккаунтов остались в неизмененном состоянии)" << endl;
    }
    else {
        cout << "Информации в файле Accounts.txt не обнаружено" << endl;
    }
}

void out() { // функция завершения работы программы
    cout << "Вы уверены, что хотите выйти из программы?\n1.Да\n2.Нет" << endl;
    int x = 0;
    checkChoice(&x, 1, 2); // инициализация x с проверкой
    switch (x) // в зависимости от значения  x
    {
    case 1:
        cout << "Выход выполнен успешно" << endl;
        exit(0); // завершаем выполнение программы
    case 2:
        break;
    }
}

int accountstoStruct() // функция записи информации об аккаунтах в массив структур (возвращает кол-во аккаунтов)
{
    ifstream fin(FILE_OF_ACCOUNTS, ios_base::in); // открываем файл для чтения
    int count = 0; // кол-во аккаунтов в файле
    char f[] = "Роль                                      Логин                                             Пароль         Режим доступа";
    if (fin.is_open())
    {
        fin.ignore(strlen(f), '\n'); // игнорируем 1-ую строку файла
        while (fin >> workers->role >> workers->login >> workers->password >> workers->access)
        {
            count++; // считаем кол-во аккаунтов в файле Accounts.txt
        }
        workers = new Account[count + 1]; // выделяем память для массива 
        fin.close(); // закрываем данный поток
        ifstream fin(FILE_OF_ACCOUNTS, ios_base::in); // открываем ещё раз
        fin.ignore(strlen(f), '\n'); // игнорируем 1-ую строку файла
        for (int i = 0; fin >> workers[i].role >> workers[i].login >> workers[i].password >> workers[i].access; i++); // записываем в массив workers данные из файла
        fin.close(); // закрываем файл Accounts.txt 
    }
    else
        cout << "Не удалось открыть файл" << endl;
    return count; // возвращаем значение кол-ва аккаунтов в файле 
}

void createFileAccs() { // для создания нового файла
    ofstream fout(FILE_OF_ACCOUNTS, ios::out); //открываем файл для записи (очищаем)
    if (fout.is_open()) // если открыт
    {
        cout << "Файл успешно создан)" << endl;
        fout << "Роль                                      Логин                                             Пароль         Режим доступа" << endl; // записываем в файл
        fout.close(); // закрываем файл
    }
    else
        cout << "Ошибка в создании файла!" << endl;
}

void addLists() { //функция добавления нового больничного листа
    int count = liststoStruct();
    char fio[30] = "\n"; // ФИО (максимум 30 символов)
    int year = 0; // год больничного листа
    string monthn; // название месяца
    int series_number = 0; // номер больничного листа
    int days = 0; // кол-во дней 
    double paymentperday = 0; // выплата за 1 день
    ofstream fadd(FILE_OF_LISTS, ios::app); // открываем файл для дозаписи (старые данные не удаляются) 
    if (fadd.is_open()) { // проверяем, открыт ли файл 
        cout << "\nВведите ФИО больного: ";
        inputFIO(fio);
        cout << endl;
        int name_len = strlen(fio); // длина введёного ФИО
        for (int i = 0; i < name_len; i++) // цикл расставления точек вместо пробелов
        {
            if (fio[i] == 32) // если пробел, то 
            {
                fio[i] = '_';
            } //заменяем на нижнее подчёркивание
        }
        Date date = getCurrentDate();
        cout << "\nВведите год больничного листа: ";
        checkChoice(&year, 1900, date.year);
        cout << "\nВведите номер месяца больничного листа: ";
        int month = 0;
        if (year == date.year)
            checkChoice(&month, 1, date.month);
        else checkChoice(&month, 1, 12);
        monthn = findmonth(month);
        while (true)
        {
            cout << "\nВведите идентификационный номер больничного листа (семизначный): ";
            checkChoice(&series_number, 1000000, 9999999);
            if (isTheonlyoneNumber(series_number, count)) break;
            else cout << "Такой идентификационный номер больничного листа уже зарегистрирован... Повторите попытку)" << endl;
        }
        cout << "\nВведите количество дней: ";
        checkChoice(&days, 1, 31);
        cout << "\nВведите выплату за 1 день в бел. рублях: ";
        paymentperday = checkDouble();
        cout << endl;
        cout << "Больничный лист успешно добавлен в систему!\n--------------------------------------------------------------------------------------------------------------\n";
        fadd << setw(30) << fio << setw(9) << year << setw(10) << monthn << setw(15) << series_number << setw(18) << days << setw(18) << paymentperday << " " << "\n";
        fadd.close(); // закрываем файл
    }
}

void  chooseDelLists() // функция удаления информации из файла
{
    displayLists();
    int choice = 0, num = 0, rez = 0; // переменные для выбора
    int count = liststoStruct(); // записываем данные из файла Lists.txt в структуру и это кол-во больничных в файле
    if (count != 0) // если кол-во больничных листов не равно 0
    {
        ofstream fout(FILE_OF_LISTS, ios::out); // открыть файл для записи с очищением
        cout << "Введите номер больничного листа, который вы хотите удалить: ";
        checkChoice(&num, 1, count);
        num--; // уменьшаем номер больничного листа, т. к. эл-ты массива начинаются с 0
            cout << "Вы уверены , что хотите удалить данный больничный лист?\n1.Да\n2.Нет" << endl;
            checkChoice(&rez, 1, 2);
            fout << "                      ФИО          Год    Месяц  Идентификационный номер Количество дней  Оплата за 1 день" << endl; // записываем эту строку в файл
            switch (rez) // в зависимости от выбора пользователя
            {
            case 1: // если уверен
                for (int i = num; i < count; i++)// перемещаем выбранный больничный лист за пределы массива
                {
                    lists[i] = lists[i + 1];
                }
                count = count - 1; // уменьшаем размер массива  
                num++; // возвращаем номер больничного листа к начальному значению
                cout << "Больничный лист № " << num << " удален из файла\n--------------------------------------------------------------------------------------------------------------" << endl;
                for (int i = 0; i < count; i++) // записываем данные массива эл-тов Lists в файл
                {
                    fout << setw(30) << lists[i].fio << setw(9) << lists[i].year << setw(10) << lists[i].month << setw(15) << lists[i].series_number << setw(18) << lists[i].days << setw(18) << lists[i].paymentperday << " " << "\n";
                }
                break;
            case 2: // если нет
                for (int i = 0; i < count; i++) // записываем без изменений
                {
                    fout << setw(30) << lists[i].fio << setw(9) << lists[i].year << setw(10) << lists[i].month << setw(15) << lists[i].series_number << setw(18) << lists[i].days << setw(18) << lists[i].paymentperday << " " << "\n";
                }
                cout << "Данные остались в неизменном состоянии\n--------------------------------------------------------------------------------------------------------------" << endl;
                break;
            }
            fout.close(); // закрываем файл
    }
    else
    {
        cout << "Информации в файле FILE_OF_ACCOUNTS не обнаружено" << endl;
    }
}

int liststoStruct() // функция записи больничных листов в массив структур
{
    ifstream fin(FILE_OF_LISTS, ios_base::in); // открываем файл для чтения
    int count = 0; // кол-во аккаунтов в файле
    char f[] = "                      ФИО          Год    Месяц  Идентификационный номер Количество дней  Оплата за 1 день";
    if (fin.is_open())
    {
        fin.ignore(strlen(f), '\n'); // игнорируем 2-ую строку файла
        while (fin>>lists->fio>>lists->year>>lists->month>>lists->series_number >>lists->days>>lists->paymentperday)
        {
            count++; // считаем кол-во аккаунтов в файле SickLists.txt
        }
        lists = new Lists[count + 1]; // выделяем память для массива 
        fin.close(); // закрываем данный поток
        ifstream fin(FILE_OF_LISTS, ios_base::in); // открываем ещё раз
        fin.ignore(strlen(f), '\n'); // игнорируем 2-ую строку файла
        for (int i = 0; fin >> lists[i].fio >> lists[i].year >> lists[i].month >> lists[i].series_number >> lists[i].days >> lists[i].paymentperday; i++); // записываем в массив workers данные из файла
    }
    else
    { 
        cout << "Не удалось открыть файл. Он будет создан)" << endl;
        createFileLists();
    }
    fin.close(); // закрываем файл SickLists.txt 
    return count; // возвращаем значение кол-ва аккаунтов в файле 
}



void createFileLists() { // для создания нового файла
    ofstream fout(FILE_OF_LISTS, ios::out); //открываем файл для записи (очищаем)
    if (fout.is_open()) // если открыт
    {
        cout << "Файл успешно создан)" << endl;
        fout << "                      ФИО          Год    Месяц  Идентификационный номер Количество дней  Оплата за 1 день" << endl; // записываем в файл
        fout.close(); // закрываем файл
    }
    else
        cout << "Ошибка в создании файла!" << endl;
}


void displayLists()
{
    int count = liststoStruct();
    if (count == 0)
        cout << "Информации в файле SickLists.txt не обнаружено" << endl;
    else
    {
        // Выводим данные в консоль
        int out = -1;
        cout << "                ФИО              | Год  |  Месяц    |Идентификационный номер|Количество дней |Оплата за 1 день, рубли" << endl;
        cout << "---------------------------------|------|-----------|-----------------------|----------------|--------------------------\n";
        for (int i = 0; i < count; i++) {
            string fio; // для красивого вывода
            fio = lists[i].fio;
            for (int i = 0; i < fio.length(); i++)
            {
                if (fio[i] == '_') fio[i] = ' ';
            }
            cout << (i + 1) << ". " << setw(30) << left << fio << "| " << setw(5) << left << lists[i].year << "|" << setw(11) << left << lists[i].month << "|" << setw(23) << left << lists[i].series_number << "|" << setw(16) << left << lists[i].days << "|" << setw(5) << left << lists[i].paymentperday << "\n";
            cout << "---------------------------------|------|-----------|-----------------------|----------------|--------------------------\n";
        }
    }
}


void display_applications() // функция вывода в консоль заявок на регистрацию
{
    int count = accountstoStruct();
    int num = 1;
    for (int i = 0; i < count; i++) {
        if (workers[i].access == 0)
        {
            num++;
        }
    }
    if (num == 1) 
    { 
        cout << "Заявок на регистрацию нет(" << endl;
        cout<<"--------------------------------------------------------------------------------------------------------------\n";
    }
    else
    { 
    char roles[3][22] = { "Пользователь","Администратор","Главный администратор" };
    Account* applications = new Account[1]; // выделение памяти для массива эл-тов application с типом Account
    cout << "\t\t\t\t\tЗаявки на регистрацию\n" << endl;
    cout << "           Роль             |          Логин           |          Пароль\n----------------------------|--------------------------|---------------------------------------------------------------" << endl;
    num = 1;
        for (int i = 0; i < count; i++) {
            if (workers[i].access == 0)
            { 
                cout << num << ". " << setw(25) << left << roles[workers[i].role] << "| " << setw(25) << left << workers[i].login <<"|"<< setw(25) << left << workers[i].password << "          " << "\n";
                cout << "----------------------------|--------------------------|---------------------------------------------------------------\n";
                applications = new Account[num];
                applications[num - 1] = workers[i];
                num++;
            }
        }
        num--;
        cout << "Хотите подтвердить какую-нибудь заявку?\n1.Да\n2.Нет\n";
        int choice = 0;
        checkChoice(&choice, 1, 2);
        if (choice == 1)
        {
            cout << "Введите номер аккаунта для подтверждения регистрации: ";
            int numofAccount = 0;
            checkChoice(&numofAccount, 1, num);
            cout << "Вы уверены, что хотите подтвердить регистрацию аккаунта №" << numofAccount << "\n1.Да\n2.Нет\n";
            int choice2 = 0;
            checkChoice(&choice2, 1, 2);
            if (choice2 == 1)
            {
                for (int i = 0; i < count; i++) {
                    if (applications[numofAccount - 1].login == workers[i].login) // можно проверить по логину, т. к. все логины уникальны
                    {
                        workers[i].access = 1;
                    }
                }
                rewriteAccounts(count);
                cout << "Регистрация подтверждена)" << endl;
            }
            else cout << "Регистрация не подтверждена("<<endl;


        }
        else cout << endl;
    }
}

void correctLists() { // функция корректировки информации о больничных листах
    displayLists();
    int num_st = 0; // номер выбранного аккаунта
    int count = liststoStruct(); // кол-во больничных листов в файле
    if (count != 0) { // если в файле есть информация
        ofstream fout(FILE_OF_LISTS, ios::out); // открываем файл для записи с очищением
        cout << "Введите номер больничного листа, данные которого вы хотите откорректировать:";
        checkChoice(&num_st, 1, count);
        num_st--; // уменьшаем, т. к. эл-ты массива начинаются с 0
        fout << "                      ФИО          Год    Месяц  Идентификационный номер Количество дней  Оплата за 1 день" << endl; // записываем в файл
        addCorrectLists(&num_st, lists,count); // вызываем ф-цию корректировки данных
        num_st++; // увеличиваем обратно
        cout << "Данные больничного листа № " << num_st << " откорректированы\n--------------------------------------------------------------------------------------------------------------\n" << endl;
        for (int i = 0; i < count; i++) // записываем э-ты массива workers в файл с изменениями
        {
            fout << setw(30) << lists[i].fio << setw(9) << lists[i].year << setw(10) << lists[i].month << setw(15) << lists[i].series_number << setw(18) << lists[i].days << setw(18) << lists[i].paymentperday << " " << "\n";
        }
        fout.close(); // закрываем файл
    }
    else {
        cout << "Информации в файле SickLists.txt не обнаружено" << endl;
    }
}

void addCorrectAccounts(int* number, Account* workers,int count)  // перезаписываем э-т массива workers под номером number
{
    int access=-1,role=-1;
    char* password = new char[10000];
    string logins;
    cout << "Выберите данные для корректировки:\n1.Роль\n2.Логин\n3.Пароль\n4.Режим доступа\n";
    int a=0;
    checkChoice(&a, 1, 4);
    switch (a)
    {
    case 1:
        cout << "\nВведите новую роль (1-администратор, 0-пользователь): ";
        checkChoice(&role, 0, 1);
        workers[*number].role = role; // перезаписываем роль от аккаунта под номером number
        break;
    case 2:
        logins = login(1,count);
        workers[*number].login = logins; // перезаписываем логин аккаунта под номером number
        break;
    case 3:
        cout << "\nВведите новый пароль: ";
        input(password);
        cout << endl;
        workers[*number].password = password; // перезаписываем пароль от аккаунта под номером number
        break;
    case 4:
        cout << "\nВведите новый режим доступа (1-доступ, 0 - доступ не разрешён): ";
        checkChoice(&access, 0, 1);
        workers[*number].access = access; // перезаписываем режим доступа от аккаунта под номером number
        break;
    }
}

void addCorrectLists(int* number, Lists* lists, int count)  // перезаписываем э-т массива lists под номером number
{
    int access = -1, role = -1, name_len = 0, month = 0, series_number = 0, year = 0, days=0;
    string monthn;
    double paymentperday = 0;
    Date date = getCurrentDate();
    cout << "Выберите данные для корректировки:\n1.ФИО\n2.Год\n3.Месяц\n4.Идентификационный номер\n5.Количество дней\n6.Оплата за 1 день\n";
    int a = 0;
    checkChoice(&a, 1, 6);
    switch (a)
    {
    case 1:
    {
        cout << "\nВведите ФИО больного: ";
        inputFIO(lists[*number].fio);
        cout << endl;
        int name_len = strlen(lists[*number].fio); // длина введёного ФИО
        for (int i = 0; i < name_len; i++) // цикл расставления точек вместо пробелов
        {
            if (lists[*number].fio[i] == 32) // если пробел, то 
            {
                lists[*number].fio[i] = '_';
            } //заменяем на нижнее подчёркивание
        }
        break;
    }
    case 2:
    {
        cout << "\nВведите новый год больничного листа: ";
        checkChoice(&year, 1900, date.year);
        lists[*number].year = year; // перезаписываем год больничного листа под номером number
        break;
    }
    case 3:
    {
        cout << "\nВведите новый номер месяца больничного листа: ";
        month = 0;
        if (year == date.year)
            checkChoice(&month, 1, date.month);
        else checkChoice(&month, 1, 12);
        monthn = findmonth(month);
        lists[*number].month = monthn; // перезаписываем  номер месяца больничного листа под номером number
        break;
    }
    case 4:
    {
        while(true)
        { 
        cout << "\nВведите новый идентификационный номер больничного листа: ";
        checkChoice(&series_number, 1000000, 9999999);
        if (isTheonlyoneNumber(series_number,count))
        {
            lists[*number].series_number = series_number; // перезаписываем  ИН больничного листа под номером number
            break;
        }
        else cout << "Такой идентификационный номер больничного листа уже зарегистрирован... Повторите попытку)" << endl;
        }
        break;
    }
    case 5:
    {
        cout << "\nВведите новое количество дней: ";
        checkChoice(&days, 1, 31);
        lists[*number].days = days; // перезаписываем количество дней больничного листа под номером number
        break;
    }
    case 6:
    {
        cout << "\nВведите новую выплату за 1 день: ";
        paymentperday=checkDouble();
        cout << endl;
        lists[*number].paymentperday = paymentperday; // перезаписываем выплату за 1 день больничного листа под номером number
        break;
    }
    }
}


string findmonth(int month) // функция поиска названия месяца по номеру
{
    switch (month)
    {
    case 1:
        return "январь";
    case 2:
        return "февраль";
    case 3:
        return "март";
    case 4:
        return "апрель";
    case 5:
        return "май";
    case 6:
        return "июнь";
    case 7:
        return "июль";
    case 8:
        return "август";
    case 9:
        return "сентябрь";
    case 10:
        return "октябрь";
    case 11:
        return "ноябрь";
    case 12:
        return "декабрь";
    }

}

void sortLists() {
    int choice = 0;
    int count = liststoStruct();
    if (count != 0) {
        ofstream fout(FILE_OF_LISTS, ios::out);
        cout << "Выберите критерий сортировки больничных листов:\n1.По количеству больничных дней\n2.По оплате за 1 день\n3.В алфавитном порядке ФИО\n";
        checkChoice(&choice, 1, 3);
        fout << "                      ФИО          Год    Месяц  Идентификационный номер Количество дней  Оплата за 1 день" << endl;
        bool swapped; // для меньшего числа итераций
        switch (choice) {
        case 1: {
            int choice = 0;
            cout << "1.По возрастанию\n2.По убыванию\n";
            checkChoice(&choice, 1, 2);
            for (int i = 0; i < count - 1; i++) {
                swapped = false;
                for (int j = 0; j < count - i - 1; j++) {
                    if (choice == 1) {
                        if (lists[j].days > lists[j + 1].days) {
                            std::swap(lists[j], lists[j + 1]);
                            swapped = true;
                        }
                    }
                    else {
                        if (lists[j].days < lists[j + 1].days) {
                            std::swap(lists[j], lists[j + 1]);
                            swapped = true;
                        }
                    }
                }
                if (!swapped) {
                    break;
                }
            }
            break;
        }
        case 2: {
            int choice = 0;
            cout << "1.По возрастанию\n2.По убыванию\n";
            checkChoice(&choice, 1, 2);
            for (int i = 0; i < count - 1; i++) {
                swapped = false;
                for (int j = 0; j < count - i - 1; j++) {
                    if (choice == 1) {
                        if (lists[j].paymentperday > lists[j + 1].paymentperday) {
                            std::swap(lists[j], lists[j + 1]);
                            swapped = true;
                        }
                    }
                    else {
                        if (lists[j].paymentperday < lists[j + 1].paymentperday) {
                            std::swap(lists[j], lists[j + 1]);
                            swapped = true;
                        }
                    }
                }
                if (!swapped) {
                    break;
                }
            }
            break;
        }
        case 3: {
            for (int i = 0; i < count - 1; i++) {
                swapped = false;
                for (int j = 0; j < count - i - 1; j++) {
                    if (strcmp(lists[j].fio, lists[j + 1].fio) > 0) {
                        std::swap(lists[j], lists[j + 1]);
                        swapped = true;
                    }
                }
                if (!swapped) {
                    break;
                }
            }
            break;
        }
        }
        cout << "Элементы успешно отсортированы\n--------------------------------------------------------------------------------------------------------------\n";
        for (int i = 0; i < count; i++) {
            fout << setw(30) << lists[i].fio << setw(9) << lists[i].year << setw(10) << lists[i].month << setw(15) << lists[i].series_number << setw(18) << lists[i].days << setw(18) << lists[i].paymentperday << " " << "\n";
        }
        fout.close();
    }
    else {
        cout << "Информации в файле SickLists.txt не обнаружено" << endl;
    }
}


void searchLists() // функция поиска больничных листов
{
    int number = liststoStruct();
    if (number>0)
    { 
    cout << "Выберите по какому параметру производить поиск:\n1. По ФИО\n2. По году\n3. По выплате за 1 день\n4. По номеру больничного листа" << endl;
    int n = 0;
    checkChoice(&n, 1, 4);
    switch (n)
    {
    case 1:
    {
        int finds = 0,num=0;
        cout << "Введите ФИО: ";
        char poisk [30];
        inputFIO(poisk);
        cout << endl;
        for (int i = 0; i < strlen(poisk); i++) // цикл расставления точек вместо пробелов
        {
            if (poisk[i] == 32) // если пробел, то 
            {
                poisk[i] = '_';
            } //заменяем на нижнее подчёркивание
        }
        cout << "Результаты поиска" << endl;
        for (int i = 0; i < number; i++)
        {
             if (strcmp(lists[i].fio, poisk) == 0)
            {
                finds++;
            }
        }
        if (finds > 0)
        {
            cout << "                ФИО              | Год  |  Месяц    |Идентификационный номер|Количество дней |Оплата за 1 день, рубли" << endl;
            cout << "---------------------------------|------|-----------|-----------------------|----------------|--------------------------\n";
            for (int i = 0; i < number; i++)
            {
                if (strcmp(lists[i].fio, poisk) == 0)
                {
                    cout << (num + 1) << ". " << setw(30) << left << lists[i].fio << "| " << setw(5) << left << lists[i].year << "|" << setw(11) << left << lists[i].month << "|" << setw(23) << left << lists[i].series_number << "|" << setw(16) << left << lists[i].days << "|" << setw(5) << left << lists[i].paymentperday << "\n";
                    cout << "---------------------------------|------|-----------|-----------------------|----------------|--------------------------\n";
                    num++;
                }
            }
        }
        else cout << "Ничего не найдено..." << endl;

        break;
    }
    case 2:
    {
        int year = 0;
        int num = 0;
        int finds = 0;
        cout << "Введите год: ";
        Date date = getCurrentDate();
        checkChoice(&year,1900,date.year);
        cout << "Результаты поиска" << endl;
        for (int i = 0; i < number; i++)
        {
            if (lists[i].year == year)
            {
                finds++;
            }
        }
        if (finds > 0)
        {
            cout << "                ФИО              | Год  |  Месяц    |Идентификационный номер|Количество дней |Оплата за 1 день, рубли" << endl;
            cout << "---------------------------------|------|-----------|-----------------------|----------------|--------------------------\n";
            for (int i = 0; i < number; i++)
            {
                if (lists[i].year == year)
                {
                    cout << (num + 1) << ". " << setw(30) << left << lists[i].fio << "| " << setw(5) << left << lists[i].year << "|" << setw(11) << left << lists[i].month << "|" << setw(23) << left << lists[i].series_number << "|" << setw(16) << left << lists[i].days << "|" << setw(5) << left << lists[i].paymentperday << "\n";
                    cout << "---------------------------------|------|-----------|-----------------------|----------------|--------------------------\n";
                    num++;
                }
            }
        }
        else cout << "Ничего не найдено..." << endl;
        break;
    }
    case 3:
    {
        int  payment = 0;
        int num = 0;
        int finds = 0;
        cout << "Введите оплату за 1 день: ";
        payment=checkDouble();
        cout << endl;
        cout << "Результаты поиска" << endl;
        for (int i = 0; i < number; i++)
        {
            if (lists[i].paymentperday == payment)
            {
                finds++;
            }
        }
        if (finds > 0)
        {
            cout << "                ФИО              | Год  |  Месяц    |Идентификационный номер|Количество дней |Оплата за 1 день, рубли" << endl;
            cout << "---------------------------------|------|-----------|-----------------------|----------------|--------------------------\n";
            for (int i = 0; i < number; i++)
            {
                if (lists[i].paymentperday == payment)
                {
                    cout << (num + 1) << ". " << setw(30) << left << lists[i].fio << "| " << setw(5) << left << lists[i].year << "|" << setw(11) << left << lists[i].month << "|" << setw(23) << left << lists[i].series_number << "|" << setw(16) << left << lists[i].days << "|" << setw(5) << left << lists[i].paymentperday << "\n";
                    cout << "---------------------------------|------|-----------|-----------------------|----------------|--------------------------\n";
                    num++;
                }
            }
        }
        else cout << "Ничего не найдено..." << endl;
        break;
    } 
    case 4:
    {
        int seriesNumber = 0;
        int num = 0;
        int finds = 0;
        cout << "Введите номер больничного листа: ";
        checkChoice(&seriesNumber, 1000000, 9999999);
        cout << "Результаты поиска" << endl;
        for (int i = 0; i < number; i++)
        {
            if (lists[i].series_number == seriesNumber)
            {
                finds++;
            }
        }
        if (finds > 0)
        {
            cout << "                ФИО              | Год  |  Месяц    |Идентификационный номер|Количество дней |Оплата за 1 день, рубли" << endl;
            cout << "---------------------------------|------|-----------|-----------------------|----------------|--------------------------\n";
            for (int i = 0; i < number; i++)
            {
                if (lists[i].series_number == seriesNumber)
                {
                    cout << (num + 1) << ". " << setw(30) << left << lists[i].fio << "| " << setw(5) << left << lists[i].year << "|" << setw(11) << left << lists[i].month << "|" << setw(23) << left << lists[i].series_number << "|" << setw(16) << left << lists[i].days << "|" << setw(5) << left << lists[i].paymentperday << "\n";
                    cout << "---------------------------------|------|-----------|-----------------------|----------------|--------------------------\n";
                    num++;
                }
            }
        }
        else
        {
            cout << "Ничего не найдено..." << endl;
        }
        break;
    }
        }
    }
    else {
        cout << "Информации в файле SickLists.txt не обнаружено..." << endl;
    }
}

Date getCurrentDate() // функция определения текущей даты
{
    struct tm localtime;
    time_t now = time(NULL);
    localtime_s(&localtime, &now);
    Date currentDate;
    currentDate.month = 1 + localtime.tm_mon; // tm_mon: months in range [0-11]
    currentDate.year = 1900 + localtime.tm_year; // tm_year: years since 1900
    return currentDate;
}

void displayTotalpayments() // функция индивидуального задания
{
    int count = liststoStruct();
    if (count > 0)
    {
        double paymentforperson = 0, totalpayment = 0;
        Date date = getCurrentDate();
        int year = 0;
        string monthName;
        cout << "Введите интересующий Вас год: ";
        checkChoice(&year, 1900, date.year);
        cout << "\nВведите номер месяца больничного листа: ";
        int month = 0;
        if (year == date.year)
            checkChoice(&month, 1, date.month);
        else checkChoice(&month, 1, 12);
        monthName = findmonth(month);
        int finds = 0;
        for (int i = 0; i < count; i++)
        {
            if (lists[i].month == monthName && lists[i].year == year)
                finds++;
        }
        if (finds != 0)
        {
            cout << "     ФИО               Идентификационный номер    Итоговая выплата, бел. рубли" << endl;
            for (int i = 0; i < count; i++)
            {
                if (lists[i].month == monthName && lists[i].year == year)
                {
                    paymentforperson = lists[i].paymentperday * lists[i].days;
                    cout << setw(30) << left << lists[i].fio << setw(30) << left<<lists[i].series_number << paymentforperson << endl;
                    totalpayment += paymentforperson;
                }
            }
            cout << "Общая сумма выплат по больничным листам за " << monthName << " составила " << totalpayment << " бел рубля." << endl;;
        }
        else cout << "Информации за " << monthName << " " << year << " года не найдено" << endl;
    }
    else cout<<"Информации в файле SickLists.txt не обнаружено..." << endl;
}


bool isTheonlyoneNumber(int identity, int count) // функция проверки идентификационного номера больничного листа на уникальность
{
    bool isTheOnlyOne = true; // для проверки на уникальность
        for (int i = 0; i < count; i++) // перебираем все больничные листы
        {
            if (lists[i].series_number == identity) // если есть совпадение в ИН
              isTheOnlyOne = false;        
        }
    return isTheOnlyOne; // возвращаем введённый логин 
}