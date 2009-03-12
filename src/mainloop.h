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

#ifndef MAINLOOP_H
#define MAINLOOP_H

#include <pulse/pulseaudio.h>
#include <pulse/glib-mainloop.h>

#include "pulse-qt.h"

namespace Pulseaudio
{

/**
 * \class Mainloop
 * \author Trever Fischer <wm161@wm161.net>
 *
 * \brief The Qt implementation of a PulseAudio event loop.
 *
 * This class represents the Qt-based PulseAudio event loop.
 * Only one exists at a time, and most people should never have to touch it.
 *
 * Other classes use the global instance transparently, so you should never have to mess with this.
 *
 * \note This class uses the singleton pattern. Call Mainloop::instance() to get the global instance.
 */

class Mainloop {
    public:
        /**
         * \brief Returns the global main loop instance
         *
         * The Mainloop class is a singleton.
         */
        static Mainloop* instance() {
            static Mainloop* instance = 0;
            if (instance == 0)
                instance = new Mainloop();
            return instance;
        };
        
        ~Mainloop();
        
    private:
        Mainloop();
        
        pa_glib_mainloop* m_loop;
        pa_mainloop_api* api() const;
        friend class Context;
};

}

#endif
