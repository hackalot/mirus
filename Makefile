PROG_BUILD_NUM=build/.build_number
BUILD_DATE = $(shell date +'%Y%m%d')
BUILD_NUM = $(shell cat $(PROG_BUILD_NUM))
BUILD_MAJOR = 0
BUILD_MINOR = 1
BUILD_CODENAME = fayette
BUILD_POSTFIX = dev

M_ARCH = i386

PROJDIRS := src/kernel src/asm src/include
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.cpp")
ASMFILES := $(shell find $(PROJDIRS) -type f -name "*.s")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.hpp")
DEPFILES := $(shell find $(PROJDIRS) -type f -name "*.d")

OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))
OBJFILES += $(patsubst %.s,%.o,$(ASMFILES))

AUXFILES := Makefile README.md LICENSE.mds
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES) $(ASMFILES)

CXX = clang++
CXXWARNINGS = -Wall -Wextra -Wno-unused-parameter
DEBUG = -D_DEBUG_ON
CXXFLAGS := $(CXXWARNINGS) -fno-builtin -fno-exceptions -ffreestanding -std=c++11 -Isrc/include -Isrc/lib -m32 -O0
CXXFLAGS += -DBUILD_DATE=$(BUILD_DATE) -DBUILD_NUM=$(BUILD_NUM)
CXXFLAGS += -DBUILD_MAJOR=$(BUILD_MAJOR) -DBUILD_MINOR=$(BUILD_MINOR)
CXXFLAGS += -DBUILD_CODENAME=$(BUILD_CODENAME) -DBUILD_POSTFIX="$(BUILD_POSTFIX)"
CXXFLAGS += $(DEBUG)

LD = ld
LDFLAGS := -T build/linker.ld -melf_i386

AS = nasm
ASFLAGS = -f elf

QEMU = qemu-system-i386
QEMUFLAGS = -serial file:/tmp/miruslog

.PHONY: all clean dist todolist dist kvm debug

TARGET = mirus-$(BUILD_MAJOR).$(BUILD_MINOR).$(BUILD_NUM)-$(BUILD_POSTFIX).$(M_ARCH).iso

ALL: $(OBJFILES)
	@$(LD) $(LDFLAGS) -o kernel.bin ${OBJFILES}
	@cp kernel.bin iso/boot/kernel.bin
	@grub-mkrescue -o $(TARGET) iso
	@if ! test -f $(PROG_BUILD_NUM); then echo 0 > $(PROG_BUILD_NUM); fi
	@echo $$(($$(cat $(PROG_BUILD_NUM)) + 1)) > $(PROG_BUILD_NUM)

-include $(DEPFILES)

%.o: %.cpp Makefile
	@$(CXX) $(CXXFLAGS) -MMD -MP -o $@ -c $<

%.o: %.s Makefile
	@$(AS) $(ASFLAGS) -o $@ $<

clean:
	@rm -f $(OBJFILES)
	@rm -f $(DEPFILES)
	@rm -f kernel.bin
	@rm -f iso/boot/kernel.bin
	@rm -f $(TARGET)
	@rm -f todo.txt
	@rm -f *.iso
	@rm -f *.bin
	@rm -f *.tar.gz
	@rm -f /tmp/miruslog

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME -e ERROR $$file; done; true

dist:
	@mkdir .tempdir
	@mkdir .tempdir/mirus
	@cp -r src .tempdir/mirus/src/
	@cp -r README.md .tempdir/mirus
	@cp -r LICENSE.md .tempdir/mirus
	@cp *.iso .tempdir/mirus
	@tar cvfz package.tar.gz .tempdir/mirus
	@rm -rf .tempdir

kvm:
	@$(QEMU) -cdrom mirus*.iso $(QEMUFLAGS)

no-iso: $(OBJFILES)
	@$(LD) $(LDFLAGS) -o kernel.bin ${OBJFILES}

debug: $(OBJFILES)
	@$(LD) $(LDFLAGS) -o kernel.bin ${OBJFILES}
	@cp kernel.bin iso/boot/kernel.bin
	@grub-mkrescue -o mirus.iso iso
