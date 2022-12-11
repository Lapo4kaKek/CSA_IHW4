#include "iostream"
#include <set>

class People {
public:
    People(std::string _name) {
        this->name = _name;
    }
    std::string returnBook() {
        std::string title = *list.begin();
        list.erase(title);
        return title;
    }
    bool arrears() {
        if (list.empty()) return false;
        return true;
    }
    bool returnBook(std::string title) {
        if (list.find(title)!= list.end()) {
            list.erase(title);
            return true;
        }
        return false;
    }
    void addWaiting(std::string title) {
        waitingList.insert(title);
    }
    bool waiting() {
        if (waitingList.empty()) return false;
        return true;
    }
    std::string takeWaiting() {
        return *waitingList.begin();
    }
    void addBook(std::string title) {
        list.insert(title);
    }

    std::string getName() {
        return name;
    }
private:
    std::set<std::string> waitingList;
    std::set<std::string> list;
    std::string name;
};