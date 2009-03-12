#include "sink.h"

Sink::Sink(const pa_sink_info* i, QObject* parent)
    : QObject(parent),
      m_name(i->name),
      m_idx(i->index),
      m_desc(i->description)
{
    
}

Sink::~Sink()
{
}