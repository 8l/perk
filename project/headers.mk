API_HEADERS = \
	$(PROJECT_DIR)/include/$(PACKAGE)/perk.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/perk_api.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/perk_consts.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/perk_meta.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/perk_output.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/perk_structs.h

INTERNAL_HEADERS = \
	$(PROJECT_DIR)/src/internal/argv/argv.h \
	$(PROJECT_DIR)/src/internal/$(PACKAGE)_driver_impl.h \
	$(PROJECT_DIR)/src/internal/$(PACKAGE)_endian_impl.h \
	$(PROJECT_DIR)/src/internal/$(PACKAGE)_output_impl.h \
	$(PROJECT_DIR)/src/internal/$(PACKAGE)_reader_impl.h \

ALL_HEADERS = $(API_HEADERS) $(INTERNAL_HEADERS)
