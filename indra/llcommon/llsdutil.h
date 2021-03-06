/** 
 * @file llsdutil.h
 * @author Phoenix
 * @date 2006-05-24
 * @brief Utility classes, functions, etc, for using structured data.
 *
 * Copyright (c) 2006-2007, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlife.com/developers/opensource/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at http://secondlife.com/developers/opensource/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 */

#ifndef LL_LLSDUTIL_H
#define LL_LLSDUTIL_H

#include "llsd.h"
#include "../llmath/v3math.h"
#include "../llmath/v4math.h"
#include "../llmath/v3dmath.h"
#include "../llmath/v2math.h"
#include "../llmath/llquaternion.h"
#include "../llmath/v4color.h"
#include "../llprimitive/lltextureanim.h"

// vector3
LLSD ll_sd_from_vector3(const LLVector3& vec);
LLVector3 ll_vector3_from_sd(const LLSD& sd, S32 start_index = 0);

// vector4
LLSD ll_sd_from_vector4(const LLVector4& vec);
LLVector4 ll_vector4_from_sd(const LLSD& sd, S32 start_index = 0);

// vector3d (double)
LLSD ll_sd_from_vector3d(const LLVector3d& vec);
LLVector3d ll_vector3d_from_sd(const LLSD& sd, S32 start_index = 0);

// vector2
LLSD ll_sd_from_vector2(const LLVector2& vec);
LLVector2 ll_vector2_from_sd(const LLSD& sd);

// Quaternion
LLSD ll_sd_from_quaternion(const LLQuaternion& quat);
LLQuaternion ll_quaternion_from_sd(const LLSD& sd);

// color4
LLSD ll_sd_from_color4(const LLColor4& c);
LLColor4 ll_color4_from_sd(const LLSD& sd);

// U32
LLSD ll_sd_from_U32(const U32);
U32 ll_U32_from_sd(const LLSD& sd);

// U64
LLSD ll_sd_from_U64(const U64);
U64 ll_U64_from_sd(const LLSD& sd);

// IP Address
LLSD ll_sd_from_ipaddr(const U32);
U32 ll_ipaddr_from_sd(const LLSD& sd);

// Binary to string
LLSD ll_string_from_binary(const LLSD& sd);

//String to binary
LLSD ll_binary_from_string(const LLSD& sd);

// Serializes sd to static buffer and returns pointer, useful for gdb debugging.
char* ll_print_sd(const LLSD& sd);

// Serializes sd to static buffer and returns pointer, using "pretty printing" mode.
char* ll_pretty_print_sd(const LLSD& sd);

#endif // LL_LLSDUTIL_H
