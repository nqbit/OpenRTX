#include <Fox/FoxTransmitter.h>
#include <toneGenerator_MDx.h>

#include <experimental/array>

const auto presine = std::experimental::make_array<uint8_t>(
    127, 135, 143, 151, 159, 166, 174, 181, 188, 195, 202, 208, 214, 220, 225,
    230, 235, 239, 242, 246, 248, 250, 252, 253, 254, 255, 254, 253, 252, 250,
    248, 246, 242, 239, 235, 230, 225, 220, 214, 208, 202, 195, 188, 181, 174,
    166, 159, 151, 143, 135, 127, 119, 111, 103, 95, 88, 80, 73, 66, 59, 52, 46,
    40, 34, 29, 24, 19, 15, 12, 8, 6, 4, 2, 1, 0, 0, 0, 1, 2, 4, 6, 8, 12, 15,
    19, 24, 29, 34, 40, 46, 52, 59, 66, 73, 80, 88, 95, 103, 111, 119);

FoxTransmitter::FoxTransmitter() : loc(0) {}

FoxTransmitter::~FoxTransmitter() {}

void FoxTransmitter::init(const char *word) {
  coder.set_word(word);
  baseband_buffer = new int16_t[2 * FOX_BUFFER_SIZE];
  activeBuffer = new (baseband_buffer) dataBuffer_t;
  int16_t *ptr = baseband_buffer + activeBuffer->size();
  idleBuffer = new (ptr) dataBuffer_t;
}

void FoxTransmitter::terminate() {
  // Delete the buffers and deallocate memory.
  activeBuffer->~dataBuffer_t();
  idleBuffer->~dataBuffer_t();
  delete[] baseband_buffer;
}

void FoxTransmitter::reset() {}

void FoxTransmitter::send() {
  for (size_t i = 0; i < FOX_BUFFER_SIZE; i++) {
    idleBuffer->at(i) = coder.next_delay() ? presine[loc] : 128;
    loc += 1;
    loc = loc % presine.size();
  }

  toneGen_waitForStreamEnd();
  std::swap(idleBuffer, activeBuffer);
  toneGen_playAudioStream(reinterpret_cast<uint16_t *>(activeBuffer->data()),
                          activeBuffer->size(), FOX_TX_AUDIO_SAMPLE_RATE);
}