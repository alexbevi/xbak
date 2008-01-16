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

#ifndef PREFERENCES_H
#define PREFERENCES_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

typedef enum _StepTurnSize {
    STS_SMALL,
    STS_MEDIUM,
    STS_LARGE
} StepTurnSize;

typedef enum _TextSpeed {
    TS_WAIT,
    TS_MEDIUM,
    TS_FAST
} TextSpeed;

typedef enum _LevelOfDetail {
    LOD_MIN,
    LOD_LOW,
    LOD_HIGH,
    LOD_MAX
} LevelOfDetail;

class Preferences
{
private:
    StepTurnSize stepSize;
    StepTurnSize turnSize;
    TextSpeed textSpeed;
    LevelOfDetail detail;
    bool sound;
    bool music;
    bool combatMusic;
    bool cdMusic;
    bool introduction;
public:
    Preferences();
    ~Preferences();
    void SetDefaults();
    void Copy ( const Preferences &prefs );
    StepTurnSize GetStepSize() const;
    void SetStepSize ( const StepTurnSize sz );
    StepTurnSize GetTurnSize() const;
    void SetTurnSize ( const StepTurnSize sz );
    TextSpeed GetTextSpeed() const;
    void SetTextSpeed ( const TextSpeed ts );
    LevelOfDetail GetDetail() const;
    void SetDetail ( const LevelOfDetail lod );
    bool GetSound() const;
    void SetSound ( const bool toggle );
    bool GetMusic() const;
    void SetMusic ( const bool toggle );
    bool GetCombatMusic() const;
    void SetCombatMusic ( const bool toggle );
    bool GetCdMusic() const;
    void SetCdMusic ( const bool toggle );
    bool GetIntroduction() const;
    void SetIntroduction ( const bool toggle );
};

#endif
