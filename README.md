# Table of Contents

- [About The Project](#about-the-project)
- [Pros](#pros)
- [Cons](#pros)
- [Know Bugs](#know-bugs)
- [Usage and Demo](#usage-and-demo)
- [License](#license)
- [Contact](#contact)

## About The Project

I was looking for a C++ Windows and Linux alternative to detect if a key was pressed and wich one.

Alternatives do not convince me:

- conio: Windows only. KeybHandle uses conio in Windows.
- ncurses: For Windows and Linux. But it's made in C and doesn't get along very well with std::cout and std::cin. In the end, you end up doing everything "in C style". Not to metion that is too heavy if all you want is to read a key.

KeybHandle, is a class with 2 static methods <strong>ispressed()</strong> y <strong>getkey()</strong>. It also returns unified key values, ideal for multiplatform programming.

## Pros

- Only one header.
- Multiplatform: Windows, Linux and UNIX.
- Works with "C++ style" using class methods.

## Cons

- Keys F11, F12, ALT, ALTGR, SHIFT, CTRL, WIN, NUMLOCK. Are not captured. This is not necessary for me, and I'm not going to implement it.

## Know Bugs

- In linux, if you use functions like sleep, you can't avoid (or at least I don't know how to do it) keyboard input, so the screen echoes. More info en the demo.
- The code is not tested 100% with all the keys, so is possible get an assert error with some combination. Actually is not an error, this key is not implemented, you can ignore it. You have 3 choices:
        
    - Implement the new keys by yourself in the code.
    - Compile as Release to delete assert.
    - Comment/delete assert manually.

## Usage and Demo

You can see how does it works with the cpp demo. An infinite loop checking always if a key has been pressed with <strong>kh::ispressed()</strong> and how to handle this key with 
<strong>kh::getkey()</strong>. There is no much more to explain.

## License

Distributed under the MIT License.

## Contact

Feel free to send me any feedback.

José Puga - josepuga.programacion@gmail.com
