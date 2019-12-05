#include <iostream>
#include <cstdlib>
#include <string>
#include "mailsender.hpp"

int main()
{
    mailsender a;
    std::string ip;
    std::cout << "to ip?\n"; // 140.138.152.75
    std::cin >> ip;
    a.set_ip(ip);
    a.set_from("s1061506");
    a.add_receiver("A");
    a.add_receiver("S");
    a.add_receiver("C");
    a.add_receiver("I");

    std::cin.get(); // pop the '\n' after cin ip from the stdin
    std::cout << "data? End with \".\\n\" or EOF\n";
    std::string data;
    while(std::getline(std::cin, data) && data != ".")
        a.add_data(data);

    try
    {
        a.send();
    }
    catch(std::string s)
    {
        std::cerr << s << std::endl;
    }

    system("pause");

    return 0;
}
