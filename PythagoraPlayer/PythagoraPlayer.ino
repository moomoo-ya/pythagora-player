/*
 * PythagoraPlayer
 */

#define TONE3_A  220  // A3
#define TONE3_B  247  // B3
#define TONE4_C  262  // C4
#define TONE4_CS 277  // C4#
#define TONE4_D  294  // D4
#define TONE4_E  330  // E4
#define TONE4_F  349  // F4
#define TONE4_FS 370  // F4#
#define TONE4_G  392  // G4
#define TONE4_A  440  // A4
#define TONE4_B  494  // B4
#define TONE5_C  523  // C5

int score[] = {
  TONE4_D, TONE4_E, TONE4_D, TONE4_E, TONE4_G, TONE4_FS,TONE4_D, TONE4_E,
  TONE4_D, TONE4_E, TONE4_D, TONE4_E, TONE5_C, TONE4_B, TONE4_G, TONE4_A,
  TONE4_D, TONE4_E, TONE4_D, TONE4_E, TONE4_G, TONE4_FS,TONE4_D, TONE4_E,
  TONE3_B, TONE3_A, TONE3_B, TONE4_C, TONE4_CS,TONE4_D, TONE4_D,
  TONE4_D, TONE4_E, TONE4_D, TONE4_E, TONE4_G, TONE4_FS,TONE4_D, TONE4_E,
  TONE4_D, TONE4_E, TONE4_D, TONE4_E, TONE5_C, TONE4_B, TONE4_G, TONE4_A,
  TONE4_D, TONE4_E, TONE4_D, TONE4_E, TONE4_G, TONE4_FS,TONE4_D, TONE4_E,
  TONE3_B, TONE3_A,
  TONE4_E, TONE4_E, TONE4_FS,TONE4_E, TONE4_FS,TONE4_G, TONE4_D, TONE3_B,
  TONE4_C, TONE4_C, TONE4_D, TONE4_C, TONE4_D, TONE3_B,
  TONE4_D, TONE4_E, TONE4_D, TONE4_E, TONE4_G, TONE4_FS,TONE4_D, TONE4_E,
  TONE4_D, TONE4_E, TONE4_D, TONE4_E, TONE4_G, TONE4_FS,TONE4_D, TONE4_E,
  TONE4_D, TONE4_E, TONE4_D, TONE4_E, TONE5_C, TONE4_B, TONE4_G,
  TONE4_D, TONE4_E, TONE4_D, TONE4_E, TONE5_C, TONE4_B, TONE4_G
};

#define SPEAKER_PIN 12
#define BUTTON_PIN   0

int scoreLength;
volatile int sequencer;
volatile bool beep;
volatile unsigned long time_prev, time_now;

void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);

  scoreLength = sizeof(score) / sizeof(int);
  sequencer = 0;
  beep = false;
  time_prev = 0;
  time_now = 0;

  attachInterrupt(BUTTON_PIN, pressButton, CHANGE);
}

void loop() {
  if (beep) {
    tone(SPEAKER_PIN, score[sequencer]);
  } else {
    noTone(SPEAKER_PIN);
  }
}

#define CHATALING_SPAN 20

void pressButton() {
  time_now = millis();
  if (time_now - time_prev > CHATALING_SPAN) {
    beep = !beep;
    if (!beep) {
      // OFF時 シーケンスインクリメント
      sequencer++;

      // シーケンスリセット
      if (sequencer >= scoreLength) {
        sequencer = 0;
      }
    }
  }
  time_prev = time_now;
}

