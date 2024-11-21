#include <stddef.h>
#include <string.h>

int ecdsa_der2raw(unsigned char *in, size_t in_len,
                  unsigned char *out, size_t *out_len, unsigned int n_bits)
{
  size_t r_off, r_len;
  size_t s_off, s_len;

  if (n_bits != 256 && n_bits != 384)
    return -1;
  if (out == NULL) {
    *out_len = n_bits / 4;
    return 0;
  }
  if (*out_len < n_bits / 4)
    return -1;
  if (in == NULL || in_len < 8 || in_len > n_bits / 4 + 8)
    return -1;
  if (in[0] != 0x30 || in[1] != in_len - 2 || in[2] != 0x02)
    return -1;
  r_len = in[3];
  r_off = 4;
  if (r_len == 0 || r_off + r_len > in_len - 2 || in[r_off] >= 0x80)
    return -1;
  if (in[r_off] == 0x00) {
    r_len--;
    r_off++;
    if (r_len != 0 && in[r_off] < 0x80)
      return -1;
  }
  if (r_len > n_bits / 8 || in[r_off + r_len] != 0x02)
    return -1;
  s_len = in[r_off + r_len + 1];
  s_off = r_off + r_len + 2;
  if (s_len == 0 || s_off + s_len != in_len || in[s_off] >= 0x80)
    return -1;
  if (in[s_off] == 0x00) {
    s_len--;
    s_off++;
    if (s_len != 0 && in[s_off] < 0x80)
      return -1;
  }
  if (s_len > n_bits / 8)
    return -1;
  memset(out, 0, n_bits / 4);
  memcpy(&out[n_bits / 8 - r_len], &in[r_off], r_len);
  memcpy(&out[n_bits / 4 - s_len], &in[s_off], s_len);
  *out_len = n_bits / 4;
  return 0;
}

int ecdsa_raw2der(unsigned char *in, size_t in_len,
                  unsigned char *out, size_t *out_len)
{
  size_t off, len;
  size_t r_pos, s_pos;

  if (in_len != 64 && in_len != 96)
    return -1;
  if (out == NULL) {
    *out_len = in_len + 8;
    return 0;
  }
  if (*out_len < in_len + 8)
    return -1;
  len = in_len / 2;
  off = 0;
  while (len > 1 && in[off] == 0x00) {
    len--;
    off++;
  }
  out[0] = 0x30;
  out[2] = 0x02;
  r_pos = 4;
  if (in[off] & 0x80)
    out[r_pos++] = 0x00;
  memcpy(&out[r_pos], &in[off], len);
  r_pos += len;
  out[3] = r_pos - 4;
  off = len = in_len / 2;
  while (len > 1 && in[off] == 0x00) {
    len--;
    off++;
  }
  out[r_pos] = 0x02;
  s_pos = r_pos + 2;
  if (in[off] & 0x80)
    out[s_pos++] = 0x00;
  memcpy(&out[s_pos], &in[off], len);
  s_pos += len;
  out[r_pos + 1] = s_pos - r_pos - 2;
  out[1] = s_pos - 2;
  *out_len = s_pos;
  return 0;
}

#include <unistd.h>
#include <stdlib.h>

int main (int argc, char**argv)
{
  unsigned char in[128], out[128];
  size_t len, outlen;
  int i;

  len = read(0, in, 128);
  if (argc == 2)
  {
    i = ecdsa_der2raw(NULL, 0, NULL, &outlen, atoi(argv[1]));
    if (i == 0)
      i = ecdsa_der2raw(in, len, out, &outlen, atoi(argv[1]));
  }
  else
  {
    i = ecdsa_raw2der(NULL, len, NULL, &outlen);
    if (i == 0)
      i = ecdsa_raw2der(in, len, out, &outlen);
  }
  if (i == 0)
  {
    if (outlen != (size_t) write(1, out, outlen))
      i = 1;
  }
  return i == 0 ? 0 : 1;
}
