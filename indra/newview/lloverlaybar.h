/** 
 * @file lloverlaybar.h
 * @brief LLOverlayBar class definition
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

#ifndef LL_LLOVERLAYBAR_H
#define LL_LLOVERLAYBAR_H

#include "llpanel.h"
#include "llmediaremotectrl.h"

// "Constants" loaded from settings.xml at start time
extern S32 STATUS_BAR_HEIGHT;

class LLButton;
class LLLineEditor;
class LLMessageSystem;
class LLTextBox;
class LLTextEditor;
class LLUICtrl;
class LLUUID;
class LLFrameTimer;
class LLStatGraph;
class LLSlider;
class LLVolumeSliderCtrl;

class LLOverlayBar
:	public LLPanel,
	public LLMediaRemoteCtrlObserver
{
public:
	LLOverlayBar(const std::string& name, const LLRect& rect );
	~LLOverlayBar();

	virtual EWidgetType getWidgetType() const;
	virtual LLString getWidgetTag() const;

	virtual void reshape(S32 width, S32 height, BOOL called_from_parent);

	void refresh();

	void layoutButtons();

	/*virtual*/ void draw();

	static void onClickIMReceived(void* data);
	static void onClickSetNotBusy(void* data);
	static void onClickReleaseKeys(void* data);
	static void onClickMouselook(void* data);
	static void onClickStandUp(void* data);
	static void onClickResetView(void* data);

	// observer overrides
	void onVolumeChange ( const LLMediaRemoteCtrlObserver::EventType& eventIn );
	void onStopButtonPressed ( const LLMediaRemoteCtrlObserver::EventType& eventIn );
	void onPlayButtonPressed ( const LLMediaRemoteCtrlObserver::EventType& eventIn );
	void onPauseButtonPressed ( const LLMediaRemoteCtrlObserver::EventType& eventIn );

	LLMediaRemoteCtrl*	getMusicRemoteControl () { return mMusicRemote; };

protected:
	
	static void* createMusicRemote(void* userdata);
	static void* createMediaRemote(void* userdata);

protected:
	LLMediaRemoteCtrl*	mMusicRemote;
	LLMediaRemoteCtrl*	mMediaRemote;
	BOOL isBuilt;
};

extern LLOverlayBar* gOverlayBar;

#endif
