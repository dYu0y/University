# SMTP
本 code 需要連結 Ws2_32.lib 才可以使用
請參考[這篇文章](https://xyz.cinc.biz/2014/02/c-socket-server-client.html)

使用方式可以參考 main.cpp
```cpp
mailsender a;
std::string ip;
std::cout << "to ip?\n"; // 140.138.152.75
std::cin >> ip;
```
設定要寄往的伺服器 ip
```cpp
a.set_ip(ip);
```
設定寄件者
```cpp
a.set_from("s1061506");
```
設定收件者
收件者可以有多個
例如這邊有 A, S, C, I 四位收件者
```cpp
a.add_receiver("A");
a.add_receiver("S");
a.add_receiver("C");
a.add_receiver("I");
```
執行到下方迴圈部分的時候開始輸入信件內容(請使用 ASCII code 可以表示的字元)

```cpp
std::cin.get(); // pop the '\n' after cin ip from the stdin
std::cout << "data? End with \".\\n\" or EOF\n";
std::string data;
while(std::getline(std::cin, data) && data != ".")
  a.add_data(data);
```
信件內容輸入結束時請以一行英文的句點作為結尾
如下圖橘框處 (本圖擷取自 wiki)
![](https://i.imgur.com/12iLXbO.png)

以下是信件內容的範例
```
Hello,
This is a test.
Goodbye.
.
```
