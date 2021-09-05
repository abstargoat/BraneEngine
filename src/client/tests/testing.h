#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

class TestFailed : public std::exception
{
private:
	std::string _message;
public:
	TestFailed(std::string message)
	{
		_message = message;
	}
	virtual const char* what() const throw()
	{
		return _message.c_str();
	}
};

class TestRunner
{
private:
	static std::vector<std::string> failedTests;
	static std::string testName;
	static int testIndex;
public:
	static void setTestCatagory(const std::string& name)
	{
		testName = name;
		testIndex = 0;
	}
	static void logFail()
	{
		failedTests.push_back(testName + " Test " + std::to_string(testIndex) + " Failed");
		++testIndex;
	}
	static void logSucess()
	{
		//completedTests.push_back(testName + " Test " + std::to_string(testIndex) + " Failed");
		++testIndex;
	}
	static void printFailedTests()
	{
		for (std::string s : failedTests)
		{
			std::cout << s << std::endl;
		}
	}
	static void throwIfFailed()
	{
		if(failedTests.size() > 0)
			throw TestFailed("A test failed");
	}
	static bool testsSucceeded()
	{
		return failedTests.size() == 0;
	}
};
std::vector<std::string> TestRunner::failedTests;
std::string TestRunner::testName = "";
int TestRunner::testIndex = 0;

#define expectError(x, error)\
	try\
	{\
		x;\
		TestRunner::logFail();\
	}\
	catch(const error& e)\
	{\
		TestRunner::logSucess();\
	}
#define expectValue(x, value)\
	if(x == value)\
		TestRunner::logSucess();\
	else \
		TestRunner::logFail();
