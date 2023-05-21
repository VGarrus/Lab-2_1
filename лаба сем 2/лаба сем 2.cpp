#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>




using namespace std;

string way = "C:\\Users\\artem\\source\\repos\\лаба сем 2\\лаба сем 2\\laba222.txt";


struct Book {
    int id;
    string name;
    string autor;

};

struct Students
{
    string name; // Фамилия Имя Отчество
    string sex;         // Пол: МУЖ или ЖЕН
    int group;        // Номер группы
    int id;           // Номер студента в списке 
    int grades[8];    // Оценки за экзамены и диф. зачёты


};

//Не относится к лабе-----------------------------------------------Тесты (начало)

void Refactfile(){
    
    setlocale(LC_ALL, "russian");
    ;
    std::ofstream out("laba222.txt", std::ios::app);
    if (out.is_open())
    {
        cout << "Что вы хотите записать (текст) ?"<<"\n";
        string save1;
        cin >> save1;
        
        std::cout << "В вайл записывается : " << save1 << std::endl;
        out << save1 << std::endl;
    }
    out.close();
}


void Reedfile() {
   
    setlocale(LC_ALL, "russian");
    std::string line;

    std::ifstream in("laba222.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
            std::cout << line << std::endl;
        }
    }
    in.close();     // закрываем файл
}


void Cleanfile() {
    cout << "Вы точно хотите удалить все записи в файле ?" << "\n";
    cout << " Да(1)               или                 Нет(0)" << "\n";
    bool clenevar;
    cin >> clenevar;
    
    switch (clenevar)
    {
    case 1:
        {
            cout << "Файл очищен" << "\n";
            ofstream file("laba222.txt");

            break;
        }
    case 0:
        {
            cout << "Файл не будет очищен" << "\n";
            break;
        }
    }
    
   
}
//Не относится к лабе-----------------------------------------------Тесты (конец)

void NewStudent() {
    Students profile;
    SetConsoleCP(1251); //Для коректной записи кириллицы в файл надо сменить кодировку консоли
    cin.ignore();
    cout << "ФИО: ";
    getline(cin, profile.name);
    cout << "Пол (МУЖ / ЖЕН): ";
    cin >> profile.sex;
    cout << "Номер группы: ";
    cin >> profile.group;
    cout << "Номер в списке группы: ";
    cin >> profile.id;
    cout << "Оценки за семестр:\n";
    for (int i = 0; i < 8; i++) {
        cin >> profile.grades[i];
    Mcr: if (profile.grades[i] > 5 || profile.grades[i] < 1) {
        cout << "Введена неверная оценка. Введите ещё раз: ";
        cin >> profile.grades[i];
        goto Mcr;
    }
    }
    int temp = 0;
    for (int i = 0; i < 8; i++) {
        if (profile.grades[i] == 2)
            temp++;
    }
    if (temp == 0) {
        ofstream database;
        database.open(way, ofstream::app);
        if (!database.is_open())
            cout << "Ошибка сохранения данных!\n";
        else {
            database << profile.name << "\n";
            database << profile.sex << "\n";
            database << profile.group << "\n";
            database << profile.id << "\n";
            for (int i = 0; i < 8; i++) {
                if (i == 7)
                    database << profile.grades[i];
                else
                    database << profile.grades[i] << " ";
            }
            database << "\n";
            cout << "Запись о студенте успешно сохранена!\n";
        }
        database.close();
    }
    else
        cout << "Студент должен быть исключён. Запись не будет сохранена\n";
    SetConsoleCP(866); //Возвращение старой кодировки
}

int CountStudents() {
    ifstream database;
    database.open(way);
    if (database.is_open())
    {
        int temp = 0;
        string data;
        while (!database.eof())
        {
            getline(database, data);
            temp++;
        }
        database.close();
        int n;
        n = temp / 5;
        
        return n;
    }
    else return 0;
}

