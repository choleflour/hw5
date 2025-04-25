#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    for (size_t d = 0; d < avail.size(); ++d) {
        std::vector<Worker_T> day;
        sched.push_back(day);
    }

    std::vector<size_t> hours(avail[0].size());

    // return schedule_helper(avail, dailyNeed, maxShifts, sched, hours, 0,0);
    return schedule_helper(avail, dailyNeed, maxShifts, sched, 0, hours);



}

// array [] of worker hours (where index = worker ids)
// start w day = 0
bool schedule_helper ( const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t day, std::vector<size_t>& hours ) {

    // base case: when you reach the last row/day
    if (day == avail.size()) {
        return true;
    }

    // check if enough workers for the day, if so move to the next day
    if (sched[day].size() >= dailyNeed) {
        return schedule_helper(avail, dailyNeed, maxShifts, sched, day + 1, hours);
    }

    // move to the next col
    for (size_t c = 0; c < avail[0].size(); ++c ) {
        // if not in sched
        if (std::find(sched[day].begin(), sched[day].end(), c) == sched[day].end()) {
            if (avail[day][c] && hours[c] < maxShifts) {
            
                hours[c] += 1;
                sched[day].push_back(c);
                // shifts += 1
    
                bool status = schedule_helper(avail, dailyNeed, maxShifts, sched, day, hours);
                if (status) {
                    return true; 
                }
        
    
                hours[c] -= 1;
                sched[day].pop_back();
                // shifts -= 1;
    
            }

        }


    }

    return false;
}
