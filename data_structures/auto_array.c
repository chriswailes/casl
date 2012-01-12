/* 
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		Chris's Awesome Standard Library
 * Description:	Basic auto-array implementation.
 */

// Standard Includes
#include <stdlib.h>
#include <string.h>

// Project Includes
#include "data_structures/auto_array.h"

// Macros

// Global Variables

// Functions

auto_array* auto_array_create(uint init_els, size_t el_size, growth_mode mode, float growth_factor) {
	auto_array* aa;
	
	if ((aa = auto_array_new()) == NULL) {
		return NULL;
	}
	
	if (!auto_array_reinit(aa, init_els, el_size, mode, growth_factor)) {
		free(aa);
		return NULL;
	}
	
	return aa;
}

void auto_array_destroy(auto_array* aa) {
	free(aa->data);
	free(aa);
}

bool auto_array_init(auto_array* aa, int init_els, size_t el_size, growth_mode mode, float growth_factor) {
	aa->data = NULL;
	
	return auto_array_reinit(aa, init_els, el_size, mode, growth_factor);
}

auto_array* auto_array_new(void) {
	return (auto_array*) malloc(sizeof(auto_array));
}

bool auto_array_reinit(auto_array* aa, int init_els, size_t el_size, vec_mode mode, float growth_factor) {
	aa->el_size = el_size;
	
	// Set the first element as the next position.
	aa->next = 0;
	
	// Set the maximum number of elements currently allowed.
	aa->max_els = init_els;
	
	if (aa->data != NULL) {
		free(aa->data);
	}
	
	// Allocate the array.
	aa->data = (init_els == 0) ? NULL : calloc(init_els, el_size);
	
	if (init_els != 0 && aa->data == NULL) {
		return FALSE;
	}
	
	// Default growth settings.
	aa->mode	= mode;
	aa->gf	= growth_factor;
	
	return TRUE;
}

inline void auto_array_fit(auto_array* aa) {
	auto_array_resize(aa, aa->el_size * aa->next);
}

inline void auto_array_resize(auto_array* aa, size_t size) {
	aa->data = realloc(aa->data, size);
}

void auto_array_add(auto_array* aa, void* el) {
	if (aa->max_els == aa->next) {
		// The vector is full.  Time to expand.
		aa->max_els	= (aa->mode == MUL) ? aa->max_els * aa->gf : aa->max_els + aa->gf;
		aa->data		= realloc(aa->data, aa->max_els * aa->el_size);
	}
	
	// Set the next available spot in the vector to our element.
	auto_array_set(aa, aa->next++, el);
}

inline void* auto_array_get(vector* aa, int index) {
	return aa->data + (index * aa->el_size);
}

inline void auto_array_set(auto_array* aa, int index, void* el) {
	memcpy(auto_array_get(aa, index), el, aa->el_size);
}
