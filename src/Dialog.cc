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
#include "Dialog.h"
#include "FileManager.h"
#include "MousePointerManager.h"
#include "WidgetFactory.h"

Dialog::Dialog()
: window(0)
, palette(0)
, widgetRes()
, action(0)
, running(false)
{
  try {
    MousePointerManager::GetInstance()->SetCurrentPointer(NORMAL_POINTER);
    MousePointerManager::GetInstance()->GetCurrentPointer()->SetVisible(true);
    memset(&widgetRes, 0, sizeof(WidgetResources));
    widgetRes.eventListener = this;
  } catch (Exception &e) {
    e.Print("Dialog::Dialog");
    throw;
  }
}

Dialog::~Dialog()
{
  if (widgetRes.font) {
    delete widgetRes.font;
  }
  if (widgetRes.label) {
    delete widgetRes.label;
  }
  if (widgetRes.screen) {
    delete widgetRes.screen;
  }
  if (widgetRes.normal) {
    delete widgetRes.normal;
  }
  if (widgetRes.pressed) {
    delete widgetRes.pressed;
  }
  if (widgetRes.compass) {
    delete widgetRes.compass;
  }
  if (widgetRes.heads) {
    delete widgetRes.heads;
  }
  if (widgetRes.request) {
    delete widgetRes.request;
  }
  if (palette) {
    delete palette;
  }
  if (window) {
    delete window;
  }
}

void
Dialog::SetFont(const std::string &name)
{
  try {
    if (widgetRes.font) {
      delete widgetRes.font;
    }
    widgetRes.font = new FontResource();
    FileManager::GetInstance()->Load(widgetRes.font, name);
  } catch (Exception &e) {
    e.Print("Dialog::SetFont");
    throw;
  }
}

void
Dialog::SetLabel(const std::string &name)
{
  try {
    if (widgetRes.label) {
      delete widgetRes.label;
    }
    widgetRes.label = new LabelResource();
    FileManager::GetInstance()->Load(widgetRes.label, name);
  } catch (Exception &e) {
    e.Print("Dialog::SetLabel");
    throw;
  }
}

void
Dialog::SetPalette(const std::string &name)
{
  try {
    if (palette) {
      delete palette;
    }
    palette = new PaletteResource();
    FileManager::GetInstance()->Load(palette, name);
  } catch (Exception &e) {
    e.Print("Dialog::Setpalette");
    throw;
  }
}

void
Dialog::SetScreen(const std::string &name)
{
  try {
    if (widgetRes.screen) {
      delete widgetRes.screen;
    }
    widgetRes.screen = new ScreenResource();
    FileManager::GetInstance()->Load(widgetRes.screen, name);
  } catch (Exception &e) {
    e.Print("Dialog::SetScreen");
    throw;
  }
}

void
Dialog::SetIcons(const std::string &normalName, const std::string &pressedName)
{
  try {
    if (widgetRes.normal) {
      delete widgetRes.normal;
    }
    widgetRes.normal = new ImageResource();
    FileManager::GetInstance()->Load(widgetRes.normal, normalName);
    if (widgetRes.pressed) {
      delete widgetRes.pressed;
    }
    widgetRes.pressed = new ImageResource();
    FileManager::GetInstance()->Load(widgetRes.pressed, pressedName);
  } catch (Exception &e) {
    e.Print("Dialog::SetIcons");
    throw;
  }
}

void
Dialog::SetCompass(const std::string &name, Orientation *orient)
{
  try {
    if (widgetRes.compass) {
      delete widgetRes.compass;
    }
    widgetRes.compass = new ImageResource();
    FileManager::GetInstance()->Load(widgetRes.compass, name);
    widgetRes.orient = orient;
  } catch (Exception &e) {
    e.Print("Dialog::SetCompass");
    throw;
  }
}

void
Dialog::SetHeads(const std::string &name)
{
  try {
    if (widgetRes.heads) {
      delete widgetRes.heads;
    }
    widgetRes.heads = new ImageResource();
    FileManager::GetInstance()->Load(widgetRes.heads, name);
  } catch (Exception &e) {
    e.Print("Dialog::SetHeads");
    throw;
  }
}

void
Dialog::SetRequest(const std::string &name)
{
  try {
    if (widgetRes.request) {
      delete widgetRes.request;
    }
    widgetRes.request = new RequestResource();
    FileManager::GetInstance()->Load(widgetRes.request, name);
  } catch (Exception &e) {
    e.Print("Dialog::SetRequest");
    throw;
  }
}

void
Dialog::SetMembers(Party *party, const int special)
{
  if (party) {
    widgetRes.special = special;
    for (unsigned int i = 0; i < MAX_ACTIVE_MEMBERS; i++) {
      PlayerCharacter *pc = party->GetActiveMember(i);
      widgetRes.members[i] = pc;
    }
  } else {
    throw NullPointer(__FILE__, __LINE__);
  }
}

