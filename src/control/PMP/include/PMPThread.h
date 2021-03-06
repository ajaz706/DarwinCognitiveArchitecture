// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
  * Copyright (C)2013  Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
  * Author:Vishwanathan Mohan
  * email: Vishwanathan Mohan@iit.it
  * Permission is granted to copy, distribute, and/or modify this program
  * under the terms of the GNU General Public License, version 2 or any
  * later version published by the Free Software Foundation.
  *
  * A copy of the license can be found at
  * http://www.robotcub.org/icub/license/gpl.txt
  *
  * This program is distributed in the hope that it will be useful, but
  * WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
  * Public License for more details
*/

/**
 * @file PMPThread.h
 * @brief Definition of a thread that computes the PMP output.
 */


#ifndef _PMP_THREAD_H_
#define _PMP_THREAD_H_

#include <yarp/sig/all.h>
#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <yarp/os/RateThread.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
//#include "segment.h"
#include <math.h>
#include <vector>

#define COMMAND_VOCAB_INIT   VOCAB4('I','N','I','T')
#define COMMAND_VOCAB_CACT   VOCAB4('C','A','C','T')
#define COMMAND_VOCAB_BCHA   VOCAB4('B','C','H','A')
#define COMMAND_VOCAB_MSIM   VOCAB4('M','S','I','M')
#define COMMAND_VOCAB_TRAJ   VOCAB4('T','R','A','J')
#define COMMAND_VOCAB_MICG   VOCAB4('M','I','C','G')
//#define COMMAND_VOCAB_GLEF   VOCAB4('G','L','E','F')
#define COMMAND_VOCAB_OBST   VOCAB4('O','B','S','T')
//#define COMMAND_VOCAB_ORIG   VOCAB4('O','R','I','G')
#define COMMAND_VOCAB_WRIO   VOCAB4('W','R','I','O')
#define COMMAND_VOCAB_FAILED VOCAB4('F','A','I','L')
#define COMMAND_VOCAB_REA    VOCAB3('R','E','A')
#define COMMAND_VOCAB_OK     VOCAB2('O','K')



class PMPThread : public yarp::os::Thread {
private:
    std::string robot;              // name of the robot
    std::string configFile;         // name of the configFile where the parameter of the camera are set
    std::string inputPortName;      // name of input port for incoming events, typically from aexGrabber
    std::string weights1Path, weights2Path, weights3Path, biases1Path, biases2Path, biases3Path;  // paths to files containing weights and biases  
    FILE *Weight1,*Weight2,*Weight3,*bias1,*bias2,*bias3;
    const static int inputL=10,hiddenL1=48,hiddenL2=55,outputL=3;
    double w1[hiddenL1][inputL],w2[hiddenL2][hiddenL1],w3[outputL][hiddenL2],b1[hiddenL1],b2[hiddenL2],b3[outputL];
	//yarp::os::BufferedPort<yarp::os::Bottle > MotCom;     // output port to command the robot
	//yarp::os::BufferedPort<yarp::os::Bottle > Inp3D;      // input port to receive 3d information 
	//yarp::os::BufferedPort<yarp::os::Bottle > Inpjoints;
	
	// output ports to command the robot parts
	yarp::os::BufferedPort<yarp::os::Bottle > cmdLeft_armPort,cmdRight_armPort,cmdTorsoPort,cmdInterfacePort,cmdEndEffectorPort;
	yarp::os::BufferedPort<yarp::os::Bottle > gazePort;
	yarp::os::BufferedPort<yarp::os::Bottle > activationsPort;

