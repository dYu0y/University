#include <iostream>
#include <string>
#include <winsock2.h>
#include "mailsender.hpp"

mailsender::mailsender()
:mailsender::mailsender("127.0.0.1", "", "", "Test")
{}

mailsender::mailsender(std::string const& ip_addr, std::string const& from, std::string const& to, std::string const& subject)
{
    set_ip(ip_addr);
    set_from(from);
    add_receiver(to);
    set_subject(subject);
}

mailsender::~mailsender()
{
    closesocket(sConnect);
}

void mailsender::set_ip(std::string const& ip_addr)
{
    addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
}
void mailsender::set_from(std::string const& from)
{
    sender = from;
}
void mailsender::add_receiver(std::string const& to)
{
    if(to != "")
        receivers.push_back(to);
}
void mailsender::clr_to()
{
    receivers.resize(0);
}
void mailsender::set_subject(std::string const& subject)
{
    this->subject = subject;
}
void mailsender::add_data(std::string const& tex)
{
    data.push_back(tex);
}

void mailsender::send()
{
    // init
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 2);
    if(WSAStartup(DLLVersion, &wsaData))   // 0 -> success  else -> fail
        throw("Winsock startup failed");

    addr.sin_family = AF_INET; // IPv4 Socket
    addr.sin_port = htons(25);
    int addrlen = sizeof(addr);

    sConnect = socket(addr.sin_family, SOCK_STREAM, 0);
    connect(sConnect, (SOCKADDR*)&addr, addrlen);

    //
    std::string tex, message;
    char buf[200]{};
    auto receive = [&](std::string const& id, std::string const& m)
                    {
                        memset(buf, 0, sizeof(buf));
                        recv(sConnect, buf, sizeof(buf), 0);
                        message.assign(buf);
                        if(noisy)   std::cout << "S: " << message;
                        if(message.substr(0, 3) != id)
                            throw(m);
                    };
    auto my_send = [&]()
                    {
                        ::send(sConnect, tex.c_str(), tex.size(), 0);
                        if(noisy)   std::cout << "C: " << tex;
                    };

    receive("220", "Can't connected!");

    tex = "ehlo\n";
    my_send();
    receive("250", "EHLO Failed!");

    tex = "mail from <" + sender + ">\n";
    my_send();
    receive("250", "Invalid sender: " + sender);

    for(auto i : receivers)
    {
        tex = "rcpt to <" + i + ">\n";
        my_send();
        receive("250", "Invalid receiver: " + i);
    }

    tex = "data\n";
    my_send();
    receive("354", "DATA failed!");

    tex = "From: " + sender + "\n";
    my_send();
    tex = "To: ";
    bool fir = true;
    for(auto i : receivers)
    {
        if(fir)
            fir = false;
        else
            tex += ", ";
        tex += i;
    }
    tex += "\n";
    my_send();
    tex = "Subject: " +  subject + "\n";
    my_send();

    for(auto i : data)
    {
        tex = i + "\n";
        my_send();
    }
    tex = ".\n";
    my_send();
    receive("250", "End DATA with error!");

    tex = "quit\n";
    my_send();
    receive("221", "QUIT failed!");
}
