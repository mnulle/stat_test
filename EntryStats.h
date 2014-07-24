/* Stats.h : Adapted from the GenMCast module for ns-2
 **********************************************************
 * This code is part of the Scalability in a Box (ScaleBox)
 * system developed at the University of Notre Dame. 
 * 
 * For additional information, please visit the NetScale
 * laboratory webpage at:
 *    http://netscale.cse.nd.edu/
 *
 * PI:       Dr. Aaron Striegel    striegel@nd.edu
 * 
 **********************************************************
 * $Revision: 1.1.1.1 $  $Date: 2008/02/13 04:21:21 $
 **********************************************************
 */

#ifndef STATS_H_
#define STATS_H_

#include <string>
using namespace std;

#include <iostream>
#include <fstream>
using namespace std;

#include "Stats.h"

class NodeDOM;

enum
{
	FIELD_TYPE_ADDITIVE=0,					// Add the field like normal
	FIELD_TYPE_CALC,						// Calculated file -> don't bother copying
	FIELD_TYPE_STATIC,						// Fixed value -> does not change

	// Do not erase this last entry!

	FIELD_TYPE_LAST
};

/** @brief The base class for deriving all stat objects
 * 
 *  The stats object allows all of the various multicast entities to share a common stat
 * basis. As a result, one can simply query each node, get the stats, and add/combine all of
 * them together. 
 */
class EntryStats: public Stats
{
	public:
		EntryStats  ();
};

#endif /*STATS_H_*/
