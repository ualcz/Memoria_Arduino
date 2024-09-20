#define NOTE_B0 31

#define NOTE_C1 33

#define NOTE_CS1 35

#define NOTE_D1 37

#define NOTE_DS1 39

#define NOTE_E1 41

#define NOTE_F1 44

#define NOTE_FS1 46

#define NOTE_G1 49

#define NOTE_GS1 52

#define NOTE_A1 55

#define NOTE_AS1 58

#define NOTE_B1 62

#define NOTE_C2 65

#define NOTE_CS2 69

#define NOTE_D2 73

#define NOTE_DS2 78

#define NOTE_E2 82

#define NOTE_F2 87

#define NOTE_FS2 93

#define NOTE_G2 98

#define NOTE_GS2 104

#define NOTE_A2 110

#define NOTE_AS2 117

#define NOTE_B2 123

#define NOTE_C3 131

#define NOTE_CS3 139

#define NOTE_D3 147

#define NOTE_DS3 156

#define NOTE_E3 165

#define NOTE_F3 175

#define NOTE_FS3 185

#define NOTE_G3 196

#define NOTE_GS3 208

#define NOTE_A3 220

#define NOTE_AS3 233

#define NOTE_B3 247

#define NOTE_C4 262

#define NOTE_CS4 277

#define NOTE_D4 294

#define NOTE_DS4 311

#define NOTE_E4 330

#define NOTE_F4 349

#define NOTE_FS4 370

#define NOTE_G4 392

#define NOTE_GS4 415

#define NOTE_A4 440

#define NOTE_AS4 466

#define NOTE_B4 494

#define NOTE_C5 523

#define NOTE_CS5 554

#define NOTE_D5 587

#define NOTE_DS5 622

#define NOTE_E5 659

#define NOTE_F5 698

#define NOTE_FS5 740

#define NOTE_G5 784

#define NOTE_GS5 831

#define NOTE_A5 880

#define NOTE_AS5 932

#define NOTE_B5 988

#define NOTE_C6 1047

#define NOTE_CS6 1109

#define NOTE_D6 1175

#define NOTE_DS6 1245

#define NOTE_E6 1319

#define NOTE_F6 1397

#define NOTE_FS6 1480

#define NOTE_G6 1568

#define NOTE_GS6 1661

#define NOTE_A6 1760

#define NOTE_AS6 1865

#define NOTE_B6 1976

#define NOTE_C7 2093

#define NOTE_CS7 2217

#define NOTE_D7 2349

#define NOTE_DS7 2489

#define NOTE_E7 2637

#define NOTE_F7 2794

#define NOTE_FS7 2960

#define NOTE_G7 3136

#define NOTE_GS7 3322

#define NOTE_A7 3520

#define NOTE_AS7 3729

#define NOTE_B7 3951

#define NOTE_C8 4186

#define NOTE_CS8 4435

#define NOTE_D8 4699

#define NOTE_DS8 4978


// Definições de Cores
#define CHOICE_OFF 0 
#define CHOICE_NONE 0
#define CHOICE_RED (1 << 0)
#define CHOICE_GREEN (1 << 1)
#define CHOICE_BLUE (1 << 2)
#define CHOICE_YELLOW (1 << 3)

// Definições de LEDs e Botões
const int leds[] = {5, 1, 3, 7}; // RED, GREEN, BLUE, YELLOW
const int buttons[] = {6, 2, 4, 8}; // RED, GREEN, BLUE, YELLOW

// Definições de Buzzer
#define BUZZER1 10
#define BUZZER2 11

// Parâmetros do jogo
#define ROUNDS_TO_WIN 3
#define ENTRY_TIME_LIMIT 3000
#define MODE_MEMORY 0

// Variáveis de estado do jogo
byte gameMode = MODE_MEMORY;
byte gameBoard[32];
byte gameRound = 0;

void setup() {
  for (int i = 0; i < 4; i++) {

    pinMode(buttons[i], INPUT_PULLUP);

    pinMode(leds[i], OUTPUT);
  }
  
  pinMode(BUZZER1, OUTPUT);

  pinMode(BUZZER2, OUTPUT);

  gameMode = MODE_MEMORY;
}

