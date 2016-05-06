/***************************************************************/
/*  perk: PE Resource Kit                                      */
/*  Copyright (C) 2015--2016  Z. Gilboa                        */
/*  Released under the Standard MIT License; see COPYING.PERK. */
/***************************************************************/

#ifndef PERK_ENDIAN_IMPL_H
#define PERK_ENDIAN_IMPL_H

#include <stdbool.h>

#define PERK_LITTLE_ENDIAN	pe_little_endian_host()

static inline bool pe_little_endian_host(void)
{
	const long test = 1;
	return *((char *)&test);
}

#endif
