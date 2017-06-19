/* ANSI-C code produced by gperf version 3.0.3 */
/* Command-line: /Library/Developer/CommandLineTools/usr/bin/gperf -l -C -L ANSI-C --struct-type --output=names.c names.gperf  */
/* Computed positions: -k'3' */

#include "names.h"
#include <cstring>

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 3 "names.gperf"
struct names { const char *name; int index; };
#include <string.h>

#define TOTAL_KEYWORDS 10
#define MIN_WORD_LENGTH 4
#define MAX_WORD_LENGTH 8
#define MIN_HASH_VALUE 4
#define MAX_HASH_VALUE 18
/* maximum key range = 15, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (const char *str, unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19,  5, 19, 10,
       5,  0, 19, 19, 19, 19, 19, 19,  5, 19,
       0, 19,  0, 19,  5, 19,  0, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
      19, 19, 19, 19, 19, 19
    };
  return len + asso_values[(unsigned char)str[2]];
}

const struct names *
gperf_nameIndex (const char *str, unsigned int len)
{
  static const unsigned char lengthtable[] =
    {
       0,  0,  0,  0,  4,  5,  6,  7,  8,  0,  5,  6,  7,  8,
       0,  0,  0,  0,  8
    };
  static const struct names wordlist[] =
    {
      {""}, {""}, {""}, {""},
#line 12 "names.gperf"
      {"Anna", 7},
#line 13 "names.gperf"
      {"Sonya", 8},
#line 5 "names.gperf"
      {"Pierre", 0},
#line 8 "names.gperf"
      {"Natasha", 3},
#line 9 "names.gperf"
      {"Napoleon", 4},
      {""},
#line 14 "names.gperf"
      {"Boris", 9},
#line 6 "names.gperf"
      {"Andrew", 1},
#line 11 "names.gperf"
      {"Anatole", 6},
#line 10 "names.gperf"
      {"Dolokhov", 5},
      {""}, {""}, {""}, {""},
#line 7 "names.gperf"
      {"Nicholas", 2}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        if (len == lengthtable[key])
          {
            const char *s = wordlist[key].name;

            if (*str == *s && !memcmp (str + 1, s + 1, len - 1))
              return &wordlist[key];
          }
    }
  return 0;
}
#line 15 "names.gperf"

int getNameIndex(const char *str)
{
    if (str[0] == 'P' || str[0] == 'N' || str[0] == 'A' ||
        str[0] == 'S' || str[0] == 'D' || str[0] == 'B') {
          const struct names *n = gperf_nameIndex(str, strlen(str));
          return n ? n->index : -1;
    } else {
          return -1;
    }
}
