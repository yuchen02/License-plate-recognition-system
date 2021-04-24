//�������
#include "Lprprprpr.h"
#include<opencv2/opencv.hpp>
#include <QTimer>
#include<iostream>
#include <qfiledialog.h>  
#include "../include/Pipeline.h"
#include<opencv2/opencv.hpp>
#include<iostream>
#include <QMessageBox>
using namespace pr;
using namespace std;
using namespace cv;
QImage Mat2QImage(cv::Mat cvImg) {
	QImage qImg;
	if (cvImg.channels() == 3)                             //3 channels color image
	{
		cv::cvtColor(cvImg, cvImg, CV_BGR2RGB);
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB888);
	}
	else if (cvImg.channels() == 1)                    //grayscale image
	{
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_Indexed8);
	}
	else
	{
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB888);
	}
	return qImg;
}

QString str2qstr(const string str)

{

	return QString::fromLocal8Bit(str.data());

}
Lprprprpr::Lprprprpr(QWidget *parent)
	: QMainWindow(parent)
	
{
	
	ui.setupUi(this);
	timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(ReadFrame()));
}

void Lprprprpr::on_pushButton_clicked() //���ļ�
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("open image"), "", tr("*.jpg"));
	String Str = fileName.toStdString();
	Src = imread(Str);
	Mat ResizeImg;
	cv::resize(Src, ResizeImg, Size(521, 411));
	QImage qimg;
	qimg = Mat2QImage(ResizeImg);
	ui.label_2->setPixmap(QPixmap::fromImage(qimg));//��ʾ��label_2����
}

void Lprprprpr::on_pushButton_2_clicked() //���ƶ�λ
{
	if (Src.data) //�г�������ʱ
	{
		pr::PipelinePR prc("./model/cascade.xml",
			"./model/HorizonalFinemapping.prototxt", "./model/HorizonalFinemapping.caffemodel",
			"./model/Segmentation.prototxt", "./model/Segmentation.caffemodel",
			"./model/CharacterRecognization.prototxt", "./model/CharacterRecognization.caffemodel"
			);//���ض�λģ�� D:/Lprprprpr/model
		Mat src;
		src = Src.clone();
		res = prc.RunPiplineAsImage(src);
		if (res.data()) 
		{
			Rect rect;
			rect.x = res[0].getPlateRect().x;//x����
			rect.y = res[0].getPlateRect().y;//y����
			rect.width = res[0].getPlateRect().width;//���
			rect.height = res[0].getPlateRect().height;//�߶�
			Point point(rect.x, rect.y);
			rectangle(src, rect, Scalar(0, 0, 255), 3, 8, 0);
			Mat src_resize;
			cv::resize(src, src_resize, Size(331, 240));
			QImage qimg;
			qimg = Mat2QImage(src_resize);
			ui.label_3->setPixmap(QPixmap::fromImage(qimg));//��ʾ��label_3����
		}
		else {
			ui.label_3->setText("Image Error.......");
			 }
	}
	else//ͼƬ�޳���
	{
		QMessageBox::information(this, "Error", "Please load image..........");
		ui.label_2->setText("Image error......");
	}

}

void Lprprprpr::on_pushButton_3_clicked() //���Ʒָ�
{
	if (res.data()) 
	{
		Mat newplant;
		newplant = res[0].getPlateImage();//getPlateImage�ȵõ�����
		cv::resize(newplant, newplant, Size(330, 60));
		QImage plantcut;
		plantcut = Mat2QImage(newplant);//�ָ�
		ui.label_4->setPixmap(QPixmap::fromImage(plantcut));//��ʾ��label_4����
	}
	else {
		ui.label_4->setText("Error......");
	      }
}

