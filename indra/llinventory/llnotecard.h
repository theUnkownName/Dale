/** 
 * @file llnotecard.h
 * @brief LLNotecard class declaration
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

#ifndef LL_NOTECARD_H
#define LL_NOTECARD_H

#include "llmemory.h"
#include "llinventory.h"

class LLNotecard
{
public:
	/**
	 * @brief anonymous enumeration to set max size.
	 */
	enum
	{
		MAX_SIZE = 65536
	};
	
	LLNotecard(S32 max_text = LLNotecard::MAX_SIZE);
	virtual ~LLNotecard();

	bool importStream(std::istream& str);
	bool exportStream(std::ostream& str);

	const std::vector<LLPointer<LLInventoryItem> >& getItems() const;
	LLString& getText();

	void setItems(const std::vector<LLPointer<LLInventoryItem> >& items);
	void setText(const LLString& text);
	S32 getVersion() { return mVersion; }
	S32 getEmbeddedVersion() { return mEmbeddedVersion; }
	
private:
	bool importEmbeddedItemsStream(std::istream& str);
	bool exportEmbeddedItemsStream(std::ostream& str);
	std::vector<LLPointer<LLInventoryItem> > mItems;
	LLString mText;
	S32 mMaxText;
	S32 mVersion;
	S32 mEmbeddedVersion;
};

#endif /* LL_NOTECARD_H */
