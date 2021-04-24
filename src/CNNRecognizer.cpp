//加载模型预测标签

#include "../include/CNNRecognizer.h"

namespace pr{
    CNNRecognizer::CNNRecognizer(std::string prototxt,std::string caffemodel){
        net = cv::dnn::readNetFromCaffe(prototxt, caffemodel);//net加载模型
    }

    label CNNRecognizer::recognizeCharacter(cv::Mat charImage){ //识别字符
        if(charImage.channels()== 3)
            cv::cvtColor(charImage,charImage,cv::COLOR_BGR2GRAY);//灰度
        cv::Mat inputBlob = cv::dnn::blobFromImage(charImage, 1/255.0, cv::Size(CHAR_INPUT_W,CHAR_INPUT_H), cv::Scalar(0,0,0),false);//转换类型
        net.setInput(inputBlob,"data");//输入到模型网络
        return net.forward();
    }
}