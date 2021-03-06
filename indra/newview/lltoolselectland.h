/** 
 * @file lltoolselectland.h
 * @brief LLToolSelectLand class header file
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

#ifndef LL_LLTOOLSELECTLAND_H
#define LL_LLTOOLSELECTLAND_H

#include "lltool.h"
#include "v3dmath.h"

class LLParcelSelection;

class LLToolSelectLand
:	public LLTool
{
public:
	LLToolSelectLand( );
	virtual ~LLToolSelectLand();

	/*virtual*/ BOOL		handleMouseDown(S32 x, S32 y, MASK mask);
	/*virtual*/ BOOL		handleDoubleClick(S32 x, S32 y, MASK mask);
	/*virtual*/ BOOL		handleMouseUp(S32 x, S32 y, MASK mask);
	/*virtual*/ BOOL		handleHover(S32 x, S32 y, MASK mask);
	/*virtual*/ void		render();				// draw the select rectangle
	/*virtual*/ BOOL		isAlwaysRendered()		{ return TRUE; }

	/*virtual*/ void		handleSelect();
	/*virtual*/ void		handleDeselect();

protected:
	BOOL			outsideSlop(S32 x, S32 y, S32 start_x, S32 start_y);
	void			roundXY(LLVector3d& vec);

protected:
	LLVector3d		mDragStartGlobal;		// global coords
	LLVector3d		mDragEndGlobal;			// global coords
	BOOL			mDragEndValid;			// is drag end a valid point in the world?

	S32				mDragStartX;			// screen coords, from left
	S32				mDragStartY;			// screen coords, from bottom

	S32				mDragEndX;
	S32				mDragEndY;

	BOOL			mMouseOutsideSlop;		// has mouse ever gone outside slop region?

	LLVector3d		mWestSouthBottom;		// global coords, from drag
	LLVector3d		mEastNorthTop;			// global coords, from drag

	BOOL			mLastShowParcelOwners;	// store last Show Parcel Owners setting
	LLHandle<LLParcelSelection> mSelection;		// hold on to a parcel selection
};

extern LLToolSelectLand *gToolParcel;

#endif
