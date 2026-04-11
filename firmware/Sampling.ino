/*
  Teensy 4.x ADC DMA example med PC-styret START/N blokke via USB-serial
  Kræver ADC_USE_DMA og ADC_USE_TIMER
*/

#include <ADC.h>
#if defined(ADC_USE_DMA) && defined(ADC_USE_TIMER)
#include <AnalogBufferDMA.h>
#include <DMAChannel.h>

// Pin-konfiguration
#ifdef ADC_DUAL_ADCS
  const int readPin_adc_0 = A0;
  const int readPin_adc_1 = A2;
#else
  const int readPin_adc_0 = A0;
  const int readPin_adc_1 = 26;
#endif

// Hvor mange samples per blok
const uint32_t buffer_size = 1500;
const float    Fs          = 15000.0f;  // samplingfrekvens i Hz
// DMA-bufferindstillinger
DMAMEM static volatile uint16_t __attribute__((aligned(32)))
  dma0_buf1[buffer_size], dma0_buf2[buffer_size];
AnalogBufferDMA abdma1(dma0_buf1, buffer_size,
                       dma0_buf2, buffer_size);

#ifdef ADC_DUAL_ADCS
DMAMEM static volatile uint16_t __attribute__((aligned(32)))
  dma1_buf1[buffer_size], dma1_buf2[buffer_size];
AnalogBufferDMA abdma2(dma1_buf1, buffer_size,
                       dma1_buf2, buffer_size);
#endif

// ADC-objekt
ADC *adc = new ADC();

// Styring af streaming
volatile int  blocksToStream  = 0;
volatile int  blocks0Streamed = 0;
volatile int  blocks1Streamed = 0;
volatile bool sampling        = false;
elapsedMillis idle_timer;

volatile uint32_t block_id_0 = 0;
#ifdef ADC_DUAL_ADCS
volatile uint32_t block_id_1 = 0;
#endif

// Forward declaration
void ProcessAnalogData(AnalogBufferDMA *pab, int8_t adc_num);

void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 5000);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(readPin_adc_0, INPUT_DISABLE);
#ifdef ADC_DUAL_ADCS
  pinMode(readPin_adc_1, INPUT_DISABLE);
#endif

  Serial.println("Teensy klar til START N / STOP-kommandoer");

  // Konfigurer ADC, men start ikke timer endnu
  adc->adc0->setAveraging(1);
  adc->adc0->setResolution(12);
#ifdef ADC_DUAL_ADCS
  adc->adc1->setAveraging(1);
  adc->adc1->setResolution(12);
#endif

  // Initialiser DMA
  abdma1.init(adc, ADC_0);
#ifdef ADC_DUAL_ADCS
  abdma2.init(adc, ADC_1);
#endif
   // Send sampling-parametre til PC
               // samme som du bruger i startTimer()
  //Serial.printf("FS=%.0f\n", Fs);
  //Serial.printf("BS=%u\n", buffer_size);
  idle_timer = 0;
}


void loop() {
  // 1) Håndter START N og STOP fra PC
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd.startsWith("START")) {
      int n = 1;
      if (cmd.length() > 6) {
        n = cmd.substring(6).toInt();
      }
      if (n > 0 && !sampling) {
        // Sæt op til streaming af n blokke pr. kanal
        blocksToStream   = n;
        blocks0Streamed  = 0;
        blocks1Streamed  = 0;
        sampling         = true;

        block_id_0 = 0;
      #ifdef ADC_DUAL_ADCS
        block_id_1 = 0;
      #endif

        // Ryd DMA-interrupts
        abdma1.clearInterrupt();
#ifdef ADC_DUAL_ADCS
        abdma2.clearInterrupt();
#endif

        // Start første blok på begge ADC’er
        adc->adc0->startSingleRead(readPin_adc_0);
        adc->adc0->startTimer(Fs);
#ifdef ADC_DUAL_ADCS
        adc->adc1->startSingleRead(readPin_adc_1);
        adc->adc1->startTimer(Fs);
#endif

        Serial.printf("START %d blokke pr. kanal\n", n);
      }
    }
    else if (cmd.equalsIgnoreCase("STOP") && sampling) {
      // Stop streaming øjeblikkeligt
      adc->adc0->stopTimer();
#ifdef ADC_DUAL_ADCS
      adc->adc1->stopTimer();
#endif
      sampling = false;
      Serial.println("STOP PET");
    }
  }

  // 2) Under sampling: håndter DMA-interrupts og blok–tællere
  if (sampling) {
    // ADC0
    if (abdma1.interrupted()) {
      ProcessAnalogData(&abdma1, 0);
      abdma1.clearInterrupt();
      blocks0Streamed++;
    }
    // ADC1 (hvis tilgængelig)
#ifdef ADC_DUAL_ADCS
    if (abdma2.interrupted()) {
      ProcessAnalogData(&abdma2, 1);
      abdma2.clearInterrupt();
      blocks1Streamed++;
    }
#endif

    // 3) Stop automatisk når begge kanaler har nået quota
    bool done0 = (blocks0Streamed >= blocksToStream);
#ifdef ADC_DUAL_ADCS
    bool done1 = (blocks1Streamed >= blocksToStream);
    if (done0 && done1) {
#else
    if (done0) {
#endif
      adc->adc0->stopTimer();
#ifdef ADC_DUAL_ADCS
      adc->adc1->stopTimer();
#endif
      sampling = false;
      Serial.println("FÆRDIG med alle blokke");
    }

    // Nulstil idle–timer ved aktivitet
    idle_timer = 0;
  }
  // 4) Heartbeat når inaktiv
  else if (idle_timer > 5000) {
    digitalWriteFast(LED_BUILTIN, HIGH);
    delay(100);
    digitalWriteFast(LED_BUILTIN, LOW);
    delay(100);
    idle_timer = 0;
  }
}



// --- Funktion, der sender én blok via USB-serial ---
void ProcessAnalogData(AnalogBufferDMA *pab, int8_t adc_num) {
  volatile uint16_t *buf = pab->bufferLastISRFilled();
  size_t count = pab->bufferCountLastISRFilled();

  if ((uint32_t)buf >= 0x20200000u) {
    arm_dcache_delete((void*)buf, count * sizeof(uint16_t));
  }

  uint32_t bid;
  if (adc_num == 0) {
    bid = block_id_0++;
  }
#ifdef ADC_DUAL_ADCS
  else {
    bid = block_id_1++;
  }
#else
  else {
    bid = 0;
  }
#endif

  uint8_t header[8] = {
    0x7E,
    (uint8_t)adc_num,
    (uint8_t)(count >> 8),
    (uint8_t)(count & 0xFF),
    (uint8_t)(bid >> 24),
    (uint8_t)(bid >> 16),
    (uint8_t)(bid >> 8),
    (uint8_t)(bid & 0xFF)
  };

  Serial.write(header, 8);
  Serial.write((uint8_t*)buf, count * sizeof(uint16_t));

  pab->clearInterrupt();
}

#else
void setup() {}
void loop() {}
#endif // ADC_USE_DMA & ADC_USE_TIMER

