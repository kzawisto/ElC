/*
 * test1.cpp
 *
 *  Created on: Oct 24, 2015
 *      Author: krystian892
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE challenges
#include <boost/test/unit_test.hpp>
#include <logic/Challenges.h>
BOOST_AUTO_TEST_CASE(test1){
	ChallengesContainer cc("mytext");
	BOOST_CHECK(cc.hasKey("OctSq_LN_2"));
	BOOST_CHECK(not cc.hasKey("OctSq_PT_5"));
	auto vec = cc.findByGrid("OctSq");
	//BOOST_CHECK_EQUAL(vec.size(), 5);
	BOOST_CHECK_EQUAL(vec[1].level,2);
	cc.add({"Sq_PT_1","Sq","PT",1,"300"});
	cc.add({"Sq_LN_1","Sq","LN",1,"30"});
	cc.serialize("my_out");

}

BOOST_AUTO_TEST_CASE(test2){
	ChallengesContainer cc("mytext");
	ChallengeLogic * cl =ChallengeLogic::get(cc.challenges["TwTriSq_PT_1"]);
	BOOST_CHECK(cl->parseResult(1001,1000,0));
	BOOST_CHECK( not cl->parseResult(999,10,10));
	ChallengeLogic * cl1 =ChallengeLogic::get(cc.challenges["OctSq_MV_2"]);
	BOOST_CHECK(cl1->parseResult(5001,99,500));
	BOOST_CHECK( not cl1->parseResult(999,10,499));
	BOOST_CHECK( not cl1->parseResult(5999,101,502));

	ChallengeLogic * cl2 =ChallengeLogic::get(cc.challenges["OctSq_LN_2"]);
	BOOST_CHECK(cl2->parseResult(0,999,60));
		BOOST_CHECK( not cl2->parseResult(999,10,59));
		delete cl,cl1,cl2;
}

BOOST_AUTO_TEST_CASE(test3){
	ChallengesContainer cc("mytext");
	auto vec =cc.getChallengeTypes("OctSq");
	for(auto v: vec){
		cout<<v<<"\n";
	}
}
