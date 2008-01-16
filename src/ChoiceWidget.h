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
 * Copyright (C) 2005-2008 Guido de Jong <guidoj@users.sf.net>
 */

#ifndef CHOICE_WIDGET_H
#define CHOICE_WIDGET_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "Image.h"
#include "Widget.h"

class ChoiceWidget
            : public ActiveWidget
{
private:
    Image *normalImage;
    Image *selectedImage;
public:
    ChoiceWidget ( const Rectangle &r, const int a );
    virtual ~ChoiceWidget();
    void SetImage ( Image *normal, Image *selected );
    void Draw();
    void LeftClick ( const bool toggle, const int x, const int y );
    void RightClick ( const bool toggle, const int x, const int y );
    void Drag ( const int x, const int y );
    void Drop ( const int x, const int y );
};

#endif

