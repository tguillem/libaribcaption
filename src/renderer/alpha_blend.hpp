/*
 * Copyright (C) 2021 magicxqq <xqq@xqq.im>. All rights reserved.
 *
 * This file is part of libaribcaption.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef ARIBCAPTION_ALPHA_BLEND_HPP
#define ARIBCAPTION_ALPHA_BLEND_HPP

#include <cstdint>
#include "color.hpp"
#include "base/always_inline.hpp"

namespace aribcaption {
namespace alphablend {

// Fast divide by 255 algorithm
ALWAYS_INLINE uint32_t Div255(uint32_t x) {
    return (x + 1 + (x >> 8)) >> 8;
}

// Alpha blend
ALWAYS_INLINE ColorRGBA BlendColor(ColorRGBA bg_color, ColorRGBA fg_color) {
    ColorRGBA color;

    // Calculate blended RGB channel
    // alpha is within range [0, 1] in the formula
    // out_rgb = foreground_rgb * foreground_alpha + background_rgb * (1 - foreground_alpha)
    color.r = Div255((uint32_t)fg_color.r * fg_color.a) + Div255((uint32_t)bg_color.r * (255 - fg_color.a));
    color.g = Div255((uint32_t)fg_color.g * fg_color.a) + Div255((uint32_t)bg_color.g * (255 - fg_color.a));
    color.b = Div255((uint32_t)fg_color.b * fg_color.a) + Div255((uint32_t)bg_color.b * (255 - fg_color.a));

    // Calculate blended alpha channel
    // alpha is within range [0, 1] in the formula
    // out_alpha = foreground_alpha + background_alpha * (1 - foreground_alpha)
    color.a = (uint32_t)fg_color.a + Div255((uint32_t)bg_color.a * (255 - fg_color.a));

    return color;
}

}  // namespace alphablend
}  // namespace aribcaption

#endif  // ARIBCAPTION_ALPHA_BLEND_HPP