	//PMPServer to Observer
	yarp::os::RpcServer PMPResponse; //server responding to Observer Client Port(/BodySchemaSim/io), with the result and motor commands
   	double *foof;
	std::string name;           // rootname of all the ports opened by this thread
    bool verboseFile, verboseTerm;
    std::ofstream wr,wr1,posi,wrL,wr_GamL,wr1L,posiL,wr_Gam,wr_Test; //output file pointers
    FILE  *jacFile;
    /*	
        double Jan[6];
		double x_ini; 
		double y_ini;
		double z_ini; 
		double x_fin,y_fin,z_fin;
    	double Gam_Arr[20000],Gam_Arry[20000],Gam_Arrz[20000],q1[20000],q2[20000],q3[20000],q4[20000],q5[20000];
		double janini0,janini3,janini4,janini5,janini6,janini1,janini2, csi_dot;
		double q6[20000];
		double ang1,ang2,ang3,ang4,ang5,ang6,konst;
		std::vector<double> movingjoints;
		double target[3];
		double X_pos[3],ffield[3],JoVel[6];
		double x_iniIC,y_iniIC,z_iniIC;
		double *ptr;
		double KFORCE,ITERATION,RAMP_KONSTANT,t_dur,KOMP_JANG,J2H,J3H;
		float s[5000];
	*/
    int ParamStiff;
    int ResPM;
    double VTGSIN[14]; // Comment VM 27 Feb: this has to be updated if we are usign both robots and making a choice which one will move
    
    double Jan[10];
    double JanL[10],Jvel[20]; //initial Joint angles
    double a[3], aL[3], aLRH[3], res[3], resL[3];
    
    double x_ini; // Using PMP+ Symmetry So Right and Left Arm movements are
    // coordinated by the forward inverse model of the left arm only
    double y_ini;
    double z_ini; 
    double x_iniL; // Init Config / O/p of target generator
    double y_iniL;
    double z_iniL;
    
    double x_fin,y_fin,z_fin;
    double x_finL,y_finL,z_finL;
    
    double Gam_Arr[20000],Gam_Arry[20000],Gam_Arrz[20000],q1[20000],q2[20000],q3[20000],q4[20000],q5[20000];
    double q6[20000],q7[20000],q8[20000],q9[20000],q10[20000];
    
    double Gam_ArrL[20000],Gam_ArryL[20000],Gam_ArrzL[20000],q1L[20000],q2L[20000],q3L[20000],q4L[20000],q5L[20000];
    double q6L[20000],q7L[20000],q8L[20000],q9L[20000],q10L[20000];
    
    double ang1,ang2,ang3,ang4,ang5,ang6,ang7,ang8,ang9,ang10;
    double ang1L,ang2L,ang3L,ang4L,ang5L,ang6L,ang7L,ang8L,ang9L,ang10L;

    double angCup,angT1,angT2,angT3,angI1,angI2,angM1,angM2,angRP,angCupL,angTL1,angTL2,angTL3,angIL1,angIL2,angML1,angML2,angRPL;
        
    double janini3,janini4,janini5,janini6,janini7,janini8,janini9,janini0,janini1,janini2;
    double janini3L,janini4L,janini5L,janini6L,janini7L,janini8L,janini9L;
	
    double x_iniIC,y_iniIC,z_iniIC,x_iniICL,y_iniICL,z_iniICL;
    double target[3],targetL[3];
    double X_pos[3],ffield[3],JoVel[20],X_posL[3],ffieldL[3];
    double *ptr;
    double KFORCE,ITERATION,RAMP_KONSTANT,t_dur;
    double KOMP_JANG,KOMP_WAISZT,KOMP_WAISZT2;
    double J0H,J1H,J2H,J5H,J6H,J7H,J8H,J9H,J3H,J4H;
    float s[5000];
    //		int ParamStiff;
    double x_fin1,y_fin1,z_fin1,x_fin2,y_fin2,z_fin2,x_fin1L,y_fin1L,z_fin1L,x_fin2L,y_fin2L,z_fin2L;
    double Gam_Arr1[20000],Gam_Arry1[20000],Gam_Arrz1[20000];
    double Gam_Arr2[20000],Gam_Arry2[20000],Gam_Arrz2[20000];
    double Gam_Arr1L[20000],Gam_Arry1L[20000],Gam_Arrz1L[20000];
    double Gam_Arr2L[20000],Gam_Arry2L[20000],Gam_Arrz2L[20000];
    double KXA,KXB,KYA,KYB,KXAL,KXBL,KYAL,KYBL,x_off1,z_off1,x_off2,z_off2,STARTini,FrameRef,XinitTarg,ZinitTarg,csi_dot1,csi_dot;
    int dividen,NoBjS,Obj1ID,Obj2ID,GoalCodePMP,BodyChain,MSimExec,TrajType,TSEC;
    // Global information management
    double MiniGoal[12], PlaceMap[10][10],BodyTrack[2][15],GoalSpace[10][23],WristOrR,WristOrL;
    double PickX,PickY,PickZ,PlacX,PlacY,PlacZ, WristO;
    double Proprioceptive[2];
	int XmitGreen;
    double meanJan[10],JHd[10], meanJanL[10],JHdL[10];

public:
    /**
    * constructor default
    */
    PMPThread();

