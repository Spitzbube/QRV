/**
 * \file mkasmoff.c
 *
 * Read the 'infile' ELF object file (created with the macros in mkasmoff.h)
 * and create an assembler include file called 'outfile' containing the
 * appropriate macro definitions.
 *
 * \copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * \license QNX NCEULA 1.01
 *          http://www.qnx.com/legal/licensing/dev_license/eula/nceula1_01.html
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <elf.h>

#ifndef ENDIAN
#if defined(__LITTLEENDIAN__) || defined(__X86__)
#define ENDIAN (0)
#elif defined(__BIGENDIAN__) || defined(__sparc)
#define ENDIAN (1)
#else
#error not configured for system
#endif
#endif

Elf32_Ehdr ehdr;
Elf32_Shdr *elf_shdr;
char **elf_shdata;
unsigned shnum;

char tmp_name[9];

struct symbol {
    struct symbol *next;
    unsigned line;
    unsigned sect;
    unsigned off;
    char name[1];               /* variable sized */
};

int fd;
struct symbol *list;
char *comment_format;
char *value_format;

struct {
    unsigned machine;
    unsigned big_endian;
    void (*build_symbols)(void);
    void (*get_data)(struct symbol *, unsigned, char *);
} info;

static void add_symbol(unsigned sect, unsigned off, char *name)
{
    char *p;
    unsigned line = 0;
    struct symbol *sym;
    struct symbol **owner;

#define COMMENT_PREFIX	"comment"
#define VALUE_PREFIX	"value"

    if ((p = strstr(name, COMMENT_PREFIX)) != NULL) {
        p += sizeof(COMMENT_PREFIX) - 1;
        line = strtoul(p, &p, 10);
        p += 1;                 /* skip the trailing "_" */
    } else if ((p = strstr(name, VALUE_PREFIX)) != NULL) {
        p += sizeof(VALUE_PREFIX) - 1;
        line = strtoul(p, &p, 10);
        p += 4;                 /* skip the trailing "____" */
    }
    if (p != NULL) {
        sym = malloc(sizeof(*sym) + strlen(p));
        strcpy(sym->name, p);
        sym->sect = sect;
        sym->off = off;
        sym->line = line;
        /* add in order of increasing line number */
        owner = &list;
        for (;;) {
            if (*owner == NULL || (*owner)->line > line)
                break;
            owner = &(*owner)->next;
        }
        sym->next = *owner;
        *owner = sym;
    }
}

static unsigned Normal16(unsigned val)
{
    if (info.big_endian == ENDIAN)
        return val;
    return ((val >> 8) & 0xff) | ((val << 8) & 0xff00);
}

static unsigned Normal32(unsigned val)
{
    if (info.big_endian == ENDIAN)
        return val;

    return ((val >> 24) & 0x000000ff)
            | ((val >> 8) & 0x0000ff00)
            | ((val << 8) & 0x00ff0000)
            | ((val << 24) & 0xff000000);
}



/**
 * \brief TODO
 */
static void *elf_load_section(unsigned i)
{
    unsigned long off;
    unsigned long size;

    if (elf_shdata[i] == NULL) {
        size = Normal32(elf_shdr[i].sh_size);
        if (Normal32(elf_shdr[i].sh_type) == SHT_NOBITS) {
            elf_shdata[i] = calloc(1, size);
            if (elf_shdata[i] == NULL) {
                fprintf(stderr, "No memory for section data\n");
                exit(1);
            }
        } else {
            off = Normal32(elf_shdr[i].sh_offset);
            if (lseek(fd, off, SEEK_SET) != off) {
                fprintf(stderr, "Could not seek to section %u data\n", i);
                exit(1);
            }
            elf_shdata[i] = malloc(size);
            if (elf_shdata[i] == NULL) {
                fprintf(stderr, "No memory for section data\n");
                exit(1);
            }
            if (read(fd, elf_shdata[i], size) != size) {
                fprintf(stderr, "Could not read section data\n");
                exit(1);
            }
        }
    }
    return elf_shdata[i];
}

static void elf_build_symbols()
{
    unsigned i;

    for (i = 0; i < shnum; ++i) {
        Elf32_Shdr *shdr = &elf_shdr[i];

        if (Normal32(shdr->sh_type) == SHT_SYMTAB) {
            Elf32_Sym *syms = elf_load_section(i);
            char *strings = elf_load_section(Normal32(shdr->sh_link));
            int num = Normal32(shdr->sh_size) / sizeof(*syms);
            int i;

            for (i = 0; i < num; i++) {
                Elf32_Sym *sym = &syms[i];

                if (Normal16(sym->st_shndx) != SHN_UNDEF) {
                    char *name = strings + Normal32(sym->st_name);

                    if (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT) {
                        add_symbol(Normal16(sym->st_shndx), Normal32(sym->st_value), name);
                    }
                }
            }
        }
    }
}

static void elf_get_data(struct symbol *sym, unsigned size, char *buff)
{
    char *p;

    p = (char *) elf_load_section(sym->sect) + sym->off;

    if (size == 0)
        size = strlen(p) + 1;
    memcpy(buff, p, size);
}

