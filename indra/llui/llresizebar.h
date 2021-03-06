/** 
 * @file llresizebar.h
 * @brief LLResizeBar base class
 *
 * Copyright (c) 2001-2007, Linden Research, Inc.
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

#ifndef LL_RESIZEBAR_H
#define LL_RESIZEBAR_H

#include "llview.h"
#include "llcoord.h"

class LLResizeBar : public LLView
{
public:
	enum Side { LEFT, TOP, RIGHT, BOTTOM };

	LLResizeBar(const LLString& name, const LLRect& rect, S32 min_width, S32 min_height, Side side );

	virtual EWidgetType getWidgetType() const;
	virtual LLString getWidgetTag() const;

//	virtual void	draw();  No appearance
	virtual BOOL	handleHover(S32 x, S32 y, MASK mask);
	virtual BOOL	handleMouseDown(S32 x, S32 y, MASK mask);
	virtual BOOL	handleMouseUp(S32 x, S32 y, MASK mask);

	void			setResizeLimits( S32 min_width, S32 min_height ) { mMinWidth = min_width; mMinHeight = min_height; }

protected:
	S32				mDragLastScreenX;
	S32				mDragLastScreenY;
	S32				mLastMouseScreenX;
	S32				mLastMouseScreenY;
	LLCoordGL		mLastMouseDir;
	S32				mMinWidth;
	S32				mMinHeight;
	Side			mSide;
};

const S32 RESIZE_BAR_HEIGHT = 3;

#endif  // LL_RESIZEBAR_H


