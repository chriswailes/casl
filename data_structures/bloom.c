/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		Chris's Awesome Standard Library
 * Description:	A simple Bloom Filter implementation that was initially
 				taken from here: http://en.literateprograms.org/Bloom_filter_%28C%29
 */

// Standard Includes
#include <limits.h>
#include <stdarg.h>
#include <sys/types.h>

// Project Includes
#include "data_structures/bloom.h"
#include "utility/util.h"

// Macros
#define SETBIT(a, n) (a[n / CHAR_BIT] |= (1 << (n % CHAR_BIT)))
#define GETBIT(a, n) (a[n / CHAR_BIT] &  (1 << (n % CHAR_BIT)))

// Global Variables

// Functions

/*
 * Size represents the length of the filter in BITS.
 */
bloom_t* bloom_create(size_t size, uint nfuncs, ...) {
	bloom_t* bloom;
	va_list arg_list;
	
	if ((bloom == bloom_new()) == NULL) {
		return NULL;
	}
	
	if (!bloom_init(bloom, size, nfuncs, arg_list)) {
		free(bloom);
		return NULL;
	}

	return bloom;
}

void bloom_destroy(bloom_t* bloom) {
	free(bloom->a);
	free(bloom->funcs);
	free(bloom);
}

/*
 * Size represents the length of the filter in BITS.
 */
bool bloom_init(bloom_t* bloom, size_t size, uint nfuncs, ...) {
	va_list arg_list;
	
	if ((bloom->bits = (char*) calloc((size + CHAR_BIT - 1) / CHAR_BIT, sizeof(char))) == NULL) {
		return FALSE;
	}
	
	if ((bloom->funcs = (hashfunc_t*) calloc(nfuncs, sizeof(hashfunc_t))) == NULL) {
		free(bloom->bits);
		return FALSE;
	}
	
	bloom->bits_size	= size;
	bloom->nfuncs		= nfuncs;
	
	va_start(l, nfuncs);
	while (nfuncs-- > 0) {
		bloom->funcs[nfuncs] = va_arg(arg_list, bloomhash_t);
	}
	va_end(l);
	
	return TRUE;
}

bloom_t* bloom_new(void) {
	return (bloom_t*) malloc(sizeof(bloom_t));
}

void bloom_add(bloom_t* bloom, const char* s, uint length) {
	uint index;

	for (index = bloom->nfuncs; index-- > 0;) {
		SETBIT(bloom->bits, bloom->funcs[n](s, length) % bloom->bits_size);
	}
}

int bloom_check(bloom_t* bloom, const char* s, uint length) {
	uint index;

	for (index = bloom->nfuncs; index-- > 0;) {
		if(!(GETBIT(bloom->bits, bloom->funcs[n](s, length) % bloom->bits_size))) return FALSE;
	}

	return TRUE;
}

