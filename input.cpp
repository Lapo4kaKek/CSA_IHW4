#include <iostream>
#include <thread>
#include "fstream"

// собственная функция рандом опирающаяся на текущее время в секундах
// rand() выдает лишь псевдослучайные числа
int randomTrue() {
    unsigned value = unsigned(std::time(nullptr));
    std::this_thread::sleep_for(std::chrono::milliseconds(1001));
    value = (value * 73129 + 95121) % 100000;
    return value;
}
// генерация рандомной строки
std::string randomString(int ch) {
    char alpha[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                       'h', 'i', 'j', 'k', 'l', 'm', 'n',
                       'o', 'p', 'q', 'r', 's', 't', 'u',
                       'v', 'w', 'x', 'y', 'z' };
    std::string result = "";
    for (int i = 0; i < ch; i++) {
        // добавляем к рандомной строке рандомный символ
        result = result + alpha[randomTrue() % 26];
        // ставим паузу в 1 секунду, чтобы рандом корректно сгенерировал новое число
        std::this_thread::sleep_for(std::chrono::milliseconds(101));
    }
    return result;
}
// Рандомный ввод
void inputRandom(std::map<std::string, int> &library, std::vector<People> &users) {
    std::cout << "Генерируем данные\n";
    int quantityBook = randomTrue() % 6 + 1;
    for (int i = 0; i < quantityBook; ++i) {
        // добавляем рандомную книгу с рандомным количеством экземпляров
        std::string title = randomString(7);
        int quantity = i % 2 + 1;
        library[title] = quantity;
    }
    int countUsers = randomTrue() % 5 + 1;
    for (int i = 0; i < countUsers; ++i) {
        users.push_back(People(randomString(5)));
    }
}
// ввод из консоли
void inputConsole(std::map<std::string, int> &library, std::vector<People> &users) {
    std::cout << "Введите количество книг:";
    int quantity;
    std::cin >> quantity;
    std::cout << "Введи название книги и количество её экземлпяров\n";
    for(int i = 0; i < quantity; ++i) {
        std::string title;
        int count;
        std::cout << i + 1 << ":";
        std::cin >> title >> count;
        library[title] = count;

    }
    int count;
    std::cout << "Введи количество юзеров:";
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        std::string name;
        std::cin >> name;
        users.push_back(People(name));
    }

}
// ввод из файла input.txt
void inputFile(std::map<std::string, int> &library, std::vector<People> &users) {
    std::string path = "input.txt";
    std::ifstream in(path);
    std::string line;
    // если файл корректно открылся
    if (in.is_open())
    {
        std::string str;
        getline(in, str);
        int countLine = stoi(str);
        // пока файл не закончился, читаем его
        while(countLine > 0) {
            --countLine;
            getline(in, line);
            std::vector<std::string> resultStr = Split(line, ' ');
            library[resultStr[0]] = std::stoi(resultStr[1]);
        }
        // дальше читаем людей
        getline(in, str);
        countLine = stoi(str);
        while (countLine > 0) {
            --countLine;
            getline(in, line);
            users.push_back(People(line));
        }
    }
    // не забываем закрыть файл
    in.close();
}
// проверка командной строки на ввод
bool check(int argc, char *argv[], std::map<std::string, int> &library, std::vector<People> &users) {
    // вытаскиваем из командной строки команду
    std::string command = argv[1];
    if (argc == 2 && command == "file") {
        std::cout << "В терминале было указано, что ввод из файла\n";
        // запускаем ввод из файла
        inputFile(library, users);
        return true;
    }
    if (argc == 2 && command == "random") {
        std::cout << "В терминале было указано, что данные должны сгенерироваться рандомно\n";
        // запускаем рандомный ввод
        inputRandom(library, users);
        return true;
    }
    return false;
}
// считывание данных из командной строки
void inputCommandLine(std::map<std::string, int> &library, std::vector<People> &users, int argc, char *argv[]) {
    std::cout << "Считываем данные из командной строки\n";
    // считываем количество книг, это второй символ
    int countBook = atoi(argv[1]);
    int count = 2;
    // считываем название книг
    while (count < countBook * 2 + 2) {
        // из-за специфики присваивания работаем с ++ --
        library[argv[--count]] = atoi(argv[++count]);
        count += 2;
    }
    int countUsers = atoi(argv[count]);
    count++;
    // читаем до конца, заполняем людей
    while(count < argc) {
        users.push_back(People(argv[count]));
        ++count;
    }
}