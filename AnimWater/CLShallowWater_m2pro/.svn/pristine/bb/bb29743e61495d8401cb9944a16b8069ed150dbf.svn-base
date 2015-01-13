/****************************************************************************
 Copyright (C) 2010-2013 Alexandre Meyer

 This file is part of CLWater.

 CLWater is free software: you can redistribute it and/or modify
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



#ifndef _CAVIEWER_H
#define _CAVIEWER_H

#include <CLWater.h>
#include <Viewer.h>


class CAViewer : public Viewer
{
public:
    CAViewer() : Viewer(), m_water(gl,prog) {}

	virtual ~CAViewer ();
	virtual void draw();
	virtual void help();
	virtual void init();
	virtual void animate();
	virtual void keyPressed(unsigned char key, int x, int y);
	virtual void specialKeyPressed(int key, int x, int y);

protected :

    clwater::CLWater m_water;
};

#endif
