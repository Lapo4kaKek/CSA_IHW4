#include <iostream>
#include <vector>
// Split аналогичный тому, что есть в C#, JS, Java и тд...
std::vector<std::string> Split(const std::string& str, char delimiter) {
    std::vector<std::string> vectorstr;
    std::string line = "";
    int count = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if (i == 0 && str[i] == delimiter) {
            vectorstr.push_back("");
            count++;
        } else if (i == str.length() - 1 && str[i] == delimiter) {
            if (line != "") {
                vectorstr.push_back(line);
            }
            if (count > 0) {
                vectorstr.push_back("");
            }
            vectorstr.push_back("");
        } else if (i == str.length() - 1 && str[i] != delimiter) {
            line+=str[i];
            vectorstr.push_back(line);
        } else {
            if (str[i] != delimiter) {
                line+=str[i];
                count = 0;
            } else if (count > 1) {
                vectorstr.push_back("");
                count = 0;
            } else {
                vectorstr.push_back(line);
                line = "";
                count++;
            }
        }
    }
    return vectorstr;
}
