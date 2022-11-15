#include"FormDataParser.h"

std::unique_ptr<std::vector<FormItem>> FormDataParser::parse(){
    auto p = std::make_unique<std::vector<FormItem>>();
        
    //跳过空白行，直到遇到边界boundary，表示一个表单数据的开始
    while(getNextLine()){
        if(atBoundaryLine()){
            break;
        }
    }
    do{
        //处理头部
        parseHeaders();
        //头部过后如果没有数据，跳出循环
        if(atEndOfData()){ break; }
        //处理该项表单数据
        parseFormData();
        //将表单数据添加到结果数组中
        FormItem formItem(_partName, _partFileName, _partContentType, 
            _data, _partDataStart, _partDataLength);
        p->push_back(std::move(formItem));
    }while(!atEndOfData());
    
    return p;
}

bool FormDataParser::getNextLine(){
    int i = _pos;
    _lineStart = -1;

    while(i < _data->size()){
        //找到一行的末尾
        if(_data->at(i) == '\n'){
            _lineStart = _pos;
            _lineLength = i - _pos;
            _pos = i + 1;
            //忽略'\r'
            if(_lineLength > 0 && _data->at(i - 1) == '\r'){
                _lineLength--;
            }
            break;
        }
        //到达表单数据的末尾了
        if(++i == _data->size()){
            _lineStart = _pos;
            _lineLength = i - _pos;
            _pos = _data->size();
        }
    }

    return _lineStart >= 0;
}


bool FormDataParser::atBoundaryLine(){
    int boundaryLength = _boundary.size();
    //最后的边界会多两个'-'符号
    if(boundaryLength != _lineLength && 
        boundaryLength + 2 != _lineLength){
        return false;
    }

    // 每个字符都和_boundary的字符串相等
    for(int i = 0; i < boundaryLength; ++i){
        if(_data->at(i + _lineStart) != _boundary[i]){ return false; }
    }

    if(_lineLength == boundaryLength){ return true; }
    //判断是否是最后的边界
    if(_data->at(boundaryLength + _lineStart) != '-' ||
        _data->at(boundaryLength + _lineStart + 1) != '-'){
        return false;
    }  

    //到达最后的边界
    _lastBoundaryFound = true;
    return true;
}

void FormDataParser::parseHeaders(){
    //清除之前的数据
    _partFileName.clear();
    _partName.clear();
    _partContentType.clear();

    while(getNextLine()){
        //头部内容结束后，会有一个空白行
        if(_lineLength == 0){ break; }
        const std::string thisLine = _data->substr(_lineStart,_lineLength);

        // std::cout <<thisLine << std::endl;

        int index = thisLine.find(':');
        if(index < 0){ continue; }

        const std::string header = thisLine.substr(0, index);
        if(header == "Content-Disposition"){
            _partName = getDispositionValue(thisLine, index + 1, "name");
            _partFileName = getDispositionValue(thisLine, index + 1, "filename");
        }else if(header == "Content-Type"){
            _partContentType = thisLine.substr(index + 1);
            trim(_partContentType);
        }
    }
}

std::string FormDataParser::getDispositionValue(
    const std::string source, int pos, const std::string name){
    //头部内容：Content-Disposition: form-data; name="projectName"
    //构建模式串
    std::string pattern = " " + name + "=";
    int i = source.find(pattern, pos);
    //更换格式继续查找位置
    if(i < 0){
        pattern = ";" + name + "=";
        i = source.find(pattern, pos);
    }
    if(i < 0){
        pattern = name + "=";
        i = source.find(pattern, pos);
    }
    //尝试了可能的字符串，还没有找到，返回空字符串        
    if(i < 0){ return std::string(); }

    i += pattern.size();
    if(source[i] =='\"'){
        ++i;
        int j = source.find('\"', i);
        if(j < 0 || i == j){ return std::string();}
        return source.substr(i, j - i);
    }else{
        int j = source.find(";", i);
        if(j < 0){ j = source.size(); }
        auto value = source.substr(i, j - i);
        //去掉前后的空白字符
        return trim(value);
    }
}

void FormDataParser::parseFormData(){
    _partDataStart = _pos;
    _partDataLength = -1;

    while(getNextLine()){
        if(atBoundaryLine()){
            //内容数据位于分解线前一行
            int indexOfEnd = _lineStart - 1;
            if(_data->at(indexOfEnd) == '\n'){ indexOfEnd--; }
            if(_data->at(indexOfEnd) == '\r'){ indexOfEnd--; }
            _partDataLength = indexOfEnd - _partDataStart + 1;
            break;
        }
    }
}
