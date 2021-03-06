/** 
 * @file llfloaterchat.h
 * @brief LLFloaterChat class definition
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

/*
 * Actually the "Chat History" floater.
 * Should be llfloaterchathistory, not llfloaterchat.
 */

#ifndef LL_LLFLOATERCHAT_H
#define LL_LLFLOATERCHAT_H

#include "llfloater.h"

class LLButton;
class LLChat;
class LLComboBox;
class LLLineEditor;
class LLViewerTextEditor;
class LLMessageSystem;
class LLUUID;
class LLCheckBoxCtrl;

class LLFloaterChat
:	public LLFloater
{
public:
	LLFloaterChat();
	~LLFloaterChat();

	void show();
	virtual void onClose(bool app_quitting);
	virtual void setVisible( BOOL b );

	static void setHistoryCursorAndScrollToEnd();
	
	// Add chat to console and history list.
	// Color based on source, type, distance.
	static void addChat(const LLChat& chat, BOOL from_im = FALSE, BOOL local_agent = FALSE);
	
	// Add chat to history alone.
	static void addChatHistory(const LLChat& chat, bool log_to_file = true);
	
	static void toggle(void*);
	static BOOL visible(void*);

	static void onClickMute(void *data);
	static void onClickChat(void *);
	static void onCommitUserSelect(LLUICtrl* caller, void* data);
	static void onClickToggleShowMute(LLUICtrl* caller, void *data);
	static void chatFromLogFile(LLString line, void* userdata);
	static void loadHistory();
};

extern LLFloaterChat* gFloaterChat;

#endif
