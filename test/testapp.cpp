#include "testapp.h"

#include <QDebug>
#include <QVariant>

TestApp::TestApp(int argc, char** argv)
    : QCoreApplication(argc, argv)
{
    m_cxt = new Context("TestApp", this);
    connect(m_cxt, SIGNAL(stateChanged(ConnectionState)), this, SLOT(getSinks()));
    connect(m_cxt, SIGNAL(requestFinished(RequestType)), this, SLOT(showSinks()));
    m_cxt->connectTo();
}

void
TestApp::getSinks()
{
    qDebug() << "Connected! Getting sinks...";
    QList<QVariant> args;
    m_cxt->request(Context::SinkList, args);
}

TestApp::~TestApp()
{
}

void
TestApp::showSinks()
{
    foreach(Sink* s, m_cxt->sinks()) {
        qDebug() << s->name();
    }
    quit();
}
