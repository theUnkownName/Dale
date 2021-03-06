/** 
 * @file lltoolpie.h
 * @brief LLToolPie class header file
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

#ifndef LL_TOOLPIE_H
#define LL_TOOLPIE_H

#include "lltool.h"
#include "lluuid.h"

class LLViewerObject;
class LLObjectSelection;

class LLToolPie 
:	public LLTool
{
public:
	LLToolPie( );

	virtual BOOL		handleMouseDown(S32 x, S32 y, MASK mask);
	virtual BOOL		handleRightMouseDown(S32 x, S32 y, MASK mask);
	virtual BOOL		handleMouseUp(S32 x, S32 y, MASK mask);
	virtual BOOL		handleRightMouseUp(S32 x, S32 y, MASK mask);
	virtual BOOL		handleHover(S32 x, S32 y, MASK mask);
	virtual BOOL		handleDoubleClick(S32 x, S32 y, MASK mask);

	virtual void		render();

	virtual void		stopEditing();

	virtual void		onMouseCaptureLost();
	virtual void		handleDeselect();
	virtual LLTool*		getOverrideTool(MASK mask);

	static void			leftMouseCallback(S32 x, S32 y, MASK mask);
	static void			rightMouseCallback(S32 x, S32 y, MASK mask);

	static void			selectionPropertiesReceived();

protected:
	BOOL outsideSlop(S32 x, S32 y, S32 start_x, S32 start_y);
	BOOL pickAndShowMenu(S32 x, S32 y, MASK mask, BOOL edit_menu);
	BOOL useClickAction(BOOL always_show, MASK mask, LLViewerObject* object,
						LLViewerObject* parent);

protected:
	BOOL				mPieMouseButtonDown;
	BOOL				mGrabMouseButtonDown;
	BOOL				mHitLand;
	LLUUID				mHitObjectID;
	BOOL				mMouseOutsideSlop;				// for this drag, has mouse moved outside slop region
	static LLViewerObject* sClickActionObject;
	static U8				sClickAction;
	static LLHandle<LLObjectSelection> sLeftClickSelection;
};

extern LLToolPie *gToolPie;

#endif
