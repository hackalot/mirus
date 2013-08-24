BUILD_DATE = $(shell date +'%Y%m%d')
BUILD_MAJOR = 0
BUILD_MINOR = 1
BUILD_POSTFIX = dev
CODENAME = nova

M_ARCH = i386

PROJDIRS := source/kernel source/asm source/include
OUTDIR   := binary
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.cpp")
ASMFILES := $(shell find $(PROJDIRS) -type f -name "*.asm")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.hpp")
DEPFILES := $(shell find $(PROJDIRS) -type f -name "*.d")

OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))
OBJFILES += $(patsubst %.asm,%.o,$(ASMFILES))

AUXFILES := Makefile
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES) $(ASMFILES)

CXX = clang++
CXXWARNINGS = -Wall -Wextra -Wno-unused-parameter
DEBUG = -D_DEBUG_ON
CXXFLAGS := $(CXXWARNINGS) -fno-builtin -fno-exceptions -ffreestanding -std=c++11 -Isource/include -Isource/library -m32 -O0
CXXFLAGS += -DBUILD_DATE=$(BUILD_DATE)
CXXFLAGS += -DBUILD_MAJOR=$(BUILD_MAJOR) -DBUILD_MINOR=$(BUILD_MINOR)
CXXFLAGS += -DBUILD_POSTFIX="$(BUILD_POSTFIX)"
CXXFLAGS += $(DEBUG)

LD = ld
LDFLAGS := -T build/linker.ld -melf_i386

AS = nasm
ASFLAGS = -f elf

QEMU = qemu-system-i386
QEMUFLAGS = -serial file:/tmp/miruslog

.PHONY: all clean dist todolist dist kvm debug

TARGET = mirus.iso

ALL: $(OBJFILES)
	@mkdir binary
	@$(LD) $(LDFLAGS) -o binary/kernel.bin ${OBJFILES}
	@cp binary/kernel.bin iso/boot/kernel.bin
	@grub2-mkrescue -o binary/$(TARGET) iso

-include $(DEPFILES)

%.o: %.cpp Makefile
	@$(CXX) $(CXXFLAGS) -MMD -MP -o $@ -c $<

%.o: %.asm Makefile
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
	@rm -rf binary

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
	@$(QEMU) -cdrom binary/mirus.iso $(QEMUFLAGS)

no-iso: $(OBJFILES)
	@mkdir binary
	@$(LD) $(LDFLAGS) -o binary/kernel.bin ${OBJFILES}
