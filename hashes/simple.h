/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		Chris's Awesome Standard Library
 * Description:	Simple, non-cryptographically secure, hashes.
 */

#ifndef SIMPLE_HASHES_H
#define SIMPLE_HASHES_H

// Standard Includes
#include <sys/types.h>

// Project Includes

// Macros

// Types

// Functions

uint bernstein_hash(const unsigned char* data, uint length);
uint sax_hash(const unsigned char* data, uint length);
uint sdbm_hash(const unsigned char* data, uint length);

#endif
