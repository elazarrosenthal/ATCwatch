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


class LogScreen : public Screen
{
  public:
    virtual void pre()
    {
      label_screen = lv_label_create(lv_scr_act());
      lv_label_set_text(label_screen, "Logging");
      lv_obj_align(label_screen, LV_ALIGN_TOP_LEFT, 0, 0);

      label_log = lv_label_create(lv_scr_act());
      lv_label_set_text(label_log, "Click on a button to test Logging");
      lv_obj_align(label_log, LV_ALIGN_CENTER, 0, -30);

      btn1 = lv_btn_create(lv_scr_act());
      lv_obj_add_event_cb(btn1, event_handler_btn1,LV_EVENT_ALL, this);
      lv_obj_align(btn1, LV_ALIGN_CENTER, -55, 50);
      btn1_label = lv_label_create(btn1);
      lv_label_set_text(btn1_label, "Millis");

      btn2 = lv_btn_create(lv_scr_act());
      lv_obj_add_event_cb(btn2, event_handler_btn2,LV_EVENT_ALL,this);
      lv_obj_align(btn2, LV_ALIGN_CENTER, 55, 50);
      btn2_label = lv_label_create(btn2);
      lv_label_set_text(btn2_label, "Battery");

    }

    virtual void main()
    {
    }

    virtual void up()
    {
    }

    virtual void down()
    {
    }

    virtual void right()
    {
      display_home();
    }

    static void event_handler_btn1(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);

        struct LogScreen * p = (LogScreen *) lv_event_get_user_data(e);

        if(code == LV_EVENT_SHORT_CLICKED) {
           int msg = millis();
           ble_write("AT+LOG:" + String(msg));
           lv_label_set_text_fmt(p->label_log, "Log: %i", msg);
           lv_obj_align(p->label_log,  LV_ALIGN_CENTER, 0, -30);
        }
    }


    static void event_handler_btn2(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);
        struct LogScreen * p = (LogScreen *) lv_event_get_user_data(e);


        if(code == LV_EVENT_SHORT_CLICKED) {
              int msg = get_battery_percent();
        ble_write("AT+LOG:" + String(msg));
        lv_label_set_text_fmt(p->label_log, "Log: %i", msg);
        lv_obj_align(p->label_log, LV_ALIGN_CENTER, 0, -30);
        }
    }


    // virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    // {
    //   if (object == btn1 && event.code
    //    == LV_EVENT_SHORT_CLICKED) {
    //     int msg = millis();
    //     ble_write("AT+LOG:" + String(msg));
    //     lv_label_set_text_fmt(label_log, "Log: %i", msg);
    //     lv_obj_align(label_log, NULL, LV_ALIGN_CENTER, 0, -30);
    //   } else if (object == btn2 && event.code == LV_EVENT_SHORT_CLICKED) {
    //     int msg = get_battery_percent();
    //     ble_write("AT+LOG:" + String(msg));
    //     lv_label_set_text_fmt(label_log, "Log: %i", msg);
    //     lv_obj_align(label_log, NULL, LV_ALIGN_CENTER, 0, -30);
    //   }
    // }

  private:
    lv_obj_t *label_screen, *label_log;
    lv_obj_t *btn1, *btn2, *btn1_label, *btn2_label;
};

LogScreen logScreen;
