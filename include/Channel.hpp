#include "iostream"
#include <vector>

class Channel
{
private:
    /* data */
public:
    Channel(/* args */);
    ~Channel();

    std::string _name;
    std::string _topic;
    std::string _password;
    std::vector<std::string> users;
    std::vector<std::string> operators;
    

};

