/** 
 * @file llpanelplace.h
 * @brief Display of a place in the Find directory.
 *
 * Copyright (c) 2004-2007, Linden Research, Inc.
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

#ifndef LL_LLPANELPLACE_H
#define LL_LLPANELPLACE_H

#include "llpanel.h"

#include "v3dmath.h"
#include "lluuid.h"

class LLButton;
class LLTextBox;
class LLLineEditor;
class LLTextEditor;
class LLTextureCtrl;
class LLMessageSystem;

class LLPanelPlace : public LLPanel
{
public:
	LLPanelPlace();
	/*virtual*/ ~LLPanelPlace();

	/*virtual*/ BOOL postBuild();


	void setParcelID(const LLUUID& parcel_id);

	void sendParcelInfoRequest();

	static void processParcelInfoReply(LLMessageSystem* msg, void**);

protected:
	static void onClickTeleport(void* data);
	static void onClickMap(void* data);
	//static void onClickLandmark(void* data);
	static void onClickAuction(void* data);

	// Go to auction web page if user clicked OK
	static void callbackAuctionWebPage(S32 option, void* data);

protected:
	LLUUID			mParcelID;
	LLUUID			mRequestedID;
	LLVector3d		mPosGlobal;
	// Zero if this is not an auction
	S32				mAuctionID;

	LLTextureCtrl* mSnapshotCtrl;

	LLLineEditor* mNameEditor;
	LLTextEditor* mDescEditor;
	LLLineEditor* mInfoEditor;
	LLLineEditor* mLocationEditor;

	LLButton*	mTeleportBtn;
	LLButton*	mMapBtn;
	//LLButton*	mLandmarkBtn;
	LLButton*	mAuctionBtn;

	typedef std::list<LLPanelPlace*> panel_list_t;
	static panel_list_t sAllPanels;
};

#endif // LL_LLPANELPLACE_H
