/** 
 * @file llpanelgroupgeneral.h
 * @brief General information about a group.
 *
 * Copyright (c) 2006-2007, Linden Research, Inc.
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

#ifndef LL_LLPANELGROUPGENERAL_H
#define LL_LLPANELGROUPGENERAL_H

#include "llpanelgroup.h"

class LLLineEditor;
class LLTextBox;
class LLTextureCtrl;
class LLTextEditor;
class LLButton;
class LLNameListCtrl;
class LLCheckBoxCtrl;
class LLComboBox;
class LLNameBox;
class LLSpinCtrl;

class LLPanelGroupGeneral : public LLPanelGroupTab
{
public:
	LLPanelGroupGeneral(const std::string& name, const LLUUID& group_id);
	virtual ~LLPanelGroupGeneral();

	// LLPanelGroupTab
	static void* createTab(void* data);
	virtual void activate();
	virtual bool needsApply(LLString& mesg);
	virtual bool apply(LLString& mesg);
	virtual void cancel();
	static void createGroupCallback(S32 option, void* user_data);
	
	virtual void update(LLGroupChange gc);
	
	virtual BOOL postBuild();
	
	virtual void draw();

private:
	static void onCommitAny(LLUICtrl* ctrl, void* data);
	static void onCommitTitle(LLUICtrl* ctrl, void* data);
	static void onCommitEnrollment(LLUICtrl* ctrl, void* data);
	static void onClickJoin(void* userdata);
	static void onClickInfo(void* userdata);
	static void onReceiveNotices(LLUICtrl* ctrl, void* data);
	static void openProfile(void* data);

    static void joinDlgCB(S32 which, void *userdata);

	void updateMembers();

	BOOL			mPendingMemberUpdate;
	BOOL			mChanged;
	BOOL			mFirstUse;
	std::string		mIncompleteMemberDataStr;
	std::string		mConfirmGroupCreateStr;
	LLUUID			mDefaultIconID;

	// Group information
	LLLineEditor		*mGroupNameEditor;
	LLTextBox			*mGroupName;
	LLNameBox			*mFounderName;
	LLTextureCtrl		*mInsignia;
	LLTextEditor		*mEditCharter;
	LLLineEditor		*mEditName;
	LLButton			*mBtnJoinGroup;
	LLButton			*mBtnInfo;

	LLNameListCtrl	*mListVisibleMembers;

	// Options
	LLCheckBoxCtrl	*mCtrlShowInGroupList;
	LLCheckBoxCtrl	*mCtrlPublishOnWeb;
	LLCheckBoxCtrl	*mCtrlMature;
	LLCheckBoxCtrl	*mCtrlOpenEnrollment;
	LLCheckBoxCtrl	*mCtrlEnrollmentFee;
	LLSpinCtrl      *mSpinEnrollmentFee;
	LLCheckBoxCtrl	*mCtrlReceiveNotices;
	LLTextBox       *mActiveTitleLabel;
	LLComboBox		*mComboActiveTitle;

	LLGroupMgrGroupData::member_iter mMemberProgress;
};

#endif
