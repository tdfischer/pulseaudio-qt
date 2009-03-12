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

#ifndef SINK_H
#define SINK_H

#include "pulse-qt.h"
#include <pulse/pulseaudio.h>

#include <QObject>

namespace Pulseaudio
{

class Sink : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(int index READ index)
    Q_PROPERTY(QString description READ description)

    public:
        virtual ~Sink();
        QString name() const {return m_name;};
        int index() const {return m_idx;};
        QString description() const {return m_desc;};
        
    private:
        Sink(const pa_sink_info* i, QObject* parent = 0);
        QString m_name;
        int m_idx;
        QString m_desc;
        friend class Context;
};

}

#endif
