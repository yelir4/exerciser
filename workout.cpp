/*
    workout.cpp implementation file
    exerciser
*/
#ifndef WORKOUT_CPP
#define WORKOUT_CPP

// include the workout.h header (and subsequently the windows api)
#include "workout.h"
#include <iostream>

// workout class is part of the "exerciser" namespace
namespace exerciser {

    // constructor for the rep class
    rep::rep(wchar_t newName[10], int newTimePerRep)
    {
        // iterate through valid indexes
        // wcslen gives length of wchar_t newName[10], not including the null terminating character
        for(int i=0; i<wcslen(newName); ++i)
        {
            //std::cout << (char)newName[i] << std::endl;
            name[i] = (char)newName[i]; // weird unicode characters will be translated to something unintelligible
                                        // its up to the user not to input weird things
        }

        name[wcslen(newName)] = '\0'; // null terminating string character to prevent glitches


        std::cout << name << std::endl;
        timePerRep = newTimePerRep;
    }

    set::set()
    {

    }

    workout::workout()
    {

    }


}

#endif