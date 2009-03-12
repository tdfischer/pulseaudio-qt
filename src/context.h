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

#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>

#include <pulse/pulseaudio.h>

class ContextPrivate;

#include "pulse-qt.h"
#include "sink.h"
//#include "input.h"

namespace Pulseaudio
{

class Context : public QObject {
    Q_OBJECT
    Q_ENUMS(RequestType)
    Q_ENUMS(ConnectionState)

    public:
        typedef enum {
            NoAutospawn
        } ServerFlag;
        Q_DECLARE_FLAGS(ServerFlags, ServerFlag)

        typedef enum {
            SinkList,
            SinkInputList,
            SourceList,
            SourceInputList,
            OutputList,
            ModuleList,
            SampleList,
            Stats,
            ServerInfo,
            //SampleList,

            SinkVolume,
            SinkMute,
            SinkSuspend,

            SourceVolume,
            SourceMute,

            ModuleLoad,
            ModuleUnload,

            ClientKill,

            SinkInputMove,
            SinkInputVolume,
            SinkInputMute,
            SinkInputKill,

        } RequestType;
        
        typedef enum {
            Unconnected,
            Connecting,
            Authorizing,
            SettingName,
            Ready,
            Failed,
            Terminated
        } ConnectionState;
        
        Context(const QString &clientName, QObject* parent = 0);
        virtual ~Context();
        
        void connectTo(const QString &server = "localhost", ServerFlags flags = 0); //TODO: pa_spawn_api

        QList<Sink*> sinks() const {return m_sinks;};
        //QList<Input> inputs();
        /*QList<Source> sources();
        QList<Output> outputs();
        QList<Module> modules();
        QList<Client> clients();
        QList<Sample> samples();
        Statistics statistics();*/
        friend class ::ContextPrivate;
        
    public slots:
        void request(RequestType type, const QList<QVariant> &args);
    
    signals:
        void requestFinished(RequestType type);
        void requestSuccess(RequestType type);
        void stateChanged(ConnectionState state);
    
    private:
        void setState(ConnectionState state);
        void addSink(const pa_sink_info* i, int eol);
        void addInput(const pa_sink_input_info* i, int eol);
        pa_context* m_cxt;
        QList<pa_operation*> m_operations;
        
        QList<Sink*> m_sinks;
        
        //QList<Input*> m_inputs;
        ContextPrivate* m_p;
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(Pulseaudio::Context::ServerFlags)

#endif
