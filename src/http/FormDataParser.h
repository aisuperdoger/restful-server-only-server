#pragma once

#include<string>
#include<memory>
#include"FormItem.h"
#include<vector>
#include<iostream>

class FormDataParser{
    private:
        std::shared_ptr<std::string> _data; ///< 指向表单数据的针
        std::string _boundary;              ///< 不同元素的分割符串

        bool _lastBoundaryFound;            ///< 是否找到了最后边界
        int _pos;                           ///< 当前解析到的位置
        int _lineStart;                     ///< 当前行的起始位置
        int _lineLength;                    ///< 当前行的长度

        std::string _partName;              ///< 当前元素的名
        std::string _partFileName;          ///< 当前元素的文件名
        std::string _partContentType;       ///< 当前元素的类型
        int _partDataStart;                 ///< 当前元素的数据表单中的起始位置
        int _partDataLength;                ///< 当前元素的数据长度
    public:
        FormDataParser(const std::shared_ptr<std::string> data, 
            const int pos, const std::string boundary):
            _data(data),
            _pos(pos),
            _boundary(boundary),
             _lastBoundaryFound(false)
            {}
        /**
         * 调用parse函数后，才会执行对应的解析操作，
         * @return 指向由FormItem组成的vector的unique_ptr
         */
        std::unique_ptr<std::vector<FormItem>> parse();  
    private:
        /**
         * 解析表单数据的头部，即紧跟着boundary后面的一行
         */
        void parseHeaders();
        /**
         * 解析表单元素中的具体数据
         */
        void parseFormData();
        /**
         * 获取下一行的数据，
         * 在此实际上是通过更新类内部的_pos, _lineStart,_lineLength实现的
         * @return 是否成功得到下一行的数据
         */
        bool getNextLine();
        /**
         * 判断是否为边界分割行
         * @return 是边界分割行放回true，否则返回false
         */
        bool atBoundaryLine();
        /**
         * 判断是否到达表单数据的末尾
         */
        inline bool atEndOfData(){
            return _pos >= _data->size() || _lastBoundaryFound;
        }            
        std::string getDispositionValue(
            const std::string source, int pos, const std::string name);
        /**
         * 去除字符串前后的空白字符
         * @return 去除空白字符的字符串
         */
        inline std::string& trim(std::string &s){
            if(s.empty()){ return s; }
            s.erase(0, s.find_first_not_of(" "));
            s.erase(s.find_last_not_of(" ") + 1);
            return s;
        }
};
