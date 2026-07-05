#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

/**
 * @class DisplayController
 * @brief Classe modular para controlar o display OLED do projeto PiBoard.
 */
class DisplayController {
public:
  // Inicializa o display OLED via I2C de Hardware
  void begin();

  // Exibe a tela de boas-vindas
  void showWelcomeMessage();

  // Atualiza o display com as informacoes requisitadas pelo usuario
  // Utiliza __FlashStringHelper* para suportar a macro F() na chamada e economizar RAM
  void showState(int direction, const __FlashStringHelper* ledName);
};

#endif // LCD_H
