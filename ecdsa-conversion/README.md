# ECDSA DER to IEEE P1363 encoding conversion
This is a sample code that can be used to convert an
ECDSA signature from DER to the RAW IEEE P1363 encoding
and vice versa.  This code may be used when your crypto
library has no convenient way to do the conversion.

The conversion from DER to RAW format is done by ecdsa_der2raw:

int ecdsa_der2raw(unsigned char *in, size_t in_len,
                  unsigned char *out, size_t *out_len, unsigned int n_bits);

where:
in, in_len: input data, DER-encoded signature value.
out, out_len: output data RAW-encoded signature value.
when out==NULL, *out_len will be set to the necessary output size.
n_bits: 256 for nistP256/brainpoolP256r1, 384 for nistP384/brainpoolP384r1.
return value: 0 for success, -1 for error.

The conversion from RAW to DER format is done by ecdsa_raw2der:

int ecdsa_raw2der(unsigned char *in, size_t in_len, 
                  unsigned char *out, size_t *out_len);

where:
in, in_len: input data, RAW-encoded signature value.
out, out_len: output data, DER-encoded signature value.
when out==NULL, *out_len will be set to the necessary output size.
return value: 0 for success, -1 for error.
