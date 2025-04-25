#include <iostream>
#include <set>
#include <string>
#include "schedwork.h"
using namespace std;

int main () {
    size_t dailyNeed = 1;
    size_t maxShifts = 2;
	// bool expectedResult = false;
    AvailabilityMatrix avail = { 
        {1},
		{1},
        {1}
    };
    DailySchedule sched;

    bool res =  schedule(avail, dailyNeed, maxShifts, sched);
    cout << res << endl;

	
}