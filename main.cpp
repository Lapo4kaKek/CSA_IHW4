#include <iostream>
#include <map>
#include <vector>
#include <mutex>
// класс описывающий человека
#include "People.cpp"
#include "function.cpp"
// ввод данных
#include "input.cpp"
// вывод в файл
#include "output.cpp"
// многопоточность
#include "thread"

std::map<std::string, int> library;
std::vector<People> users;
std::timed_mutex mutex;
void returnBook() {
    // ставим таймаут в 2 секунды
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    int i = 10;
    while(i > 0) {
        --i;
        int number = rand() % users.size();
        // если есть долги, то возвращаем
        if (users[number].arrears() && mutex.try_lock_for(std::chrono::milliseconds (100))) {
            std::string title = users[number].returnBook();
            library[title] += 1;
            std::cout << users[number].getName() << " вернул " << title << " обратно\n";
            // выводим в файл текущую информацию
            output(users[number].getName() + " вернул " + title + " обратно\n");
            mutex.unlock();
        }
        // таймаут в 3 секунды
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

// имитация работы библиотеки
void work(int index) {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    if (users[index].waiting()) {
        // если он ждет книгу, то
        std::string title = users[index].takeWaiting();
        if (library[title] > 0 && mutex.try_lock_for(std::chrono::milliseconds (100))) {
            library[title] -= 1;
            users[index].addBook(title);
            std::cout << users[index].getName() << " дождался книгу: " << title << "\n";
            output(users[index].getName() + " дождался книгу: " + title + "\n");
            // ставим рандомный таймаут (на промежутке от 0 до 2000)
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));
            mutex.unlock();
        } else {
            std::cout << users[index].getName() << " продолжает ждать книгу " << title << "\n";
            output(users[index].getName() + " продолжает ждать книгу " + title + "\n");
        }
    } else {
        // количество книг которое берет чел
        int countTake = rand() % 3 + 1;
        for(int i = 0; i < countTake; ++i) {
            std::map<std::string, int>::iterator  iter = library.begin();
            // двигаем итератор map на рандомное количество позиций (идейно аналогично с iter += rand() % ...
            std::advance(iter, rand() % library.size());
            if (iter->second > 0 && mutex.try_lock()) {
                iter->second -= 1;
                users[index].addBook(iter->first);
                std::cout << users[index].getName() << " берет книгу: " << iter->first << "\n";
                // выводим состояние в файл
                output(users[index].getName() + " берет книгу: " + iter->first + "\n");
                // ставим таймаут на 1.7 секунды
                std::this_thread::sleep_for(std::chrono::milliseconds(1600));
                mutex.unlock();
            } else { // если конкретной книги нет, то добавляем в лист ожидания
                std::string title = iter->first;
                users[index].addWaiting(title);
                std::cout << users[index].getName() << " ждет книгу: " << title << "\n";
                // выводим состояние в файл
                output(users[index].getName() + " ждет книгу: " + title + "\n");
                // ставим таймаут в 1.3 секунды
                std::this_thread::sleep_for(std::chrono::milliseconds(1300));
            }

        }
    }
}

int main(int argc, char *argv[]) {
    // установили русскую локаль для отображения кириллицы
    setlocale(LC_ALL, "rus");
    if (argc > 1) {
        // если ввод не из файла то из командной строки
        if(!check(argc, argv, library, users)) {
            inputCommandLine(library, users, argc, argv);
        }
    } else {
        std::cout << "Введи 1 - если ввод из файла\n2 - консоль\n3 - рандомный ввод\nВвод:";
        int command;
        std::cin >> command;
        switch (command) {
            case 1:
                inputFile(library, users);
                break;
            case 2:
                inputConsole(library, users);
                break;
            case 3:
                inputRandom(library, users);
                break;
            default:
                std::cout << "Давай пока )";
                return 0;
        }
    }
    // Создаем поток в который передаем метод по возвращению книг в библиотеку
    std::thread th2(returnBook);
    // Запускаем выполнение потока в фоновом режите
    th2.detach();

    int index = 0;
    // для каждого похода человека в библиотеку создаем поток
    while (index < users.size() * 3) {
        std::thread th(work, index % users.size());
        // Запускаем выполнение очередного потока в фоновом режите
        th.detach();
        // делаем таймаут текущего потока на пол секунды, чтобы лучше проследить что происходит:)
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        ++index;
    }
    // таймаут в 20 секунд перед завершением кода (наша библиотека работае 30 секунд, да-да)
    std::this_thread::sleep_for(std::chrono::milliseconds(30000));
    std::cout << "Библиотека закрывается";
    return 0;
}
