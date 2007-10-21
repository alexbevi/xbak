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

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "Event.h"

class KeyboardEventListener
{
public:
    KeyboardEventListener()
    {};
    virtual ~KeyboardEventListener()
    {};
    virtual void KeyPressed ( const KeyboardEvent &kbe ) = 0;
    virtual void KeyReleased ( const KeyboardEvent &kbe ) = 0;
};

class PointerButtonEventListener
{
public:
    PointerButtonEventListener()
    {};
    virtual ~PointerButtonEventListener()
    {};
    virtual void PointerButtonPressed ( const PointerButtonEvent &pbe ) = 0;
    virtual void PointerButtonReleased ( const PointerButtonEvent &pbe ) = 0;
};

class PointerMotionEventListener
{
public:
    PointerMotionEventListener()
    {};
    virtual ~PointerMotionEventListener()
    {};
    virtual void PointerMoved ( const PointerMotionEvent &mme ) = 0;
};

class TimerEventListener
{
public:
    TimerEventListener()
    {};
    virtual ~TimerEventListener()
    {};
    virtual void TimerExpired ( const TimerEvent &te ) = 0;
};

class LoopEventListener
{
public:
    LoopEventListener()
    {};
    virtual ~LoopEventListener()
    {};
    virtual void LoopComplete ( const LoopEvent &le ) = 0;
};

class ActionEventListener
{
public:
    ActionEventListener()
    {};
    virtual ~ActionEventListener()
    {};
    virtual void ActionPerformed ( const ActionEvent &ae ) = 0;
};

class DragEventListener
{
public:
    DragEventListener()
    {};
    virtual ~DragEventListener()
    {};
    virtual void PointerDragged ( const DragEvent &de ) = 0;
};

#endif
