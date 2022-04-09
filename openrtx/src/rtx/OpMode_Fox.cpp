#include <OpMode_Fox.h>
#include <core/state.h>
#include <dsp.h>
#include <interfaces/audio.h>
#include <interfaces/delays.h>
#include <interfaces/platform.h>
#include <interfaces/radio.h>
#include <rtx.h>

#include <memory>
#include <vector>

using namespace std;

OpMode_Fox::OpMode_Fox() {}

OpMode_Fox::~OpMode_Fox() {}

void OpMode_Fox::enable() { foxTx.init(state.settings.fox_string); }

void OpMode_Fox::disable() { foxTx.terminate(); }

void OpMode_Fox::update(rtxStatus_t *const status, const bool newCfg) {
  (void)newCfg;

  // TX logic
  if (platform_getPttStatus() && (status->txDisable == 0)) {
    // Enter Tx mode, setup transmission
    if (status->opStatus != TX) {
      audio_disableAmp();
      radio_disableRtx();
      radio_enableTx();
      foxTx.reset();
      status->opStatus = TX;
    } else {
      // Transmission is ongoing, just modulate
      foxTx.send();
    }
  }

  // PTT is off, transition to Rx state
  if (!platform_getPttStatus() && (status->opStatus == TX)) {
    radio_disableRtx();
    status->opStatus = OFF;
  }

  // Led control logic
  switch (status->opStatus) {
    case RX:
      // Unused TX only
      break;

    case TX:
      platform_ledOff(GREEN);
      platform_ledOn(RED);
      break;

    default:
      platform_ledOff(GREEN);
      platform_ledOff(RED);
      break;
  }

  // Sleep thread for 30ms for 33Hz update rate
  sleepFor(0u, 30u);
}