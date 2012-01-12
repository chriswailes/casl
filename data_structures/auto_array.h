/* 
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		HPSC Semester Project
 * Description:	Basic vector implementation.
 */

#ifndef AUTO_ARRAY_H
#define AUTO_ARRAY_H

// Standard Includes
#include <stdlib.h>
#include <sys/types.h>

// Project Includes
#include "utility/util.h"

// Macros

// Types

typedef enum {
	ADD,
	MUL
} growth_mode;

typedef struct {
	int max_els;
	int next;
	
	int el_size;
	
	growth_mode mode;
	float gf;
	
	void* data;
} auto_array;

// Functions

auto_array*	auto_array_create(uint init_els, size_t el_size, growth_mode mode, float browth_factor);
void			auto_array_destroy(auto_array* aa);
bool			auto_array_init(auto_array* aa, int init_els, size_t el_size, growth_mode mode, float growth_factor);
auto_array*	auto_array_new(void);
bool			auto_array_reinit(auto_array* aa, int init_els, size_t el_size, growth_mode mode, float growth_factor);

void auto_array_fit(auto_array* aa);
void auto_array_resize(auto_array* aa, size_t size);

void auto_array_add(auto_array* aa, void* el);

void* auto_array_get(auto_array* aa, uint index);
void  auto_array_set(auto_array* aa, uint index, void* el);

#endif
