#include <Fox/FoxCoder.h>

#include <cstring>
#include <experimental/array>
#include <map>

namespace {
constexpr uint32_t kDitCount = 5000;
constexpr uint32_t kDotCount = kDitCount * 3;
constexpr uint32_t kDitSpacingCount = kDitCount;
constexpr uint32_t kLetterSpacingCount = kDotCount;
constexpr uint32_t kWordSpacingCount = kDotCount * 7;

const char default_word[] = "hello world";
const std::map<char, const char*> morse_lut = {
    {'A', ".-"},   {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},  {'E', "."},
    {'F', "..-."}, {'G', "--."},  {'H', "...."}, {'I', ".."},   {'J', ".---"},
    {'K', "-.-"},  {'L', ".-.."}, {'M', "--"},   {'N', "-."},   {'O', "---"},
    {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},  {'S', "..."},  {'T', "-"},
    {'U', "..-"},  {'V', "...-"}, {'W', ".--"},  {'X', "-..-"}, {'Y', "-.--"},
    {'Z', "--.."}, {' ', " "},
};
}  // namespace

FoxCoder::FoxCoder()
    : letter_idx(0), dit_idx(0), wait_counter(0), dit_counter(0), delay(0) {
  memset(_word, 0, sizeof(_word));
  // define delay between letters
  // define dit length
  // define dot length
}

void FoxCoder::set_word(const char* word) {
  strncpy(_word, word, sizeof(_word) - 1);
  _word[sizeof(_word) - 1] = '\x00';
  letter_idx = 0;
  dit_idx = 0;
  wait_counter = 0;
  dit_counter = 0;
  delay = 0;
}

bool FoxCoder::next_delay() {
  if (delay != 0) {
    wait_counter++;
    if (wait_counter == delay) {
      delay = 0;
      wait_counter = 0;
    }
    return false;
  }

  char current_letter = _word[letter_idx];

  if (morse_lut.find(current_letter) == morse_lut.end()) {
    return false;
  }

  const char* morse = morse_lut.at(current_letter);
  char dit_or_dot = morse[dit_idx];

  switch (dit_or_dot) {
    case '.':
      dit_counter += 1;
      if (dit_counter == kDitCount) {
        dit_counter = 0;
        dit_idx++;
        delay = kDitSpacingCount;
      }
      break;
    case '-':
      dit_counter += 1;
      if (dit_counter == kDotCount) {
        dit_counter = 0;
        dit_idx++;
        delay = kDitSpacingCount;
      }
      break;
    case ' ':
      dit_idx++;
      delay = kLetterSpacingCount;
      break;
  }

  if (dit_idx == strlen(morse)) {
    letter_idx++;
    dit_idx = 0;
    delay = kLetterSpacingCount;
  }

  if (letter_idx == strlen(_word)) {
    letter_idx = 0;
    delay = kWordSpacingCount;
  }

  return true;
}