/*8. Разработайте программу, реализующую работу с бинарными файлами. Необходимо хранить информацию о товаре в магазине:
•  номер товара (уникален);
•  название;
•  цена за единицу;
•  количество.
Реализовать следующие функции, вызываемые из меню:
1.  Ввод информации  о товаре с клавиатуры и сохранение ее в бинарном файле с выбранным пользователем названием.
2.  Просмотр содержимого бинарного файла с выбранным пользователем названием.
3.  Вывод информации о товаре по введенному пользователем названию из выбранного пользователем файла.
4.  Вывод информации обо всех товарах с ценой ниже 15.
5.  Удаление информации из выбранного бинарного файла о товаре с выбранным количеством.
6.  Изменение информации о названии товара для всех товаров из выбранного файла, имеющих цену меньше, чем вводит пользователь.
7.  Вывод названий товаров с максимальной ценой из выбранного файла.
8.  Изменение информации о названии автора по введенной цене. Файл вводит пользователь.*/
#include<iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdio>
using namespace std;
struct tovar {
    int number;
    char name[30];
    int price;
    int kolvo;
};
void create(int& size) {
    char name[10];
    cout << "введите имя файла\n";
    cin >> name;
    bool unique = true;
    fstream file(name, ios::binary | ios::app);
    if (file)
    {
        file.seekp(0, ios::end);
        tovar tovars[3];
        cout << "Введите размер\n"; cin >> size;
        for (int i = 0; i < size; i++)
        {
            cout << "Номер " << i + 1 << " - го товара\n"; cin >> tovars[i].number;
            unique = true;
            for (int j = 0; j < i; j++)
            {
                if (tovars[i].number == tovars[j].number)
                {
                    unique = false;
                    break;
                }
            }
            while (!unique)
            {
                cout << "Номер товара должен быть уникальным " << endl;
                cout << "Введите номер товара еще раз " << endl;
                cin >> tovars[i].number;
                unique = true;
                for (int j = 0; j < i; j++)
                {
                    if (tovars[i].number == tovars[j].number)
                    {
                        unique = false;
                        break;
                    }
                }
            }
            cout << "Название " << i + 1 << "-го товара\n"; cin >> tovars[i].name;
            cout << "Цена за еденицу " << i + 1 << "-го товара\n"; cin >> tovars[i].price;
            cout << "Колчество " << i + 1 << "-го товара\n"; cin >> tovars[i].kolvo;
            file.write(reinterpret_cast<char*>(&tovars[i]), sizeof(tovars[i]));
        }
        file.close();
    }
    else {
        file.seekp(0);
        tovar tovars[3];
        int size; cout << "Введите размер\n"; cin >> size;
        for (int i = 0; i < size; i++) {
            cout << "Номер: " << i + 1; cin >> tovars[i].number;
            cout << "Название: " << i + 1; cin >> tovars[i].name;
            cout << "Цена за единицу: " << i + 1; cin >> tovars[i].price;
            cout << "Количество: " << i + 1; cin >> tovars[i].kolvo;
            file.write(reinterpret_cast<char*>(&tovars), sizeof(tovars));
        }
        file.close();
    }
}
void info() {
    tovar s;
    char name[10];
    cout << "введите имя файла\n";
    cin >> name;
    ifstream file(name, ios::binary);
    file.read(reinterpret_cast<char*>(&s), sizeof(s));
    if (!file) {
        cout << "no file" << endl;
        return;
    }
    while (!file.eof()) {
        cout << "Номер " << s.number << endl;
        cout << "Название " << s.name << endl;
        cout << "Цена за еденицу " << s.price << endl;
        cout << "Количество " << s.kolvo << endl;
        file.read(reinterpret_cast<char*>(&s), sizeof(s));
    }
    file.close();
}
//3.  Вывод информации о товаре по введенному пользователем названию из выбранного пользователем файла.
void search1() {//
    tovar s;
    char name[10];
    cout << "введите имя файла: \n";
    cin >> name;
    string g;
    cout << "введите название товара: ";
    cin >> g;
    ifstream file(name, ios::binary);
    file.read(reinterpret_cast<char*>(&s), sizeof(s));
    if (!file) {
        cout << "no file" << endl;
        return;
    }
    while (!file.eof())
    {
        if (s.name == g)
        {
            cout << "Номер " << s.number << endl;
            cout << "Название " << s.name << endl;
            cout << "Цена за еденицу " << s.price << endl;
            cout << "Количество " << s.kolvo << endl;
        }
        file.read(reinterpret_cast<char*>(&s), sizeof(s));
    }
    file.close();
}
void search2() {
    tovar s;
    char name[10];
    cout << "введите имя файла\n";
    cin >> name;
    ifstream file(name, ios::binary);
    file.read(reinterpret_cast<char*>(&s), sizeof(s));
    while (!file.eof())
    {
        if (s.price < 15)
        {
            cout << "Номер " << s.number << endl;
            cout << "Название " << s.name << endl;
            cout << "Цена за еденицу " << s.price << endl;
            cout << "Количество " << s.kolvo << endl;
        }
        file.read(reinterpret_cast<char*>(&s), sizeof(s));
    }
}
//5.  Удаление информации из выбранного бинарного файла о товаре с выбранным количеством.
void del()
{
    tovar s;
    char name[10];
    cout << "введите имя файла\n";
    cin >> name;
    int n, c = 0;
    cout << "введите количество товара: ";
    cin >> n;
    ifstream file(name, ios::binary);
    ofstream tmp("tmp.bin", ios::binary);
    file.read(reinterpret_cast<char*>(&s), sizeof(s));
    while (!file.eof()) {
        if (s.kolvo != n) {
            tmp.write(reinterpret_cast<char*>(&s), sizeof(s));
        }
        file.read(reinterpret_cast<char*>(&s), sizeof(s));
        c++;
    }
    file.close();
    tmp.close();
    remove(name);
    rename("tmp.bin", name);
}
//6.  Изменение информации о названии товара для всех товаров из выбранного файла, имеющих цену меньше, чем вводит пользователь.(?)
void Change1()
{
    tovar s{};
    char name[10];
    cout << "введите имя файла\n";
    cin >> name;
    int n, c = 0;
    cout << "Введите цену:";
    cin >> n;
    ifstream file(name, ios::binary);
    ofstream tmp("tmp.bin", ios::binary);
    file.read(reinterpret_cast<char*>(&s), sizeof(s));
    while (!file.eof())
    {
        if (s.price < n)
        {
            cout << "\nВведите название: "; cin >> s.name;
        }
        tmp.write(reinterpret_cast<char*>(&s), sizeof(s));
        file.read(reinterpret_cast<char*>(&s), sizeof(s));
    }

    file.close();
    tmp.close();
    remove(name);
    rename("tmp.bin", name);
}
void max() {
    tovar s[3];
    char name[10];
    cout << "введите имя файла\n";
    cin >> name;
    ifstream file(name, ios::binary);
    file.read(reinterpret_cast<char*>(&s), sizeof(s));
    int max = s[0].price;
    for (int i = 0; i < 3; i++) {
        if (s[i].price > max)
            max = s[i].price;
    }
    for (int i = 0; i < 3; i++) {
        if (s[i].price == max) {
            cout << "Номер " << s[i].number << endl;
            cout << "Название " << s[i].name << endl;
            cout << "Цена за еденицу " << s[i].price << endl;
            cout << "Количество " << s[i].kolvo << endl;
        }
        file.read(reinterpret_cast<char*>(&s), sizeof(s));
    }
    file.close();
}
//8.  Изменение информации о названии автора по введенной цене.Файл вводит пользователь.
void change2() {
    tovar s{};
    char name[10];
    cout << "Введите название файла\n";
    cin >> name;
    int n;
    int c = 0;
    cout << "Введите цену: ";
    cin >> n;
    ifstream file(name, ios::binary);
    ofstream tmp("tmp.bin", ios::binary);
    file.read(reinterpret_cast<char*>(&s), sizeof(s));

    while (!file.eof()) {
        if (s.price == n) {
            cout << "\nВведите название: "; cin >> s.name;


        }
        tmp.write(reinterpret_cast<char*>(&s), sizeof(s));
        file.read(reinterpret_cast<char*>(&s), sizeof(s));
    }

    file.close();
    tmp.close();
    remove(name);
    rename("tmp.bin", name);

}
int main() {
    setlocale(LC_ALL, "RUS");
    int input = 1;
    int size;
    while (input) {
        cout << "Выберите действие:\n1.  Ввод информации  о товаре с клавиатуры и сохранение ее в бинарном файле с выбранным пользователем названием.\n";
        cout << "2.  Просмотр содержимого бинарного файла с выбранным пользователем названием.\n";
        cout << "3.  Вывод информации о товаре по введенному пользователем названию из выбранного пользователем файла.\n";
        cout << "4.Вывод информации обо всех товарах с ценой ниже 15 \n";
        cout << "5.  Удаление информации из выбранного бинарного файла о товаре с выбранным количеством.\n";
        cout << "6.  Изменение информации о названии товара для всех товаров из выбранного файла, имеющих цену меньше, чем вводит пользователь.\n";
        cout << "7.  Вывод названий товаров с максимальной ценой из выбранного файла.\n";
        cout << "8.  Изменение информации о названии автора по введенной цене. Файл вводит пользователь.\n";
        cout << "9. Выход(exit).\n";
        cin >> input;
        switch (input) {
        case 1:
            create(size);
            break;
        case 2:
            info();
            break;
        case 3:
            search1();
            break;
        case 4:
            search2();
            break;
        case 5:
            del();
            break;
        case 6:
            Change1();
            break;
        case 7:
            max();
            break;
        case 8:
            change2();
            break;
        case 9:
            exit(0);
            break;
        }
    }
}