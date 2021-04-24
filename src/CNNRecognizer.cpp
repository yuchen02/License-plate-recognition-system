//����ģ��Ԥ���ǩ

#include "../include/CNNRecognizer.h"

namespace pr{
    CNNRecognizer::CNNRecognizer(std::string prototxt,std::string caffemodel){
        net = cv::dnn::readNetFromCaffe(prototxt, caffemodel);//net����ģ��
    }

    label CNNRecognizer::recognizeCharacter(cv::Mat charImage){ //ʶ���ַ�
        if(charImage.channels()== 3)
            cv::cvtColor(charImage,charImage,cv::COLOR_BGR2GRAY);//�Ҷ�
        cv::Mat inputBlob = cv::dnn::blobFromImage(charImage, 1/255.0, cv::Size(CHAR_INPUT_W,CHAR_INPUT_H), cv::Scalar(0,0,0),false);//ת������
        net.setInput(inputBlob,"data");//���뵽ģ������
        return net.forward();
    }
}