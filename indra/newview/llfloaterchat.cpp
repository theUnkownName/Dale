/** 
 * @file llfloaterchat.cpp
 * @brief LLFloaterChat class implementation
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

/**
 * Actually the "Chat History" floater.
 * Should be llfloaterchathistory, not llfloaterchat.
 */

#include "llviewerprecompiledheaders.h"

#include "llfloaterchat.h"
#include "llfloaterscriptdebug.h"

#include "llchat.h"
#include "llfontgl.h"
#include "llrect.h"
#include "llerror.h"
#include "llstring.h"
#include "message.h"

// project include
#include "llagent.h"
#include "llbutton.h"
#include "llcheckboxctrl.h"
#include "llcombobox.h"
#include "llconsole.h"
#include "llfloatermute.h"
#include "llkeyboard.h"
//#include "lllineeditor.h"
#include "llmutelist.h"
//#include "llresizehandle.h"
#include "llstatusbar.h"
#include "llviewertexteditor.h"
#include "llviewergesture.h"			// for triggering gestures
#include "llviewermessage.h"
#include "llviewerwindow.h"
#include "llviewercontrol.h"
#include "llvieweruictrlfactory.h"
#include "llchatbar.h"
#include "lllogchat.h"
#include "lltexteditor.h"
#include "llfloaterhtml.h"
#include "llweb.h"

//
// Constants
//
const char FLOATER_TITLE[] = "Chat History";
const F32 INSTANT_MSG_SIZE = 8.0f;
const F32 CHAT_MSG_SIZE = 8.0f;
const LLColor4 INSTANT_MSG_COLOR(1, 1, 1, 1);
const LLColor4 MUTED_MSG_COLOR(0.5f, 0.5f, 0.5f, 1.f);
const S32 MAX_CHATTER_COUNT = 16;

//
// Global statics
//
LLFloaterChat* gFloaterChat = NULL;

LLColor4 get_text_color(const LLChat& chat);

//
// Member Functions
//
LLFloaterChat::LLFloaterChat()
:	LLFloater("chat floater", "FloaterChatRect", FLOATER_TITLE, 
			  RESIZE_YES, 440, 100, DRAG_ON_TOP, MINIMIZE_NO, CLOSE_YES)
{
	
	gUICtrlFactory->buildFloater(this,"floater_chat_history.xml");

	childSetAction("Mute resident",onClickMute,this);
	childSetAction("Chat", onClickChat, this);
	childSetCommitCallback("chatter combobox",onCommitUserSelect,this);
	childSetCommitCallback("show mutes",onClickToggleShowMute,this); //show mutes
	childSetVisible("Chat History Editor with mute",FALSE);
	setDefaultBtn("Chat");
}

LLFloaterChat::~LLFloaterChat()
{
	// Children all cleaned up by default view destructor.
}

void LLFloaterChat::setVisible(BOOL visible)
{
	LLFloater::setVisible( visible );

	gSavedSettings.setBOOL("ShowChatHistory", visible);

	// Hide the chat overlay when our history is visible.
	gConsole->setVisible( !visible );
}


// public virtual
void LLFloaterChat::onClose(bool app_quitting)
{
	LLFloater::setVisible( FALSE );

	if (!app_quitting)
	{
		gSavedSettings.setBOOL("ShowChatHistory", FALSE);
	}

	// Hide the chat overlay when our history is visible.
	gConsole->setVisible( TRUE );
}


// public
void LLFloaterChat::show()
{
	open();		/*Flawfinder: ignore*/
}

void add_timestamped_line(LLViewerTextEditor* edit, const LLString& line, const LLColor4& color)
{
	bool prepend_newline = true;
	if (gSavedSettings.getBOOL("ChatShowTimestamps"))
	{
		edit->appendTime(prepend_newline);
		prepend_newline = false;
	}
	edit->appendColoredText(line, false, prepend_newline, color);
}

