
#include "http/http_server.hpp"
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

// 定义控制器，处理路由对应的请求，MVC模式里边的C部分，
class LogicalController : public Controller{
    SetupController(LogicalController);
 
public: 
    // 轻易请求的映射，这里的名称就是路由的地址
    DefRequestMapping(getReturn);
};

// 定义路由的处理函数，类java spring。这里使用返回值作为response。实际上支持多种，请看具体代码
Json::Value LogicalController::getReturn(const Json::Value& param){

    Json::Value data;
    data["alpha"] = 3.15;
    data["name"] = "张三";

    cout << param["filename"] << endl;
    return success(data);
}

int main(int argc, char** argv) {

    // 创建http服务器，具有32个线程
    auto server = createHttpServer("0.0.0.0:8090", 32);
    if(server == nullptr) return -1;
    
    // 添加控制器对于路由v1
    server->add_controller("/api", make_shared<LogicalController>());

    // 添加静态文件访问，对于路由/static，绑定到路径./上
    server->add_controller("/static", create_file_access_controller("./"));     
    
    return iLogger::while_loop();
}



// // 测试：使用FormItem.h、FormDataParser.cpp和FormDataParser.h用于解析http协议的form-data格式信息
// void read(const std::string file_name,std::string &data){
//     std::ifstream myfile;
//     myfile.open(file_name,std::ios::in); 

//     if (!myfile.is_open()) 
//     { 
//         std::cout << "未成功打开文件" << std::endl; 
//     }
//     std::string temp;
//     while(getline(myfile,temp)){
//         data+=temp;
//         data+='\r\n';
//     }
//     // std::cout<<res<< std::endl;
//     myfile.close(); 

// }


// // 测试：使用FormItem.h、FormDataParser.cpp和FormDataParser.h用于解析http协议的form-data格式信息
// int main(int argc, char** argv) {
//     std::string data;
//     read("form-data.txt",data);

//     // std::cout<<  data << std::endl; 

//     std::shared_ptr<std::string> sptr_data(new std::string(data));
//     std::string boundary("------WebKitFormBoundaryGtk7c80r1MlNUTef");

//     FormDataParser fdp(sptr_data,0,boundary);
//     auto p = fdp.parse();

//     for (std::vector<FormItem>::iterator it = p->begin(); it != p->end();++it) {
// 		std::cout << (*(it)).getName() << (*(it)).getContent() <<std::endl;
// 	}
//     return 0;
// }