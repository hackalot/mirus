PROG_BUILD_NUM=build/.build_number
BUILD_DATE = $(shell date +'%Y%m%d')
BUILD_NUM = $(shell cat $(PROG_BUILD_NUM))
BUILD_MAJOR = 0
BUILD_MINOR = 0

PROJDIRS := src/kernel src/asm src/include
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.cpp")
ASMFILES := $(shell find $(PROJDIRS) -type f -name "*.s")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.hpp")
DEPFILES := $(shell find $(PROJDIRS) -type f -name "*.d")

OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))
OBJFILES += $(patsubst %.s,%.o,$(ASMFILES))

AUXFILES := Makefile Readme.md License.md
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES) $(ASMFILES)

CXX = clang++
CXXWARNINGS = -Wall -Wextra -pedantic
CXXFLAGS := $(CXXWARNINGS) -fno-builtin -fno-exceptions -ffreestanding -std=c++11 -Isrc/include -Isrc/mstl
CXXFLAGS += -DBUILD_DATE=$(BUILD_DATE) -DBUILD_NUM=$(BUILD_NUM)
CXXFLAGS += -DBUILD_MAJOR=$(BUILD_MAJOR) -DBUILD_MINOR=$(BUILD_MINOR)

LD = ld
LDFLAGS := -T build/linker.ld

AS = nasm
ASFLAGS = -f elf

.PHONY: all clean dist todolist dist

TARGET = test.iso

ALL: $(OBJFILES)
	@$(LD) $(LDFLAGS) -o kernel.bin ${OBJFILES}
	@cp kernel.bin iso/boot/kernel.bin
	@grub2-mkrescue -o $(TARGET) iso
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

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true

dist:
	@mkdir .tempdir
	@cp -r src .tempdir/src/
	@cp -r Readme.md .tempdir/
	@cp -r License.md .tempdir/
	@cp $(TARGET) .tempdir/
	@tar cvfz package.tar.gz .tempdir
	@rm -rf .tempdir