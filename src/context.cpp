#include "context.h"
#include "mainloop.h"
#include <QDebug>

class ContextPrivate {
    public:
        ContextPrivate(Context* d) : m_d(d) {};
        Context* m_d;
        
        void addSink(const pa_sink_info* i, int eol) {
            m_d->addSink(i, eol);
        };
        
        void addInput(const pa_sink_input_info* i, int eol) {
            m_d->addInput(i, eol);
        };
        
        void setState(Context::ConnectionState c) {
            m_d->setState(c);
        };
};

void sinkList(pa_context* c, const pa_sink_info* i, int eol, void* data) {
    ContextPrivate* cxt = static_cast<ContextPrivate*>(data);
    cxt->addSink(i, eol);
}

void sinkInputList(pa_context* c, const pa_sink_input_info* i, int eol, void* data) {
    ContextPrivate* cxt = static_cast<ContextPrivate*>(data);
    cxt->addInput(i, eol);
}

void connectionState(pa_context* c, void* data) {
    
    ContextPrivate* cxt = static_cast<ContextPrivate*>(data);
    switch (pa_context_get_state(c)) {
        case PA_CONTEXT_CONNECTING:
            cxt->setState(Context::Connecting);
            break;
        case PA_CONTEXT_AUTHORIZING:
            cxt->setState(Context::Authorizing);
            break;
        case PA_CONTEXT_SETTING_NAME:
            cxt->setState(Context::SettingName);
            break;
        case PA_CONTEXT_READY:
            cxt->setState(Context::Ready);
            break;
        case PA_CONTEXT_FAILED:
            cxt->setState(Context::Failed);
            break;
        case PA_CONTEXT_TERMINATED:
            cxt->setState(Context::Terminated);
            break;
    }
}

Context::Context(const QString &clientName, QObject* parent)
    : QObject(parent),
      m_p(new ContextPrivate(this))
{
    m_cxt = pa_context_new(Mainloop::instance()->api(), clientName.toUtf8());
    pa_context_set_state_callback(m_cxt, connectionState, this);
}

Context::~Context() {
    delete m_p;
}


void
Context::connectTo(const QString &server, ServerFlags)
{
    int ret = pa_context_connect(m_cxt, server.toAscii(), (pa_context_flags_t)0, NULL);
    qDebug() << "Connected:" << ret;
}

void
Context::addSink(const pa_sink_info* i, int eol)
{
    if (eol>0)
        emit requestFinished(SinkList);
    else {
        Sink* s = new Sink(i, this);
        m_sinks.append(s);
    }
}

void
Context::addInput(const pa_sink_input_info* i, int eol)
{
    
}

void
Context::setState(ConnectionState state) {
    qDebug() << "State changed.";
    emit stateChanged(state);
}

void
Context::request(RequestType type, const QList<QVariant> &args)
{
    switch(type) {
        case SinkList:
            m_sinks.clear();
            pa_context_get_sink_info_list(m_cxt, sinkList, m_p);
            break;
        case SinkInputList:
            //m_inputs.clear();
            //pa_context_get_sink_input_info_list(m_cxt, Callbacks::sinkInputList, this);
            break;
    }
}