void CreateMassStudents(Students* student, int size) {
    char trash;
    ifstream database;
    database.open(way);
    if (!database.is_open())
        cout << "Ошибка открытия файла!\n";
    else {
        if (size == 0)
            cout << "Файл пуст!";
        else {
            for (Students* p = student; p < student + size; p++) {
                getline(database, p->name);
                getline(database, p->sex);
                database >> p->group >> p->id;
                for (int i = 0; i < 8; i++)
                    database >> p->grades[i];
                database.get(trash);
            }
        }
    }
}

void ChangeStudent() {
        int size;
        size = CountStudents();
        Students* student = new Students[size];
        CreateMassStudents(student, size);
        if (size == 0) {
            delete[] student;
            system("pause");
            return;
        }
        string chName;
        int change;
        cin.ignore();
        SetConsoleCP(1251);
        while (true) {
            cout << "Введите полное имя студента, или введите 'выход' : \n";
            getline(cin, chName);
            if (chName == "выход")
                break;
            for (int i = 0; i < size; i++) {
                if (student[i].name == chName) {
                    cout << "Что вы ходите изменить?\n" << "1 - ФИО.\n" << "2 - Пол.\n" << "3 - Номер группы.\n" << "5 - Оценки за семестр.\n" << "6 - Отменить изменение.\n" << "0 - Выход" << "Ваш выбор: ";
                        
                    cin >> change;
                    switch (change) {
                    case 1:
                        cout << "Введите новые данные: ";
                        cin.ignore();
                        getline(cin, student[i].name);
                        break;
                    case 2:
                        cout << "Введите новые данные: ";
                        cin >> student[i].sex;
                        cin.ignore();
                        break;
                    case 3:
                        cout << "Введите новые данные: ";
                        cin >> student[i].group;
                        cin.ignore();
                        break;
                    case 4:
                        cout << "Введите новые данные: ";
                        cin >> student[i].id;
                        cin.ignore();
                        break;
                    case 5:
                        cout << "Введите новые данные:\n";
                        for (int j = 0; j < 8; j++) {
                            cin >> student[i].grades[j];
                        Mch: if (student[i].grades[j] > 5 || student[i].grades[j] < 1) {
                            cout << "Введена неверная оценка. Введите ещё раз: ";
                            cin >> student[i].grades[j];
                            goto Mch;
                        }
                        }
                        cin.ignore();
                        break;
                    case 6:
                        cin.ignore();
                        break;
                    case 0:
                        chName = "выход";

                    }
                    break;
                }
                if (i == (size - 1))
                    cout << "Данный студент не найден!\n";
            }
        }
        ofstream database;
        database.open(way);
        if (!database.is_open()) {
            cout << "Ошибка открытия файла!\n";
        }
        else {
            for (Students* p = student; p < student + size; p++) {
                    database << p->name << "\n" << p->sex << "\n" << p->group << "\n" << p->id << "\n";
                for (int i = 0; i < 8; i++) {
                    if (i == 7)
                    database << p->grades[i];
                    else
                    database << p->grades[i] << " ";
                }
                    database << "\n";
            }
        }
        database.close();
        cout << "Сохранение успешно завершено!\n";
        SetConsoleCP(866);
        
        delete[] student;
    }

void showGroup()
{
    int n;
    cout << "Введите номер группы: ";
    cin >> n;
    int size;
    size = CountStudents();
    Students* student = new Students[size];
    CreateMassStudents(student, size);
    if (size == 0) {
        delete[] student;
        return;
    }
    int temp = 0;
    for (Students* p = student; p < student + size; p++)
        if (p->group == n) {
            temp++;
            cout << "ФИО: " << p->name << "\nПол: " << p->sex << "\nгруппа: " << p->group << "\nНомер в группе: " << p->id << "\nОценки за семестр: ";
            for (int i = 0; i < 8; i++)
                cout << p->grades[i] << " ";
            cout << "\n\n";
        }
    delete[] student;
    if (temp == 0)
        cout << "Студентов данной группы не найдено!\n";
}

