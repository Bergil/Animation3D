/****************************************************************************
Copyright (C) 2010-2011 Alexandre Meyer

This file is part of Sami library.

Sami is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sami is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sami.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/


#ifndef TIMER_H
#define TIMER_H

#ifdef WIN32
# include <windows.h>
#else 
# include <sys/time.h>
# include <unistd.h>
#endif //WIN32

#include <iostream>


namespace clwater
{

#define USEC_BY_SEC 1000000

	/** @addtogroup Tools
    @{
*/

/*! \brief A simple timer. */
class Timer
{
public:

	/*! \brief The default constructor. Do nothing. */  
	Timer() : m_bPause( false ) {}

	/*! \brief Start the timer. */  
	void	start();

	/*! \brief Set the timer to a pause state, or lets it continue.
	 *  \param bPause Set the time in pause state or not. */
	void	pause( bool bPause = true );

	bool	isPaused() const;

	/*! \brief Return the time elapsed since the start (pause time is removed).
	 *  \return Time elapsed in seconds. */
	double	elapsedTime() const;

protected:

#ifdef WIN32
	LARGE_INTEGER m_start;
	LARGE_INTEGER m_pause;
	LARGE_INTEGER m_freq;
#else
	timeval m_start;
	timeval m_pause;
#endif //WIN32
	
	bool m_bPause;
};

//=============================================================================================
// 
//=============================================================================================
inline void Timer::start()
{
#ifdef WIN32
	QueryPerformanceFrequency( &m_freq );
	QueryPerformanceCounter( &m_start );
#else
	gettimeofday( &m_start, NULL );
#endif //WIN32
    m_bPause = false;

}

//=============================================================================================
// 
//=============================================================================================
inline void Timer::pause( bool bPause )
{
	if ( m_bPause == bPause ) 
		return;
	else if ( bPause )
	{
#ifdef WIN32
		QueryPerformanceCounter( &m_pause );
#else
		gettimeofday( &m_pause, NULL );
#endif //WIN32
		m_bPause = true;
	}
	else if ( !bPause )
	{
#ifdef WIN32
		LARGE_INTEGER now;
		QueryPerformanceCounter( &now );
		m_start.QuadPart += now.QuadPart - m_pause.QuadPart;
#else
		timeval now;
		gettimeofday( &now, NULL );
		m_start.tv_sec  += ( now.tv_sec  - m_pause.tv_sec  );
		m_start.tv_usec += ( now.tv_usec - m_pause.tv_usec );
#endif //WIN32
		m_bPause = false;
	}	
}

//=============================================================================================
// 
//=============================================================================================
inline bool	Timer::isPaused() const
{
	return m_bPause;
}

//=============================================================================================
// 
//=============================================================================================
inline double Timer::elapsedTime() const
{
#ifdef WIN32
	static LARGE_INTEGER now;
#else
	static timeval now;
#endif //WIN32

	if ( !m_bPause )
#ifdef WIN32
		QueryPerformanceCounter( &now );
#else
		gettimeofday( &now, NULL );
#endif //WIN32
	else 
	{
#ifdef WIN32
		now.QuadPart = m_pause.QuadPart;
#else
		now.tv_sec = m_pause.tv_sec;
		now.tv_usec= m_pause.tv_usec;
#endif //WIN32
	}
#ifdef WIN32
	return static_cast<double>( now.QuadPart - m_start.QuadPart ) / static_cast<double>( m_freq.QuadPart );
#else
	int elapsed_sec = now.tv_sec - m_start.tv_sec;
	int elapsed_usec;

	if ( now.tv_usec < m_start.tv_usec )
	{
		elapsed_sec--;
		elapsed_usec = USEC_BY_SEC - ( m_start.tv_usec - now.tv_usec );
	}
	else 
		elapsed_usec = now.tv_usec - m_start.tv_usec;

	return static_cast<double>( elapsed_sec ) + static_cast<double>( elapsed_usec ) / static_cast<double>( USEC_BY_SEC );
#endif//WIN32
}


inline char* printTime(unsigned long int clockMS, char txt[])
{
    int ms = static_cast<int>(clockMS%1000);
    int s = static_cast<int>(clockMS/1000);
    int m = s/60;
    s = s%60;
    sprintf( txt, "%dm%ds%dms", m, s, ms);
    return txt;
}

/** @}
*/


} // namespace 

#endif //TIMER_H

