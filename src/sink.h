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
