#include <QCoreApplication>
#include <myserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer myserver;
    myserver.startServer();

    return a.exec();
}
