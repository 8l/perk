#ifndef PERK_IMPL_H
#define PERK_IMPL_H

#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

#include <perk/perk.h>
#include <perk/perk_meta.h>

struct pe_driver_ctx_impl {
	struct pe_common_ctx	cctx;
	struct pe_driver_ctx	ctx;
};

struct pe_unit_ctx_impl {
	const char *		path;
	struct pe_raw_image	map;
	struct pe_image_meta *	meta;
	struct pe_common_ctx	cctx;
	struct pe_unit_ctx	uctx;
};

#endif