void showsex()
{
    
    string n;
    cout << "Введите пол: ";
    setlocale(LC_ALL, "Rus"); // Подключение русского языка
    SetConsoleCP(1251); //Для коректной записи кириллицы в файл надо сменить кодировку консоли
    cin >> n;
    SetConsoleCP(866);
    //cout << n;
    int size;
    size = CountStudents();
    Students* student = new Students[size];
    CreateMassStudents(student, size);
    if (size == 0) {
        delete[] student;
        return;
    }
    int temp = 0;

    int men = 0, women = 0;
    if (size == 0) {
        delete[] student;
        return;
    }
    for (Students* p = student; p < student + size; p++) {
        if (p->sex == "МУЖ")
            men++;
        
        if (p->sex == "ЖЕН")
            women++;
     }
    cout << "Найдено:\n"<< "Парней : "<<men<<"\n"<<"Девушек : " << women << "\n";
    cout <<"\n"<<"Список найденых стдудентов  :" << "\n";


    
    for (Students* p = student; p < student + size; p++)
        if (p->sex == n) {
            temp++;
            cout << "ФИО: " << p->name << "\nПол: " << p->sex << "\nгруппа: " << p->group << "\nНомер в группе: " << p->id << "\nОценки за семестр: ";
            for (int i = 0; i < 8; i++)
                cout << p->grades[i] << " ";
            cout << "\n\n";
           
        }
    delete[] student;
    if (temp == 0)
        cout << "Студентов данной группы не найдено!\n";
}
void showid()
{
    int n;
    cout << "Введите ID: ";
    cin >> n;
    int size;
    size = CountStudents();
    Students* student = new Students[size];
    CreateMassStudents(student, size);
    if (size == 0) {
        delete[] student;
        return;
    }
    int temp = 0;
    for (Students* p = student; p < student + size; p++)
        if (p->id == n) {
            temp++;
            cout << "ФИО: " << p->name << "\nПол: " << p->sex << "\nгруппа: " << p->group << "\nНомер в группе: " << p->id << "\nОценки за семестр: ";
            for (int i = 0; i < 8; i++)
                cout << p->grades[i] << " ";
            cout << "\n\n";
        }
    delete[] student;
    if (temp == 0)
        cout << "Студентов данной группы не найдено!\n";
}
    


