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
 * Copyright (C) 2005-2006  Guido de Jong <guidoj@users.sf.net>
 */

#ifndef GAME_H
#define GAME_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "Chapter.h"
#include "ImageResource.h"
#include "Party.h"
#include "PartyResource.h"

class Game {
  private:
    std::string name;
    Chapter *chapter;
    Party *party;
    PartyResource partyRes;
    ImageResource heads;
  public:
    Game();
    ~Game();
    std::string& GetName();
    Party* GetParty();
    Chapter* GetChapter();
    void Load(FileBuffer *buffer);
};

#endif

