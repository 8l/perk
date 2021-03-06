#ifndef PERK_H
#define PERK_H

#include <stdint.h>
#include <stdio.h>

#include "perk_api.h"
#include "perk_consts.h"
#include "perk_structs.h"
#include "perk_meta.h"

#ifdef __cplusplus
extern "C" {
#endif

/* pre-alpha */
#ifndef PERK_APP
#ifndef PERK_PRE_ALPHA
#error  libperk: pre-alpha: ABI is not final!
#error  to use the library, please pass -DPERK_PRE_ALPHA to the compiler.
#endif
#endif

/* status codes */
#define PERK_OK				0x00
#define PERK_USAGE			0x01
#define PERK_BAD_OPT			0x02
#define PERK_BAD_OPT_VAL		0x03
#define PERK_IO_ERROR			0xA0
#define PERK_MAP_ERROR			0xA1
#define PERK_BAD_DOS_HEADER		0xA2
#define PERK_BAD_COFF_HEADER		0xA3
#define PERK_BAD_IMAGE_TYPE		0xA4
#define PERK_MALFORMED_IMAGE		0xA5

/* driver flags */
#define PERK_DRIVER_VERBOSITY_NONE	0x0000
#define PERK_DRIVER_VERBOSITY_ERRORS	0x0001
#define PERK_DRIVER_VERBOSITY_STATUS	0x0002
#define PERK_DRIVER_VERBOSITY_USAGE	0x0004
#define PERK_DRIVER_CLONE_VECTOR	0x0008

#define PERK_DRIVER_VERSION		0x0010
#define PERK_DRIVER_DRY_RUN		0x0020

/* unit action flags */
#define PERK_ACTION_MAP_READWRITE	0x0001

struct pe_source_version {
	int		major;
	int		minor;
	int		revision;
	const char *	commit;
};

struct pe_raw_image {
	void *	addr;
	size_t	size;
};

struct pe_image_summary {
	int32_t		nexpsyms;
	int32_t		nimplibs;
	int32_t		nrelocs;
};

struct pe_image_meta {
	struct pe_raw_image		image;
	struct pe_image_summary		summary;

	struct pe_meta_image_dos_hdr	dos;
	struct pe_meta_coff_file_hdr	coff;
	struct pe_meta_opt_hdr		opt;
	struct pe_meta_sec_hdr *	sectbl;

	struct pe_image_dos_hdr *	ados;
	struct pe_coff_file_hdr *	acoff;
	union  pe_opt_hdr *		aopt;
	struct pe_sec_hdr *		asectbl;

	struct pe_meta_export_hdr	edata;
	struct pe_export_hdr *		aedata;
	struct pe_meta_sec_hdr *	hedata;

	struct pe_meta_import_hdr *	idata;
	struct pe_import_hdr *		aidata;
	struct pe_meta_sec_hdr *	hidata;
};

struct pe_symbol_ctx {
	const char **			attrs;
	const char **			append;
	const char **			exclude;
};

struct pe_output_ctx {
	const char **			attrs;
	const char *			header;
	const char *			footer;
};

struct pe_linker_ctx {
	const char **			attrs;
};

struct pe_server_ctx {
	const char **			attrs;
};

struct pe_io_ctx {
	int				status;
	int				prot;
	int				mode;
	int				fdin;
	int				fdout;
	int				fderr;
	int				fdlog;
	int				fdsrc;
	int				fddst;
	int				fdtmp;
};

struct pe_common_ctx {
	uint64_t			drvflags;
	uint64_t			actflags;
	uint64_t			fmtflags;
	uint64_t			lnkflags;
	const char *			output;
	const char *			srcdir;
	const char *			dstdir;
	const char *			tmpdir;
	const struct pe_symbol_ctx *	symctx;
	const struct pe_output_ctx *	outctx;
	const struct pe_linker_ctx *	lnkctx;
	const struct pe_server_ctx *	srvctx;
	const struct pe_io_ctx *	ioctx;
};

struct pe_driver_ctx {
	const char **			units;
	const char *			program;
	const char *			module;
	const struct pe_common_ctx *	cctx;
	void *				any;
	int				status;
	int				nerrors;
};

struct pe_unit_ctx {
	const char * const *		path;
	const struct pe_raw_image *	map;
	const struct pe_image_meta *	meta;
	const struct pe_common_ctx *	cctx;
	void *				any;
	int				status;
	int				nerrors;
};

/* package info */
perk_api				const struct pe_source_version * pe_source_version(void);

/* driver api */
perk_api int  pe_get_driver_ctx		(char ** argv, char ** envp, uint32_t flags, struct pe_driver_ctx **);
perk_api void pe_free_driver_ctx	(struct pe_driver_ctx *);

perk_api int  pe_get_unit_ctx		(const struct pe_driver_ctx *, const char * path, struct pe_unit_ctx **);
perk_api void pe_free_unit_ctx		(struct pe_unit_ctx *);

/* utility api */
perk_api int  pe_main			(int, char **, char **);
perk_api int  pe_output_export_symbols	(const struct pe_image_meta *, const struct pe_common_ctx *, FILE *);
perk_api int  pe_output_import_libraries(const struct pe_image_meta *, const struct pe_common_ctx *, FILE *);

/* high-level api */
perk_api int  pe_map_raw_image		(int fd, const char * path, int prot, struct pe_raw_image *);
perk_api int  pe_unmap_raw_image	(struct pe_raw_image *);

perk_api int  pe_get_image_meta		(const struct pe_raw_image *, struct pe_image_meta **);
perk_api void pe_free_image_meta	(struct pe_image_meta *);

perk_api int  pe_get_named_section_index(const struct pe_image_meta *, const char * name);
perk_api int  pe_get_block_section_index(const struct pe_image_meta *, const struct pe_block *);

/* low-level api */
perk_api int  pe_read_dos_header	(const struct pe_image_dos_hdr *,	struct pe_meta_image_dos_hdr *);
perk_api int  pe_read_coff_header	(const struct pe_coff_file_hdr *,	struct pe_meta_coff_file_hdr *);
perk_api int  pe_read_optional_header	(const union  pe_opt_hdr *,		struct pe_meta_opt_hdr *);
perk_api int  pe_read_section_header	(const struct pe_sec_hdr *,		struct pe_meta_sec_hdr *);
perk_api int  pe_read_export_header	(const struct pe_export_hdr *,		struct pe_meta_export_hdr *);
perk_api int  pe_read_import_header	(const struct pe_import_hdr *,		struct pe_meta_import_hdr *);
perk_api int  pe_read_import_lookup_item(const union  pe_import_lookup_item *,	struct pe_meta_import_lookup_item *, uint32_t magic);

#ifdef __cplusplus
}
#endif

#endif
