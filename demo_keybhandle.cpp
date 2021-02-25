#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "keybhandle.hpp"
using namespace std;
int main()
{
#ifndef _WIN32
    cout << R"(
As you can see, there is a echo when you type any key. The problem is the
keyboard is not ignored during sleep in C++. Delete/comment the line

this_thread::sleep_for(std::chrono::milliseconds(200));

and all will be fine. Just remember that if you want to avoid echo: 
Do NOT use sleep thread or the sleep()/usleep() functions to handle delays.
This issue is Linux/UNIX only.

)";
#endif // ! _WIN32 
    cout << "Press keys. ESC to exit.\n";
    string msg = "";
    while (true) {
        if (kh::ispressed()) {
            auto myKey = kh::getkey();
            if (myKey >= key::f1 && myKey <= key::f10) {
                msg = "[Fn Key]";
            } else {
                switch (myKey) {
                    case key::esc:
                        return 0;
                    case key::up:
                        msg = "[UP]";
                        break;
                    case key::down:
                        msg = "[DOWN]";
                        break;
                    case key::left:
                        msg = "[LEFT]";
                        break;
                    case key::right:
                        msg = "[RIGHT]";
                        break;
                    case key::enter:
                        msg = "[ENTER]\n";
                        break;
                    default:
                        msg = "(" + to_string(myKey) + ")";
                        //keyAscii = static_cast<char>(myKey);
                }
            }
            cout << msg;
        }
        //To show that program is not paused waiting for a key...
        this_thread::sleep_for(std::chrono::milliseconds(200));
        cout << "." << flush;
    }    
}