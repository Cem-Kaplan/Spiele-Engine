# Spiele-Engine

Hier hab ich eine Spiele Engine mit folgenden Bibliotheken kombiniert:
### - QT5 (Benutzeroberfläche)
### - Raylib (Spiele Engine)

bauen auf linux mit:

    $ g++ -fPIC -o main src/main.cpp -I include -L liblinux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 `pkg-config --cflags --libs Qt5Widgets`
    
oder:

    $ ./build_app.sh

dann ausführen mit:

    $ ./main.o

# Was macht die Engine?

- Sie erstellt mit QT ein GUI um Raylib spiele auszuführen
- Sie kann auch ausführbare .o spiele erstellen, die dann überall auf linux ausführbar sind