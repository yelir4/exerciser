/*
    workout.h header file
    exerciser
*/
#ifndef WORKOUT_H
#define WORKOUT_H

// including the winapi here
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>


// class is part of exerciser namespace
namespace exerciser
{

    // rep class goes before workout class so the compiler doesn't complain
    // and because the workout takes reps in its vector
    class rep
    {
    public:
        rep(wchar_t name[10], int timePerRep = 10);
    private:
        char name[10];   // what exactly is the activity you are doing,
        int timePerRep;       // and for how long are you doing it?
    };

    class set
    {
    public:
        set();
    private:
        int iterations; // how many times will you perform this exercise?
        std::vector<rep> setOfInterest; // vector of reps, so that you will perform ALL REPS in the set "iterations" amount of times
    };

    class workout
    {
    public:
        workout();
    private:
        std::vector<set> workoutOfInterest;
    };


}


#endif