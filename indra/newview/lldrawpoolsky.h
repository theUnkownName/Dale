/** 
 * @file lldrawpoolsky.h
 * @brief LLDrawPoolSky class definition
 *
 * Copyright (c) 2002-2007, Linden Research, Inc.
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

#ifndef LL_LLDRAWPOOLSKY_H
#define LL_LLDRAWPOOLSKY_H

#include "lldrawpool.h"

class LLSkyTex;
class LLHeavenBody;

class LLDrawPoolSky : public LLFacePool
{
private:
	LLSkyTex			*mSkyTex;
	LLHeavenBody		*mHB[2]; // Sun and Moon

public:
	enum
	{
		VERTEX_DATA_MASK =	LLVertexBuffer::MAP_VERTEX |
							LLVertexBuffer::MAP_TEXCOORD
	};

	virtual U32 getVertexDataMask() { return VERTEX_DATA_MASK; }

	LLDrawPoolSky();

	/*virtual*/ LLDrawPool *instancePool();

	/*virtual*/ void prerender();
	/*virtual*/ void render(S32 pass = 0);
	/*virtual*/ void renderForSelect();
	void setSkyTex(LLSkyTex* const st) { mSkyTex = st; }
	void setSun(LLHeavenBody* sun) { mHB[0] = sun; }
	void setMoon(LLHeavenBody* moon) { mHB[1] = moon; }

	void renderSkyCubeFace(U8 side);
	void renderHeavenlyBody(U8 hb, LLFace* face);
	void renderSunHalo(LLFace* face);

	virtual S32 getMaterialAttribIndex() { return 0; }
};

#endif // LL_LLDRAWPOOLSKY_H
