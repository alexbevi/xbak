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

#include "Exception.h"
#include "ZoneTableResource.h"

ZoneTableResource::ZoneTableResource()
: TaggedResource()
, mapItems()
, appItems()
{
}

ZoneTableResource::~ZoneTableResource()
{
  Clear();
}

unsigned int
ZoneTableResource::GetMapSize() const
{
  return mapItems.size();
}

std::string&
ZoneTableResource::GetMapItem(const unsigned int i)
{
  return mapItems[i];
}

unsigned int
ZoneTableResource::GetAppSize() const
{
  return appItems.size();
}

AppInfo&
ZoneTableResource::GetAppItem(const unsigned int i)
{
  return appItems[i];
}

unsigned int
ZoneTableResource::GetDatSize() const
{
  return datItems.size();
}

DatInfo&
ZoneTableResource::GetDatItem(const unsigned int i)
{
  return datItems[i];
}

unsigned int
ZoneTableResource::GetGidSize() const
{
  return gidItems.size();
}

GidInfo&
ZoneTableResource::GetGidItem(const unsigned int i)
{
  return gidItems[i];
}

void
ZoneTableResource::Clear()
{
  mapItems.clear();
  for (unsigned int i = 0; i < appItems.size(); i++) {
    delete[] appItems[i].data;
  }
  appItems.clear();
  gidItems.clear();
}

void
ZoneTableResource::Load(FileBuffer *buffer)
{
  try {
    Clear();
    Split(buffer);
    FileBuffer *mapbuf;
    FileBuffer *appbuf;
    FileBuffer *gidbuf;
    FileBuffer *datbuf;
    if (!Find(TAG_MAP, mapbuf) ||
        !Find(TAG_APP, appbuf) ||
        !Find(TAG_GID, gidbuf) ||
        !Find(TAG_DAT, datbuf)) {
      ClearTags();
      throw DataCorruption(__FILE__, __LINE__);
    }
    mapbuf->Skip(2);
    unsigned int numMapItems = mapbuf->GetUint16LE();
    unsigned int *mapOffset = new unsigned int [numMapItems];
    for (unsigned int i = 0; i < numMapItems; i++) {
      mapOffset[i] = mapbuf->GetUint16LE();
    }
    mapbuf->Skip(2);
    unsigned int mapDataStart = mapbuf->GetBytesDone();
    for (unsigned int i = 0; i < numMapItems; i++) {
      mapbuf->Seek(mapDataStart + mapOffset[i]);
      std::string item = mapbuf->GetString();
      mapItems.push_back(item);
    }
    delete[] mapOffset;

    unsigned int numAppItems = appbuf->GetUint16LE();
    unsigned int appDataSize = appbuf->GetUint16LE();
    for (unsigned int i = 0; i< numAppItems; i++) {
      AppInfo item;
      item.size = appDataSize;
      item.data = new uint8_t[appDataSize];
      appbuf->GetData(item.data, item.size);
      appItems.push_back(item);
    }

    unsigned int *gidOffset = new unsigned int [numMapItems];
    for (unsigned int i = 0; i < numMapItems; i++) {
      gidOffset[i] = (gidbuf->GetUint16LE() & 0x000f) + (gidbuf->GetUint16LE() << 4);
    }
    for (unsigned int i = 0; i < numMapItems; i++) {
      gidbuf->Seek(gidOffset[i]);
      GidInfo item;
      item.xsize = gidbuf->GetUint16LE();
      item.ysize = gidbuf->GetUint16LE();
      item.more = gidbuf->GetUint16LE() > 0;
      item.flags = gidbuf->GetUint16LE();
      if (item.more) {
        // TODO
      }
      gidItems.push_back(item);
    }
    delete[] gidOffset;

    unsigned int *datOffset = new unsigned int [numMapItems];
    for (unsigned int i = 0; i < numMapItems; i++) {
      datOffset[i] = (datbuf->GetUint16LE() & 0x000f) + (datbuf->GetUint16LE() << 4);
    }
    for (unsigned int i = 0; i < numMapItems; i++) {
      datbuf->Seek(datOffset[i]);
      DatInfo item;
      item.type = datbuf->GetUint32LE();
      datbuf->Skip(4);
      item.more = datbuf->GetUint16LE() > 0;
      datbuf->Skip(4);
      if (item.more) {
        // TODO
      }
    }
    delete[] datOffset;

    ClearTags();
  } catch (Exception &e) {
    e.Print("ZoneTableResource::Load");
    ClearTags();
    throw;
  }
}

void
ZoneTableResource::Save(FileBuffer *buffer)
{
  try {
    // TODO
    buffer = buffer;
  } catch (Exception &e) {
    e.Print("ZoneTableResource::Save");
    throw;
  }
}
