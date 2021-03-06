/** 
 * @file llcaphttpsender.h
 * @brief Abstracts details of sending messages via the
 *        UntrustedMessage capability.
 *
 * Copyright (c) 2007-2007, Linden Research, Inc.
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

#ifndef LL_CAP_HTTP_SENDER_H
#define LL_CAP_HTTP_SENDER_H

#include "llhttpsender.h"

class LLCapHTTPSender : public LLHTTPSender
{
public:
	LLCapHTTPSender(const std::string& cap);

	/** @brief Send message via UntrustedMessage capability with body,
		call response when done */ 
	virtual void send(const LLHost& host, 
					  const char* message, const LLSD& body, 
					  LLHTTPClient::ResponderPtr response) const;

private:
	std::string mCap;
};

#endif // LL_CAP_HTTP_SENDER_H
