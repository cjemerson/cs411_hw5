// build.cpp
// Charles Emerson
// Created: 23 September 2019
// Updated: 13 November 2019
//
// For CS 411 Fall 2019
// Source for function build
// Solution to Assignment 5, Exercise A
//
// This is a fork from my solution for Assignment 2, Exercise A
// https://github.com/cjemerson/cs411_hw5/

#include "build.hpp"


/***** FUNCTION DECLARATIONS *****/

// Helper function
// (definition and documentation below)
void sortAndCull(std::vector<std::vector<int>> & bridges);

/***** HELPER CLASS DECLARATION *****/
// DynProgrammingBuildContext Class Declaration
// Maintains a list of memorized results
class DynProgrammingBuildContext
{
public:
    // Changes ownership of bridges and creates empty list of memoized results
    DynProgrammingBuildContext(std::vector<std::vector<int>> && bridges)
        : _memoizedResults(bridges.size(), 0),
          _bridges{}
    {
        std::swap(_bridges, bridges);
        sortAndCull(_bridges);
    }

    // Public Interface
    // Wrapper Function for build_recurse()
    inline int build()
    {
        return build_recurse();
    }

private:
    // Memoization Functions
    inline int getMemoizedResult(int i) const
    {
        return _memoizedResults[i];
    }

    inline void setMemoizedResult(int i, int value)
    {
        _memoizedResults[i] = value;
    }

    // Workhorse function (RECURSIVE)
    // *** Default arguments specified here. ***
    // (definition and documentation below)
    int build_recurse(int i = 0, int nextWestCity = 0, int nextEastCity = 0);

private:
    std::vector<int> _memoizedResults;
    std::vector<std::vector<int>> _bridges;
};


/***** PUBLIC INTERFACE FUNCTION DEFINITION *****/

// build - Wrapper function (RECURSIVE)
// Finds the maximum cumulative toll possible for a given a set of
// bridges. Bridges can be combined if they do not start from the
// same West city, end at the same East city or cross another.
//
// The following defines crossing bridges:
//   Two bridges {w1, e1, t1} and {w2, e2, t2} cross,
//     if (w1 < w2 and e1 > e2) or (w1 > w2 and e1 < e2)
//
// The bridge format is {West city number, East city number, toll}
//
// Preconditions:
//   * w must be greater than the maximum West City
//   * e must be greater than the maximum East City
//   * bridges is a vector of size-3 vectors
int build(int w, int e, std::vector<std::vector<int>> bridges)
{
    (void) w, (void) e; // To suppress -Wunused-parameter

    DynProgrammingBuildContext solution(std::move(bridges));

    return solution.build();
}


/***** RECURSIVE WORKHORSE FUNCTION DEFINITION *****/

// build_recurse - Workhorse function (RECURSIVE)
// Finds the maximum toll by recursively combining of bridges that do
// not cross. The variable i is the index of the bridge currently
// considered. The variables nextWestCity and nextEastCity represent
// the lowest bridge connections under consideration.
//
// Default args (See declaration):
//   * i = 0
//   * nextWestCity = 0
//   * nextEastCity = 0
// Preconditions:
//   * i, nextWestCity and nextEastCity are initially zero
//      (in the first recursive call).
//   * _bridges is sorted according to sortAndCull()
//   * _memoizedResult is filled with zeroes
// Invariants:
//   * [nextWestCity, max West City] is available for a bridge or
//      nextWestCity > max West city.
//   * [nextEastCity, max East City] is available for a bridge or
//      nextEastCity > max East city.
int DynProgrammingBuildContext::build_recurse(int i, int nextWestCity, int nextEastCity)
{
    const int BRIDGES_SIZE = int(_bridges.size());

    // If we are at the end of the bridges
    if (i >= BRIDGES_SIZE)
    {
        return 0;
    }

    auto max_toll = 0;
    auto current_w = _bridges[i][0];
    auto current_e = _bridges[i][1];

    // If we can place a bridge
    if (current_w >= nextWestCity && current_e >= nextEastCity)
    {
        // Use the memoized result if we have it
        if ( !(max_toll = getMemoizedResult(i)) )
        {
            // Try with the bridge
            auto temp = _bridges[i][2] + build_recurse(i + 1, current_w + 1, current_e + 1);
            max_toll = (max_toll < temp)? temp : max_toll;

            // Save the result (using this bridge)
            setMemoizedResult(i, max_toll);
        }
    }

    // Try without the bridge
    auto temp = build_recurse(i + 1, nextWestCity, nextEastCity);
    max_toll = (max_toll < temp)? temp : max_toll;

    return max_toll;
}


/***** HELPER FUNCTION DEFINITIONS *****/

// sortAndCull - Helper function (Modifies the set of bridges)
// Sorts the set of bridges in ascending order of West to East cities,
// then in descending order of toll. Duplicate bridges with less than
// or equal toll are removed from the set of bridges.
void sortAndCull(std::vector<std::vector<int>> & bridges)
{
    // Sort bridges in the following order:
    //   1) Ascending order of West city numbers (Lowest to Highest)
    //   2) Ascending order of East city numbers (Lowest to Highest)
    //   3) Descending order of bridge tolls (Highest to Lowest)
    std::sort(bridges.begin(), bridges.end(),
        [](const auto & a, const auto & b)
        {
            return std::forward_as_tuple(a[0], a[1], -a[2]) < std::forward_as_tuple(b[0], b[1], -b[2]);
        });

    // Cull every subsequent duplicate bridge after the first.
    // (Duplicate bridges, which have the same West and East cities,
    // are consecutive in order of highest toll to lowest toll.)
    int last_w = -1, last_e = -1;

    auto it = std::remove_if(bridges.begin(), bridges.end(),
        [&](const auto & bridge)
        {
            auto value = bridge[0] == last_w && bridge[1] == last_e;
            last_w = bridge[0], last_e = bridge[1];
            return value;
        });

    bridges.erase(it, bridges.end());
}
