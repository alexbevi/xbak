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

#include "DialogWindow.h"
#include "MousePointerManager.h"

DialogWindow::DialogWindow(PanelWidget *panelwidget)
: panel(panelwidget)
{
}

DialogWindow::~DialogWindow()
{
  if (panel) {
    delete panel;
  }
}

void
DialogWindow::Draw()
{
  panel->Draw();
  MousePointerManager::GetInstance()->GetCurrentPointer()->Draw();
  MediaToolkit::GetInstance()->GetVideo()->Refresh();
}

void
DialogWindow::FadeIn(Palette* pal)
{
  panel->Reset();
  panel->Draw();
  MousePointerManager::GetInstance()->GetCurrentPointer()->Draw();
  pal->FadeIn(0, VIDEO_COLORS, 64, 5);
}

void
DialogWindow::FadeOut(Palette* pal)
{
  panel->Draw();
  MousePointerManager::GetInstance()->GetCurrentPointer()->Draw();
  pal->FadeOut(0, VIDEO_COLORS, 64, 5);
}

void
DialogWindow::LeftClickWidget(const bool toggle)
{
  panel->LeftClick(toggle);
}

void
DialogWindow::RightClickWidget(const bool toggle)
{
  panel->RightClick(toggle);
}

void
DialogWindow::LeftClickWidget(const bool toggle, const int x, const int y)
{
  panel->LeftClick(toggle, x, y);
}

void
DialogWindow::RightClickWidget(const bool toggle, const int x, const int y)
{
  panel->RightClick(toggle, x, y);
}

void
DialogWindow::MouseOverWidget(const int x, const int y)
{
  panel->MouseOver(x, y);
}

void
DialogWindow::SelectNextWidget()
{
  panel->NextWidget();
}

void
DialogWindow::SelectPreviousWidget()
{
  panel->PreviousWidget();
}
