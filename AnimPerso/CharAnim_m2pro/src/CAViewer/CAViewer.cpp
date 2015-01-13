

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>
#include "CAViewer.h"
#include <BVH.h>
#include <BVHChannel.h>
#include <Mat4.h>
#include <Quaternion.h>
#include "Tools.h"

using namespace chara;
using namespace std;


void CAViewer::help()
{
	printf("Animation:\n");
	printf("   n: Next character pose\n");
	printf("   b: Back(Previous) character pose");
	printf("   shift+arrows: Move the target point");
	Viewer::help();
}

CAViewer::~CAViewer()
{
}

void CAViewer::init()
{
	Viewer::init();
	start = std::chrono::system_clock::now();
	//std::string fn_front = "G:/alex/code/CharAnim_m2pro/data/OneArm.bvh";
	//std::string fn_front = "/home/pers/alexandre.meyer/code/CharAnim_m2pro/data/OneArm.bvh";
	//std::string fn_front = "../data/OneArm.bvh";
	std::string fn_front = "../data/danse.bvh";

	if (fn_front!="")
	{
		std::string current_file( fn_front );
		printf("%s\n", current_file.c_str());
		m_bvh = new BVH(current_file.c_str(), true );

		cout<<"BVH"<<endl;
		cout<<*m_bvh<<endl;
		cout<<"------------"<<endl;
	}
	else cout<<"No BVH\n";
	m_skel.remplissageSkeleton(m_bvh->getRoot(), -1);
    m_target.set( 10, 10, 0);
}

void CAViewer::draw()
{
    glPushMatrix();
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	auto framemilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds);
	
    float animTime = m_bvh->getFrameTime();
    if( framemilliseconds.count() >= animTime){
		start = std::chrono::system_clock::now();
		animate();
	}
	//bvhTransitionDrawGL(*m_bvh, m_bvhFrame, *m_bvh, (m_bvhFrame+1)%m_bvh->getNumFrame(), framemilliseconds.count()/1000.0/animTime);
	m_skel.setPose(*m_bvh, m_bvhFrame);
	m_skel.drawGL();	
    glPopMatrix();

}

void CAViewer::bvhTransitionDrawGL(const BVH& bvhSRC, int frameNumberSRC, const BVH& bvhDST, int frameNumberDST, const float interpolationValue){
	bvhTransitionDrawGLRec(*bvhSRC.getRoot(), frameNumberSRC, *bvhDST.getRoot(), frameNumberDST,interpolationValue);
	float i = calculDistanceEntrePoses(bvhSRC,  frameNumberSRC,bvhDST,frameNumberDST);
	cout<<"calculDistanceEntrePoses = "<<i<<endl;
}
void CAViewer::bvhTransitionDrawGLRec(const BVHJoint& bvhSRC, int frameNumberSRC, const BVHJoint& bvhDST, int frameNumberDST, const float interpolationValue){
	
	glPushMatrix();
	
	math::TQuaternion<float> TQsrc;
	math::TQuaternion<float> TQdst;
	math::Vec3<float> vecTrans(0.0,0.0,0.0);
	math::Vec3<float> vecAxisX(1.0,0.0,0.0);
	math::Vec3<float> vecAxisY(0.0,1.0,0.0);
	math::Vec3<float> vecAxisZ(0.0,0.0,1.0);
	float v[3];
	bvhSRC.getOffset(v[0], v[1], v[2]);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(v[0], v[1], v[2]);
	glEnd();
	glTranslatef(v[0], v[1], v[2]);
	 
	
	for(int i = 0; i < bvhSRC.getNumChannel(); i++){
		chara::BVHChannel* chan = bvhSRC.getChannel(i);
		if(chan->isRotation()){
			switch(chan->getAxis()){
				case AXIS_X : 
							TQsrc *= math::TQuaternion<float>(vecAxisX, convertDegreeToRadian(chan->getData(frameNumberSRC)));
							TQdst *= math::TQuaternion<float>(vecAxisX, convertDegreeToRadian(chan->getData(frameNumberDST)));
							//glRotatef(chan->getData(frameNumber),1,0,0);
							break;
				case AXIS_Y : 
							TQsrc *= math::TQuaternion<float>(vecAxisY, convertDegreeToRadian(chan->getData(frameNumberSRC)));
							TQdst *= math::TQuaternion<float>(vecAxisY, convertDegreeToRadian(chan->getData(frameNumberDST)));

							//glRotatef(chan->getData(frameNumber),0,1,0);
							break;
				case AXIS_Z : 
							TQsrc *= math::TQuaternion<float>(vecAxisZ, convertDegreeToRadian(chan->getData(frameNumberSRC)));
							TQdst *= math::TQuaternion<float>(vecAxisZ, convertDegreeToRadian(chan->getData(frameNumberDST)));
							//glRotatef(chan->getData(frameNumber),0,0,1);
							break;
			}
					
		}else if(chan->isTranslation()){
			switch(chan->getAxis()){
				case AXIS_X : 
							vecTrans[0] = chan->getData(frameNumberSRC)*(1-interpolationValue) + chan->getData(frameNumberDST)*(interpolationValue);
							break;
				case AXIS_Y : 
							vecTrans[1] = chan->getData(frameNumberSRC)*(1-interpolationValue) + chan->getData(frameNumberDST)*(interpolationValue);
							break;
				case AXIS_Z : 
							vecTrans[2] = chan->getData(frameNumberSRC)*(1-interpolationValue) + chan->getData(frameNumberDST)*(interpolationValue);
							break;
			}		
		}
	}
	TQsrc = math::TQuaternion<float>::slerp(TQsrc, TQdst, interpolationValue);
	glTranslatef(vecTrans[0], vecTrans[1], vecTrans[2]);		
	glRotatef(convertRadianToDegree(TQsrc.angle()), TQsrc.axis()[0], TQsrc.axis()[1], TQsrc.axis()[2] );
	draw_cube();
	for(int i = 0; i < bvhSRC.getNumChild(); i++){
		bvhTransitionDrawGLRec(*bvhSRC.getChild(i), frameNumberSRC, *bvhDST.getChild(i), frameNumberDST, interpolationValue );
	}
	glPopMatrix();
}



