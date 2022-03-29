#include <iostream>
#include <stdexcept>

class My_logic_error : public std::logic_error {
public:
    My_logic_error(const char* what): std::logic_error(what) { }
};


void validateArguments(int argc)
{
    if(argc != 2)
    {
        std::cerr << "You need to pass 1 argument" << std::endl;
        exit(-1);
    }
}

class Resource
{
public:
    void use(const char* arg)
    {
        std::cout << "Using resource. Passed " << *arg << std::endl;
        if (*arg == 'd')
        {
            throw My_logic_error("Passed d. d is prohibited.");
        }
    }
};

int main(int argc, char* argv[])
{
    validateArguments(argc);

    const char* argument = argv[1];
    Resource* rsc = nullptr;

    try
    {
        rsc = new Resource();
        rsc->use(argument);
        delete rsc;
    }
    catch (My_logic_error& e)
    {
        delete rsc;
        std::cout << e.what() << std::endl;
    }
    return 0;
}

