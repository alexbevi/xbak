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
#include "NameResource.h"

NameResource::NameResource()
{
}

NameResource::~NameResource()
{
  name.clear();
}

unsigned int
NameResource::GetSize() const {
  return name.size();
}

std::string
NameResource::GetName(unsigned int n) const {
  return name[n];
}

void
NameResource::Load(FileBuffer *buffer)
{
  try {
    unsigned int n = buffer->GetUint16();
    unsigned int *offset = new unsigned int[n];
    for (unsigned int i = 0; i < n; i++) {
      offset[i] = buffer->GetUint16();
    }
    buffer->Skip(2);
    unsigned int start = buffer->GetBytesDone();
    for (unsigned int i = 0; i < n; i++) {
      buffer->Seek(start + offset[i]);
      name.push_back(buffer->GetString());
    }
    delete[] offset;
  } catch (Exception &e) {
    e.Print("NameResource::Load");
  }
}