void CAViewer::bvhDrawGL(const BVH& b, int frameNumber){	
	bvhDrawGLRec(*b.getRoot(), frameNumber);
}


void CAViewer::bvhDrawGLRec(const BVHJoint& b, int frameNumber){ // la fonction récursive sur le squelette
	
	glPushMatrix();
	float v[3];
	b.getOffset(v[0], v[1], v[2]);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(v[0], v[1], v[2]);
	glEnd();
	glTranslatef(v[0], v[1], v[2]);
	
	for(int i = 0; i < b.getNumChannel(); i++){
		chara::BVHChannel* chan = b.getChannel(i);
		if(chan->isRotation()){
			switch(chan->getAxis()){
				case AXIS_X : 
							glRotatef(chan->getData(frameNumber),1,0,0);
							break;
				case AXIS_Y : 
							glRotatef(chan->getData(frameNumber),0,1,0);
							break;
				case AXIS_Z : 
							glRotatef(chan->getData(frameNumber),0,0,1);
							break;
			}					
		}
		else if(chan->isTranslation()){
			switch(chan->getAxis()){
				case AXIS_X : 
							glTranslatef(chan->getData(frameNumber),0,0);
							break;
				case AXIS_Y : 
							glTranslatef(0,chan->getData(frameNumber),0);
							break;
				case AXIS_Z : 
							glTranslatef(0,0,chan->getData(frameNumber));
							break;
			}		
		}
	}
	draw_cube();
	for(int i = 0; i < b.getNumChild(); i++){
		bvhDrawGLRec(*b.getChild(i), frameNumber);
	}
	glPopMatrix();
}

void CAViewer::keyPressed(unsigned char key, int x, int y)
{
	bool handled = false;
	if ((key=='n'))
	{
		++m_bvhFrame;
		//m_skel->setPostureFromBVH( *m_bvh, m_bvhFrame);
		handled = true;
	}
	else
	if ((key=='b'))
	{
		--m_bvhFrame;
		//m_skel->setPostureFromBVH( *m_bvh, m_bvhFrame);
		handled = true;
	}
	else
	if (key=='w')
	{
		bWireframe = !bWireframe;
		if (bWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		handled = true;
	}

	if (!handled)
	{
		Viewer::keyPressed(key,x,y);
	}
	updateGL();
}


void CAViewer::specialKeyPressed(int key, int x, int y)
{
	bool handled = false;

	if (glutGetModifiers()==GLUT_ACTIVE_SHIFT)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			m_target.y += 1;
			handled=true;
			break;
		case GLUT_KEY_DOWN:
			m_target.y -= 1;
			handled=true;
			break;
		case GLUT_KEY_LEFT:
			m_target.x -= 1;
			handled=true;
			break;
		case GLUT_KEY_RIGHT:
			m_target.x += 1;
			handled=true;
			break;
		case GLUT_KEY_PAGE_UP:
			m_target.z += 1;
			handled=true;
			break;
		case GLUT_KEY_PAGE_DOWN:
			m_target.z -= 1;
			handled=true;
			break;
		}
	}


	if (!handled)
	{
        Viewer::specialKeyPressed(key,x,y);
	}
	updateGL();
}



void CAViewer::animate()
{
	if (m_bvh)
	{
		++m_bvhFrame;
		if (m_bvhFrame>=m_bvh->getNumFrame()) m_bvhFrame=0;
		//m_skel->setPostureFromBVH( *m_bvh, m_bvhFrame);
	}
}


