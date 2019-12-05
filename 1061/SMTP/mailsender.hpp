#ifndef _mail_sender_
#define _mail_sender_
#include <string>
#include <vector>
#include <winsock2.h>

using string_list = std::vector<std::string>;

class mailsender
{
public:
    mailsender();
    mailsender(std::string const& ip_addr, std::string const& from, std::string const& to, std::string const& subject);
    ~mailsender();

    void set_ip(std::string const& ip_addr);
    void set_from(std::string const& from);
    void add_receiver(std::string const& from);
    void clr_to();
    void set_subject(std::string const& subject);
    void add_data(std::string const&);

    void send();
private:
    SOCKADDR_IN addr;
    SOCKET sConnect;
    std::string sender;
    string_list receivers;
    std::string subject;
    string_list data;
    bool noisy = true;
};

#endif //define _mail_sender_