void Lprprprpr::on_pushButton_4_clicked() //�ַ��ָ�
{
	
	if (res.data()) 
	{
		if (res[0].plateChars.size() == 7) 
		{
			Mat CutImg1 = res[0].plateChars[0].second;
			Mat CutImg2 = res[0].plateChars[1].second;
			Mat CutImg3 = res[0].plateChars[2].second;
			Mat CutImg4 = res[0].plateChars[3].second;
			Mat CutImg5 = res[0].plateChars[4].second;
			Mat CutImg6 = res[0].plateChars[5].second;
			Mat CutImg7 = res[0].plateChars[6].second;
			Mat resize_cut_1, resize_cut_2, resize_cut_3, resize_cut_4, resize_cut_5, resize_cut_6, resize_cut_7;
			QImage qimage_1, qimage_2, qimage_3, qimage_4, qimage_5, qimage_6, qimage_7;
			cv::resize(CutImg1, resize_cut_1, Size(46, 60));//��һ���ַ�
			qimage_1 = Mat2QImage(resize_cut_1);
			ui.label_5->setPixmap(QPixmap::fromImage(qimage_1));

			cv::resize(CutImg2, resize_cut_2, Size(46, 60));//�ڶ����ַ�
			qimage_2 = Mat2QImage(resize_cut_2);
			ui.label_6->setPixmap(QPixmap::fromImage(qimage_2));

			cv::resize(CutImg3, resize_cut_3, Size(46, 60));//�������ַ�
			qimage_3 = Mat2QImage(resize_cut_3);
			ui.label_7->setPixmap(QPixmap::fromImage(qimage_3));

			cv::resize(CutImg4, resize_cut_4, Size(46, 60));//���ĸ��ַ�
			qimage_4 = Mat2QImage(resize_cut_4);
			ui.label_8->setPixmap(QPixmap::fromImage(qimage_4));

			cv::resize(CutImg5, resize_cut_5, Size(46, 60));//������ַ�
			qimage_5 = Mat2QImage(resize_cut_5);
			ui.label_9->setPixmap(QPixmap::fromImage(qimage_5));

			cv::resize(CutImg6, resize_cut_6, Size(46, 60));//�������ַ�
			qimage_6 = Mat2QImage(resize_cut_6);
			ui.label_10->setPixmap(QPixmap::fromImage(qimage_6));

			cv::resize(CutImg7, resize_cut_7, Size(46, 60));//���߸��ַ�
			qimage_7 = Mat2QImage(resize_cut_7);
			ui.label_11->setPixmap(QPixmap::fromImage(qimage_7));
		}
	}
	else {
		ui.label_4->setText("Error......");
	      }
}
void Lprprprpr::on_pushButton_5_clicked() //ʶ����
{
	if (Src.data) 
	{
		pr::PipelinePR prc("./model/cascade.xml",
			"./model/HorizonalFinemapping.prototxt", "./model/HorizonalFinemapping.caffemodel",
			"./model/Segmentation.prototxt", "./model/Segmentation.caffemodel",
			"./model/CharacterRecognization.prototxt", "./model/CharacterRecognization.caffemodel"
			);//����ʶ���
		Mat src;
		src = Src.clone();
		res = prc.RunPiplineAsImage(src);

		if (res.data()) //�г��ƿ�ʼʶ��
		{
			Rect rect;
			rect.x = res[0].getPlateRect().x;
			rect.y = res[0].getPlateRect().y;
			rect.width = res[0].getPlateRect().width;
			rect.height = res[0].getPlateRect().height;
			Point point(rect.x, rect.y);
			rectangle(src, rect, Scalar(0, 0, 255), 3, 8, 0);
			ImageSave = src.clone();
			Mat src_resize;
			cv::resize(src, src_resize, Size(331, 240));//331, 240
			QImage qimg;
			qimg = Mat2QImage(src_resize);
			ui.label_3->setPixmap(QPixmap::fromImage(qimg));
			time(&Time);
			string str = res[0].getPlateName();
			PlantName = str;
			float con = res[0].confidence * 100;
			String constr = format("%f", con);
			QString qstr, qconstr;
			qconstr = str2qstr(constr);
			qstr = str2qstr(str);
			ui.label_12->setText("license:" + qstr + "\n" + "time: " + ctime(&Time) + "\n" + "Credibility:" + qconstr);
		}//ʶ������ʾ
		else
		{
			QMessageBox::information(this, "Error", "Please load image..........");
			ui.label_2->setText("Image error......");
		}
	}
	else {
		QMessageBox::information(this, "Error", "Please load image..........");
		ui.label_2->setText("Image error......");
	}
}
void Lprprprpr::on_pushButton_6_clicked()//������ͷʶ��
{
	Camera.open(0);						 //�ʼǱ��Դ�����ͷ
	if (!Camera.isOpened()) 
	{
		QMessageBox::information(this, "Error", "Cameras not connected,please cheak your equipments....");
	}
	timer->start(10);//��ʱ
}
void Lprprprpr::ReadFrame()//��ȡ����ͷ
{
	if (Camera.isOpened()) 
	{
		Camera >> Cameraframe;
		Mat CamResize;
		cv::resize(Cameraframe, CamResize, Size(620, 560));
		//cvtColor(CamResize, CamResize,CV_BGR2RGB);
		QImage outputimage;
		outputimage = Mat2QImage(CamResize);
		ui.label->setPixmap(QPixmap::fromImage(outputimage));
	}
	else 
	{
		ui.label->setText("Camera linked error.........");
	}
}
void Lprprprpr::on_pushButton_7_clicked() //���հ�ť
{
	Src = Cameraframe.clone();//Src�����������
	if (Src.data) 
	{
		Mat ResizeImg;
		cv::resize(Src, ResizeImg, Size(640, 480));
		QImage qimg;
		qimg = Mat2QImage(ResizeImg);
		ui.label_2->setPixmap(QPixmap::fromImage(qimg));
	}
	else 
	{
		ui.label_2->setText("Error.....SnapShot error......");
		return;
	}
}
void Lprprprpr::on_pushButton_8_clicked() //�ر����
{
	timer->stop();
	Camera.release();
	QMessageBox::information(this, "Message", "cameras were closed......");
	
	ui.label->setText("cameras were closed......");
	return;
}
void Lprprprpr::on_pushButton_9_clicked() //��ʶ�����ݱ���
{
	if (res.data()) 
	{
		time(&Time);
		string ImageInformation = res[0].getPlateName();
		string ImageTime = ctime(&Time);
		putText(ImageSave, ImageInformation, Point(0, 40), FONT_HERSHEY_DUPLEX, 0.7, Scalar(0, 0, 200), 1, 8);
		putText(ImageSave, ImageTime, Point(0, 80), FONT_HERSHEY_DUPLEX, 0.7, Scalar(0, 0, 200), 1, 8);
		string ImageName = PlantName + ".jpg";
		imwrite(ImageName, ImageSave);
	}
	else {
		QMessageBox::information(this, "Message", "Error");
	      }
}



