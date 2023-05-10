#include <iostream>





int ft_error(std::string string) {
    std::cout << "Error" << std::endl;
    std::cout << string << std::endl;
    return 1;
}


int main(int argc, char **argv) {
    if (argc != 3)
        return ft_error("Wrong amount of arguments");
    
}