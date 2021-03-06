/** 
 * @file llstatusbar.h
 * @brief LLStatusBar class definition
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

#ifndef LL_LLSTATUSBAR_H
#define LL_LLSTATUSBAR_H

#include "llpanel.h"

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

class LLStatusBar
:	public LLPanel
{
public:
	LLStatusBar(const std::string& name, const LLRect& rect );
	~LLStatusBar();
	virtual BOOL postBuild();
	
	virtual EWidgetType getWidgetType() const;
	virtual LLString getWidgetTag() const;

	// OVERRIDES
	virtual void draw();

	// MANIPULATORS
	void		setBalance(S32 balance);
	void		debitBalance(S32 debit);
	void		creditBalance(S32 credit);

	void		setHealth(S32 percent);

	void setLandCredit(S32 credit);
	void setLandCommitted(S32 committed);

	void		refresh();
	void setVisibleForMouselook(bool visible);
		// some elements should hide in mouselook

	// ACCESSORS
	S32			getBalance() const;
	S32			getHealth() const;

	BOOL isUserTiered() const;
	S32 getSquareMetersCredit() const;
	S32 getSquareMetersCommitted() const;
	S32 getSquareMetersLeft() const;

protected:
	static void onClickParcelInfo(void*);
	static void onClickBalance(void*);
	static void onClickBuyCurrency(void*);
	static void onClickRegionInfo(void*);
	static void onClickHealth(void*);
	static void onClickFly(void*);
	static void onClickPush(void*);
	static void onClickBuild(void*);
	static void onClickScripts(void*);
	static void onClickBuyLand(void*);
	static void onClickScriptDebug(void*);

protected:
	LLTextBox	*mTextBalance;
	LLTextBox	*mTextHealth;
	LLTextBox	*mTextTime;

	LLButton	*mBtnScriptOut;
	LLButton	*mBtnHealth;
	LLButton	*mBtnFly;
	LLButton	*mBtnBuild;
	LLButton	*mBtnScripts;
	LLButton	*mBtnPush;
	LLButton	*mBtnBuyLand;


	LLTextBox*	mTextParcelName;

	LLStatGraph *mSGBandwidth;
	LLStatGraph *mSGPacketLoss;

	LLButton	*mBtnBuyCurrency;

	S32				mBalance;
	S32				mHealth;
	S32				mSquareMetersCredit;
	S32				mSquareMetersCommitted;
	LLFrameTimer*	mBalanceTimer;
	LLFrameTimer*	mHealthTimer;
};

// *HACK: Status bar owns your cached money balance. JC
BOOL can_afford_transaction(S32 cost);

extern LLStatusBar *gStatusBar;

#endif
