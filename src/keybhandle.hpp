/*
MIT License

Copyright (c) 2020 José Puga

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//showkey is your friend
#ifndef KEYBHANDLE_HPP
#define KEYBHANDLE_HPP
#define KEYBHANDLE_HPP_VERSION "1.0"
#include <cassert>
#ifdef _WIN32
#include <conio.h>
#else
#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif // _WIN32


class kh {
    public:
    static bool ispressed();
    static int getkey();

    private:
    kh() {};
};

namespace key {
    //Common keys. FILL WITH YOURS.
    const int esc = 27;
    const int space = 32;
    const int tab = 9;
    const int plus = 43;
    const int minus = 45;

    //Platform specific
#ifdef _WIN32
    const int enter = 13;
    const int backspace = 8;
#else
    const int enter = 10;
    const int backspace = 127;
#endif

    //No hay una forma fácil de lidiar con estos valores para hacerlos
    //multiplataforma sin modificarlos.
    //Non standard.
    const int up = 1101;
    const int down = 1102;
    const int right = 1103;
    const int left = 1104;
    const int f1 = 1001;
    const int f2 = 1002;
    const int f3 = 1003;
    const int f4 = 1004;
    const int f5 = 1005;
    const int f6 = 1006;
    const int f7 = 1007;
    const int f8 = 1008;
    const int f9 = 1009;
    const int f10 = 1010;
}


#ifdef _WIN32
bool kh::ispressed()
{
    return static_cast<bool>(_kbhit());
}
#else
bool kh::ispressed()
{
    struct termios oldt, newt;
    int oldf;    
    //Keep settings of the current terminal in oldt.
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    //Disable "canonical mode": Process lines waiting for "\n" of EOF (AKA 
    //buffered IO), and echo.
    newt.c_lflag &= ~(ICANON | ECHO);
    //new settings. TSCANOW if for apply inmediately.
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    //Non blocking mode.
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);    
    int key = getchar();
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    auto result = (key != EOF);
    if (result) {
        //Put the key again on the stdin buffer.        
        ungetc(key, stdin);
    } 
    return result;
}
#endif // _WIN32

#ifdef _WIN32
int kh::getkey()
{
    int key = getch();    
    //Cursor or Function key
    if (key == 224 || key == 0) {
        switch (getch()) { //Second one is the valid key.
            case 72:
                key = key::up;
                break;
            case 75:
                key = key::left;
                break;
            case 77:
                key = key::right;
                break;
            case 80:
                key = key::down;
                break;
            case 59: //59=f1 ... 68=f10
                key = key::f1; 
                break;
            case 60: 
                key = key::f2;
                break;
            case 61: 
                key = key::f3;
                break;
            case 62: 
                key = key::f4;
                break;
            case 63: 
                key = key::f5;
                break;
            case 64: 
                key = key::f6;
                break;
            case 65: 
                key = key::f7;
                break;
            case 66: 
                key = key::f8;
                break;
            case 67: 
                key = key::f9;
                break;
            case 68: 
                key = key::f10;
                break;
            default:
                //You shall not pass.
                assert(false && "No special key to handle.");
                break;
        }
    } 
    return key;
}
#else
int kh::getkey()
{
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); //STDIN_FILENO = fileno(stdin)
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    int key = getchar();
    if (key == key::esc) { //First sequence. is ESC for special keys
        //Thats the problem: Special keys are ESC+more. How to detect *ONLY*
        //the real ESC key pressed?. Checking if the buffer is empty.
        if (!ispressed()) { //No more keys is *the real ESC*
            putchar(key::esc); //I dont know why but the system waits for ANOTHER ESC.
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return key;
        }
        auto secondKey = getchar();
        if (secondKey == 91) { //Cursors or F5...F10
            switch(getchar()) {
                case 'A':
                    key = key::up;
                    break;
                case 'B':
                    key = key::down;
                    break;
                case 'C':
                    key = key::right;
                    break;
                case 'D':
                    key = key::left;
                    break;
                case 49: //F5..F8. What the f...!
                    switch (getchar()) {
                        case 53:
                            key = key::f5;
                            break;
                        case 55:
                            key = key::f6;
                            break;
                        case 56:
                            key = key::f7;
                            break;
                        case 57:
                            key = key::f8;
                            break;
                        default:
                            assert((key >= key::f5 && key <= key::f8)  && "F5-F8. Special key not defined");
                            break;
                    }
                    getchar(); //rubbish 126 value inside.
                    break;
                case 50: //F9 and F10. What the f... again!
                    switch (getchar()) {
                        case 48:
                            key = key::f9;
                            break;
                        case 49:
                            key = key::f10;
                            break;
                        default:
                            assert((key >= key::f9 && key <= key::f10)  && "F9-F10. Special key not defined");
                            break;
                    }
                    getchar(); //rubbish 126 value inside.
                    break;
                default:
                    assert(false && "This special key is not defined");
                    break;
            }
        } 
        if (secondKey == 79 ) { //F1..F4
            switch(getchar()) {
            case 80:
                key = key::f1;
                break;
            case 81:
                key = key::f2;
                break;
            case 82:
                key = key::f3;
                break;
            case 83:
                key = key::f4;
                break;    
            default:
                //You shall not pass.
                assert(false && "F1-F4. Special key not defined");
                break;
            }
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return key;
}
#endif // _WIN32
#endif // KEYBHANDLE_HPP