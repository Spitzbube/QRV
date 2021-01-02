/**
 * \brief kprintf() and friends implementation.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <startup.h>

void dummy_print_char(int c) {}

static void (*print_char)(int) = dummy_print_char;

static void one_char(char c)
{
#ifdef CONFIG_MINIDRIVER
    mdriver_check();
#endif
    if (c == '\n')
        print_char('\r');
    print_char(c);
}

static void puts(const char *s)
{
    int i;
    paddr_t p = (paddr_t)s;

    if (p < CONFIG_KPRINTF_PTR_BOUND_LOW ||
        p > CONFIG_KPRINTF_PTR_BOUND_HIGH) {
        puts("(invptr)");
        return;
    }

    for (i = 0; i < CONFIG_KPRINTF_MAX_LIMIT; i++) {
        if (s[i] == 0)
            break;
        one_char(s[i]);
    }
}

static const char c[] = "0123456789abcdef";

static void vmsg(const char *fmt, va_list args)
{
    char *vs;
    uint64_t num;
    unsigned radix;
    int dig;
    char buf[64];
    bool was_modifier = 0;
    bool pad_with_zeros;

    for (; *fmt; ++fmt) {
        if (*fmt != '%' && !was_modifier) {
            one_char(*fmt);
            continue;
        }
        was_modifier = false;
        pad_with_zeros = CONFIG_KPRINTF_PAD_HEX_WITH_ZEROS;
        radix = dig = 0;
        switch (*++fmt) {
        case 'b':
            num = va_arg(args, unsigned);
            dig = sizeof(uint8_t) * 2;
            radix = 16;
            break;
        case 'w':
            num = va_arg(args, unsigned);
            dig = sizeof(uint16_t) * 2;
            radix = 16;
            break;
        case 'p':
        case 'P':
            num = va_arg(args, paddr_t);
            dig = sizeof(paddr_t) * 2;
            radix = 16;
            break;
        case 'x':
        case 'X':
            if (*(fmt - 1) == 'l') {
                if (*(fmt - 2) == 'l') {
                    num = va_arg(args, uint64_t);
                    dig = sizeof(uint64_t) * 2;
                } else {
                    num = va_arg(args, unsigned long);
                    dig = sizeof(unsigned long) * 2;
                }
            } else {
                num = va_arg(args, unsigned);
                dig = sizeof(unsigned) * 2;
            }
            radix = 16;
            break;
        case 'L':
            num = va_arg(args, uint64_t);
            dig = sizeof(uint64_t) * 2;
            radix = 16;
            break;
        case 'd':
        case 'i':
            num = va_arg(args, int);
            radix = 10;
            break;
        case 'u':
            num = va_arg(args, unsigned);
            radix = 10;
            break;
        case 's':
            vs = va_arg(args, char *);
            if (vs == NULL)
                puts("(NULL)");
            else
                puts(vs);
            continue;
        case 'c':
            num = va_arg(args, unsigned);
            one_char((char)num);
            continue;

        /* Modifiers */
        case '0':
            pad_with_zeros = was_modifier = true;
            --fmt;
            continue;
        case '#':
            one_char('0');
            one_char('x');
            was_modifier = true;
            --fmt;
            continue;
        case 'l':
            was_modifier = true;
            --fmt;
            continue;

        default:
            one_char(*fmt);
            continue;
        }
        vs = &buf[sizeof(buf)];

        *--vs = '\0';
        do {
            *--vs = c[num % radix];
            num /= radix;
        } while (num);
        for (dig -= &buf[sizeof(buf) - 1] - vs; dig > 0; --dig) {
            if (pad_with_zeros)
                one_char('0');
        }
        while (*vs) {
            one_char(*vs++);
        }
    }
}

void kprintf(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vmsg(fmt, args);
    va_end(args);
}

static char *string_ptr;

static void string_print_char(int c)
{
    *string_ptr++ = c;
}


void ksprintf(char *buff, const char *fmt, ...)
{
    va_list args;
    void (*old_print_char)(int) = print_char;

    print_char = string_print_char;
    string_ptr = buff;
    va_start(args, fmt);
    vmsg(fmt, args);
    va_end(args);
    *string_ptr = '\0';
    print_char = old_print_char;
}

void crash(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vmsg(fmt, args);
    va_end(args);
    for (;;) ;
}

void set_print_char(void (*prt)(int))
{
    print_char = prt;
}

void (*get_print_char(void))(int) {
    return print_char;
}
