#ifndef T9_H
#define T9_H

#ifndef __cplusplus
#error This header is C++ only!
#endif

#include <stdint.h>

class T9 {
 public:
  struct State {
    char letter;
    bool newletter;
    bool has_letter;
  };

  enum class KeyCode {
    kNoKey,
    k0,
    k1,
    k2,
    k3,
    k4,
    k5,
    k6,
    k7,
    k8,
    k9,
    kHash,
    kStar
  };

  State poll(uint32_t current_time_micros, KeyCode key_code);
  void get_letter();
  void cycle_letter();
  void set_letter(const KeyCode& key_code);

 private:
  bool active = false;
  bool first_letter = true;
  KeyCode active_key = KeyCode::kNoKey;
  KeyCode last_key = KeyCode::kNoKey;
  uint32_t timeout_value;
  uint8_t t9_idx;
};

#endif  // T9_H