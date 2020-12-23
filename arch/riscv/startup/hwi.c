/**
 * \brief Hardware item routines.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <kernel/startup.h>

void hwi_default()
{
    hwi_tag *tag;

    tag = hwi_alloc_item(HWI_TAG_INFO(group), HWI_ITEM_ROOT_HW, HWI_NULL_OFF);

    hwi_alloc_item(HWI_TAG_INFO(bus), HWI_ITEM_BUS_UNKNOWN, hwi_tag2off(tag));
}

char *__hwi_find_string(unsigned off)
{
    char *p = lsp.strings.p->data;
    return p + off;
}

void *__hwi_base()
{
    return lsp.hwinfo.p->data;
}


static unsigned offset = 0;
static unsigned last_item = 0;

static void align_tag(unsigned align)
{
    unsigned grow;

    grow = ROUND(offset, align) - offset;
    if (grow != 0) {
        hwi_alloc_tag(HWI_TAG_INFO(pad));
    }
}

void *hwi_alloc_tag(const char *name, unsigned size, unsigned align)
{
    uint8_t *p;
    hwi_tag *tag;
    unsigned name_off;

    align_tag(align);
    name_off = add_string(name);
    p = grow_syspage_section(&lsp.hwinfo, size);
    tag = (hwi_tag *) (p + last_item);
    tag->item.itemsize += size / 4;
    tag = (hwi_tag *) (p + offset);
    tag->prefix.size = size / 4;
    tag->prefix.name = name_off;
    offset += size;
    return tag;
}

void *hwi_alloc_item(const char *name, unsigned size, unsigned align,
                     const char *itemname, unsigned owner)
{
    hwi_tag *tag;
    unsigned saved_in;

    /* Do add_string() up front so that the tag pointer doesn't move due
     * to shifting section sizes.
     */
    saved_in = add_string(itemname);
    align_tag(align);
    last_item = offset;
    tag = hwi_alloc_tag(name, size, align);
    tag->item.itemname = saved_in;
    tag->item.owner = owner;
    if (owner != HWI_NULL_OFF) {
        hwi_tag *owner_tag;

        owner_tag = hwi_off2tag(owner);
        owner_tag->item.kids++;
    }
    return tag;
}

void *hwi_grow_tag(unsigned offset, unsigned size)
{
    uint8_t *p;
    hwi_tag *tag;

    p = grow_syspage_section(&lsp.hwinfo, size);
    tag = (hwi_tag *) (p + last_item);
    tag->item.itemsize += size / 4;
    tag = (hwi_tag *) (p + offset);
    tag->prefix.size += size / 4;
    offset += size;
    return tag;
}
