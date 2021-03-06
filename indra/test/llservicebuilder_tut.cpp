/**
* @file   llservicebuilder_tut.cpp
* @brief  LLServiceBuilder unit tests
* @date   March 2007
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

#include <tut/tut.h>
#include "lltut.h"

#include "llsd.h"
#include "llservicebuilder.h"

namespace tut
{

	struct ServiceBuilderTestData {
		LLServiceBuilder mServiceBuilder;
	};

	typedef test_group<ServiceBuilderTestData>	ServiceBuilderTestGroup;
	typedef ServiceBuilderTestGroup::object	ServiceBuilderTestObject;

	ServiceBuilderTestGroup serviceBuilderTestGroup("ServiceBuilder");

	template<> template<>
	void ServiceBuilderTestObject::test<1>()
	{
		//Simple service build and reply with no mapping
		LLSD test_block;
		test_block["service-builder"] = "/agent/name";
		mServiceBuilder.createServiceDefinition("ServiceBuilderTest", test_block["service-builder"]);
		std::string test_url = mServiceBuilder.buildServiceURI("ServiceBuilderTest");
		ensure_equals("Basic URL Creation", test_url , "/agent/name");
	}	

	template<> template<>
	void ServiceBuilderTestObject::test<2>()
	{
		//Simple replace test
		LLSD test_block;
		test_block["service-builder"] = "/agent/{$agent-id}/name";
		mServiceBuilder.createServiceDefinition("ServiceBuilderTest", test_block["service-builder"]);	
		LLSD data_map;
		data_map["agent-id"] = "257c631f-a0c5-4f29-8a9f-9031feaae6c6";
		std::string test_url = mServiceBuilder.buildServiceURI("ServiceBuilderTest", data_map);
		ensure_equals("Replacement URL Creation", test_url , "/agent/257c631f-a0c5-4f29-8a9f-9031feaae6c6/name");
	}	

	template<> template<>
	void ServiceBuilderTestObject::test<3>()
	{
		//Incorrect service test
		LLSD test_block;
		test_block["service-builder"] = "/agent/{$agent-id}/name";
		mServiceBuilder.createServiceDefinition("ServiceBuilderTest", test_block["service-builder"]);	
		std::string test_url = mServiceBuilder.buildServiceURI("ServiceBuilder");
		ensure_equals("Replacement URL Creation for Non-existant Service", test_url , "");
	}

	template<> template<>
	void ServiceBuilderTestObject::test<4>()
	{
		//Incorrect service test
		LLSD test_block;
		test_block["service-builder"] = "/agent/{$agent-id}/name";
		mServiceBuilder.createServiceDefinition("ServiceBuilderTest", test_block["service-builder"]);
		LLSD data_map;
		data_map["agent_id"] = "257c631f-a0c5-4f29-8a9f-9031feaae6c6";
		std::string test_url = mServiceBuilder.buildServiceURI("ServiceBuilderTest", data_map);
		ensure_equals("Replacement URL Creation for Non-existant Service", test_url , "/agent/{$agent-id}/name");
	}
}

