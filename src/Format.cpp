#include "Streams/Format.hpp"

using namespace Streams::Impl;

bool Format::format(write_f write, void *ctx, Impl::Decimal<uint8_t> dec) {
    uint8_t v = dec.value;
    if (v > 99) {
        if (!write(ctx, '0' + (v / 100))) return false;
        v %= 100;
        if (!write(ctx, '0' + (v / 10))) return false;
        v %= 10;
    } else if (v > 9) {
        if (!write(ctx, '0' + (v / 10))) return false;
        v %= 10;
    }
    return write(ctx, '0' + v);
}

bool Format::format(write_f write, void *ctx, Impl::Decimal<int8_t> v) {
    if (v.value < 0) {
        if (!write(ctx, '-')) return false;
        return format(write, ctx, dec(uint8_t(-v.value)));
    } else {
        return format(write, ctx, dec(uint8_t(v.value)));
    }
}

bool Format::format(write_f write, void *ctx, Impl::Decimal<uint16_t> v) {
    const uint16_t n = v.value;

    uint8_t d4, d3, d2, d1, q;
    uint16_t d0;

    d0 = n       & 0xF;
    d1 = (n>>4)  & 0xF;
    d2 = (n>>8)  & 0xF;
    d3 = (n>>12);

    d0 = 6*(d3 + d2 + d1) + d0;
    q = d0 / 10;
    d0 = d0 % 10;

    d1 = q + 9*d3 + 5*d2 + d1;
    if (d1 != 0) {
        q = d1 / 10;
        d1 = d1 % 10;

        d2 = q + 2*d2;
        if ((d2 != 0) || (d3 != 0)) {
            q = d2 / 10;
            d2 = d2 % 10;

            d3 = q + 4*d3;
            if (d3 != 0) {
                q = d3 / 10;
                d3 = d3 % 10;

                d4 = q;

                if (d4 != 0) {
                    if (!write(ctx, d4 + '0' )) return false;
                }
                if (!write(ctx, d3 + '0' )) return false;
            }
            if (!write(ctx, d2 + '0' )) return false;
        }
        if (!write(ctx, d1 + '0' )) return false;
    }
    return write(ctx, d0 + '0' );
}

bool Format::format(write_f write, void *ctx, Impl::Decimal<int16_t> v) {
    if (v.value < 0) {
        if (!write(ctx, '-')) return false;
        return format(write, ctx, dec(uint16_t(-v.value)));
    } else {
        return format(write, ctx, dec(uint16_t(v.value)));
    }
}

bool Format::format(write_f write, void *ctx, Impl::Decimal<uint32_t> v) {
    const uint32_t n = v.value;

    const uint8_t n0 = n & 0x1F;
    const uint8_t n1 = (n >> 5) & 0xF;
    const uint8_t n2 = (n >> 9) & 0xF;
    const uint8_t n3 = (n >> 13) & 0xF;
    const uint8_t n4 = (n >> 17) & 0xF;
    const uint8_t n5 = (n >> 21) & 0xF;
    const uint8_t n6 = (n >> 25) & 0xF;
    const uint8_t n7 = (n >> 29) & 0x7;

    uint8_t q;

    uint8_t d0 = 2 * (n7 + n6 + n5 + n4 + n3 + n2 + n1) + n0;
    q = d0 / 10;
    d0 = d0 % 10;

    uint16_t d1 = q + n7 + 5 * n5 + 3 * (n6 + n1) + 7 * n4 + 9 * n3 + n2;
    q = d1 / 10;
    d1 = d1 % 10;

    uint16_t d2 = q + 9 * n7 + 4 * n6 + n5 + n3 + 5 * n2;
    q = d2 / 10;
    d2 = d2 % 10;

    uint16_t d3 = q + 4 * n6 + 7 * n5 + n4 + 8 * n3;
    q = d3 / 10;
    d3 = d3 % 10;

    uint16_t d4 = q + 7 * n7 + 3 * n4 + 5 * n6 + 9 * n5;
    q = d4 / 10;
    d4 = d4 % 10;

    uint8_t d5 = q + 8 * n7 + 5 * n6 + n4;
    q = d5 / 10;
    d5 = d5 % 10;

    uint8_t d6 = q + 6 * n7 + 3 * n6 + 2 * n5;
    q = d6 / 10;
    d6 = d6 % 10;

    uint8_t d7 = q + 3 * n7 + 3 * n6;
    q = d7 / 10;
    d7 = d7 % 10;

    uint8_t d8 = q + 5 * n7;
    q = d8 / 10;
    d8 = d8 % 10;

    bool started = false;
    if (q != 0) {
        if (!write (ctx, q + '0')) return false;
        started = true;
    }
    if (started || d8 != 0) {
        if (!write (ctx, d8 + '0')) return false;
        started = true;
    }
    if (started || d7 != 0) {
        if (!write (ctx, d7 + '0')) return false;
        started = true;
    }
    if (started || d6 != 0) {
        if (!write (ctx, d6 + '0')) return false;
        started = true;
    }
    if (started || d5 != 0) {
        if (!write (ctx, d5 + '0')) return false;
        started = true;
    }
    if (started || d4 != 0) {
        if (!write (ctx, d4 + '0')) return false;
        started = true;
    }
    if (started || d3 != 0) {
        if (!write (ctx, d3 + '0')) return false;
        started = true;
    }
    if (started || d2 != 0) {
        if (!write (ctx, d2 + '0')) return false;
        started = true;
    }
    if (started || d1 != 0) {
        if (!write (ctx, d1 + '0')) return false;
        started = true;
    }
    return write(ctx, d0 + '0');
}

bool Format::format(write_f write, void *ctx, Impl::Decimal<int32_t> v) {
    if (v.value < 0) {
        if (!write(ctx, '-')) return false;
        return format(write, ctx, dec(uint32_t(-v.value)));
    } else {
        return format(write, ctx, dec(uint32_t(v.value)));
    }
}