void Lprprprpr::on_pushButton_10_clicked()   //�رճ���
{
	close();
}

void Lprprprpr::on_pushButton_11_clicked()   //�Զ�ʶ��
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("open image"), "", tr("*.jpg"));
	String Str = fileName.toStdString();
	Src = imread(Str);
	Mat ResizeImg;
	if (Src.data) {
		cv::resize(Src, ResizeImg, Size(521, 411));

	}
	else {
		close();
	}
	QImage qimg;
	qimg = Mat2QImage(ResizeImg);
	ui.label_2->setPixmap(QPixmap::fromImage(qimg));						//��ʾ��label_2����

	if (Src.data)
	{
		pr::PipelinePR prc("./model/cascade.xml",
			"./model/HorizonalFinemapping.prototxt", "./model/HorizonalFinemapping.caffemodel",
			"./model/Segmentation.prototxt", "./model/Segmentation.caffemodel",
			"./model/CharacterRecognization.prototxt", "./model/CharacterRecognization.caffemodel"
		);//����ʶ���
		Mat src;
		src = Src.clone();
		res = prc.RunPiplineAsImage(src);

		if (res.data()) //�г��ƿ�ʼʶ��
		{
			Rect rect;
			rect.x = res[0].getPlateRect().x;
			rect.y = res[0].getPlateRect().y;
			rect.width = res[0].getPlateRect().width;
			rect.height = res[0].getPlateRect().height;
			Point point(rect.x, rect.y);
			rectangle(src, rect, Scalar(0, 0, 255), 3, 8, 0);
			ImageSave = src.clone();
			Mat src_resize;
			cv::resize(src, src_resize, Size(320, 240));
			/*QImage qimg;
			qimg = Mat2QImage(src_resize);
			ui.label_3->setPixmap(QPixmap::fromImage(qimg));*/
			time(&Time);
			string str = res[0].getPlateName();
			PlantName = str;
			float con = res[0].confidence * 100;
			String constr = format("%f", con);
			QString qstr, qconstr;
			qconstr = str2qstr(constr);
			qstr = str2qstr(str);
			ui.label_12->setText("license:" + qstr + "\n" + "time: " + ctime(&Time) + "\n" + "Credibility:" + qconstr);
		}//ʶ������ʾ
		else
		{
			QMessageBox::information(this, "Error", "Please load image..........");
			ui.label_2->setText("Image error......");
		}
	}
	else {
		QMessageBox::information(this, "Error", "Please load image..........");
		ui.label_2->setText("Image error......");
		close();


	}
}
