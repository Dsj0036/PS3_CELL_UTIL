#pragma once
#include "..\types.h"


typedef struct {
    uint8_t e_ident[16];              /* ELF identification */
    uint16_t e_type;                  /* object file type */
    uint16_t e_machine;               /* machine type */
    uint32_t e_version;               /* object file version */
    uint64_t e_entry;                 /* entry point address */
    uint64_t e_phoff;                 /* program header offset */
    uint64_t e_shoff;                 /* section header offset */
    uint32_t e_flags;                 /* processor-specific flags */
    uint16_t e_ehsize;                /* ELF header size */
    uint16_t e_phentsize;             /* size of program header entry */
    uint16_t e_phnum;                 /* number of program header entries */
    uint16_t e_shentsize;             /* size of section header entry */
    uint16_t e_shnum;                 /* number of section header entries */
    uint16_t e_shstrndx;              /* section name string table index */
} __attribute__((packed)) ELF;