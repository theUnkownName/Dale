/**
 * @file llmetrics.h
 * @author Kelly
 * @date 2007-05-25
 * @brief Declaration of metrics accumulation and associated functions
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

#ifndef LL_LLMETRICS_H
#define LL_LLMETRICS_H

class LLMetricsImpl;
class LLSD;

class LLMetrics
{
public:
	LLMetrics();
	virtual ~LLMetrics();

	// Adds this event to aggregate totals and records details to syslog (llinfos)
	virtual void recordEventDetails(const std::string& location, 
						const std::string& mesg, 
						bool success, 
						LLSD stats);

	// Adds this event to aggregate totals
	virtual void recordEvent(const std::string& location, const std::string& mesg, bool success);

	// Prints aggregate totals and resets the counts.
	virtual void printTotals(LLSD meta);


private:
	
	LLMetricsImpl* mImpl;
};

#endif

