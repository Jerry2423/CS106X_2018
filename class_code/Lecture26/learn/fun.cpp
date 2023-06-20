#include <iostream>
using namespace std;

class Father {
    public:
        Father(int member) {
            this->member = member;
        }
        virtual void speak() {
            cout << "father" << endl;
        }
    private:
        int member;
};

class Son : public Father {
    public:
        Son(int member, bool mom) : Father(member) {
            this->mom = mom;
        }
        void speak() {
            cout << "song"  << endl;
        }
    private:
        bool mom;
};

int main() {
    Son rf = Son(10, false);
    rf.speak();
    return 0;
}