void
Dialog::Enter()
{
  try {
    window = new DialogWindow(widgetRes);
    MediaToolkit::GetInstance()->GetVideo()->Clear();
    window->FadeIn(palette->GetPalette(), MediaToolkit::GetInstance());
  } catch (Exception &e) {
    e.Print("Dialog::Enter");
    throw;
  }
}

void
Dialog::Leave()
{
  try {
    window->FadeOut(palette->GetPalette(), MediaToolkit::GetInstance());
    MediaToolkit::GetInstance()->GetVideo()->Clear();
    delete window;
    window = 0;
  } catch (Exception &e) {
    e.Print("Dialog::Leave");
    throw;
  }
}

unsigned int
Dialog::Execute()
{
  try {
    MediaToolkit* media = MediaToolkit::GetInstance();
    media->AddKeyboardListener(this);
    media->AddMouseButtonListener(this);
    media->AddUpdateListener(this);
    running = true;
    media->PollEventLoop();
    running = false;
    media->RemoveUpdateListener(this);
    media->RemoveMouseButtonListener(this);
    media->RemoveKeyboardListener(this);
    return action;
  } catch (Exception &e) {
    e.Print("Dialog::Execute");
    throw;
  }
}

void
Dialog::Update(const UpdateEvent& ue)
{
  ue.GetTicks();
  if (running) {
    window->Draw(MediaToolkit::GetInstance()->GetVideo());
  }
}

void
Dialog::ActionPerformed(const ActionEvent& ae)
{
  action = ae.GetAction();
  MediaToolkit::GetInstance()->TerminateEventLoop();
}

void
Dialog::MouseButtonPressed(const MouseButtonEvent& mbe)
{
  switch (mbe.GetButton()) {
    case MB_LEFT:
      if (running) {
        window->LeftClickWidget(true, mbe.GetXPos(), mbe.GetYPos());
      }
      break;
    case MB_RIGHT:
      if (running) {
        window->RightClickWidget(true, mbe.GetXPos(), mbe.GetYPos());
      }
      break;
    default:
      break;
  }
}

void
Dialog::MouseButtonReleased(const MouseButtonEvent& mbe)
{
  switch (mbe.GetButton()) {
    case MB_LEFT:
      if (running) {
        window->LeftClickWidget(false, mbe.GetXPos(), mbe.GetYPos());
      }
      break;
    case MB_RIGHT:
      if (running) {
        window->RightClickWidget(false, mbe.GetXPos(), mbe.GetYPos());
      }
      break;
    default:
      break;
  }
}


GameDialog::GameDialog()
: Dialog()
{
}

GameDialog::~GameDialog()
{
}

void
GameDialog::KeyPressed(const KeyboardEvent& kbe)
{
  switch (kbe.GetKey()) {
    case KEY_ESCAPE:
      action = ACT_ESCAPE;
      MediaToolkit::GetInstance()->TerminateEventLoop();
      break;
    case KEY_UP:
      action = ACT_UP;
      MediaToolkit::GetInstance()->TerminateEventLoop();
      break;
    case KEY_DOWN:
      action = ACT_DOWN;
      MediaToolkit::GetInstance()->TerminateEventLoop();
      break;
    case KEY_LEFT:
      action = ACT_LEFT;
      MediaToolkit::GetInstance()->TerminateEventLoop();
      break;
    case KEY_RIGHT:
      action = ACT_RIGHT;
      MediaToolkit::GetInstance()->TerminateEventLoop();
      break;
    default:
      break;
  }
}

void
GameDialog::KeyReleased(const KeyboardEvent& kbe)
{
  switch (kbe.GetKey()) {
    default:
      break;
  }
}


OptionsDialog::OptionsDialog()
: Dialog()
{
}

OptionsDialog::~OptionsDialog()
{
}

void
OptionsDialog::KeyPressed(const KeyboardEvent& kbe)
{
  switch (kbe.GetKey()) {
    case KEY_ESCAPE:
      action = ACT_ESCAPE;
      MediaToolkit::GetInstance()->TerminateEventLoop();
      break;
    case KEY_DOWN:
    case KEY_TAB:
      if (running) {
        window->SelectNextWidget(MediaToolkit::GetInstance()->GetVideo());
      }
      break;
    case KEY_UP:
      if (running) {
        window->SelectPreviousWidget(MediaToolkit::GetInstance()->GetVideo());
      }
      break;
    case KEY_RETURN:
    case KEY_SPACE:
      if (running) {
        window->LeftClickWidget(true);
      }
      break;
    default:
      break;
  }
}

void
OptionsDialog::KeyReleased(const KeyboardEvent& kbe)
{
  switch (kbe.GetKey()) {
    case KEY_RETURN:
    case KEY_SPACE:
      if (running) {
        window->LeftClickWidget(false);
      }
      break;
    default:
      break;
  }
}
