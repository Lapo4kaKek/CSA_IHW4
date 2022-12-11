#include <fstream>
// метод вывода инофрмации в файл
void output(std::string line) {
    std::string path = "output.txt";
    std::ofstream out;
    out.open(path, std::ios::app);
    // если файл корректно открылся, записываем строку
    if (out.is_open())
    {
        out << line;
    }
    // закрываем файл
    out.close();
}
