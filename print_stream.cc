//
//  print_stream.cpp
//  write by @snibug
//
//  Created by ssh on 2/21/15.
//
//

#include "print_stream.h"

#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <iostream>


typedef unsigned char byte;

const int kOffsetPos = 0;
const int kHexCodePos = 16;
const int kCharCodePos = 60;
const int kMaxLineBytes = 16;
const int kLineLength = 80;


void print_line(std::ostream &out, const char *data, const int len,
                const int data_offset)
{
  char buffer[kLineLength];
  memset(buffer, ' ', kLineLength);

  // print offset
  sprintf(buffer, "%#10.04x", data_offset);

  // print hex code
  int hex_offset = 0;
  for (int pos = 0; pos < len; pos += 2) {
    sprintf(buffer + kHexCodePos + hex_offset, "%02x", byte(data[pos]));
    hex_offset += 2;

    sprintf(buffer + kHexCodePos + hex_offset, "%02x", byte(data[pos + 1]));
    hex_offset += 2;

    buffer[kHexCodePos + hex_offset] = ' ';
    hex_offset++;
  }

  // print char code
  for (int pos = 0; pos < len; ++pos) {
    char c = isgraph(data[pos]) ? data[pos] : '.';
    buffer[kCharCodePos + pos] = c;
  }

  for (int pos = 0; pos < sizeof(buffer); ++pos) {
    putchar(buffer[pos]);
  }

  putchar('\n');
}


void dump_stream(std::ostream& out, const char *data, const int len)
{
  for (int i = 0; i < len; i += kMaxLineBytes) {
    int line_len = len-i >= kMaxLineBytes ? kMaxLineBytes: len % kMaxLineBytes;
    print_line(out, data + i, line_len, i);
  }
}


int main()
{
  char test_data[200] = {0, };
  for (int i = 0; i < sizeof(test_data); ++i) {
    test_data[i] = static_cast<char>(i);
  }

  dump_stream(std::cout, test_data, sizeof(test_data));
  return 0;
}
