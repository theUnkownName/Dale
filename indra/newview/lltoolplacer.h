/** 
 * @file lltoolplacer.h
 * @brief Tool for placing new objects into the world
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

#ifndef LL_TOOLPLACER_H
#define LL_TOOLPLACER_H

#include "llprimitive.h"
#include "llpanel.h"
#include "lltool.h"

class LLButton;

////////////////////////////////////////////////////
// LLToolPlacer

class LLToolPlacer
 :	public LLTool
{
public:
	LLToolPlacer();

	virtual BOOL	placeObject(S32 x, S32 y, MASK mask);
	virtual BOOL	handleHover(S32 x, S32 y, MASK mask);
	virtual void	handleSelect();	// do stuff when your tool is selected
	virtual void	handleDeselect();	// clean up when your tool is deselected

	static void	setObjectType( LLPCode type )		{ sObjectType = type; }
	static LLPCode getObjectType()					{ return sObjectType; }

protected:
	static LLPCode	sObjectType;
};

////////////////////////////////////////////////////
// LLToolPlacerPanel


const S32 TOOL_PLACER_NUM_BUTTONS = 14;


class LLToolPlacerPanel : public LLPanel
{
public:

	LLToolPlacerPanel(const std::string& name, const LLRect& rect);
 	
	static void	setObjectType( void* data );

	static LLPCode sCube;
	static LLPCode sPrism;
	static LLPCode sPyramid;
	static LLPCode sTetrahedron;
	static LLPCode sCylinder;
	static LLPCode sCylinderHemi;
	static LLPCode sCone; 
	static LLPCode sConeHemi;
	static LLPCode sTorus;
	static LLPCode sSquareTorus;
	static LLPCode sTriangleTorus;
	static LLPCode sSphere; 
	static LLPCode sSphereHemi;
	static LLPCode sTree;
	static LLPCode sGrass;

private:
	void		addButton( const LLString& up_state, const LLString& down_state, LLPCode* pcode );

private:
	static S32			sButtonsAdded;
	static LLButton*	sButtons[ TOOL_PLACER_NUM_BUTTONS ];
};

#endif
