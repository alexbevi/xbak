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

#include "MediaToolkit.h"
#include "RatingsWidget.h"

RatingsWidget::RatingsWidget(const int x, const int y, const int w, const int h, PlayerCharacter *pc, FontResource &f)
: Widget(x, y, w, h)
, playerCharacter(pc)
, horizontalBorder(0)
, verticalBorder(0)
, ratingsLabel(0)
, conditionLabel(0)
, healthLabel(0)
, staminaLabel(0)
, speedLabel(0)
, strengthLabel(0)
, healthOfLabel(0)
, staminaOfLabel(0)
{
  ratingsLabel = new LabelWidget(x + 11, y + 5, 40, 11, f);
  ratingsLabel->SetText("Ratings:");
  ratingsLabel->SetAlignment(HA_LEFT, VA_TOP);
  ratingsLabel->SetColor(RATINGS_TEXT_COLOR);
  ratingsLabel->SetShadow(COLOR_BLACK);
  conditionLabel = new LabelWidget(x + 126, y + 5, 50, 11, f);
  conditionLabel->SetText("Condition:");
  conditionLabel->SetAlignment(HA_LEFT, VA_TOP);
  conditionLabel->SetColor(RATINGS_TEXT_COLOR);
  conditionLabel->SetShadow(COLOR_BLACK);
  healthLabel = new LabelWidget(x + 21, y + 19, 40, 11, f);
  healthLabel->SetText("Health");
  healthLabel->SetAlignment(HA_LEFT, VA_TOP);
  healthLabel->SetColor(RATINGS_TEXT_COLOR);
  healthLabel->SetShadow(COLOR_BLACK);
  staminaLabel = new LabelWidget(x + 21, y + 30, 40, 11, f);
  staminaLabel->SetText("Stamina");
  staminaLabel->SetAlignment(HA_LEFT, VA_TOP);
  staminaLabel->SetColor(RATINGS_TEXT_COLOR);
  staminaLabel->SetShadow(COLOR_BLACK);
  speedLabel = new LabelWidget(x + 21, y + 41, 40, 11, f);
  speedLabel->SetText("Speed");
  speedLabel->SetAlignment(HA_LEFT, VA_TOP);
  speedLabel->SetColor(RATINGS_TEXT_COLOR);
  speedLabel->SetShadow(COLOR_BLACK);
  strengthLabel = new LabelWidget(x + 21, y + 52, 40, 11, f);
  strengthLabel->SetText("Strength");
  strengthLabel->SetAlignment(HA_LEFT, VA_TOP);
  strengthLabel->SetColor(RATINGS_TEXT_COLOR);
  strengthLabel->SetShadow(COLOR_BLACK);
  healthOfLabel = new LabelWidget(x + 86, y + 19, 12, 11, f);
  healthOfLabel->SetText("of");
  healthOfLabel->SetAlignment(HA_LEFT, VA_TOP);
  healthOfLabel->SetColor(RATINGS_TEXT_COLOR);
  healthOfLabel->SetShadow(COLOR_BLACK);
  staminaOfLabel = new LabelWidget(x + 86, y + 30, 12, 11, f);
  staminaOfLabel->SetText("of");
  staminaOfLabel->SetAlignment(HA_LEFT, VA_TOP);
  staminaOfLabel->SetColor(RATINGS_TEXT_COLOR);
  staminaOfLabel->SetShadow(COLOR_BLACK);
}

RatingsWidget::~RatingsWidget()
{
  if (ratingsLabel) {
    delete ratingsLabel;
  }
  if (conditionLabel) {
    delete conditionLabel;
  }
  if (healthLabel) {
    delete healthLabel;
  }
  if (staminaLabel) {
    delete staminaLabel;
  }
  if (speedLabel) {
    delete speedLabel;
  }
  if (strengthLabel) {
    delete strengthLabel;
  }
  if (healthOfLabel) {
    delete healthOfLabel;
  }
  if (staminaOfLabel) {
    delete staminaOfLabel;
  }
}

void
RatingsWidget::SetBorders(Image *hb, Image *vb)
{
  horizontalBorder = hb;
  verticalBorder = vb;
}

void
RatingsWidget::Draw()
{
  int xoff = 0;
  int yoff = 0;
  if (horizontalBorder && verticalBorder)
  {
    horizontalBorder->Draw(xpos + verticalBorder->GetWidth(), ypos,
                           xpos + verticalBorder->GetWidth(), ypos,
                           width - 2 * verticalBorder->GetWidth(), horizontalBorder->GetHeight());
    horizontalBorder->Draw(xpos + verticalBorder->GetWidth(), ypos + height - horizontalBorder->GetHeight(),
                           xpos + verticalBorder->GetWidth(), ypos + height - horizontalBorder->GetHeight(),
                           width - 2 * verticalBorder->GetWidth(), horizontalBorder->GetHeight());
    verticalBorder->Draw(xpos, ypos,
                         xpos, ypos,
                         verticalBorder->GetWidth(), height);
    verticalBorder->Draw(xpos + width - verticalBorder->GetWidth(), ypos,
                         xpos + width - verticalBorder->GetWidth(), ypos,
                         verticalBorder->GetWidth(), height);
    xoff = verticalBorder->GetWidth();
    yoff = horizontalBorder->GetHeight();
  }
  Video *video = MediaToolkit::GetInstance()->GetVideo();
  video->FillRect(xpos + xoff, ypos + yoff, width - 2 * xoff, height - 2 * yoff, 168);
  ratingsLabel->Draw();
  conditionLabel->Draw();
  healthLabel->Draw();
  staminaLabel->Draw();
  speedLabel->Draw();
  strengthLabel->Draw();
  healthOfLabel->Draw();
  staminaOfLabel->Draw();
}
