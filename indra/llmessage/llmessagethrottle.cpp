/** 
 * @file llmessagethrottle.cpp
 * @brief LLMessageThrottle class used for throttling messages.
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

#include "llhash.h"

#include "llmessagethrottle.h"
#include "llframetimer.h"

// This is used for the stl search_n function.
bool eq_message_throttle_entry(LLMessageThrottleEntry a, LLMessageThrottleEntry b)
		{ return a.getHash() == b.getHash(); }

const U64 SEC_TO_USEC = 1000000;
		
// How long (in microseconds) each type of message stays in its throttle list.
const U64 MAX_MESSAGE_AGE[MTC_EOF] =
{
	10 * SEC_TO_USEC,	// MTC_VIEWER_ALERT
	10 * SEC_TO_USEC	// MTC_AGENT_ALERT
};

LLMessageThrottle::LLMessageThrottle()
{
}

LLMessageThrottle::~LLMessageThrottle()
{
}

void LLMessageThrottle::pruneEntries()
{
	// Go through each message category, and prune entries older than max age.
	S32 cat;
	for (cat = 0; cat < MTC_EOF; cat++)
	{
		message_list_t* message_list = &(mMessageList[cat]);

		// Use a reverse iterator, since entries on the back will be the oldest.
		message_list_reverse_iterator_t r_iterator 	= message_list->rbegin();
		message_list_reverse_iterator_t r_last 		= message_list->rend();

		// Look for the first entry younger than the maximum age.
		F32 max_age = (F32)MAX_MESSAGE_AGE[cat]; 
		BOOL found = FALSE;
		while (r_iterator != r_last && !found)
		{
			if ( LLFrameTimer::getTotalTime() - (*r_iterator).getEntryTime() < max_age )
			{
				// We found a young enough entry.
				found = TRUE;

				// Did we find at least one entry to remove?
				if (r_iterator != message_list->rbegin())
				{
					// Yes, remove it.
					message_list->erase(r_iterator.base(), message_list->end());
				}
			}
			else
			{
				r_iterator++;
			}
		}

		// If we didn't find any entries young enough to keep, remove them all.
		if (!found)
		{
			message_list->clear();
		}
	}
}

BOOL LLMessageThrottle::addViewerAlert(const LLUUID& to, const char* mesg)
{
	message_list_t* message_list = &(mMessageList[MTC_VIEWER_ALERT]);

	// Concatenate from,to,mesg into one string.
	std::ostringstream full_mesg;
	full_mesg << to << mesg;

	// Create an entry for this message.
	size_t hash = llhash<const char*> (full_mesg.str().c_str());
	LLMessageThrottleEntry entry(hash, LLFrameTimer::getTotalTime());

	// Check if this message is already in the list.
	message_list_iterator_t found = std::search_n(message_list->begin(), message_list->end(),
												  1, entry, eq_message_throttle_entry);

	if (found == message_list->end())
	{
		// This message was not found.  Add it to the list.
		message_list->push_front(entry);
		return TRUE;
	}
	else
	{
		// This message was already in the list.
		return FALSE;
	}
}

BOOL LLMessageThrottle::addAgentAlert(const LLUUID& agent, const LLUUID& task, const char* mesg)
{
	message_list_t* message_list = &(mMessageList[MTC_AGENT_ALERT]);

	// Concatenate from,to,mesg into one string.
	std::ostringstream full_mesg;
	full_mesg << agent << task << mesg;

	// Create an entry for this message.
	size_t hash = llhash<const char*> (full_mesg.str().c_str());
	LLMessageThrottleEntry entry(hash, LLFrameTimer::getTotalTime());

	// Check if this message is already in the list.
	message_list_iterator_t found = std::search_n(message_list->begin(), message_list->end(),
												  1, entry, eq_message_throttle_entry);

	if (found == message_list->end())
	{
		// This message was not found.  Add it to the list.
		message_list->push_front(entry);
		return TRUE;
	}
	else
	{
		// This message was already in the list.
		return FALSE;
	}
}

