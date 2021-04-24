//识别

#include "../include/Recognizer.h"

namespace pr{
    void GeneralRecognizer::SegmentBasedSequenceRecognition(PlateInfo &plateinfo){

		//识别车牌字符
        for(auto char_instance:plateinfo.plateChars)
        {


            std::pair<CharType,cv::Mat> res;
            cv::Mat code_table= recognizeCharacter(char_instance.second);
            res.first = char_instance.first;
            code_table.copyTo(res.second);
            plateinfo.appendPlateCoding(res);

        }



    }
}