// static
void LLFloaterChat::addChatHistory(const LLChat& chat, bool log_to_file)
{
	if ( gSavedPerAccountSettings.getBOOL("LogChat") && log_to_file) 
	{
		LLLogChat::saveHistory("chat",chat.mText);
	}
	
	LLColor4 color = get_text_color(chat);
	
	if (!log_to_file) color = LLColor4::grey;	//Recap from log file.

	if (chat.mChatType == CHAT_TYPE_DEBUG_MSG)
	{
		LLFloaterScriptDebug::addScriptLine(chat.mText,
											chat.mFromName, 
											color, 
											chat.mFromID);
		if (!gSavedSettings.getBOOL("ScriptErrorsAsChat"))
		{
			return;
		}
	}
	
	// could flash the chat button in the status bar here. JC
	if (!gFloaterChat) return;

	LLViewerTextEditor*	HistoryEditor = (LLViewerTextEditor*)gFloaterChat->getChildByName("Chat History Editor");
	LLViewerTextEditor*	HistoryEditorWithMute = (LLViewerTextEditor*)gFloaterChat->getChildByName("Chat History Editor with mute");

	HistoryEditor->setParseHTML(TRUE);
	HistoryEditorWithMute->setParseHTML(TRUE);
	
	if (!chat.mMuted)
	{
		add_timestamped_line(HistoryEditor, chat.mText, color);
		add_timestamped_line(HistoryEditorWithMute, chat.mText, color);
	}
	else
	{
		// desaturate muted chat
		LLColor4 muted_color = lerp(color, LLColor4::grey, 0.5f);
		add_timestamped_line(HistoryEditorWithMute, chat.mText, color);
	}

	if (!chat.mMuted
		&& chat.mSourceType != CHAT_SOURCE_SYSTEM
		&& chat.mFromID.notNull()
		&& chat.mFromID != gAgent.getID())
	{
			
		LLComboBox*	ChatterCombo = LLUICtrlFactory::getComboBoxByName(gFloaterChat,"chatter combobox");
		
		if(!ChatterCombo)
				return;

		if (!ChatterCombo->setCurrentByID(chat.mFromID))
		{
			// if we have too many items...
			if (ChatterCombo->getItemCount() >= MAX_CHATTER_COUNT)
			{
				ChatterCombo->remove(0);
			}
			
			LLMute mute(chat.mFromID, chat.mFromName);
			if (chat.mSourceType == CHAT_SOURCE_OBJECT)
			{
				mute.mType = LLMute::OBJECT;
			}
			else if (chat.mSourceType == CHAT_SOURCE_AGENT)
			{
				mute.mType = LLMute::AGENT;
			}
			LLString item = mute.getDisplayName();
			ChatterCombo->add(item, chat.mFromID);
			ChatterCombo->setCurrentByIndex(ChatterCombo->getItemCount() - 1);
			gFloaterChat->childSetEnabled("Mute resident",TRUE);
		}
	}
}

// static
void LLFloaterChat::setHistoryCursorAndScrollToEnd()
{
	if (gFloaterChat)
	{
		LLViewerTextEditor*	HistoryEditor = (LLViewerTextEditor*)gFloaterChat->getChildByName("Chat History Editor");
		LLViewerTextEditor*	HistoryEditorWithMute = (LLViewerTextEditor*)gFloaterChat->getChildByName("Chat History Editor with mute");
		
		HistoryEditor->setCursorAndScrollToEnd();
		HistoryEditorWithMute->setCursorAndScrollToEnd();
	}
}


// static
void LLFloaterChat::toggle(void*)
{
	if (gFloaterChat->getVisible())
	{
		gFloaterChat->close();
	}
	else
	{
		gFloaterChat->show();
	}
}

// static
BOOL LLFloaterChat::visible(void*)
{
	return (gFloaterChat && gFloaterChat->getVisible());
}

//static 
void LLFloaterChat::onClickMute(void *data)
{
	LLFloaterChat* self = (LLFloaterChat*)data;

	LLComboBox*	ChatterCombo = LLUICtrlFactory::getComboBoxByName(self,"chatter combobox");

	const LLString& name = ChatterCombo->getSimple();
	LLUUID id = ChatterCombo->getCurrentID();

	if (name.empty()) return;

	LLMute mute(id);
	mute.setFromDisplayName(name);
	gMuteListp->add(mute);
	
	if (gFloaterMute)
	{
		gFloaterMute->show();
	}
}

//static
void LLFloaterChat::onClickChat(void*)
{
	// we need this function as a level of indirection because otherwise startChat would
	// cast the data pointer to a character string, and dump garbage in the chat
	LLChatBar::startChat(NULL);
}