void loop() {

  attractMode();

  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW);

  delay(1000);

  setLEDs(CHOICE_OFF);

  delay(250);

  if (gameMode == MODE_MEMORY) {
    if (play_memory()) 
      play_winner();
    else 
      play_loser();
  }
}

boolean play_memory() {
  randomSeed(millis());
  gameRound = 0;
  
  while (gameRound < ROUNDS_TO_WIN) {
    add_to_moves();
    playMoves();

    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++) {
      byte choice = wait_for_button();
      if (choice == CHOICE_NONE || choice != gameBoard[currentMove]) return false;
    }
    delay(1000);
  }
  return true;
}

void add_to_moves() {
  byte newButton = random(0, 4);
  gameBoard[gameRound++] = (1 << newButton);
}

void playMoves() {
  for (byte currentMove = 0; currentMove < gameRound; currentMove++) {
    byte ledToLight = gameBoard[currentMove];
    toner(ledToLight, 150);
    delay(150);
    setLEDs(CHOICE_OFF);
    delay(150);
  }
}

void setLEDs(byte ledMask) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], (ledMask & (1 << i)) ? HIGH : LOW);
  }
}

byte wait_for_button() {
  long startTime = millis();

  while ((millis() - startTime) < ENTRY_TIME_LIMIT) {
    byte button = checkButton();
    if (button != CHOICE_NONE) {
      toner(button, 150);
      while (checkButton() != CHOICE_NONE);
      delay(10);
      return button;
    }
  }
  return CHOICE_NONE;
}

byte checkButton() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttons[i]) == LOW) return (1 << i);
  }
  return CHOICE_NONE;
}

void toner(byte which, int buzz_length_ms) {
  setLEDs(which);
  buzz_sound(buzz_length_ms, 1136 / (which ? which : 1));
  setLEDs(CHOICE_OFF);
}

void buzz_sound(int buzz_length_ms, int buzz_delay_us) {
  long buzz_length_us = buzz_length_ms * 1000L;
  while (buzz_length_us > (buzz_delay_us * 2)) {
    buzz_length_us -= buzz_delay_us * 2;
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(buzz_delay_us);
    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(buzz_delay_us);
  }
}

void play_winner() {
  for (int i = 0; i < 4; i++) {
    setLEDs(i % 2 == 0 ? CHOICE_GREEN | CHOICE_BLUE : CHOICE_RED | CHOICE_YELLOW);
    play_bluebird_chorus();
  }
}

void play_victory_melody() {
  int victoryMelody[] = {NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_G5, NOTE_C6};
  int noteDurations[] = {4, 4, 4, 4, 4, 4, 4, 4, 2};

  for (int i = 0; i < sizeof(victoryMelody) / sizeof(victoryMelody[0]); i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(BUZZER2, victoryMelody[i], noteDuration);
    delay(noteDuration + 50);
    noTone(BUZZER2);
  }
}

void play_bluebird_chorus() {
  int melody[] = {NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_G5};
  int noteDurations[] = {4, 4, 4, 4, 4, 2}; // Duração das notas (baseado na fração da batida)

  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(BUZZER2, melody[i], noteDuration);
    delay(noteDuration + 50);
    noTone(BUZZER2);
  }
}

void play_loser() {
  for (int i = 0; i < 4; i++) {
    setLEDs(i % 2 == 0 ? CHOICE_RED | CHOICE_GREEN : CHOICE_BLUE | CHOICE_YELLOW);
    buzz_sound(255, 1500);
  }
}

void attractMode() {
  byte colors[] = {CHOICE_RED, CHOICE_BLUE, CHOICE_GREEN, CHOICE_YELLOW};

  while (true) {
    for (int i = 0; i < 4; i++) {
      setLEDs(colors[i]);
      delay(100);
      if (checkButton() != CHOICE_NONE) return;
    }
  }
}
