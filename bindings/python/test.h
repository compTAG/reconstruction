#pragma once

// #include <ctag/test.h>


namespace ctag {

class Test {
public:
	/**
	* Simple class example
	*/
  Test() {}
  int add(int a, int b){ return a+b;}
};

};

using PyTest = ctag::Test;

