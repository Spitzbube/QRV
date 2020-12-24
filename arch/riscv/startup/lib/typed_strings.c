/**
 * \brief Typed strings support.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <kernel/startup.h>

int find_typed_string(int type_index)
{
    char *p = lsp.typed_strings.p->data;
    unsigned i;
    unsigned type;

    i = 0;
    for (;;) {
        type = *(uint32_t *) & p[i];
        if (type == type_index)
            return i;
        if (type == _CS_NONE)
            return -1;
        i += sizeof(uint32_t);
        i += strlen(&p[i]) + 1;
        i = ROUND(i, sizeof(uint32_t));
    }
}

int del_typed_string(int type_index)
{
    char *p = lsp.typed_strings.p->data;
    int i;
    int j;
    int end;

    i = find_typed_string(type_index);
    if (i < 0)
        return 0;
    j = i + strlen(&p[i + sizeof(uint32_t)]) + 1;
    j = ROUND(j, sizeof(uint32_t));
    end = find_typed_string(_CS_NONE);
    while (j < end) {
        p[i++] = p[j++];
    }
    while (i < j) {
        p[i++] = 0;
    }
    return 1;
}

unsigned add_typed_string(int type_index, const char *name)
{
    char *p = lsp.typed_strings.p->data;
    unsigned i;
    unsigned len;
    unsigned spare;
    unsigned need;

    del_typed_string(type_index);
    i = find_typed_string(_CS_NONE);
    len = strlen(name) + 1;
    len = ROUND(len, sizeof(uint32_t));
    need = len + 2 * sizeof(uint32_t);
    spare = lsp.typed_strings.size - i;
    if (spare < need) {
        grow_syspage_section(&lsp.typed_strings, need - spare);
    }
    *(uint32_t *) & p[i] = type_index;
    strcpy(&p[i + sizeof(uint32_t)], name);
    return i;
}

unsigned add_string(const char *name)
{
    char *p = lsp.strings.p->data;
    char *str;
    unsigned i, len, spare;

    i = 0;
    for (;;) {
        str = &p[i];
        if (*str == '\0')
            break;
        if (strcmp(name, str) == 0)
            return i;
        i += strlen(str) + 1;
    }
    len = strlen(name) + 2;
    spare = lsp.strings.size - i;
    if (len > spare) {
        grow_syspage_section(&lsp.strings, len - (lsp.strings.size - i));
    }
    strcpy(str, name);
    return i;
}

