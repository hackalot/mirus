// Copyright 2013 Mirus Project

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// elf.hpp - ELF loader
// 			 All information comes from the ELF specification from Oracle,
//			 See: http://docs.oracle.com/cd/E23824_01/html/819-0690/chapter6-46512.html
//			 TODO: impliment ELF64 when we get to that point
//

namespace mirus 
{
	namespace system
	{
		//
		// ELF magic structure
		//
		const unsigned char ELFMAG0   = 0x7f;
		const unsigned char ELFMAG1   = 'E';
		const unsigned char ELFMAG2   = 'L';
		const unsigned char ELFMAG3   = 'F';
		const unsigned char EI_NIDENT = 16;

		//
		// ELF data types
		//
		typedef uint32_t Elf32_Addr;
		typedef uint32_t Elf32_Half;
		typedef uint32_t Elf32_Off;
		typedef uint32_t Elf32_Sword;
		typedef uint16_t Elf32_Word;

		//
		// ELF header
		//
		typedef struct 
		{
			unsigned char 		e_ident[EI_NIDENT];
			Elf32_Half    		e_type;
			Elf32_Half    		e_machine;
			Elf32_Word    		e_version;
			Elf32_Addr    		e_entry;
			Elf32_Off     		e_phoff;
			Elf32_Off     		e_shoff;
			Elf32_Word    		e_flags;
			Elf32_Half    		e_ehsize;
			Elf32_Half    		e_phentsize;
			Elf32_Half    		e_phnum;
			Elf32_Half    		e_shentsize;
			Elf32_Half    		e_shnum;
			Elf32_Half    		e_shstrndx;
		} Elf32_Header;

		//
		// ELF program header
		//
		typedef struct 
		{
			Elf32_Word p_type;
			Elf32_Off  p_offset;
			Elf32_Addr p_vaddr;
			Elf32_Addr p_paddr;
			Elf32_Word p_filesz;
			Elf32_Word p_flags;
			Elf32_Word p_align;
		} Elf32_Phdr;

		//
		// ELF section header
		//
		typedef struct
		{
			Elf32_Word 			sh_name;
			Elf32_Word 			sh_type;
			Elf32_Word 			sh_flags;
			Elf32_Addr 			sh_addr;
			Elf32_Off 			sh_offset;
			Elf32_Word 			sh_size;
			Elf32_Word 			sh_link;
			Elf32_Word 			sh_info;
			Elf32_Word 			sh_addralign;
			Elf32_Word 			sh_entsize;
		} Elf32_Shdr;

		//
		// ELF auxv
		//
		typedef struct
		{
			uint32_t			id;
			uintptr_t			ptr;
		} Elf32_auxv;

		//
		// ELF type - used for the e_type field of the header
		//
		enum class Elf_Type : Elf32_Half
		{
			ET_NONE				= 0,			// No file type
			ET_REL				= 1,			// Relocatable file
			ET_EXEC				= 2,			// Executable file
			ET_DYN				= 3,			// Shared object file
			ET_CORE				= 4,			// Core file
			ET_LOPROC			= 0xff00,		// Processor specific
			ET_HIPROC			= 0xffff		// Processor specific
		};

		//
		// ELF machine - used for the e_machine field of the header
		//
		enum class Elf_Machine : Elf32_Half
		{
			EM_NONE 			= 0,
			EM_SPARC 			= 2,
			EM_386 				= 3,
			EM_SPARC32PLUS 		= 18,
			EM_SPARCV9 			= 43,
			EM_AMD64 			= 62
		};

		//
		// ELF Version - used for the e_version field of the header
		//
		enum class Elf_Version : Elf32_Word
		{
			EV_NONE				= 0,			// Invalid version
			EV_CURRENT			= 1 			// Current version (>= 1)
		};

		//
		// ELF Flags - used for the e_flags field of the header
		//
		#define EF_SPARC_EXT_MASK	 0xffff00		// Vendor execption mask
		#define EF_SPARC_32PLUS		 0x000100		// Generic V8+ features
		#define EF_SPARC_SUN_US1	 0x000200		// Sun UltraSPARC 1 extensions
		#define EF_SPARC_HALR1		 0x000400		// HAL R1 extensions
		#define EF_SPARC_SUN_US4	 0x000800		// Sun UltraSPARC 3 extensions
		#define EF_SPARCV9MM		 0x3			// Mask for memory model
		#define EF_SPARCV9_TSO		 0x0			// Total store ordering
		#define EF_SPARCV9_PSO		 0x1			// Partial store ordering
		#define EF_SPARCV9_RMO		 0x2 			// Relaxed memory ordering
		//
		// ELF Program Flags - used for the p_flags field of the program header
		//
		#define PT_NULL				 0 				// Unused
		#define PT_LOAD				 1 				// Loadable segment
		#define PT_DYNAMIC 			 2     			// Dynamic linking information
		#define PT_INTERP			 3 				// Interperter
		#define PT_NOTE 			 4 				// Auxillary information
		#define PT_SHLIB 			 5				// Reserved
		#define PT_PHDR 			 6 				// Back reference to header table
		#define PT_LOPROC			 0x70000000
		#define PT_HIPROC			 0x7FFFFFFF

		//
		// ELF Section Header Type - used for sh_type
		//
		enum class Elf_ShType : Elf32_Word
		{
			SHT_NONE			= 0,
			SHT_PROGBITS 		= 1,
			SHT_SYMTAB			= 2,
			SHT_STRTAB			= 3,
			SHT_NOBITS			= 4
		};

		//
		// exec - Load a static elf executable
		//
		int exec(uint32_t address);
	} // !namespace
} // !namespace