#ifndef HEADER_WTSWIDTH_3BD91CCF_2635_44D1_9D88_5114B59F8255_1_1
#define HEADER_WTSWIDTH_3BD91CCF_2635_44D1_9D88_5114B59F8255_1_1

/// @copyright Copyright (c) 2024 Steffen Illhardt,
///            Licensed under the MIT license
///            ( https://opensource.org/license/mit/ ).
/// @file      wtswidth.h
/// @brief     Interface for determining the number of code units that make up a
///            grapheme cluster and for counting the number of columns required
///            to represent a string in the Windows Terminal.
/// @version   1.1
/// @author    Steffen Illhardt
/// @date      2024
/// @pre       Requires compiler support for at least C11.
///
/// <br>
/// I don't claim any credits because the essential components of this code are
///  not my intellectual properties.
///
/// The C code of this library is substantially a copy of C++ code authored and
///  published by Microsoft under the MIT license. <br>
/// Copyright (c) Microsoft Corporation. All rights reserved. <br>
///  ( refer to https://github.com/microsoft/terminal/blob/main/LICENSE )
///
/// Furthermore, code to convert UTF-8 to a code point is taken from or derived
///  from Björn Höhrmann's "Flexible and Economical UTF-8 Decoder". <br>
/// Copyright (c) 2008-2010 Bjoern Hoehrmann <bjoern@hoehrmann.de> <br>
///  See https://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

// TODO: Replace "char" with "char8_t" when used more frequently.

#include <stddef.h>
#if defined(__cplusplus)
extern "C" {
#else
#  include <uchar.h>
#endif

/// @brief Count the number of UTF-8 code units (bytes) that the first grapheme
///        cluster in the string pointed to by `str` consists of.
///
/// @param str     Pointer to the first character of the UTF-8 encoded string.
/// @param len     Number of UTF-8 code units (bytes) in the string pointed to
///                by `str`. Terminating null not counted (if any).
/// @param pWidth  Pointer to an object that receives the number of columns
///                needed to represent the grapheme cluster in the Windows
///                Terminal. <br>
///                A NULL pointer can be passed to this parameter to indicate
///                that it shall not be used.
///
/// @return The number of UTF-8 code units (bytes) that the first grapheme
///         cluster in the string pointed to by `str` consists of.
int wts8clusterlen(const char *str, size_t len, int *pWidth);

/// @brief Count the number of UTF-16 code units (char16_t elements) that the
///        first grapheme cluster in the string pointed to by `str` consists of.
///
/// @param str     Pointer to the first character of the UTF-16 encoded string.
/// @param len     Number of UTF-16 code units (char16_t elements) in the string
///                pointed to by `str`. Terminating null not counted (if any).
/// @param pWidth  Pointer to an object that receives the number of columns
///                needed to represent the grapheme cluster in the Windows
///                Terminal. <br>
///                A NULL pointer can be passed to this parameter to indicate
///                that it shall not be used.
///
/// @return The number of UTF-16 code units (char16_t elements) that the first
///         grapheme cluster in the string pointed to by `str` consists of.
int wts16clusterlen(const char16_t *str, size_t len, int *pWidth);

/// @brief Count the number of columns needed to represent the UTF-8 encoded
///        string pointed to by `str` in the Windows Terminal.
///
/// @param str  Pointer to the first character of the UTF-8 encoded string to
///             be measured.
/// @param len  Number of UTF-8 code units (bytes) in the string pointed to
///             by `str`. Terminating null not counted (if any).
///
/// @return The number of column positions for the string pointed to by `str`.
int wts8width(const char *str, size_t len);

/// @brief Count the number of columns needed to represent the UTF-16 encoded
///        string pointed to by `str` in the Windows Terminal.
///
/// @param str  Pointer to the first character of the UTF-16 encoded string to
///             be measured.
/// @param len  Number of UTF-16 code units (char16_t elements) in the string
///             pointed to by `str`. Terminating null not counted (if any).
///
/// @return The number of column positions for the string pointed to by `str`.
int wts16width(const char16_t *str, size_t len);

#if defined __cplusplus
} // extern "C"
#endif

#endif // header guard
