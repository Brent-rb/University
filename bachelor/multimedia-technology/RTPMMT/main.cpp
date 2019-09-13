#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Advapi32.lib")
#include "RTPSyncer.h"
#include <thread>
#include "rtpplayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if (argc != 4) {
            std::cout << "Invalid number of arguments." << std::endl;
            return -1;
        }

    #ifdef WIN32
        WSADATA dat;
        WSAStartup(MAKEWORD(2, 2), &dat);
    #endif // WIN32

        RTPSession sess;
        uint16_t portbase, destport;
        uint32_t destip;

        inet_pton(AF_INET, argv[1], &destip);
        if (destip == INADDR_NONE)
        {
            std::cerr << "Bad IP address specified" << std::endl;
            return -1;
        }

        sscanf(argv[2], "%hu", &destport);
        sscanf(argv[3], "%hu", &portbase);

        RTPSyncer syncer(portbase, destip, destport, -1);
        RTPPlayer player(&w, &syncer);
        QObject::connect(&player, SIGNAL(playFrame(QImage*, uint8_t*)), &w, SLOT(updateImage(QImage*, uint8_t*)));
        QObject::connect(&syncer, SIGNAL(frameReady()), &player, SLOT(wake()));
        std::thread thread(&RTPSyncer::run, &syncer);
        player.start();

    a.exec();
    syncer.cancel();
    player.cancel();
    thread.join();
    player.wait();
    #ifdef WIN32
        WSACleanup();
    #endif // WIN32
        return 0;
}
