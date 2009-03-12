/**
* Copyright (C) 2009 Trever Fischer <wm161@wm161.net>
*
* This file is part of PulseAudio-Qt.
*
*  Glovebox is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  Glovebox is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with PulseAudio-Qt.  If not, see <http://www.gnu.org/licenses/>.
*/
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
