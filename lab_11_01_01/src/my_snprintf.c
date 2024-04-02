#include <stdarg.h>
#include <stdio.h>
#include <math.h>

#include "my_snprintf.h"

static int putnum(char *buf, int maxlen, long num, int numsys);
static void num_to_symbols(long num, int numsys, int *out, int *size);
static int put_num_symbols(char *buf, char sign, int *out, int size, int maxlen);

int my_snprintf(char *buf, size_t maxlen, const char *format, ...)
{
    va_list params;
    va_start(params, format);
    int it = 0;
    char pch;
    char *pstr;
    int pint;
    unsigned pun;
    short psh;
    unsigned short punsh;
    for (; *format; ++it, ++format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'c')
            {
                pch = va_arg(params, int);
                if (buf && it < maxlen)
                    buf[it] = pch;
            }
            else if (*format == 's')
            {
                pstr = va_arg(params, char *);
                for (; *pstr; ++it, ++pstr)
                    if (buf && it < maxlen)
                        buf[it] = *pstr;
                --it;
            }
            else if (*format == 'd')
            {
                pint = va_arg(params, int);
                it += putnum(buf + it, (it < maxlen) ? maxlen - it : 0, pint, 10);
            }
            else if (*format == 'x')
            {
                pun = va_arg(params, int);
                it += putnum(buf + it, (it < maxlen) ? maxlen - it : 0, pun, 16);
            }
            else if (*format == 'h')
            {
                ++format;
                if (*format == 'd')
                {
                    psh = va_arg(params, int);
                    it += putnum(buf + it, (it < maxlen) ? maxlen - it : 0, psh, 10);
                }
                else if (*format == 'x')
                {
                    punsh = va_arg(params, int);
                    it += putnum(buf + it, (it < maxlen) ? maxlen - it : 0, punsh, 16);
                }
                else
                {
                    if (buf && it < maxlen)
                        buf[it] = '%';
                    --format;
                }
            }
            else if (buf && it < maxlen)
                buf[it] = '%';
        }
        else if (buf && it < maxlen)
            buf[it] = *format;
    }
    if (buf && maxlen)
        buf[(it < maxlen) ? it : maxlen - 1] = '\0';
    va_end(params);
    return it;
}

static int putnum(char *buf, int maxlen, long num, int numsys)
{
    int out[15];
    char sign = '+';
    if (num < 0)
    {
        sign = '-';
        num *= -1;
    }
    int size = 0;
    num_to_symbols(num, numsys, out, &size);
    return put_num_symbols(buf, sign, out, size, maxlen);
}

static void num_to_symbols(long num, int numsys, int *out, int *size)
{
    int add;
    for (; num; num /= numsys, ++(*size))
    {
        add = num % numsys;
        for (int i = *size; i; --i)
            out[i] = out[i - 1];
        out[0] = add;
    }
    if (*size == 0)
    {
        out[0] = 0;
        *size = 1;
    }
}

static int put_num_symbols(char *buf, char sign, int *out, int size, int maxlen)
{
    static char *alpha = "0123456789abcdef";
    int i = 0;
    if (sign == '-')
    {
        if (buf && maxlen > 0)
            *buf = sign;
        ++i;
    }
    for (; i - (sign == '-') < size; ++i)
        if (buf && i < maxlen)
            buf[i] = alpha[out[i - (sign == '-')]];
    return i - 1;
}
