CELL_MK_DIR = $(CELL_SDK)/samples/mk
include $(CELL_MK_DIR)/sdk.makedef.mk

PPU_PRX_FLAGS = -mprx -mno-sn-ld -Os -ffunction-sections -fdata-sections \
                -fno-builtin-printf -nodefaultlibs -std=gnu99

PPU_CFLAGS = $(PPU_PRX_FLAGS)
PPU_LDFLAGS += $(PPU_PRX_FLAGS)
PPU_PRX_LDFLAGS += -mprx -ffunction-sections -fdata-sections

PPU_SRCS = src/main.c
PPU_PRX_TARGET = km_hen.prx

all:
	$(MAKE) $(PPU_OBJS_DEPENDS)
	$(PPU_PRX_STRIP) $(PPU_PRX_STRIPFLAGS) $(PPU_PRX_TARGET)

include $(CELL_MK_DIR)/sdk.target.mk
