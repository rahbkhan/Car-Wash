#include <assert.h>
#include <cstdlib>
#include <queue>
#include <stdlib.h>
#include <time.h>

using namespace std;

namespace carWash
{

	void start()
	{
		queue<int> q; // this is the waiting line for the cars
                int cur, next, wash_time, s_len, car_denied; 
		// next = car in front of q, cur = # of car that may be added to q, s_len = simulation time
                double a_rate; // arrival rate of cars. range: 0~1
                char answer[2];

                do{
                  cout<<"\nEnter simulation length: ";
                  cin>>s_len;
                  cout<<"Enter wash time for a car: ";
                  cin>>wash_time;
                  cout<<"Enter Arrival rate (0~1): ";
                  cin>>a_rate;

// creation of the wash machine objects
                  washMachine car_wash(wash_time);
	washMachine car_wash2(wash_time), car_wash3(wash_time);

// creation of arrival object
                  arrival car_rate(a_rate);

// creation of the averager obj
                  averager cal;

                  srand(time(NULL));

// for loop that puts car into the waiting q if they are below the acceptance rate (isCarComing)
                  for(cur = 1; cur < s_len; cur++)
                  {
	                  if(car_rate.isCarComing())
        	                  q.push(cur); // put the car in the waiting line

	// this is where i need to decide which car goes where
                          if(!car_wash.isBusy() && !q.empty())
                          {
                                  next = q.front();
                                //cout<<endl<<cur<<" "<< next<< endl;
                                  q.pop();
                                  cal.plusNextNumber( cur - next);
                                  car_wash.startWashing();

                          } // end of if
	// let's put them here as an else if!
			  else if ( !car_wash2.isBusy() && !q.empty() )
			  {
				  next = q.front(); // get it ready to be washed
				  q.pop(); // it's going to the wash, take out of q
				  cal.plusNextNumber( cur - next);
				  car_wash2.startWashing(); // set the wash time left
			
			  } // end of carwash 2 if

			  else if ( !car_wash3.isBusy() && !q.empty() )
			  {
				  next = q.front(); // get it ready to be washed
				  q.pop(); // it's going to the wash, take out of q
				  cal.plusNextNumber( cur - next);
				  car_wash3.startWashing(); // wash it! activate the wash time left

			  } // end of carwash3 if
                
// decrease the washing times left for every machine
		          car_wash.oneSecond(); 
			  car_wash2.oneSecond();
			  car_wash3.oneSecond();
                
	          } // end of for

	// the end of that do things part?


                  car_denied=0;

                  while(!q.empty()) //clean the car queue if any
                  {
	                  q.pop();
                          car_denied++;
                  } // end of while

                  cout<<"\nCars washed were: "<<cal.howManyCars();
                  cout<<"\nThe number of cars denied: "<<car_denied; 
                  cout<<"\nThe average waiting time is: "<< cal.averageTime();

                  cout<<"\nWould you like to do it again (y/n): ";
                  cin>>answer;
                  cout<<endl;


                  }while (tolower(answer[0]) == 'y');

                  cout<<"Thank you for using this program! Bye. " << endl;

       
	} // end of start()

	arrival::arrival(double p) // is passed a_rate from main
	{
		assert( p >= 0 );
		assert( p <= 1 );
		p_rate = p;

	} // end of arrival(double p)

	bool arrival::isCarComing()
	{
		return rand() < p_rate * RAND_MAX;

	} // end of isCarComing	

	washMachine::washMachine(int n)
	{
		timeForWash = n;
		washTimeLeft = 0;

	} // end of washMAchine(int)

	void washMachine::oneSecond()
	{
		if( isBusy() )
			washTimeLeft--; // reduces the amount of time left for the car being washed by 1

	} // end of oneSecond

	void washMachine::startWashing()
	{
		assert( !isBusy() );
		washTimeLeft = timeForWash;

	} // end of startWashing()

	bool washMachine::isBusy()
	{
		return washTimeLeft > 0;

	} // end of isBusy()

	averager::averager()
	{
		cnt = 0;
		sum = 0;

	} // end of averager()

	void averager::plusNextNumber(int value)
	{
		cnt++;
		sum+= value;

	} // end of plusNextNumber()

	double averager::averageTime()
	{
		assert( cnt > 0);
		return (sum / cnt);

	} // end of averageTime()

	int averager::howManyCars()
	{
		return cnt;

	} // end of howManyCars()






}; // end of carWash namespace