int main()
{
    
    setlocale(LC_ALL, "Rus"); // Подключение русского языка

   
    
    
    
    {
        while (true) {
            
            system("cls");

            cout << "____________________________________________________________________________________" << "\n";
            cout << "|                                 Меню :                                           |" << "\n";
            cout << "| Тестовые пункты:                                                                 |" << "\n";
            cout << "|   1) 1 Сделать запись в файле(просто добовление текста в блокнот).               |" << "\n";
            cout << "|   2) 2 Прочитать записи в файле(посмотреть всех студентов) .                    |" << "\n";
            cout << "|   3) 3 Удалить все записи в файле.                                               |" << "\n";
            cout << "|                                                                                  |" << "\n";
            cout << "| Начало заданий по лабораторной работы                                            |" << "\n";
            cout << "|   4) 4 Запись о новом студенте                                                   |" << "\n";
            cout << "|   5) 5 Изменение записи о студенте                                               |" << "\n";
            cout << "|   6) 6 Вывод информации обо всех студентах определенной группы                   |" << "\n";
            cout << "|   7) 7 Вывод определленного пола студентов                                       |" << "\n";
            cout << "|   8) 8 Вывод определленного ID                                                   |" << "\n";
            cout << "|   0) 0 Выход из программы                                                        |" << "\n";
            cout << "|__________________________________________________________________________________|" << "\n";
            cout << "Выберите пункт : " << "\n";
            cout << endl;
            int choice;
            cin >> choice ;
            switch (choice) {
            case 0:
                system("cls");
                cout << "                         Спасибо за просмотр" << "\n";
                cout << "                           попугай вторник" << "\n";

                cout << "___________________________________________$$$$$$$$$$$$" << "\n";
                cout << "________________________________________$$$$$$$$$_ __$$$" << "\n";
                cout << "____________________________________$$$$$$$$_____( &)_$$$$" << "\n";
                cout << "________________________________$$$$$$$$$$________ ____$$$$" << "\n";
                cout << "_____________________________$$$$$$$$$$$$$$$____§ §§§_____$" << "\n";
                cout << "___________________________$$$$$$$$$$$$$$$$$$§§ ?§_§§§_____$" << "\n";
                cout << "_________________________$$$$$$$$$$$$$$$$$$$$$§§ §§§_§____" << "\n";
                cout << "______________________$$$$$$$$$$$$$$$$$$_$$$$___§ §§__§_$" << "\n";
                cout << "____________________$$$$$$$$$$$$$_$$$$$$$$_$______ __§" << "\n";
                cout << "___________________$$$$$$$$$$$$$$$$$$$$$$$$_$" << "\n";
                cout << "_________________$$$$$$$$$_$$$$$$$$$$$$$$$$_$" << "\n";
                cout << "_______________$$$$$$$$_§$$$$$$$$$§$$$$$$$$_$" << "\n";
                cout << "_____________$$$$$$$_$$§§§$$$§$$§§$$$$§§$_ $$$" << "\n";
                cout << "____________$$$$$$_§§§$$§§$$§§§$$§§$$§ ?$_$$$" << "\n";
                cout << "___________$$$$$_$§§§$$$$§§§$$$§§§§§$$_ $$$$$" << "\n";
                cout << "__________$$$$$_§§§§§§$$§§§$$§§§§§§ §_$$$$$$" << "\n";
                cout << "_________$$$$_§§0§§§§§§§§§§§§§§§ ?_$$$$$$$" << "\n";
                cout << "________$$$_000§§§00§§§§§000§00§_$$$$$$" << "\n";
                cout << "________$$_0000§§0000§§§00§0§_$$$$$$" << "\n";
                cout << "_______$_0000§§00000§0000_$$$$$$$" << "\n";
                cout << "_____§§00000§000§0000_$$$$$$$$" << "\n";
                cout << "___§00000§0000000_$$$$$$$$$$" << "\n";
                cout << "___000§00000§_§§§§$$$$$$$$$$$$$___......" << "\n";
                cout << "___000§00000§_§§§§$$$$$$$$$$$$$___......" << "\n";
                cout << "_000§0_§§§§§§$$$$$$$_§000_$$$§§§_000000 0000000000000" << "\n";
                cout << "00____§§§§§$$$$$$$_§§00000_$§§§_00000000 000000000000" << "\n";
                cout << "______§§§§$$$$$$$_§§§_’’______§§§__???’" << "\n";
                cout << "_____§§§$$$$$$" << "\n";
                cout << "____§§$$$$$$$" << "\n";
                cout << "___$$$$$$$$" << "\n";
                cout << "__$$$$$$$$" << "\n";
                cout << "_$$$$$$$$" << "\n";
                cout << "$$$$$$$$" << "\n";
                cout << "$$$$$$$" << "\n";
                cout << "$$$$$$" << "\n";
                cout << "$$$$" << "\n";
                return 0;
            case 1:
                system("cls");
                Refactfile();
                Reedfile();

                system("pause");
                break;
            case 2:
                system("cls");
                Reedfile();
               
                system("pause");
                break;
            case 3:
                system("cls");
                Cleanfile();
                Reedfile();

                system("pause");
                break;
            case 4:
                system("cls");
                NewStudent();

                system("pause");
                break;
            case 5:
                system("cls");
                ChangeStudent();

                system("pause");
                break;
            case 6:
                system("cls");
                showGroup();

                system("pause");
                break;
            case 7:
                system("cls");
                showsex();

                system("pause");
                break;
            case 8:
                system("cls");
                showid();

                system("pause");
                break;
            case 9:
                system("cls");
                cout << "|" << "Students        =" << " " << sizeof(Students) << "byte" << "|" << endl;

                system("pause");
                break;
            default:
                cout << "\n не найден данный символ " << choice << " d" << endl;
                system("pause");
                break;
            }
        }
    }

    return 0;
}