static void comment(char *comment)
{
    printf(comment_format, comment);
}

static void value(char *name, unsigned long value)
{
    printf(value_format, name, value);
}

struct format {
    char *name;
    char *comment;
    char *value;
};

const static struct format formats[] = {
    { "masm", "; %s\n", "%s = 0%8.8lxh\n" },
    { "gas", "# %s\n", ".set %s, 0x%8.8lx\n" },
    { "cpp", "/* %s */\n", "#define %s 0x%8.8lx\n" },
    { "c6x", "; %s\n", "%s .set 0%8.8lxh\n" },
    { NULL, NULL, NULL },
};

int main(int argc, char *argv[])
{
    char buff[256];
    unsigned long off;
    unsigned size;
    int n;
    int i;
    char *format = "";

    while ((n = getopt(argc, argv, "f:")) != -1) {
        switch (n) {
        case 'f':
            format = optarg;
            break;
        }
    }
    argv += optind;
    if (argv[0] == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: mkasmoff [-f <format> ] <infile> <outfile>\n");
        return 1;
    }
    fd = open(argv[0], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Can not open '%s': %s\n", argv[0], strerror(errno));
        return 1;
    }
    if (freopen(argv[1], "w", stdout) == NULL) {
        fprintf(stderr, "Can not open '%s': %s\n", argv[1], strerror(errno));
        return 1;
    }

    lseek(fd, 0, SEEK_SET);
    if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr)) {
        fprintf(stderr, "Could not read ELF header\n");
        return 1;
    }

    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "Doesn't look like an ELF file\n");
        return 1;
    }

    switch (ehdr.e_ident[EI_DATA]) {
        case ELFDATA2MSB:
            info.big_endian = 1;
            break;
    }

    switch (Normal16(ehdr.e_type)) {
        case ET_REL:
            break;
        default:
            fprintf(stderr, "Don't understand ELF type %d\n", Normal16(ehdr.e_type));
            return 1;
    }

    if (Normal16(ehdr.e_shentsize) != sizeof(Elf32_Shdr)) {
        fprintf(stderr, "Wrong section entry size\n");
        return 1;
    }

    shnum = Normal16(ehdr.e_shnum);
    size = shnum * sizeof(Elf32_Shdr);
    elf_shdr = malloc(size);
    if (elf_shdr == NULL) {
        fprintf(stderr, "No memory for section header\n");
        return 1;
    }

    off = Normal32(ehdr.e_shoff);
    if (lseek(fd, off, SEEK_SET) != off) {
        fprintf(stderr, "Seek for section header failed\n");
        return 1;
    }

    if (read(fd, elf_shdr, size) != size) {
        fprintf(stderr, "Could not read section header table\n");
        return 1;
    }

    elf_shdata = malloc(shnum * sizeof(*elf_shdata));
    if (elf_shdata == NULL) {
        fprintf(stderr, "No memory for section data pointers\n");
        return 1;
    }

    memset(elf_shdata, 0, shnum * sizeof(*elf_shdata));
    info.machine = Normal16(ehdr.e_machine);
    info.get_data = elf_get_data;
    info.build_symbols = elf_build_symbols;

    if (format[0] == '\0') {
        switch (info.machine) {
        case EM_386:
            format = "nasm";
            break;
        case EM_PPC:
        case EM_SH:
            format = "gas";
            break;
        case EM_MIPS:
        case EM_ARM:
            format = "cpp";
            break;
        default:
            fprintf(stderr, "Don't know machine type %d\n", ehdr.e_machine);
            return 1;
        }
    }
    i = 0;
    for (;;) {
        if (formats[i].name == NULL) {
            fprintf(stderr, "Unrecognized output format '%s'\n", format);
            return 1;
        }
        if (strcmp(formats[i].name, format) == 0)
            break;
        ++i;
    }
    comment_format = formats[i].comment;
    value_format = formats[i].value;

    comment(" This file was produced by:");
    sprintf(buff, "    mkasmoff -f%s %s %s", format, argv[0], argv[1]);
    comment(buff);
    sprintf(buff, "    (machine type is %d)", info.machine);
    comment(buff);
    comment("");

    info.build_symbols();
    while (list != NULL) {
        if (list->name[0] == '\0') {
            info.get_data(list, 0, buff);
            comment("");
            comment(buff);
            comment("");
        } else {
            unsigned char buff[4];

            info.get_data(list, 4, buff);
            if (info.big_endian) {
                value(list->name, (unsigned long) buff[3]
                      + ((unsigned long) buff[2] << 8)
                      + ((unsigned long) buff[1] << 16)
                      + ((unsigned long) buff[0] << 24));
            } else {
                value(list->name, (unsigned long) buff[0]
                      + ((unsigned long) buff[1] << 8)
                      + ((unsigned long) buff[2] << 16)
                      + ((unsigned long) buff[3] << 24));
            }
        }
        list = list->next;
    }
    return 0;
}
