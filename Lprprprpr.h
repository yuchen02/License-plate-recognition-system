#pragma once

#include <QtWidgets/QMainWindow>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
#include "../include/Pipeline.h"
#include "ui_Lprprprpr.h"
using namespace cv;
using namespace  std;
using namespace pr;
class Lprprprpr : public QMainWindow
{
	Q_OBJECT

public:
	Lprprprpr(QWidget *parent = Q_NULLPTR);
	Mat Src;
	Mat ImageSave;
	vector<PlateInfo> res;
	VideoCapture Camera;
	Mat CameraFrame;
	Mat Cameraframe;
	time_t Time;
	string PlantName;
private:
	Ui::LprprprprClass ui;
	QTimer *timer;
private slots:

  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void ReadFrame();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_10_clicked();
  void on_pushButton_11_clicked();

//private slots:
	//void on_pushButton_clicked();


};
