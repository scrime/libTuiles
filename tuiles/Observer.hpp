/***************************************************************************
 *  Observer.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef Observer_h
#define Observer_h

namespace tuiles {

class Observer {	
	public:
		virtual ~Observer(){}
		virtual void notifyUpdate()=0;
        virtual void notifyDelete()=0;
};

}

#endif

