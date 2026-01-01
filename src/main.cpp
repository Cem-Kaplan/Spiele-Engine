#include "raylib.h"
#include <iostream>
#include <raymath.h>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <cstdio>
#include <QThread>
#include <atomic>
#include <QProcess>
#include <QDebug>
#include <QLabel>
#include <game.cpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setWindowTitle("Game Engine von Cem");
    mainWindow.resize(1000, 500);

    QPushButton debugButton("Test", &mainWindow);
    debugButton.resize(200, 50);
    debugButton.move(10, 10);
    
    QPushButton stopButton("Stop Test", &mainWindow);
    stopButton.resize(200, 50);
    stopButton.move(10, 70);
    
    QPushButton buildButton("Build", &mainWindow);
    buildButton.resize(200, 50);
    buildButton.move(10, 130);

    QPushButton settingsButton("Settings", &mainWindow);
    settingsButton.resize(200, 50);
    settingsButton.move(10, 190);

    QWidget settingsWindow;
    settingsWindow.setWindowTitle("Engine Settings");
    settingsWindow.resize(500, 250);

    QLabel settingsText("Still in work", &settingsWindow);
    settingsText.resize(200,50);
    settingsText.move(220,80);

    mainWindow.setStyleSheet("QWidget {"
        " background-color: #0a0029"
        "}"
    );

    debugButton.setStyleSheet("QPushButton {"
        " color: white"
        "}"
    );
    stopButton.setStyleSheet("QPushButton {"
        " color: white"
        "}"
    );
    settingsButton.setStyleSheet("QPushButton {"
        " color: white"
        "}"
    );
    buildButton.setStyleSheet("QPushButton {"
        " color: white"
        "}"
    );
    settingsWindow.setStyleSheet("QWidget {"
        "background-color: #0a0029"
        "}"
    );
    settingsText.setStyleSheet("QLabel{"
        "color: white"
        "}"
    );
    mainWindow.show();

    class GameWorker : public QThread {
    protected:
        void run() override {
            running = true;
            game();
        }
    };
    
    auto* worker = new GameWorker();

    QObject::connect(&debugButton, &QPushButton::clicked, [&]() {
        worker->start();

    }); 

    QObject::connect(&stopButton, &QPushButton::clicked, [&]() {
        running = false;
    });

    QObject::connect(&buildButton, &QPushButton::clicked, [&]() {
        QProcess* build = new QProcess(nullptr);
        QString program = "../build_game.sh";
        QStringList arguments;
        build->start(program, arguments);
        qDebug() << "Build started";
    });

    QObject::connect(&settingsButton, &QPushButton::clicked, [&]() {
        qDebug() << "Settings Opened";
        settingsWindow.show();
    });

    app.exec();

    return 0;
}