//static 
void LLFloaterChat::onCommitUserSelect(LLUICtrl* caller, void* data)
{
	LLFloaterChat* floater = (LLFloaterChat*)data;
	LLComboBox* combo = (LLComboBox*)caller;

	if (combo->getCurrentIndex() == -1)
	{
		floater->childSetEnabled("Mute resident",FALSE);
	}
	else
	{
		floater->childSetEnabled("Mute resident",TRUE);
	}
}

//static
void LLFloaterChat::onClickToggleShowMute(LLUICtrl* caller, void *data)
{
	LLFloaterChat* floater = (LLFloaterChat*)data;


	//LLCheckBoxCtrl*	
	BOOL show_mute = LLUICtrlFactory::getCheckBoxByName(floater,"show mutes")->get();
	LLViewerTextEditor*	HistoryEditor = (LLViewerTextEditor*)floater->getChildByName("Chat History Editor");
	LLViewerTextEditor*	HistoryEditorWithMute = (LLViewerTextEditor*)floater->getChildByName("Chat History Editor with mute");

	if (!HistoryEditor || !HistoryEditorWithMute)
		return;

	//BOOL show_mute = floater->mShowMuteCheckBox->get();
	if (show_mute)
	{
		HistoryEditor->setVisible(FALSE);
		HistoryEditorWithMute->setVisible(TRUE);
		HistoryEditorWithMute->setCursorAndScrollToEnd();
	}
	else
	{
		HistoryEditor->setVisible(TRUE);
		HistoryEditorWithMute->setVisible(FALSE);
		HistoryEditor->setCursorAndScrollToEnd();
	}
}

// Put a line of chat in all the right places
void LLFloaterChat::addChat(const LLChat& chat, 
			  BOOL from_instant_message, 
			  BOOL local_agent)
{
	LLColor4 text_color = get_text_color(chat);

	BOOL invisible_script_debug_chat = 
			chat.mChatType == CHAT_TYPE_DEBUG_MSG
			&& !gSavedSettings.getBOOL("ScriptErrorsAsChat");

	if (!invisible_script_debug_chat 
		&& !chat.mMuted 
		&& gConsole 
		&& !local_agent)
	{
		F32 size = CHAT_MSG_SIZE;
		if(from_instant_message)
		{
			text_color = INSTANT_MSG_COLOR;
			size = INSTANT_MSG_SIZE;
		}
		gConsole->addLine(chat.mText, size, text_color);
	}

	if( !from_instant_message || gSavedSettings.getBOOL("IMInChatHistory") )
	{
		addChatHistory(chat);
	}
}

LLColor4 get_text_color(const LLChat& chat)
{
	LLColor4 text_color;

	if(chat.mMuted)
	{
		text_color.setVec(0.8f, 0.8f, 0.8f, 1.f);
	}
	else
	{
		switch(chat.mSourceType)
		{
		case CHAT_SOURCE_SYSTEM:
			text_color = gSavedSettings.getColor4("SystemChatColor");
			break;
		case CHAT_SOURCE_AGENT:
		    if (chat.mFromID.isNull())
			{
				text_color = gSavedSettings.getColor4("SystemChatColor");
			}
			else
			{
				text_color = gSavedSettings.getColor4("AgentChatColor");
			}
			break;
		case CHAT_SOURCE_OBJECT:
			if (chat.mChatType == CHAT_TYPE_DEBUG_MSG)
			{
				text_color = gSavedSettings.getColor4("ScriptErrorColor");
			}
			else
			{
				text_color = gSavedSettings.getColor4("ObjectChatColor");
			}
			break;
		default:
			text_color.setToWhite();
		}

		if (!chat.mPosAgent.isExactlyZero())
		{
			LLVector3 pos_agent = gAgent.getPositionAgent();
			F32 distance = dist_vec(pos_agent, chat.mPosAgent);
			if (distance > gAgent.getNearChatRadius())
			{
				// diminish far-off chat
				text_color.mV[VALPHA] = 0.8f;
			}
		}
	}

	return text_color;
}

//static
void LLFloaterChat::loadHistory()
{
	LLLogChat::loadHistory("chat", &chatFromLogFile, (void *)gFloaterChat); 
}

//static
void LLFloaterChat::chatFromLogFile(LLString line, void* userdata)
{
	LLChat chat;
				
	chat.mText = line;
	addChatHistory(chat,  FALSE);
}
