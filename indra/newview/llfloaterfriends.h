/** 
 * @file llfloaterfriends.h
 * @author Phoenix
 * @date 2005-01-13
 * @brief Declaration of class for displaying the local agent's friends.
 *
 * Copyright (c) 2005-2007, Linden Research, Inc.
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

#ifndef LL_LLFLOATERFRIENDS_H
#define LL_LLFLOATERFRIENDS_H

#include "llfloater.h"
#include "llstring.h"
#include "lluuid.h"
#include "lltimer.h"

class LLFriendObserver;


/** 
 * @class LLFloaterFriends
 * @brief An instance of this class is used for displaying your friends
 * and gives you quick access to all agents which a user relationship.
 *
 * @sa LLFloater
 */
class LLFloaterFriends : public LLFloater, public LLEventTimer
{
public:
	virtual ~LLFloaterFriends();

	/** 
	 * @brief This method either creates or brings to the front the
	 * current instantiation of this floater. There is only once since
	 * you can currently only look at your local friends.
	 */
	static void show(void* ignored = NULL);

	virtual void tick();

	/** 
	 * @brief This method is called in response to the LLAvatarTracker
	 * sending out a changed() message.
	 */
	void updateFriends(U32 changed_mask);

	virtual BOOL postBuild();

	static BOOL visible(void* unused = NULL);

	// Toggles visibility of floater
	static void toggle(void* unused = NULL);

	// Show a dialog explaining what friendship entails, then request
	// friendship. JC
	static void requestFriendshipDialog(const LLUUID& target_id, 
										const std::string& target_name);

	// Just request friendship, no dialog.
	static void requestFriendship(const LLUUID& target_id,
								  const LLString& target_name);

private:

	enum FRIENDS_COLUMN_ORDER
	{
		LIST_ONLINE_STATUS,
		LIST_FRIEND_NAME,
		LIST_VISIBLE_ONLINE,
		LIST_VISIBLE_MAP,
		LIST_EDIT_MINE,
		LIST_EDIT_THEIRS
	};

	// protected members
	LLFloaterFriends();

	void reloadNames();
	void refreshNames();
	void refreshUI();
	void refreshRightsChangeList(U8 state);
	void applyRightsToFriends(S32 flag, BOOL value);
	void updateMenuState(S32 flag, BOOL value);
	S32 getMenuState() { return mMenuState; }
	void addFriend(const std::string& name, const LLUUID& agent_id);	

	// return LLUUID::null if nothing is selected
	static LLDynamicArray<LLUUID> getSelectedIDs();

	// callback methods
	static void onSelectName(LLUICtrl* ctrl, void* user_data);
	static void callbackAddFriend(S32 option, void* user_data);
	static void onPickAvatar(const std::vector<std::string>& names, const std::vector<LLUUID>& ids, void* user_data);
	static void onMaximumSelect(void* user_data);

	static void onClickIM(void* user_data);
	static void onClickProfile(void* user_data);
	static void onClickAddFriend(void* user_data);
	static void onClickRemove(void* user_data);

	static void onClickOfferTeleport(void* user_data);
	static void onClickPay(void* user_data);

	static void onClickClose(void* user_data);

	static void onClickOnlineStatus(LLUICtrl* ctrl, void* user_data);
	static void onClickMapStatus(LLUICtrl* ctrl, void* user_data);
	static void onClickModifyStatus(LLUICtrl* ctrl, void* user_data);

	static void handleRemove(S32 option, void* user_data);
	static void handleModifyRights(S32 option, void* user_data);

private:
	// static data
	static LLFloaterFriends* sInstance;

	// member data
	LLFriendObserver* mObserver;
	LLUUID mAddFriendID;
	LLString mAddFriendName;
	LLScrollListCtrl*			mFriendsList;
	S32		mMenuState;
	BOOL mShowMaxSelectWarning;
	BOOL mAllowRightsChange;
	S32 mNumRightsChanged;
};


#endif // LL_LLFLOATERFRIENDS_H
