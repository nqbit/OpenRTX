#ifndef FOXCODER_H
#define FOXCODER_H

#include <array>
#include <string>

/**
 * Fox transmitter.
 */
class FoxCoder {
 public:
  /**
   * Constructor.
   */
  FoxCoder();
  bool next_delay();
  void set_word(const char* word);

 private:
  uint16_t letter_idx;
  uint8_t dit_idx;
  uint32_t wait_counter;
  uint32_t dit_counter;
  uint32_t delay;
  char _word[32];
};

#endif  // FOXCODER_H
