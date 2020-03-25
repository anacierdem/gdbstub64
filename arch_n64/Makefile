# ROOTDIR = $(N64_INST)
# BUILD_PATH = $(CURDIR)/build
# SOURCE_PATH = $(CURDIR)/src
# INCLUDE_PATH = $(CURDIR)/include

# CFLAGS = -std=gnu99 -O2 -G0 -Wall -Werror -mtune=vr4300 -march=vr4300 -I$(INCLUDE_PATH) -I$(ROOTDIR)/mips64-elf/include
# ASFLAGS = -mtune=vr4300 -march=vr4300
# N64PREFIX = $(N64_INST)/bin/mips64-elf-
# INSTALLDIR = $(N64_INST)
# CC = $(N64PREFIX)gcc
# AS = $(N64PREFIX)as
# LD = $(N64PREFIX)ld
# AR = $(N64PREFIX)ar

# all: libgdbstub64

# libgdbstub64: $(BUILD_PATH)/libgdbstub64.a

# $(BUILD_PATH)/libgdbstub64.a: $(BUILD_PATH)/libgdbstub64.o
# 	$(AR) -rcs -o $(BUILD_PATH)/libgdbstub64.a $(BUILD_PATH)/libgdbstub64.o

# $(BUILD_PATH)/libgdbstub64.o: $(SOURCE_PATH)/libgdbstub64.c
# 	mkdir -p $(BUILD_PATH)
# 	$(CC) $(CFLAGS) -c -o $(BUILD_PATH)/libgdbstub64.o $(SOURCE_PATH)/libgdbstub64.c

# install:
# 	install -m 0644 $(BUILD_PATH)/libgdbstub64.a $(INSTALLDIR)/mips64-elf/lib/libgdbstub64.a
# 	install -m 0644 $(INCLUDE_PATH)/libgdbstub64.h $(INSTALLDIR)/mips64-elf/include/libgdbstub64.h

# test:
# 	make -C test

# .PHONY: clean

# clean:
# 	rm -rf $(BUILD_PATH)/*

ROOTDIR = $(N64_INST)
GCCN64PREFIX = $(ROOTDIR)/bin/mips64-elf-
CHKSUM64PATH = $(ROOTDIR)/bin/chksum64
MKDFSPATH = $(ROOTDIR)/bin/mkdfs
HEADERPATH = $(ROOTDIR)/mips64-elf/lib
N64TOOL = $(ROOTDIR)/bin/n64tool
HEADERNAME = header
LINK_FLAGS = -L$(ROOTDIR)/mips64-elf/lib -led64 -ldragon -lc -lm -ldragonsys -Tn64.ld
CFLAGS = -std=gnu99 -march=vr4300 -mtune=vr4300 -O2 -Wall -I$(ROOTDIR)/mips64-elf/include -I$(CURDIR)
ASFLAGS = -mtune=vr4300 -march=vr4300
CC = $(GCCN64PREFIX)gcc
AS = $(GCCN64PREFIX)as
LD = $(GCCN64PREFIX)ld
OBJCOPY = $(GCCN64PREFIX)objcopy

BUILD_PATH = $(CURDIR)/build
SOURCE_PATH = $(CURDIR)
PROG_NAME = $(BUILD_PATH)/main

N64_FLAGS = -l 2M -h $(HEADERPATH)/$(HEADERNAME) -o $(PROG_NAME)$(ROM_EXTENSION) $(PROG_NAME).bin
ifeq ($(N64_BYTE_SWAP),true)
ROM_EXTENSION = .v64
N64_FLAGS = -b $(N64_FLAGS)
else
ROM_EXTENSION = .z64
endif

$(PROG_NAME)$(ROM_EXTENSION): $(PROG_NAME).elf
	$(OBJCOPY) $(PROG_NAME).elf $(PROG_NAME).bin -O binary
	rm -f $(PROG_NAME)$(ROM_EXTENSION)
	$(N64TOOL) $(N64_FLAGS) -t "ED64"
	$(CHKSUM64PATH) $(PROG_NAME)$(ROM_EXTENSION)

$(BUILD_PATH)/gdbstub_sys.o: $(SOURCE_PATH)/gdbstub_sys.c
	mkdir -p $(BUILD_PATH)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_PATH)/gdbstub.o: $(SOURCE_PATH)/../gdbstub.c
	mkdir -p $(BUILD_PATH)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROG_NAME).o: $(SOURCE_PATH)/main.c
	mkdir -p $(BUILD_PATH)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROG_NAME).elf: $(PROG_NAME).o $(BUILD_PATH)/gdbstub_sys.o $(BUILD_PATH)/gdbstub.o
	$(LD) -o $@ $^ $(LINK_FLAGS)

all: $(PROG_NAME)$(ROM_EXTENSION)

.PHONY: clean

clean:
	rm -rf $(BUILD_PATH)/*