    /**
    * constructor 
    * @param robotname name of the robot
    */
    PMPThread(std::string robotname,std::string configFile);

    /**
     * destructor
     */
    ~PMPThread();

    /**
    *  initialises the thread
    */
    bool threadInit();

    /**
    *  correctly releases the thread
    */
    void threadRelease();

    /**
    *  active part of the thread
    */
    void run(); 

    /**
    *  on stopping of the thread
    */
    void onStop();

    /*
    * function that sets the rootname of all the ports that are going to be created by the thread
    * @param str rootnma
    */
    void setName(std::string str);
    
    /**
    * function that returns the original root name and appends another string iff passed as parameter
    * @param p pointer to the string that has to be added
    * @return rootname 
    */
    std::string getName(const char* p);
    
    /*
    * function that sets the robot name of all related ports that are going to be created by the thread
    * @param str robotName

    */
    void setRobotName(std::string robotname);

    /*
    * function that sets the inputPort name
    */
    void setInputPortName(std::string inpPrtName);
    
    /*
    * function that enables/disables the verbose terminal and file
    */
    void setVerbose(bool vFile, bool vTerm) {verboseFile = vFile; verboseTerm = vTerm;};
    

    /*
    * functions that set path variables to corresponding paths of weight and bias files
    */
    void setWeightsPath(std::string s, int i);
    void setBiasesPath(std::string s, int i);

    /*
    * function loads weight and bias values from the corresponding files
    */
    void loadNeuralNetwork();
    void computeNeuralJacobian(double* Jacob, double* Jan);
    /*
    * function that sets the inputPort name
    */
    //    void setColorPath(std::string inp) { colorMapPath = inp; };

    /*
    * function that sets the model path
    */
    //  void setModelPath(std::string inp) { modelPath = inp; };

    double* forward_Kinematics(double *u , int l);
    double* forward_KinematicsL(double *uL , int lef);
    double* forward_KinematicsLRH(double *uLRH , int lefRH);
    double* forcefield(double *w, double*v);
    double* forcefieldL(double *wL, double*vL);
    double* PMP(double *force,double *forceL);
    double Gamma_Int(double *Gar,int n);
    double Gamma(int _Time);
    double Gamma1(int _Time1);
    double GammaDisc(int _Time);
    double Gamma_IntDisc(double *Gar,int n);
    void Reason(int typeGoal);
    int VTGS(double *MiniGoal, int ChoiceAct,int HandAct,int MSim, double Wrist, int TrajT);
    void MotCon(double T1, double T2, double T3,double TL1, double TL2, double TL3,int time, double Gam,int HAct);
    void MessagePassR();
    void MessagePassT();
    void MessagePassL();
    int FrameGoal();
    void MessageDevDriverR();
    void MessageDevDriverL();
    void MessageDevDriverT();
    void cmdInterfacePassR();
    void cmdInterfacePassL();
    void cmdInterfacePassT();
    void cmdInterfacePassRhand();
    void cmdInterfacePassLhand();
    void initiCubUp();
    void InitializeJan();
    void InitializeJanObst();
    void InitializeWrld(int visiontype);
    void CubGrazp1();
    void CubGrazp2();
    void CubGrazp3();
    void CubGrazp4();
    void CubGrazpL3();
    void CubGrazpL4();
    void CubUp(int HandUp);
    void CubRelease();
    void CubReleaseSoft();
    void Grab();
    void Kompliance(int TagK);
    void PredictReachability(int whichOb);
    void GetObjID();
    void GraspDetectVisionR();
    void GraspDetectVisionL();
    void GraspR();
    void GraspL();
    void PandP();
    void Interpret(int CCode,int PtCode,double AmplificationX,double AmplificationZ);
	void gazeControl(double x, double y, double z);
};

#endif  //_PMP_THREAD_H_

//----- end-of-file --- ( next line intentionally left blank ) ------------------

