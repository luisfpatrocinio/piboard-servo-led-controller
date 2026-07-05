#include "lcd.h"
#include <Arduino.h>
#include <U8g2lib.h>

// Configura o I2C por software: Clock no pino 8, Dados no pino 7
U8G2_SSD1306_128X64_NONAME_F_SW_I2C display(U8G2_R0, /* clock=*/8, /* data=*/7,
                                            /* reset=*/U8X8_PIN_NONE);

void initLCD() {
  Serial.println(F("Inicializando display OLED via Software I2C..."));

  display.begin();

  Serial.println(F("Display OLED inicializado com sucesso."));
}

void showInitialMessage() {
  display.clearBuffer();                 // Limpa a memória interna do display
  display.setFont(u8g2_font_ncenB08_tr); // Define uma fonte bonita e legível

  display.drawStr(0, 15, "Patrocinio"); // X=0, Y=15
  display.drawStr(0, 30, "Testando OLED");

  display.sendBuffer(); // Envia da memória para a tela

  delay(2000);

  display.clearBuffer();
  display.sendBuffer();
}

void showButtonState(bool state) {
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB08_tr);

  if (state == LOW) {
    display.drawStr(0, 15, "Botao: Apertado");
  } else {
    display.drawStr(0, 15, "Botao: Solto");
  }

  display.sendBuffer();
}