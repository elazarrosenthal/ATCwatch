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


class SettingsTimeScreen : public Screen
{
  struct rollers_s {lv_obj_t *roller, *roller1;};

  public:
    virtual void pre()
    {
      set_swipe_enabled(true);

      label_screen = lv_label_create(lv_scr_act());
      lv_label_set_text(label_screen, "Set Time");
      lv_obj_align(label_screen, LV_ALIGN_TOP_LEFT, 0, 0);

      label_points = lv_label_create(lv_scr_act());
      lv_label_set_text(label_points, ":");
      lv_obj_align(label_points, LV_ALIGN_CENTER, 0, -15);

      btn1 = lv_btn_create(lv_scr_act());
      lv_obj_add_event_cb(btn1, event_handler_btn1, LV_EVENT_ALL, NULL);
      lv_obj_align(btn1, LV_ALIGN_BOTTOM_MID, -55, 0);
     // lv_btn_set_fit2(btn1, LV_FIT_NONE, LV_FIT_TIGHT);
      btn1_label = lv_label_create(btn1);
      lv_label_set_text(btn1_label, "Abort");

      btn2 = lv_btn_create(lv_scr_act());
      lv_obj_add_event_cb(btn2, event_handler_btn2, LV_EVENT_ALL, &rollers);
     // lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);
      lv_obj_align(btn2, LV_ALIGN_BOTTOM_MID, 55, 0);
      btn2_label = lv_label_create(btn2);
      lv_label_set_text(btn2_label, "Save");

      rollers.roller1 = lv_roller_create(lv_scr_act());
      lv_roller_set_options(rollers.roller1,
                            "00\n"
                            "01\n"
                            "02\n"
                            "03\n"
                            "04\n"
                            "05\n"
                            "06\n"
                            "07\n"
                            "08\n"
                            "09\n"
                            "10\n"
                            "11\n"
                            "12\n"
                            "13\n"
                            "14\n"
                            "15\n"
                            "16\n"
                            "17\n"
                            "18\n"
                            "19\n"
                            "20\n"
                            "21\n"
                            "22\n"
                            "23\n"
                            "24\n"
                            "25\n"
                            "26\n"
                            "27\n"
                            "28\n"
                            "29\n"
                            "30\n"
                            "31\n"
                            "32\n"
                            "33\n"
                            "34\n"
                            "35\n"
                            "36\n"
                            "37\n"
                            "38\n"
                            "39\n"
                            "40\n"
                            "41\n"
                            "42\n"
                            "43\n"
                            "44\n"
                            "45\n"
                            "46\n"
                            "47\n"
                            "48\n"
                            "49\n"
                            "50\n"
                            "51\n"
                            "52\n"
                            "53\n"
                            "54\n"
                            "55\n"
                            "56\n"
                            "57\n"
                            "58\n"
                            "59",
                            LV_ROLLER_MODE_INFINITE);

      lv_roller_set_visible_row_count(rollers.roller1, 4);
      lv_obj_align(rollers.roller1, LV_ALIGN_CENTER, 30, -15);

      rollers.roller = lv_roller_create(lv_scr_act());
      lv_roller_set_options(rollers.roller,
                            "00\n"
                            "01\n"
                            "02\n"
                            "03\n"
                            "04\n"
                            "05\n"
                            "06\n"
                            "07\n"
                            "08\n"
                            "09\n"
                            "10\n"
                            "11\n"
                            "12\n"
                            "13\n"
                            "14\n"
                            "15\n"
                            "16\n"
                            "17\n"
                            "18\n"
                            "19\n"
                            "20\n"
                            "21\n"
                            "22\n"
                            "23",
                            LV_ROLLER_MODE_INFINITE);

      lv_roller_set_visible_row_count(rollers.roller, 4);
      lv_obj_align(rollers.roller, LV_ALIGN_CENTER, -30, -15);

      time_data_struct time_data = get_time();
      lv_roller_set_selected(rollers.roller, time_data.hr, LV_ANIM_OFF);
      lv_roller_set_selected(rollers.roller1, time_data.min, LV_ANIM_OFF);
    }

    static void event_handler_btn1(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);

        if(code == LV_EVENT_SHORT_CLICKED) {
           set_last_menu();
        }
    }

    static void event_handler_btn2(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);

        struct rollers_s * rs = (struct rollers_s *) lv_event_get_user_data(e);

        if(code == LV_EVENT_SHORT_CLICKED) {
          int roller_hours = lv_roller_get_selected(rs->roller);
          int roller_minutes = lv_roller_get_selected(rs->roller1);
          SetTime(roller_hours, roller_minutes);
          set_last_menu();
          set_motor_ms(35);        
        }
    }

    // virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    // {
    //   if (object == btn1 && event == LV_EVENT_SHORT_CLICKED) {
    //     set_last_menu();
    //   } else if (object == btn2 && event == LV_EVENT_SHORT_CLICKED) {
    //     int roller_hours = lv_roller_get_selected(roller);
    //     int roller_minutes = lv_roller_get_selected(roller1);
    //     SetTime(roller_hours, roller_minutes);
    //     set_last_menu();
    //     set_motor_ms(35);
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
    lv_obj_t *label_screen;
    lv_obj_t *btn1, *btn2, *btn1_label, *btn2_label, *label_points;
    // lv_obj_t *roller, *roller1;
    struct rollers_s  rollers;
};

SettingsTimeScreen settingsTimeScreen;
