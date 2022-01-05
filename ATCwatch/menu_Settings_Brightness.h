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


class SettingsBrightnessScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_swipe_enabled(true);

      backlight_brightness = get_backlight();

      label_screen = lv_label_create(lv_scr_act());
      lv_label_set_text(label_screen, "Set Brightness");
      lv_obj_align(label_screen, LV_ALIGN_TOP_LEFT, 0, 0);

      btn1 = lv_btn_create(lv_scr_act());
      lv_obj_add_event_cb(btn1, event_handler_btn1, LV_EVENT_ALL, this);
      lv_obj_align(btn1, LV_ALIGN_BOTTOM_MID, -55, 0);
      //lv_btn_set_fit2(btn1, LV_FIT_NONE, LV_FIT_TIGHT);
      btn1_label = lv_label_create(btn1);
      lv_label_set_text(btn1_label, "Abort");

      btn2 = lv_btn_create(lv_scr_act());
      lv_obj_add_event_cb(btn2, event_handler_btn2, LV_EVENT_ALL, this);
      //lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);
      lv_obj_align(btn2, LV_ALIGN_BOTTOM_MID, 55, 0);
      btn2_label = lv_label_create(btn2);
      lv_label_set_text(btn2_label, "Save");

      slider = lv_slider_create(lv_scr_act());
      lv_slider_set_range(slider, 1, 7);
      lv_obj_add_event_cb(slider, event_handler_slider,LV_EVENT_ALL, this);
      lv_obj_align(slider, LV_ALIGN_CENTER, 0, -10);
      lv_slider_set_value(slider, get_backlight(), LV_ANIM_OFF);

      slider_label = lv_label_create(lv_scr_act());
      lv_label_set_text_fmt(slider_label, "%u", lv_slider_get_value(slider));
      //lv_obj_set_auto_realign(slider_label, true);
      lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    }

    static void event_handler_btn1(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);
        SettingsBrightnessScreen * p = (SettingsBrightnessScreen *) lv_event_get_user_data(e);

        if(code == LV_EVENT_SHORT_CLICKED) {
           set_backlight(p->backlight_brightness);
           set_last_menu();
        }
    }

    static void event_handler_btn2(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);

        SettingsBrightnessScreen * p = (SettingsBrightnessScreen *) lv_event_get_user_data(e);

        if(code == LV_EVENT_SHORT_CLICKED) {
           set_last_menu();
           set_motor_ms(35);       
        }
    }

    static void event_handler_slider(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);

        SettingsBrightnessScreen * p = (SettingsBrightnessScreen *) lv_event_get_user_data(e);

        if(code == LV_EVENT_VALUE_CHANGED) {
            int slider_backlight = lv_slider_get_value(p->slider);
            lv_label_set_text_fmt(p->slider_label, "%u", slider_backlight);
            set_backlight(slider_backlight);     
        }
    }



    // virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    // {
    //   if (object == btn1 && event == LV_EVENT_SHORT_CLICKED) {
    //     set_backlight(backlight_brightness);
    //     set_last_menu();
    //   } else if (object == btn2 && event == LV_EVENT_SHORT_CLICKED) {
    //     set_last_menu();
    //     set_motor_ms(35);
    //   } else if (object == slider && event == LV_EVENT_VALUE_CHANGED) {
    //     int slider_backlight = lv_slider_get_value(slider);
    //     lv_label_set_text_fmt(slider_label, "%u", slider_backlight);
    //     set_backlight(slider_backlight);
    //   }
    // }

    virtual void up()
    {
    }

    virtual void down()
    {
    }

    virtual void right()
    {
    }

    virtual void left()
    {
    }

  private:
    int backlight_brightness;
    lv_obj_t *label_screen;
    lv_obj_t *btn1, *btn2, *btn1_label, *btn2_label, *label_points;
    lv_obj_t *slider, *slider_label;
};

SettingsBrightnessScreen settingsBrightnessScreen;
