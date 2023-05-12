//#include "irc.hpp"

# include <iostream>

// https://cdn.intra.42.fr/pdf/pdf/83324/en.subject.pdf

int ft_error(std::string string) {
    std::cout << "Error" << std::endl;
    std::cout << string << std::endl;
    return 1;
}


int main(int argc, char **argv) {
    if (argc != 3)
        return ft_error("Wrong amount of arguments");
    
}