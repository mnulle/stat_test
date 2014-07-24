
#include <iostream>
using namespace std;

#include<fstream>
using namespace std;

#include<string>
using namespace std;

#include "Stats.h"


Stats::Stats ()
{
    m_pnStats = NULL;
    m_pbyType = NULL;
    m_nSize = 0;
    m_fTime = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

Stats::~Stats ()
{
    delete m_pnStats;
    delete m_pbyType;
    m_nSize = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void	Stats::Calc_Data ()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////

void  Stats::Set_Time (double fTime)
{
    m_fTime = fTime;
    this->Calc_Data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void	Stats::Add_Stat (int nStat, int nVal)
{
	if(nStat >= m_nSize || nStat < 0)
	{
		printf("* Warning: Illegal value for stats field in Add_Stat (%d, %f)\n", nStat, nVal);
		printf("			Max size = %d w/array at 0x%X\n", m_nSize, m_pnStats);
		return;
	}

	m_pnStats[nStat] += nVal;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void	Stats::Get_Title	(int nStat, char * szTitle)
{
	if(nStat >= m_nSize || nStat < 0)
	{
		printf("* Warning: Illegal value for stats field in Get_Stat (%d)\n", nStat);
		printf("			Max size = %d w/array at 0x%X\n", m_nSize, m_pnStats);
		return;
	}

	sprintf(szTitle, "F%04d", nStat);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int  Stats::Get_Stat (int nStat)
{
	if(nStat >= m_nSize || nStat < 0)
	{
		printf("* Warning: Illegal value for stats field in Get_Stat (%d)\n", nStat);
		printf("			Max size = %d w/array at 0x%X\n", m_nSize, m_pnStats);
		return -1;
	}

	return m_pnStats[nStat];
}

void	Stats::Set_Stat (int nStat, int nVal)
{
    if(nStat >= m_nSize || nStat < 0) {
        printf("* Warning: Illegal value for stats field in Set_Stat (%d, %f)\n", nStat, nVal);
        printf("			Max size = %d w/array at 0x%X\n", m_nSize, m_pnStats);
        return;
    }

    m_pnStats[nStat] = nVal;
}

void	Stats::Set_Stat_Type	(int nStat, char byType)
{
	if(nStat >= m_nSize || nStat < 0)
	{
		printf("* Warning: Illegal value for stats field in Set_Stat_Type (%d, %d)\n", nStat, byType);
		printf("			Max size = %d w/array at 0x%X\n", m_nSize, m_pnStats);
		return;
	}

	m_pbyType[nStat] = byType;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void	Stats::Allocate (int nSize)
{
	int		j;

	m_pnStats = new int [nSize];
	m_pbyType = new char   [nSize];
	m_nSize = nSize;

	for(j=0; j<nSize; j++)
	{
		m_pnStats[j] = 0;
		m_pbyType[j] = FIELD_TYPE_ADDITIVE;
	}
}
 
void Stats::writeGIPSE_XML (char * szFile) {
    int j;
    char		szTemp[150];
    char    szOut[250];
    fstream     OutFile;
	   	
    OutFile.open(szFile, ios::out|ios::app);

    Calc_Data ();

    for(j=0; j<m_nSize; j++) {
        Get_Title(j, szTemp);		
        sprintf(szOut, "        <dataPoint name = %c%s%c value = %c%d%c />", 34,szTemp,34,34,m_pnStats[j],34);
        OutFile << szOut << endl;
    } 
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void	Stats::Dump ()
{
    printf("Dumping Stats object at 0x%X\n", this);
  
    int		j, k;
    char	szString[100];    

    for(j=0; j<m_nSize; j+=2)
    {
        for(k=j; k<j+2 && k<m_nSize; k++)
        {
          Get_Title(k, szString);
          printf("%20s: %10d ", szString, m_pnStats[k]);
        }

        printf("\n");
    }  
}

void Stats::syncAll (Stats * pOtherStat)
{
    int		j;

    for(j=0; j<m_nSize; j++)
    {
    	m_pnStats[j] = pOtherStat->m_pnStats[j];
    }
}

void Stats::computeDiff (Stats * p1, Stats * p2)
{
    int		j;

    for(j=0; j<m_nSize; j++)
    {
    	m_pnStats[j] = p2->m_pnStats[j] - p1->m_pnStats[j];
    }
}

void Stats::GetValueString (int nStat, char * szValue)
{
	sprintf(szValue, "%d", m_pnStats[nStat]);
}

void Stats::logCSV_FieldNames   (ofstream & outStream)
{
	char	szTemp[256];
    int		j;

    for(j=0; j<m_nSize; j++)
    {
    	this->Get_Title(j, szTemp);
    	outStream << szTemp << ",";
    }
}


void Stats::logCSV (ofstream & outStream)
{
    int		j;
    char szTemp[128];

    for(j=0; j<m_nSize; j++)
    {
    	this->GetValueString(j,szTemp);
    	outStream << szTemp << ",";
    }
}

void Stats::logCSV_TimeAvg      (ofstream & outStream, double fTime)
{
    int		j;
    double  fResult;

    for(j=0; j<m_nSize; j++)
    {
    	if(fTime > 0)
    	{
    		fResult = (double) m_pnStats[j] / fTime;
    		outStream << fResult << ",";
    	}
    	else
    	{
    		outStream << "0" << ",";
    	}
    }
}


void		Stats::Reset		()
{
    int			j;

    for(j=0; j<m_nSize; j++)
    {
        Set_Stat(j, 0);
    }   
}



void	Stats::operator	+= (Stats & SumVal)
{
    int		j;

	for(j=0; j<m_nSize; j++)
	{
		switch(m_pbyType[j])
		{
			case FIELD_TYPE_ADDITIVE:
				m_pnStats[j] += SumVal.m_pnStats[j];
				break;
			case FIELD_TYPE_CALC:
				break;
			case FIELD_TYPE_STATIC:
				break;
			default:
				printf("* Error: Unable to add fields, undefined field type\n");
				return;
		}
	}

	Calc_Data();
}
