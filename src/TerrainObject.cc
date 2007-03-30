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
 * Copyright (C) 2007 Guido de Jong <guidoj@users.sf.net>
 */

#include "TerrainObject.h"

TerrainObject::TerrainObject(const Vector2D &p, const int w, const int h)
: GenericObject(p, w, h)
{
}

TerrainObject::~TerrainObject()
{
}

void
TerrainObject::DrawFirstPerson(const int x, const int y, const int w, const int h, const int heading)
{
  if (x && y && w && h && heading);
}

void
TerrainObject::DrawTopDown()
{
}
