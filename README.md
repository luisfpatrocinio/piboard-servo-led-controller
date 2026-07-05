# PIBoard ServoCtrl

Este projeto foi desenvolvido para a **PIBoard**, uma placa de desenvolvimento educacional. O objetivo é demonstrar o uso integrado de diversos componentes eletrônicos, como botões (com interrupção), LEDs, Servomotor e um Display OLED, tudo orquestrado de forma modular e não-bloqueante utilizando a linguagem C++ no ambiente Arduino.

## 🚀 Como Funciona?

O projeto funciona como uma **Máquina de Estados**. Ao pressionar o botão, o sistema avança (ou retrocede) entre 3 configurações diferentes. O sentido de navegação é invertido sempre que o sistema atinge os limites (0 ou 2), garantindo um ciclo contínuo de vai e vem (0 ➔ 1 ➔ 2 ➔ 1 ➔ 0).

- **Estado 0:** LED Verde Aceso | Servomotor em 0°
- **Estado 1:** LED Amarelo Aceso | Servomotor em 90°
- **Estado 2:** LED Vermelho Aceso | Servomotor em 180°

O **Display OLED** fornece um feedback visual instantâneo amigável:
- Informa qual LED está ativo no momento.
- Exibe setas grandes centralizadas (`>>>` ou `<<<`) indicando a direção para a qual a máquina de estados está indo.

## 🔌 Pinagem e Conexões

Abaixo está o mapeamento dos pinos utilizados pela estrutura da PIBoard:

| Componente | Pino Arduino | Observação |
| :--- | :--- | :--- |
| **Botão** | `D2` | Utiliza Interrupção Externa, garantindo que nenhum clique seja perdido. |
| **LED Verde** | `D4` | Saída Digital. |
| **LED Amarelo** | `D12` | Saída Digital. |
| **LED Vermelho** | `D13` | Saída Digital. |
| **Servomotor** | `D11` | Saída PWM para controle de ângulo (0° a 180°). |
| **Display OLED (SDA)** | `D7` | Linha de Dados do I2C por Software (Específico da PIBoard). |
| **Display OLED (SCL)** | `D8` | Linha de Clock do I2C por Software (Específico da PIBoard). |

## 🧠 Arquitetura e Conceitos Educacionais

O código foi projetado com forte foco em **Modularidade** e **Boas Práticas**, sendo excelente para estudos:

1. **Uso de Interrupções de Hardware:**
   A leitura do botão não fica "presa" sendo verificada em looping dentro do `loop()`. Ao invés disso, configuramos uma interrupção de hardware (`attachInterrupt`) no Pino 2. Assim que você aperta o botão, o processador pausa instantaneamente o que estiver fazendo para registrar a ação, tornando o sistema 100% responsivo e à prova de engasgos (já com a proteção anti-ruído mecânico, *debounce*, de 200ms).

2. **Modularização com Orientação a Objetos (C++):**
   A pesada e complexa lógica de controle do display OLED foi separada do código principal e encapsulada em uma classe própria, chamada `DisplayController` (arquivos `lcd.h` e `lcd.cpp`). Desse modo, o arquivo principal `main.cpp` ficou extremamente limpo e assemelha-se à linguagem falada: basta instanciar o objeto e chamar algo como `oled.showState()`. Você pode copiar esses dois arquivos e utilizá-los sem dificuldades em projetos futuros!

3. **I2C por Software (U8g2) e Otimização de RAM:**
   Como a PIBoard liga a tela em pinos digitais comuns (7 e 8, e não nos pinos de hardware A4/A5 do I2C nativo do Uno), foi necessário simular o protocolo I2C através da poderosa biblioteca `U8g2`. 
   Para evitar a "cintilação" (flicker) de a tela apagar e acender cada vez que o texto atualiza, utilizamos a técnica de *Full Buffer* (`U8G2_..._F_...`), que monta a nova imagem inteira na memória RAM e depois projeta na tela de uma vez só. 
   Para compensar o alto gasto de RAM desse buffer, todos os textos fixos utilizam a macro `F("Seu Texto")`, orientando o processador a armazená-los na memória Flash.

## 🛠️ Como Compilar e Enviar

Este projeto foi empacotado usando o **PlatformIO**. 
Certifique-se de que o seu arquivo `platformio.ini` contém as bibliotecas essenciais declaradas:
- `arduino-libraries/Servo`
- `olikraus/U8g2`

Tendo o ambiente configurado, basta plugar a sua PIBoard, abrir a pasta do projeto na sua IDE e dar o comando de **Upload**. As bibliotecas e compilação serão resolvidas automaticamente.

---
*Projeto educacional focado em boas práticas de sistemas embarcados.*
