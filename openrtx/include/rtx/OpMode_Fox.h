#ifndef OPMODE_FOX_H
#define OPMODE_FOX_H

#include <Fox/FoxTransmitter.h>

#include <array>

#include "OpMode.h"

/**
 * Specialisation of the OpMode class for the management of Fox operating mode.
 */
class OpMode_Fox : public OpMode {
 public:
  /**
   * Constructor.
   */
  OpMode_Fox();

  /**
   * Destructor.
   */
  ~OpMode_Fox();

  /**
   * Enable the operating mode.
   *
   * Application must ensure this function is being called when entering the
   * new operating mode and always before the first call of "update".
   */
  virtual void enable() override;

  /**
   * Disable the operating mode. This function stops the DMA transfers
   * between the baseband, microphone and speakers. It also ensures that
   * the radio, the audio amplifier and the microphone are in OFF state.
   *
   * Application must ensure this function is being called when exiting the
   * current operating mode.
   */
  virtual void disable() override;

  /**
   * Update the internal FSM.
   * Application code has to call this function periodically, to ensure proper
   * functionality.
   *
   * @param status: pointer to the rtxStatus_t structure containing the current
   * RTX status. Internal FSM may change the current value of the opStatus flag.
   * @param newCfg: flag used inform the internal FSM that a new RTX
   * configuration has been applied.
   */
  virtual void update(rtxStatus_t *const status, const bool newCfg) override;

  /**
   * Get the mode identifier corresponding to the OpMode class.
   *
   * @return the corresponding flag from the opmode enum.
   */
  virtual opmode getID() override { return FOX; }

  /**
   * Check if RX squelch is open.
   *
   * @return true if RX squelch is open.
   */
  virtual bool rxSquelchOpen() override { return false; }

 private:
  FoxTransmitter foxTx;  ///< Fox transmission manager.
};

#endif /* OPMODE_FOX_H */
