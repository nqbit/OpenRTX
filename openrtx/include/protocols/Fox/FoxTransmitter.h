#ifndef FOXTRANSMITTER_H
#define FOXTRANSMITTER_H

#ifndef __cplusplus
#error This header is C++ only!
#endif

#include <Fox/FoxCoder.h>

#include <array>
#include <string>

/**
 * Fox transmitter.
 */
class FoxTransmitter {
 public:
  /**
   * Constructor.
   */
  FoxTransmitter();

  /**
   * Destructor.
   */
  ~FoxTransmitter();

  // mode switching
  void init(const char *word);
  void terminate();

  // ptt
  void send();
  void reset();

 private:
  static constexpr size_t FOX_TX_AUDIO_SAMPLE_RATE = 48000;
  static constexpr size_t FOX_BUFFER_SIZE = 1920UL;

  using dataBuffer_t = std::array<int16_t, FOX_BUFFER_SIZE>;

  int16_t *baseband_buffer;    ///< Buffer for baseband audio handling.
  dataBuffer_t *activeBuffer;  ///< Half baseband buffer, in transmission.
  dataBuffer_t *idleBuffer;    ///< Half baseband buffer, free for processing.

  FoxCoder coder;
  int16_t loc;
};

#endif /* FOXTRANSMITTER_H */
