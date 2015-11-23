COMMON_SRCS = \
	src/driver/pe_driver_ctx.c \
	src/driver/pe_unit_ctx.c \
	src/logic/pe_get_image_meta.c \
	src/logic/pe_map_raw_image.c \
	src/output/pe_output_export_symbols.c \
	src/reader/pe_read_coff_header.c \
	src/reader/pe_read_dos_header.c \
	src/reader/pe_read_export_header.c \
	src/reader/pe_read_import_header.c \
	src/reader/pe_read_optional_header.c \
	src/reader/pe_read_section_header.c \

APP_SRCS = \
	src/perk.c
