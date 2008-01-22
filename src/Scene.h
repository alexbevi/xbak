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
 * Copyright (C) 2007-2008 Guido de Jong <guidoj@users.sf.net>
 */

#ifndef SCENE_H
#define SCENE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <map>

#include "Camera.h"
#include "GenericObject.h"
#include "Image.h"
#include "SpritedObject.h"
#include "TerrainObject.h"
#include "Video.h"

class Scene
{
    private:
        Video *video;
        Image *horizonTexture;
        Image *terrainTexture;
        std::multimap<const Vector2D, SpritedObject *> sprites;
        std::multimap<const Vector2D, TerrainObject *> terrains;
        std::multimap<const unsigned int, SpritedObject *> spriteZBuffer;
        std::multimap<const unsigned int, TerrainObject *> terrainZBuffer;
        void FillSpriteZBuffer ( Camera *cam );
        void FillTerrainZBuffer ( Camera *cam );
        void DrawHorizon ( const int x, const int y, const int w, const int h, Camera *cam );
        void DrawGround ( const int x, const int y, const int w, const int h, Camera *cam );
        void DrawZBuffer ( const int x, const int y, const int w, const int h, Camera *cam );
    public:
        Scene ( Image *horizon, Image *terrain );
        ~Scene();
        void AddObject ( const Vector2D &cell, SpritedObject *obj );
        void AddObject ( const Vector2D &cell, TerrainObject *obj );
        void DrawFirstPerson ( const int x, const int y, const int w, const int h, Camera *cam );
        void DrawTopDown();
};

#endif
