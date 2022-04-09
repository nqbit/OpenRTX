#include <input/t9.h>

#include <cstring>
#include <map>

namespace {
const std::map<T9::KeyCode, const char*> dict = {
    {T9::KeyCode::k0, " 0"},   {T9::KeyCode::k1, ",.?1"},
    {T9::KeyCode::k2, "abc2"}, {T9::KeyCode::k3, "def3"},
    {T9::KeyCode::k4, "ghi4"}, {T9::KeyCode::k5, "jkl5"},
    {T9::KeyCode::k6, "mno6"}, {T9::KeyCode::k7, "pqrs7"},
    {T9::KeyCode::k8, "tuv8"}, {T9::KeyCode::k9, "wxyz9"},
};

const char* getStrForKey(T9::KeyCode key_code) {
  switch (key_code) {
    case T9::KeyCode::k0:
      return " 0";
    case T9::KeyCode::k1:
      return ",.?1";
    case T9::KeyCode::k2:
      return "ABC2";
    case T9::KeyCode::k3:
      return "DEF3";
    case T9::KeyCode::k4:
      return "GHI4";
    case T9::KeyCode::k5:
      return "JKL5";
    case T9::KeyCode::k6:
      return "MNO6";
    case T9::KeyCode::k7:
      return "PQRS7";
    case T9::KeyCode::k8:
      return "TUV8";
    case T9::KeyCode::k9:
      return "WXYZ9";
    default:
      return "";
  }
}

}  // namespace

T9::State T9::poll(uint32_t millis, KeyCode key_code) {
  bool commit_key = false;
  State l;
  l.has_letter = true;
  l.newletter = false;

  if (last_key != key_code && key_code != KeyCode::kNoKey) {
    l.newletter = !first_letter;
    first_letter = false;
    t9_idx = 0;
  }

  if (key_code == KeyCode::kNoKey) {
    l.has_letter = false;
    return l;
  }

  const char* active_str = getStrForKey(key_code);

  if (strlen(active_str) == 0) {
    l.has_letter = false;
    return l;
  }

  l.letter = active_str[t9_idx];
  t9_idx = (t9_idx + 1) % strlen(active_str);

  if (key_code != KeyCode::kNoKey) {
    last_key = key_code;
  }

  return l;
}

void T9::cycle_letter() {
  const std::string active_str = dict.at(active_key);
  t9_idx = (t9_idx + 1) % active_str.length();
}

void T9::set_letter(const T9::KeyCode& key_code) {
  active_key = key_code;
  t9_idx = 0;
}
