/** 
 * @file llradiogroup.h
 * @brief LLRadioGroup base class
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

// An invisible view containing multiple mutually exclusive toggling 
// buttons (usually radio buttons).  Automatically handles the mutex
// condition by highlighting only one button at a time.

#ifndef LL_LLRADIOGROUP_H
#define LL_LLRADIOGROUP_H

#include "lluictrl.h"
#include "llcheckboxctrl.h"

class LLFontGL;

// Radio controls are checkbox controls with use_radio_style true
class LLRadioCtrl : public LLCheckBoxCtrl 
{
public:
	LLRadioCtrl(const LLString& name, const LLRect& rect, const LLString& label,	
		const LLFontGL* font = NULL,
		void (*commit_callback)(LLUICtrl*, void*) = NULL,
		void* callback_userdata = NULL);
	/*virtual*/ ~LLRadioCtrl();

	/*virtual*/ void setValue(const LLSD& value);
};

class LLRadioGroup
:	public LLUICtrl
{
public:
	// Build a radio group.  The number (0...n-1) of the currently selected
	// element will be stored in the named control.  After the control is
	// changed the callback will be called.
	LLRadioGroup(const LLString& name, const LLRect& rect, 
		const LLString& control_name, 
		LLUICtrlCallback callback = NULL,
		void* userdata = NULL,
		BOOL border = TRUE);

	// Another radio group constructor, but this one doesn't rely on
	// needing a control
	LLRadioGroup(const LLString& name, const LLRect& rect,
				 S32 initial_index,
				 LLUICtrlCallback callback = NULL,
				 void* userdata = NULL,
				 BOOL border = TRUE);

	virtual ~LLRadioGroup();
	virtual EWidgetType getWidgetType() const { return WIDGET_TYPE_RADIO_GROUP; }
	virtual LLString getWidgetTag() const { return LL_RADIO_GROUP_TAG; }

	virtual BOOL handleKeyHere(KEY key, MASK mask, BOOL called_from_parent);

	virtual void setEnabled(BOOL enabled);
	virtual LLXMLNodePtr getXML(bool save_children = true) const;
	static LLView* fromXML(LLXMLNodePtr node, LLView *parent, LLUICtrlFactory *factory);
	void setIndexEnabled(S32 index, BOOL enabled);
	
	S32 getItemCount() { return mRadioButtons.size(); }
	// return the index value of the selected item
	S32 getSelectedIndex() const;
	
	// set the index value programatically
	BOOL setSelectedIndex(S32 index, BOOL from_event = FALSE);

	// Accept and retrieve strings of the radio group control names
	virtual void	setValue(const LLSD& value );
	virtual LLSD	getValue() const;

	// Draw the group, but also fix the highlighting based on the
	// control.
	void draw();

	// You must use this method to add buttons to a radio group.
	// Don't use addChild -- it won't set the callback function
	// correctly.
	LLRadioCtrl* addRadioButton(const LLString& name, const LLString& label, const LLRect& rect, const LLFontGL* font);
	LLRadioCtrl* getRadioButton(const S32& index) { return mRadioButtons[index]; }
	// Update the control as needed.  Userdata must be a pointer to the
	// button.
	static void onClickButton(LLUICtrl* radio, void* userdata);
	
protected:
	// protected function shared by the two constructors.
	void init(BOOL border);

	S32 mSelectedIndex;
	typedef std::vector<LLRadioCtrl*> button_list_t;
	button_list_t mRadioButtons;

	BOOL mHasBorder;
};


#endif
