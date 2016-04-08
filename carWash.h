// This is carWash.h
// for the carWash program
// declares a new namespace (carWash),
// and the 3 classes that go in it: arrival, washMachine, and averager

#ifndef carWash_h_
#define carWash_h_

#include <iostream>

namespace carWash
{
	void start(); // the start function to be used in main

	class arrival
	{
		double p_rate; // will be set to be a_rate in the constructor

	  public:
		
		arrival(double); // is passed a_rate from main
		bool isCarComing(); // compares a generated random number to acceptance rate, if <=, then car is coming

	}; // end of arrival class

	class washMachine
	{
		int timeForWash, washTimeLeft; // how long the machine takes to wash a car. how much longer the machine has to wash the car

	  public:
		
		washMachine(int); // accepts washTime from main, sets timeToWash = to washTime
		void oneSecond(); // reduces the washTimeLeft by one second if the machine is in use
		bool isBusy(); // checks if the machine is washing a car
		void startWashing(); // if the machine isnt busy, accepts the car and sets the washTimeLeft

	}; // end of washMachine class

	class averager
	{
		double sum; // stores the sum of wait times for the cars
		int cnt; // stores the amount of cars that came

	  public:

		averager(); // sets cnt and sum to 0
		void plusNextNumber(int); // accepts cur - next from main, adds that value to the sum, increases count
		int howManyCars(); // returns the count
		double averageTime(); // returns the total wait-time divided by the number of cars that came

	}; // end of average class 


}; // end of namespace

#include "carWash.cpp"

#endif
