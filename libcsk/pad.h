#ifndef _HAVE_CSK_ZPADDING
#define _HAVE_CSK_ZPADDING

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <limits.h>

#include "mem.h"

#ifdef DEBUG
#define ZPADCHAR 48
#else
#define ZPADCHAR 0
#endif

// prepends a binary stream with a number of
// \0's as required by the secret_box and
// secret_box_open functions of libsodium.
//
// parameters:
//
// padded:    destination array (ref)
// unpadded:  source array without padding
// padlen:    length of padding
// unpadlen:  length of source array
//
// turns "efa5" into "00000000efa5" with padlen 8
//
// if DEBUG is set, destination will be padded with
// the character '0', NOT the integer 0.
//
// allocates memory for padded and it is up to the
// user to free it after use.
//
// sample call:
//
// char unpadded[] = {0xef, 0xa5};
// unsigned char *padded;
// csk_pad_prepend(&padded, unpadded, 8, 2);
//
// the result, padded, would be 10 bytes long, 8
// bytes for the leading zeros and 2 for the content
// of the original unpadded.
void csk_pad_prepend(unsigned char **padded, unsigned char *unpadded,
		 size_t padlen, size_t unpadlen);

// removes zero's of a binary stream, which is
// the reverse of csk_pad_prepend().
//
// parameters:
// 
// unpadded:   destination array (ref), with padding removed
// padded:     source array with padding
// padlen:     length of padding
// unpadlen:   length of source array
//
// turns "00000000efa5" into "efa5" with padlen 8
//
// allocates memory for unpadded and it is up to the
// user to free it after use.
//
// sample call:
//
// char padded[] = {0x0, 0x0, 0x0, 0x0, 0xef, 0xa5};
// unsigned char *unpadded;
// csk_pad_remove(unpadded, padded, 4, 2);
//
// the result, unpadded would be 2 bytes long containing
// only the 2 bytes we want to have with zeros removed.
void csk_pad_remove(unsigned char **unpadded, unsigned char *padded,
		size_t padlen, size_t unpadlen);


#endif // _HAVE_CSK_ZPADDING
