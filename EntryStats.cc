
#include <iostream>
using namespace std;

#include<fstream>
using namespace std;

#include<string>
using namespace std;

#include "Stats.h"


EntryStats::EntryStats ()
{
    m_pnStats = NULL;
    m_pbyType = NULL;
    m_nSize = 0;
    m_fTime = 0.0;
}

