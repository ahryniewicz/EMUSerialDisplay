#include "display.hpp"
#include <TFT_eSPI.h>
#include "FreeSerif8pt7b.h"

int brightnes = 200;
uint16_t ft_color = TFT_WHITE;
uint16_t bg_color = TFT_BLACK;
uint16_t ln_color = TFT_LIGHTGREY;
uint16_t warning_color = TFT_ORANGE;
uint16_t error_color = TFT_RED;

display_t displayUp = {0};
display_t displayDown = {0};
display_t display[3] = {
  {0, 90, 79, 60},
  {80, 90, 79, 60},
  {160, 90, 79, 60},
};

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite img = TFT_eSprite(&tft);

void drawLines(void)
{
  img.drawLine(0,89,240,89,ln_color);
  img.drawLine(0,150,240,150,ln_color);
  img.drawLine(79,89,79,150,ln_color);
  img.drawLine(159,89,159,150,ln_color);
}

void displayUp_update()
{
  uint16_t w, h;
  img.setTextColor(ft_color);
  img.setFreeFont(&FreeSerifBold24pt7b);
  w=img.textWidth(*displayUp.p_info->p_value);
  h=img.fontHeight();
  img.setCursor(150-w, 80);
  img.println(*displayUp.p_info->p_value);

  img.setTextColor(ln_color);
  img.setFreeFont(&FreeSerif8pt7b);
  w=img.textWidth(displayUp.p_info->label);
  h=img.fontHeight();
  img.setCursor(120-(w/2), 40);
  img.println(displayUp.p_info->label);
  
  int map = displayUp.p_info->p_value->toInt();
  int arc_add = ((map*100)/200);
  if (arc_add < 0)
    arc_add = 0;
  if (arc_add > 100)
    arc_add = 100;
  img.drawSmoothArc(120, 120, 115, 125, 129, 130+arc_add, ln_color, bg_color);

  img.drawSmoothArc(120, 120, 108, 120, 129, 131, ft_color, bg_color);
  for (uint8_t i=0; i<100; i+=10) {
    img.drawSmoothArc(120, 120, 108, 120, 140+i, 141+i, ft_color, bg_color);  
  }
  img.drawSmoothArc(120, 120, 108, 120, 229, 231, ft_color, bg_color);

  img.drawSmoothArc(120, 120, 115, 125, 128+arc_add, 132+arc_add, TFT_RED, bg_color);
}

void displayDown_update()
{
  uint16_t w, h;
  img.setTextColor(ft_color);
  img.setFreeFont(&FreeSerifBold24pt7b);
  w=img.textWidth(*displayDown.p_info->p_value);
  h=img.fontHeight();
  img.setCursor(152-w, 158+h/2+4);
  img.println(*displayDown.p_info->p_value);

  img.setTextColor(ln_color);
  img.setFreeFont(&FreeSerif8pt7b);
  w=img.textWidth(displayDown.p_info->label);
  h=img.fontHeight();
  img.setCursor(120-(w/2), 200+h/2+2);
  img.println(displayDown.p_info->label);
  
  float afr = displayDown.p_info->p_value->toFloat();
  int arc_add = (((afr*10)-100)*100/100);
  if (arc_add < 0)
    arc_add = 0;
  if (arc_add > 100)
    arc_add = 100;
  img.drawArc(120, 120, 115, 125, (309+(100-arc_add))%360, 49, ln_color, bg_color);
  
  img.drawSmoothArc(120, 120, 108, 120, 309, 311, ft_color, bg_color);
  for (uint8_t i=0; i<100; i+=10) {
    img.drawSmoothArc(120, 120, 108, 120, (320+i)%360, (321+i)%360, ft_color, bg_color);  
  }
  img.drawSmoothArc(120, 120, 108, 120, 49, 51, ft_color, bg_color);

  img.drawArc(120, 120, 115, 125, (308+(100-arc_add))%360, (312+(100-arc_add))%360, TFT_RED, bg_color);
}

void display_update(display_t *p_display)
{
  uint16_t w, h;
  uint16_t label_color = ln_color;
  uint16_t value_color = ft_color;
  uint16_t background_color = bg_color;

  if (p_display->p_info->warning) {
    label_color = bg_color;
    value_color = bg_color;
    background_color = warning_color;
  }
  if (p_display->p_info->error) {
    label_color = bg_color;
    value_color = bg_color;
    background_color = error_color;
  }

  if (p_display->p_info->error || p_display->p_info->warning) {
    img.fillRect(p_display->x, p_display->y, p_display->w, p_display->h, background_color);  
  }

  img.setTextColor(label_color);
  img.setFreeFont(&FreeSerif8pt7b);
  w=img.textWidth(p_display->p_info->label);
  h=img.fontHeight();
  img.setCursor(p_display->x+5, p_display->y+h/2+7);
  img.println(p_display->p_info->label);

  img.setTextColor(value_color);
  img.setFreeFont(&FreeSerifBold18pt7b);
  w=img.textWidth(*(p_display->p_info->p_value));
  h=img.fontHeight();
  img.setCursor(p_display->x+p_display->w-10-w, p_display->y+p_display->h-10);
  img.println(*(p_display->p_info->p_value));
}


void display_init(void) {
  /* Display init */
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  img.createSprite(239,239);

  pinMode(TFT_BL, OUTPUT);
  ledcAttachPin(TFT_BL, 0);
  ledcSetup(0, 1000, 8);
}

int last_enc_val = 0;
void update_brightnes(int enc_val) {
  int enc_diff = enc_val - last_enc_val;
  last_enc_val = enc_val;  
  brightnes += enc_diff*10;
  if (brightnes > 250)
    brightnes = 250;
  if (brightnes < 0)
    brightnes = 0;

  ledcWrite(0, brightnes);
}

void update_display(int enc_val, boolean pb_pressed)
{
  update_brightnes (enc_val);
  img.fillScreen(bg_color);

  drawLines();
  displayUp_update();
  displayDown_update();
  display_update(&display[0]);
  display_update(&display[1]);
  display_update(&display[2]);

  img.pushSprite(0,0);
}