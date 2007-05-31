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

#include "EquipmentWidget.h"
#include "Exception.h"
#include "ObjectResource.h"
#include "WidgetFactory.h"

EquipmentWidget::EquipmentWidget(const Rectangle &r, PlayerCharacter *pc, ImageResource& img, Font *f)
: ContainerWidget(r)
, Observer()
, character(pc)
, images(img)
, font(f)
{
  character->Attach(this);
  character->GetInventory()->Attach(this);
  Update();
}

EquipmentWidget::~EquipmentWidget()
{
  character->GetInventory()->Detach(this);
  character->Detach(this);
}

void
EquipmentWidget::Update()
{
  Clear();
  WidgetFactory wf;
  for (unsigned int i = 0; i < character->GetInventory()->GetSize(); i++) {
    InventoryItem *item = character->GetInventory()->GetItem(i);
    if ((item->IsEquiped())) {
      Image *image = images.GetImage(item->GetId());
      int width;
      int height;
      int yoffset;
      ObjectInfo objInfo = ObjectResource::GetInstance()->GetObjectInfo(item->GetId());
      switch (objInfo.imageSize) {
        case 1:
          width = MAX_INVENTORY_ITEM_WIDGET_WIDTH / 2;
          height = MAX_INVENTORY_ITEM_WIDGET_HEIGHT / 2;
          break;
        case 2:
          width = MAX_INVENTORY_ITEM_WIDGET_WIDTH;
          height = MAX_INVENTORY_ITEM_WIDGET_HEIGHT / 2;
          break;
        case 4:
          width = MAX_INVENTORY_ITEM_WIDGET_WIDTH;
          height = MAX_INVENTORY_ITEM_WIDGET_HEIGHT;
          break;
        default:
          throw UnexpectedValue(__FILE__, __LINE__, objInfo.imageSize);
          break;
      }
      switch (objInfo.type) {
        case OT_SWORD:
          yoffset = 0;
          break;
        case OT_CROSSBOW:
          yoffset = 30;
          break;
        case OT_STAFF:
          yoffset = 0;
          break;
        case OT_ARMOR:
          yoffset = 60;
          break;
        default:
          throw UnexpectedValue(__FILE__, __LINE__, objInfo.type);
          break;
      }
      InventoryItemWidget *invitem = wf.CreateInventoryItem(Rectangle(rect.GetXPos() + 1, rect.GetYPos() + yoffset + 1, width, height),
                                                            INVENTORY_OFFSET + i, image, item->ToString(), font);
      AddActiveWidget(invitem);
    }
  }
  SetVisible(character->IsSelected());
}
