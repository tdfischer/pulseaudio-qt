#include "mainloop.h"


Mainloop::Mainloop()
{
    m_loop = pa_glib_mainloop_new(NULL);
}

Mainloop::~Mainloop()
{
    pa_glib_mainloop_free(m_loop);
}

pa_mainloop_api*
Mainloop::api() const
{
    return pa_glib_mainloop_get_api(m_loop);
}