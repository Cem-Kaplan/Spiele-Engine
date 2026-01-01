# Spiele-Engine

Hier hab ich eine Spiele Engine mit folgenden Bibliotheken kombiniert:
### - QT5 (Benutzeroberfläche)
### - Libray (Spiele Engine)

ausführen auf linux mit:

    $ g++ -fPIC -o main src/main.cpp -I include -L liblinux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 `pkg-config --cflags --libs Qt5Widgets`
    
oder:

    $ ./build_game.sh
