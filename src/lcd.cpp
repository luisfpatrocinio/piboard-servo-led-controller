#include "lcd.h"
#include <U8g2lib.h>

// A PIBoard utiliza os pinos 7 e 8 para comunicar com a tela, necessitando do I2C por Software.
// A classe "F" aloca 1024 bytes de RAM para um buffer oculto, evitando a cintilação (flicker).
U8G2_SSD1306_128X64_NONAME_F_SW_I2C display(U8G2_R0, /* clock=*/8, /* data=*/7, /* reset=*/U8X8_PIN_NONE);

void DisplayController::begin() {
  Serial.println(F("Inicializando display OLED via U8g2 (Software I2C)..."));
  
  display.begin();
  
  Serial.println(F("Display OLED inicializado com sucesso."));
}

void DisplayController::showWelcomeMessage() {
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB08_tr);
  
  const char* title = "PiBoard V2";
  int textWidth = display.getStrWidth(title);
  
  // A biblioteca U8g2 desenha usando a base da letra (baseline), então o Y deve ser maior que 0.
  display.setCursor((128 - textWidth) / 2, 25);
  display.print(title);
  
  const char* subtitle = "Iniciando...";
  textWidth = display.getStrWidth(subtitle);
  display.setCursor((128 - textWidth) / 2, 45);
  display.print(subtitle);
  
  display.sendBuffer();
  
  delay(2000); // É seguro usar delay() aqui pois é apenas na inicialização (setup)
  
  display.clearBuffer();
  display.sendBuffer();
}

void DisplayController::showState(int direction, const __FlashStringHelper* ledName) {
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB08_tr);

  // -- 1. Header Centralizado --
  const char* headerText = "PiBoard V2";
  int textWidth = display.getStrWidth(headerText);
  display.setCursor((128 - textWidth) / 2, 12); 
  display.print(headerText);
  display.drawHLine(0, 15, 128); // Linha separadora

  // -- 2. Informacoes Dinâmicas do Hardware --
  display.setCursor(0, 35);
  display.print(F("LED ativo: "));
  display.print(ledName);
  
  // -- 3. Direção (Setas Centralizadas) --
  display.setFont(u8g2_font_ncenB14_tr); // Aumenta a fonte para destacar a direção
  const char* dirStr = (direction == 1) ? ">>>" : "<<<";
  int dirWidth = display.getStrWidth(dirStr);
  display.setCursor((128 - dirWidth) / 2, 60);
  display.print(dirStr);

  // -- 4. Renderiza na tela via Full Buffer --
  display.sendBuffer();
}