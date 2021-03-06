/** 
 * @file llpanellogin.h
 * @brief Login username entry fields.
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

#ifndef LL_LLPANELLOGIN_H
#define LL_LLPANELLOGIN_H

#include "llpanel.h"

#include "lldbstrings.h"
#include "llmemory.h"
#include "llviewerimage.h"
#include "llstring.h"

class LLTextBox;
class LLLineEditor;
class LLCheckBoxCtrl;
class LLButton;
class LLComboBox;

class LLPanelLogin
:	public LLPanel
{
public:
	LLPanelLogin(const LLRect &rect, BOOL show_server, 
				void (*callback)(S32 option, void* user_data),
				void *callback_data);
	~LLPanelLogin();

	virtual BOOL handleKeyHere(KEY key, MASK mask, BOOL called_from_parent);
	virtual void draw();
	virtual void setFocus( BOOL b );

	static void show(const LLRect &rect, BOOL show_server, 
		void (*callback)(S32 option, void* user_data), 
		void* callback_data);

	static void setFields(const std::string& firstname, const std::string& lastname, 
		const std::string& password, BOOL remember);

	static void addServer(const char *server, S32 domain_name);
	static void refreshLocation( bool force_visible );

	static void getFields(LLString &firstname, LLString &lastname,
		LLString &password, BOOL &remember);

	static void getServer(LLString &server, S32& domain_name);
	static void getLocation(LLString &location);

	static void close();

	void setSiteIsAlive( bool alive );

	static void	giveFocus();
	static void mungePassword(LLUICtrl* caller, void* user_data);
	
private:
	static void onClickConnect(void*);
	static void onClickNewAccount(void*);
	static void newAccountAlertCallback(S32 option, void*);
	static void onClickQuit(void*);
	static void onClickVersion(void*);
	static void onPassKey(LLLineEditor* caller, void* user_data);

private:
	LLPointer<LLViewerImage> mLogoImage;

	void			(*mCallback)(S32 option, void *userdata);
	void*			mCallbackData;

	char mIncomingPassword[DB_USER_PASSWORD_BUF_SIZE];		/*Flawfinder: ignore*/
	char mMungedPassword[MD5HEX_STR_SIZE];		/*Flawfinder: ignore*/

	static LLPanelLogin* sInstance;
	static BOOL		sCapslockDidNotification;
	BOOL			mHtmlAvailable;
};

#endif
