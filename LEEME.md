# Tabla de Contenidos

- [Sobre el Proyecto](#sobre-el-proyecto)
- [Pros](#pros)
- [Cons](#pros)
- [Fallos Conocidos](#fallos-conocidos)
- [Uso y Demo](#uso-y-demo)
- [License](#license)
- [Contact](#contact)

## Sobre el Proyecto

Buscaba una alternativa en C++ para Windows y Linux para poder detectar si se ha pulsado una tecla y qué tecla se ha pulsado.

Las alternativas no me convencian:

- conio: Sólo para Windows. KeybHandle lo usa en Windows.
- ncurses: Para Windows y Linux. Pero está hecha en C y no se lleva muy bien con std::cout y std::cin. Al final terminas haciendo todo "a lo C". Sin contar que es demasiado pesada si lo único que quieres es leer una tecla.

KeybHandle, es una clase con 2 métodos estáticos <strong>ispressed()</strong> y <strong>getkey()</strong>. Además devuelve las teclas con unos valores unificados que la hace ideal para programar multiplataforma.

## Pros

- Sólo un header.
- Multiplataforma: Windows, Linux y UNIX.
- Permite trabajar "a lo C++" usando métodos a una clase.

## Cons

- Las teclas F11, F12, ALT, ALTGR, SHIFT, CTRL, WIN, NUMLOCK, y algunas especiales más, no se capturan. Esto no es algo que necesite, por lo que no voy a molestarme en implementarlo.

## Fallos conocidos

- En linux, si se usan funciones como sleep, no se puede evitar (o a menos yo no sé cómo hacerlo) la entrada por teclado, por lo que se produce un eco en pantalla de lo que se teclea mientras dura la pausa. Más info en la demo.
- El código no está testeado 100% con todas la teclas por lo que es posible que alguna combinación dé error con un assert(). En realidad no es un error, sino que esa tecla especial no está implementada y se puede ignorar. Tienes 3 opciones:
        
    - Implementar esas nuevas teclas por ti mismo en el código.
    - Compilar como Release para eliminar los assert.
    - Comentar/Eliminar los assert.

## Uso y Demo

En el cpp de demostración puedes ver el funcionamiento. Un bucle infinito en el que se comprueba constantemente si se ha pulsado una tecla con <strong>kh::ispressed()</strong> y la gestión de dicha tecla con <strong>kh::getkey()</strong>. No hay mucho más que explicar.

## License

Distributed under the MIT License.

## Contact

Feel free to send me any feedback.

José Puga - josepuga.programacion@gmail.com
