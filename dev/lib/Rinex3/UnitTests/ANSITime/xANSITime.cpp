#include "xANSITime.hpp"
#include <iostream>
#include <fstream>

CPPUNIT_TEST_SUITE_REGISTRATION (xANSITime);

using namespace gpstk;

void xANSITime :: setUp (void)
{
}

void xANSITime :: setFromInfoTest (void)
{
	Rinex3::ANSITime setFromInfo1;
	Rinex3::ANSITime setFromInfo2;
	
	gpstk::TimeTag::IdToValue Id;

	Id.insert(make_pair('K',"13500000"));
	CPPUNIT_ASSERT(setFromInfo1.setFromInfo(Id));
	Id.erase('K');
	CPPUNIT_ASSERT(setFromInfo2.setFromInfo(Id));
	ofstream out("Logs/printfOutput");
	
	out << setFromInfo1 << endl;
	out << setFromInfo2 << endl;
}

void xANSITime :: operatorTest (void)
{
	
	Rinex3::ANSITime Compare(13500000);
	Rinex3::ANSITime LessThan(13400000);
	Rinex3::ANSITime CompareCopy(Compare);
	Rinex3::ANSITime CompareCopy2;

	//Assignment
	CompareCopy2 = CompareCopy;
	//Equality Assertion
	CPPUNIT_ASSERT_EQUAL(Compare,CompareCopy);
	//Non-equality Assertion
	CPPUNIT_ASSERT(Compare != LessThan);
	//Less than assertions
	CPPUNIT_ASSERT(LessThan < Compare);
	CPPUNIT_ASSERT(!(Compare < LessThan));
	//Greater than assertions
	CPPUNIT_ASSERT(Compare > LessThan);
	//Less than equals assertion
	CPPUNIT_ASSERT(LessThan <= Compare);
	CPPUNIT_ASSERT(CompareCopy <= Compare);
	//Greater than equals assertion
	CPPUNIT_ASSERT(Compare >= LessThan);
	CPPUNIT_ASSERT(Compare >= CompareCopy);
	
	CPPUNIT_ASSERT(Compare.isValid());
}

void xANSITime :: resetTest (void)
{
	Rinex3::ANSITime Compare(13500000,gpstk::GPS);

	CPPUNIT_ASSERT_EQUAL(gpstk::GPS,Compare.getTimeSystem());
	CPPUNIT_ASSERT_EQUAL(13500000,(int)Compare.time);

	Compare.reset();
	CPPUNIT_ASSERT_EQUAL(gpstk::Unknown,Compare.getTimeSystem());
	CPPUNIT_ASSERT_EQUAL(0,(int)Compare.time);
}

void xANSITime :: timeSystemTest (void)
{
	Rinex3::ANSITime GPS1(13500000,gpstk::GPS);
	Rinex3::ANSITime GPS2(13400000,gpstk::GPS);
	Rinex3::ANSITime UTC(13500000,gpstk::UTC);
	Rinex3::ANSITime UNKNOWN(13500000,gpstk::Unknown);

	CPPUNIT_ASSERT(GPS1 != GPS2);
	CPPUNIT_ASSERT(GPS1 != UTC);
	CPPUNIT_ASSERT(GPS1 != UNKNOWN);
	CPPUNIT_ASSERT(GPS1.convertToCommonTime() > gpstk::CommonTime::BEGINNING_OF_TIME);
	CPPUNIT_ASSERT(gpstk::CommonTime::BEGINNING_OF_TIME < GPS1);
}