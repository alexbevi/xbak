/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Copyright (C) 2005-2007  Guido de Jong <guidoj@users.sf.net>
 */

#include "Exception.h"
#include "MediaToolkit.h"
#include "SDL_Toolkit.h"

MediaToolkit* MediaToolkit::instance = 0;

MediaToolkit::MediaToolkit()
        : audio(0)
        , clock(0)
        , video(0)
        , eventLoopRunning(false)
        , keyboardListeners()
        , mouseButtonListeners()
        , mouseMotionListeners()
        , dragListeners()
        , dropListeners()
        , timerListeners()
        , loopListeners()
{}

MediaToolkit::~MediaToolkit()
{
    keyboardListeners.clear();
    mouseButtonListeners.clear();
    mouseMotionListeners.clear();
    dragListeners.clear();
    dropListeners.clear();
    timerListeners.clear();
    loopListeners.clear();
}

MediaToolkit*
MediaToolkit::GetInstance()
{
    if (!instance)
    {
        instance = new SDL_Toolkit();
    }
    return instance;
}

void
MediaToolkit::CleanUp()
{
    if (instance)
    {
        delete instance;
        instance = 0;
    }
}

Audio*
MediaToolkit::GetAudio() const
{
    return audio;
}

Clock*
MediaToolkit::GetClock() const
{
    return clock;
}

Video*
MediaToolkit::GetVideo() const
{
    return video;
}

void
MediaToolkit::AddKeyboardListener(KeyboardEventListener *kel)
{
    keyboardListeners.push_back(kel);
}

void
MediaToolkit::RemoveKeyboardListener(KeyboardEventListener *kel)
{
    keyboardListeners.remove(kel);
}

void
MediaToolkit::AddMouseButtonListener(MouseButtonEventListener *mbel)
{
    mouseButtonListeners.push_back(mbel);
}

void
MediaToolkit::RemoveMouseButtonListener(MouseButtonEventListener *mbel)
{
    mouseButtonListeners.remove(mbel);
}

void
MediaToolkit::AddMouseMotionListener(MouseMotionEventListener *mmel)
{
    mouseMotionListeners.push_back(mmel);
}

void
MediaToolkit::RemoveMouseMotionListener(MouseMotionEventListener *mmel)
{
    mouseMotionListeners.remove(mmel);
}

void
MediaToolkit::AddDragListener(DragEventListener *diel)
{
    dragListeners.push_back(diel);
}

void
MediaToolkit::RemoveDragListener(DragEventListener *diel)
{
    dragListeners.remove(diel);
}

void
MediaToolkit::AddDropListener(DropEventListener *diel)
{
    dropListeners.push_back(diel);
}

void
MediaToolkit::RemoveDropListener(DropEventListener *diel)
{
    dropListeners.remove(diel);
}

void
MediaToolkit::AddTimerListener(TimerEventListener *tel)
{
    timerListeners.push_back(tel);
}

void
MediaToolkit::RemoveTimerListener(TimerEventListener *tel)
{
    timerListeners.remove(tel);
}

void
MediaToolkit::AddUpdateListener(LoopEventListener *lel)
{
    loopListeners.push_back(lel);
}

void
MediaToolkit::RemoveUpdateListener(LoopEventListener *lel)
{
    loopListeners.remove(lel);
}

void
MediaToolkit::TerminateEventLoop()
{
    eventLoopRunning = false;
}
