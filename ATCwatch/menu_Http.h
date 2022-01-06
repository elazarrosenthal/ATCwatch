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


class HttpScreen : public Screen
{
  public:
    virtual void pre()
    {
      label_screen = lv_label_create(lv_scr_act());
      lv_label_set_text(label_screen, "HTTP Demo");
      lv_obj_align(label_screen, LV_ALIGN_TOP_LEFT, 0, 0);

      label_http_req = lv_label_create(lv_scr_act());
      lv_label_set_text_fmt(label_http_req, "HTTP:%s", string2char(get_http_msg()));
      lv_obj_align(label_http_req, LV_ALIGN_CENTER, 0, -70);

      btn1 = lv_btn_create(lv_scr_act());
      lv_obj_add_event_cb(btn1, event_handler_btn1,LV_EVENT_ALL,NULL);
      lv_obj_align(btn1, LV_ALIGN_CENTER, -55, -10);
      btn1_label = lv_label_create(btn1);
      lv_label_set_text(btn1_label, "Millis");

      btn2 = lv_btn_create(lv_scr_act());
      lv_obj_add_event_cb(btn2, event_handler_btn2,LV_EVENT_ALL,NULL);
      lv_obj_align(btn2, LV_ALIGN_CENTER, 55, -10);
      btn2_label = lv_label_create(btn2);
      lv_label_set_text(btn2_label, "Test");

      label_garage = lv_label_create(lv_scr_act());
      lv_label_set_text(label_garage, "Garage");
      lv_obj_align(label_garage, LV_ALIGN_CENTER, 0, 35);

      btn3 = lv_btn_create(lv_scr_act());
      lv_obj_add_event_cb(btn3, event_handler_btn3,LV_EVENT_ALL,NULL);
      lv_obj_align(btn3, LV_ALIGN_CENTER, -55, 78);
      btn3_label = lv_label_create(btn3);
      lv_label_set_text(btn3_label, "Open");

      btn4 = lv_btn_create(lv_scr_act());
      lv_obj_add_event_cb(btn4, event_handler_btn4, LV_EVENT_ALL, NULL);
      lv_obj_align(btn4,  LV_ALIGN_CENTER, 55, 78);
      btn4_label = lv_label_create(btn4);
      lv_label_set_text(btn4_label, "Close");
    }

    virtual void main()
    {
      lv_label_set_text_fmt(label_http_req, "%s", string2char(get_http_msg()));
      lv_obj_align(label_http_req, LV_ALIGN_CENTER, 0, -70);
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

        if(code == LV_EVENT_SHORT_CLICKED) {
           ble_write("AT+HTTP:CMD" + String(millis()));
        }
    }

    static void event_handler_btn2(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);

        if(code == LV_EVENT_SHORT_CLICKED) {
                  ble_write("AT+HTTP:TEST");

        }
    }

        static void event_handler_btn3(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);

        if(code == LV_EVENT_SHORT_CLICKED) {
                  ble_write("AT+HTTP:OPEN");

        }
    }

        static void event_handler_btn4(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);

        if(code == LV_EVENT_SHORT_CLICKED) {
                  ble_write("AT+HTTP:CLOSE");

          

        }
    }
    // virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    // {
    //   if (object == btn1 && event == LV_EVENT_SHORT_CLICKED) {
    //     ble_write("AT+HTTP:CMD" + String(millis()));
    //   } else if (object == btn2 && event == LV_EVENT_SHORT_CLICKED) {
    //     ble_write("AT+HTTP:TEST");
    //   } else if (object == btn3 && event == LV_EVENT_SHORT_CLICKED) {
    //     ble_write("AT+HTTP:OPEN");
    //   } else if (object == btn4 && event == LV_EVENT_SHORT_CLICKED) {
    //     ble_write("AT+HTTP:CLOSE");
    //   }
    // }

  private:
    lv_obj_t *label_screen, *label_http_req, *label_garage;
    lv_obj_t *btn1, *btn2, *btn1_label, *btn2_label;
    lv_obj_t *btn3, *btn4, *btn3_label, *btn4_label;

    char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

HttpScreen httpScreen;
