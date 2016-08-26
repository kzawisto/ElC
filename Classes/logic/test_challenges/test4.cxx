/*
 * test4.cxx
 *
 *  Created on: Oct 25, 2015
 *      Author: krystian892
 */
#include <iosfwd>
#include <map>
#include <string>

using std::map;
using std::string;

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE module4

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test41){
	map<string, int> m = {{"Karol",1},{"Kamil",1}, {"Ewa",2},{"Karolina",1},{"Katarzyna",3}};
	BOOST_CHECK(m.lower_bound("Kry") == m.end());
	BOOST_CHECK(m.upper_bound("Kry") == m.end());
	map<string, int> m1 {m.lower_bound("Ka"), m.upper_bound(string("Ka") + char(127))};
	BOOST_CHECK_EQUAL(m1.size(),4);
	std::cout<<int('_');
}


BOOST_AUTO_TEST_CASE(test42){


}
