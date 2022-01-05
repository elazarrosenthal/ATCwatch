/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Arduino.h"
#include "class.h"
#include "images.h"
#include "menu.h"
#include "display.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "heartrate.h"
#include "screen_style.h"
#include <lvgl.h>


class BootScreen : public Screen
{
  public:
    virtual void pre()
    {
      //set_gray_screen_style(&lv_font_roboto_28);
      set_gray_screen_style( &lv_font_montserrat_14);

      lv_obj_t *label = lv_label_create(lv_scr_act());
      lv_label_set_text(label, "Booting\n""ATCwatch");
 //     lv_label_set_align(label, LV_ALIGN_CENTER);
      lv_obj_align(label,  LV_ALIGN_CENTER, 0, -60);

      lv_obj_t * img1 = lv_img_create(lv_scr_act());
      lv_img_set_src(img1, &Iimage2);
      lv_obj_align(img1,  LV_ALIGN_CENTER, 0, 20);
    }

    virtual void main()
    {

    }

  private:
};

BootScreen bootScreen;
