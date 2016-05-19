#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

bool compare_files(std::string f1, std::string f2) {
    std::ifstream is1(f1), is2(f2);
    if(!is1.is_open() || !is2.is_open()) {
        std::cerr << "could not open one of the files" << std::endl;
        return false;
    }
    char c1, c2;
    while(is1.get(c1)) {
        is2.get(c2);
        if(c1 != c2) {
            return false;
        }
    }
    return is1.eof() != is2.eof();
}

int main(void)
{
        assert(compare_files("output1.txt", "MobileBattleshipGame1DesiredOuput.txt"));
        assert(compare_files("output2.txt", "MobileBattleshipGame2DesiredOuput.txt"));
        assert(compare_files("output3.txt", "StaticBattleshipGame1DesiredOuput.txt"));
        assert(compare_files("output4.txt", "CheckersGame1DesiredOutput.txt"));
        assert(compare_files("output5.txt", "CheckersGame2DesiredOutput.txt"));
        std::cout << "Success!" << std::endl;
        return 0;
}

