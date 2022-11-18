

#include "http_server.hpp"
#include <string.h>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "mongoose.h"
#include <future>
#include <condition_variable>
#include <iostream>

using namespace std;

static unordered_map<string, string> CONTENT_TYPE = {
    {"", "application/octet-stream"},
    {".", "application/octet-stream"},
    {".*", "application/octet-stream"},
    {".001", "application/x-001"},
    {".301", "application/x-301"},
    {".323", "text/h323"},
    {".906", "application/x-906"},
    {".907", "drawing/907"},
    {".a11", "application/x-a11"},
    {".acp", "audio/x-mei-aac"},
    {".ai", "application/postscript"},
    {".aif", "audio/aiff"},
    {".aifc", "audio/aiff"},
    {".aiff", "audio/aiff"},
    {".anv", "application/x-anv"},
    {".asa", "text/asa"},
    {".asf", "video/x-ms-asf"},
    {".asp", "text/asp"},
    {".asx", "video/x-ms-asf"},
    {".au", "audio/basic"},
    {".avi", "video/avi"},
    {".awf", "application/vnd.adobe.workflow"},
    {".biz", "text/xml"},
    {".bmp", "application/x-bmp"},
    {".bot", "application/x-bot"},
    {".c4t", "application/x-c4t"},
    {".c90", "application/x-c90"},
    {".cal", "application/x-cals"},
    {".cat", "application/s-pki.seccat"},
    {".cdf", "application/x-netcdf"},
    {".cdr", "application/x-cdr"},
    {".cel", "application/x-cel"},
    {".cer", "application/x-x509-ca-cert"},
    {".cg4", "application/x-g4"},
    {".cgm", "application/x-cgm"},
    {".cit", "application/x-cit"},
    {".class", "java/*"},
    {".cml", "text/xml"},
    {".cmp", "application/x-cmp"},
    {".cmx", "application/x-cmx"},
    {".cot", "application/x-cot"},
    {".crl", "application/pkix-crl"},
    {".crt", "application/x-x509-ca-cert"},
    {".csi", "application/x-csi"},
    {".css", "text/css"},
    {".cut", "application/x-cut"},
    {".dbf", "application/x-dbf"},
    {".dbm", "application/x-dbm"},
    {".dbx", "application/x-dbx"},
    {".dcd", "text/xml"},
    {".dcx", "application/x-dcx"},
    {".der", "application/x-x509-ca-cert"},
    {".dgn", "application/x-dgn"},
    {".dib", "application/x-dib"},
    {".dll", "application/x-msdownload"},
    {".doc", "application/msword"},
    {".dot", "application/msword"},
    {".drw", "application/x-drw"},
    {".dtd", "text/xml"},
    {".dwf", "Model/vnd.dwf"},
    {".dwf", "application/x-dwf"},
    {".dwg", "application/x-dwg"},
    {".dxb", "application/x-dxb"},
    {".dxf", "application/x-dxf"},
    {".edn", "application/vnd.adobe.edn"},
    {".emf", "application/x-emf"},
    {".eml", "message/rfc822"},
    {".ent", "text/xml"},
    {".epi", "application/x-epi"},
    {".eps", "application/x-ps"},
    {".eps", "application/postscript"},
    {".etd", "application/x-ebx"},
    {".exe", "application/x-msdownload"},
    {".fax", "image/fax"},
    {".fdf", "application/vnd.fdf"},
    {".fif", "application/fractals"},
    {".fo", "text/xml"},
    {".frm", "application/x-frm"},
    {".g4", "application/x-g4"},
    {".gbr", "application/x-gbr"},
    {".gcd", "application/x-gcd"},
    {".gif", "image/gif"},
    {".gl2", "application/x-gl2"},
    {".gp4", "application/x-gp4"},
    {".hgl", "application/x-hgl"},
    {".hmr", "application/x-hmr"},
    {".hpg", "application/x-hpgl"},
    {".hpl", "application/x-hpl"},
    {".hqx", "application/mac-binhex40"},
    {".hrf", "application/x-hrf"},
    {".hta", "application/hta"},
    {".htc", "text/x-component"},
    {".htm", "text/html"},
    {".html", "text/html"},
    {".htt", "text/webviewhtml"},
    {".htx", "text/html"},
    {".icb", "application/x-icb"},
    {".ico", "image/x-icon"},
    {".ico", "application/x-ico"},
    {".iff", "application/x-iff"},
    {".ig4", "application/x-g4"},
    {".igs", "application/x-igs"},
    {".iii", "application/x-iphone"},
    {".img", "application/x-img"},
    {".ins", "application/x-internet-signup"},
    {".isp", "application/x-internet-signup"},
    {".IVF", "video/x-ivf"},
    {".java", "java/*"},
    {".jfif", "image/jpeg"},
    {".jpe", "image/jpeg"},
    {".jpe", "application/x-jpe"},
    {".jpeg", "image/jpeg"},
    {".jpg", "image/jpeg"},
    {".js", "text/javascript"},
    {".json", "application/json"},
    {".jsp", "text/html"},
    {".la1", "audio/x-liquid-file"},
    {".lar", "application/x-laplayer-reg"},
    {".latex", "application/x-latex"},
    {".lavs", "audio/x-liquid-secure"},
    {".lbm", "application/x-lbm"},
    {".lmsff", "audio/x-la-lms"},
    {".ls", "application/x-javascript"},
    {".ltr", "application/x-ltr"},
    {".m1v", "video/x-mpeg"},
    {".m2v", "video/x-mpeg"},
    {".m3u", "audio/mpegurl"},
    {".m4e", "video/mpeg4"},
    {".mac", "application/x-mac"},
    {".man", "application/x-troff-man"},
    {".math", "text/xml"},
    {".mdb", "application/msaccess"},
    {".mdb", "application/x-mdb"},
    {".mfp", "application/x-shockwave-flash"},
    {".mht", "message/rfc822"},
    {".mhtml", "message/rfc822"},
    {".mi", "application/x-mi"},
    {".mid", "audio/mid"},
    {".midi", "audio/mid"},
    {".mil", "application/x-mil"},
    {".mml", "text/xml"},
    {".mnd", "audio/x-musicnet-download"},
    {".mns", "audio/x-musicnet-stream"},
    {".mocha", "application/x-javascript"},
    {".movie", "video/x-sgi-movie"},
    {".mp1", "audio/mp1"},
    {".mp2", "audio/mp2"},
    {".mp2v", "video/mpeg"},
    {".mp3", "audio/mp3"},
    {".mp4", "video/mp4"},
    {".mpa", "video/x-mpg"},
    {".mpd", "application/-project"},
    {".mpe", "video/x-mpeg"},
    {".mpeg", "video/mpg"},
    {".mpg", "video/mpg"},
    {".mpga", "audio/rn-mpeg"},
    {".mpp", "application/-project"},
    {".mps", "video/x-mpeg"},
    {".mpt", "application/-project"},
    {".mpv", "video/mpg"},
    {".mpv2", "video/mpeg"},
    {".mpw", "application/s-project"},
    {".mpx", "application/-project"},
    {".mtx", "text/xml"},
    {".mxp", "application/x-mmxp"},
    {".net", "image/pnetvue"},
    {".nrf", "application/x-nrf"},
    {".nws", "message/rfc822"},
    {".odc", "text/x-ms-odc"},
    {".out", "application/x-out"},
    {".p10", "application/pkcs10"},
    {".p12", "application/x-pkcs12"},
    {".p7b", "application/x-pkcs7-certificates"},
    {".p7c", "application/pkcs7-mime"},
    {".p7m", "application/pkcs7-mime"},
    {".p7r", "application/x-pkcs7-certreqresp"},
    {".p7s", "application/pkcs7-signature"},
    {".pc5", "application/x-pc5"},
    {".pci", "application/x-pci"},
    {".pcl", "application/x-pcl"},
    {".pcx", "application/x-pcx"},
    {".pdf", "application/pdf"},
    {".pdf", "application/pdf"},
    {".pdx", "application/vnd.adobe.pdx"},
    {".pfx", "application/x-pkcs12"},
    {".pgl", "application/x-pgl"},
    {".pic", "application/x-pic"},
    {".pko", "application-pki.pko"},
    {".pl", "application/x-perl"},
    {".plg", "text/html"},
    {".pls", "audio/scpls"},
    {".plt", "application/x-plt"},
    {".png", "image/png"},
    {".pot", "applications-powerpoint"},
    {".ppa", "application/vs-powerpoint"},
    {".ppm", "application/x-ppm"},
    {".pps", "application-powerpoint"},
    {".ppt", "applications-powerpoint"},
    {".ppt", "application/x-ppt"},
    {".prf", "application/pics-rules"},
    {".prn", "application/x-prn"},
    {".prt", "application/x-prt"},
    {".ps", "application/x-ps"},
    {".ps", "application/postscript"},
    {".ptn", "application/x-ptn"},
    {".pwz", "application/powerpoint"},
    {".r3t", "text/vnd.rn-realtext3d"},
    {".ra", "audio/vnd.rn-realaudio"},
    {".ram", "audio/x-pn-realaudio"},
    {".ras", "application/x-ras"},
    {".rat", "application/rat-file"},
    {".rdf", "text/xml"},
    {".rec", "application/vnd.rn-recording"},
    {".red", "application/x-red"},
    {".rgb", "application/x-rgb"},
    {".rjs", "application/vnd.rn-realsystem-rjs"},
    {".rjt", "application/vnd.rn-realsystem-rjt"},
    {".rlc", "application/x-rlc"},
    {".rle", "application/x-rle"},
    {".rm", "application/vnd.rn-realmedia"},
    {".rmf", "application/vnd.adobe.rmf"},
    {".rmi", "audio/mid"},
    {".rmj", "application/vnd.rn-realsystem-rmj"},
    {".rmm", "audio/x-pn-realaudio"},
    {".rmp", "application/vnd.rn-rn_music_package"},
    {".rms", "application/vnd.rn-realmedia-secure"},
    {".rmvb", "application/vnd.rn-realmedia-vbr"},
    {".rmx", "application/vnd.rn-realsystem-rmx"},
    {".rnx", "application/vnd.rn-realplayer"},
    {".rp", "image/vnd.rn-realpix"},
    {".rpm", "audio/x-pn-realaudio-plugin"},
    {".rsml", "application/vnd.rn-rsml"},
    {".rt", "text/vnd.rn-realtext"},
    {".rtf", "application/msword"},
    {".rtf", "application/x-rtf"},
    {".rv", "video/vnd.rn-realvideo"},
    {".sam", "application/x-sam"},
    {".sat", "application/x-sat"},
    {".sdp", "application/sdp"},
    {".sdw", "application/x-sdw"},
    {".sit", "application/x-stuffit"},
    {".slb", "application/x-slb"},
    {".sld", "application/x-sld"},
    {".slk", "drawing/x-slk"},
    {".smi", "application/smil"},
    {".smil", "application/smil"},
    {".smk", "application/x-smk"},
    {".snd", "audio/basic"},
    {".sol", "text/plain"},
    {".sor", "text/plain"},
    {".spc", "application/x-pkcs7-certificates"},
    {".spl", "application/futuresplash"},
    {".spp", "text/xml"},
    {".ssm", "application/streamingmedia"},
    {".sst", "application-pki.certstore"},
    {".stl", "application/-pki.stl"},
    {".stm", "text/html"},
    {".sty", "application/x-sty"},
    {".svg", "text/xml"},
    {".swf", "application/x-shockwave-flash"},
    {".tdf", "application/x-tdf"},
    {".tg4", "application/x-tg4"},
    {".tga", "application/x-tga"},
    {".tif", "image/tiff"},
    {".tif", "application/x-tif"},
    {".tiff", "image/tiff"},
    {".tld", "text/xml"},
    {".top", "drawing/x-top"},
    {".torrent", "application/x-bittorrent"},
    {".tsd", "text/xml"},
    {".txt", "text/plain"},
    {".uin", "application/x-icq"},
    {".uls", "text/iuls"},
    {".vcf", "text/x-vcard"},
    {".vda", "application/x-vda"},
    {".vdx", "application/vnd.visio"},
    {".vml", "text/xml"},
    {".vpg", "application/x-vpeg005"},
    {".vsd", "application/vnd.visio"},
    {".vsd", "application/x-vsd"},
    {".vss", "application/vnd.visio"},
    {".vst", "application/vnd.visio"},
    {".vst", "application/x-vst"},
    {".vsw", "application/vnd.visio"},
    {".vsx", "application/vnd.visio"},
    {".vtx", "application/vnd.visio"},
    {".vxml", "text/xml"},
    {".wav", "audio/wav"},
    {".wax", "audio/x-ms-wax"},
    {".wb1", "application/x-wb1"},
    {".wb2", "application/x-wb2"},
    {".wb3", "application/x-wb3"},
    {".wbmp", "image/vnd.wap.wbmp"},
    {".wiz", "application/msword"},
    {".wk3", "application/x-wk3"},
    {".wk4", "application/x-wk4"},
    {".wkq", "application/x-wkq"},
    {".wks", "application/x-wks"},
    {".wm", "video/x-ms-wm"},
    {".wma", "audio/x-ms-wma"},
    {".wmd", "application/x-ms-wmd"},
    {".wmf", "application/x-wmf"},
    {".wml", "text/vnd.wap.wml"},
    {".wmv", "video/x-ms-wmv"},
    {".wmx", "video/x-ms-wmx"},
    {".wmz", "application/x-ms-wmz"},
    {".wp6", "application/x-wp6"},
    {".wpd", "application/x-wpd"},
    {".wpg", "application/x-wpg"},
    {".wpl", "application/-wpl"},
    {".wq1", "application/x-wq1"},
    {".wr1", "application/x-wr1"},
    {".wri", "application/x-wri"},
    {".wrk", "application/x-wrk"},
    {".ws", "application/x-ws"},
    {".ws2", "application/x-ws"},
    {".wsc", "text/scriptlet"},
    {".wsdl", "text/xml"},
    {".wvx", "video/x-ms-wvx"},
    {".xdp", "application/vnd.adobe.xdp"},
    {".xdr", "text/xml"},
    {".xfd", "application/vnd.adobe.xfd"},
    {".xfdf", "application/vnd.adobe.xfdf"},
    {".xhtml", "text/html"},
    {".xls", "application/-excel"},
    {".xls", "application/x-xls"},
    {".xlw", "application/x-xlw"},
    {".xml", "text/xml"},
    {".xpl", "audio/scpls"},
    {".xq", "text/xml"},
    {".xql", "text/xml"},
    {".xquery", "text/xml"},
    {".xsd", "text/xml"},
    {".xsl", "text/xml"},
    {".xslt", "text/xml"},
    {".xwd", "application/x-xwd"},
    {".x_b", "application/x-x_b"},
    {".x_t", "application/x-x_t"}
};

struct WorkerResult{
	SessionID conn_id;
};

Response::Response(){
	set_status_code(200);
	set_header("Server", "HTTP Server/1.1");
	//set_header("Transfer-Encoding", "chunked");
	set_header("Content-Type", "application/json");
}

bool Request::has_header(const string& name){
	return this->headers.find(name) != this->headers.end();
}

string Request::get_header(const string& name){
	auto iter = headers.find(name);
	if(iter != headers.end())
		return iter->second;
	return "";
}

void Response::write_binary(const void* pdata, size_t size){
	output.write(pdata, size);
	this->write_mode = ResponseWriteMode_WriteCustom;
}

void Response::write_plain_text(const string& val){
	set_header("Content-Type", "text/plain");
	output.writeData(val);
	this->write_mode = ResponseWriteMode_WriteCustom;
}

void Response::write_file(const string& file){
	this->file_path = file;
	this->remove_header("Content-Type");
	this->write_mode = ResponseWriteMode_WriteFile;
}

void Response::write_json_styled(const Json::Value& val){
	set_header("Content-Type", "application/json");
	output.writeData(val.toStyledString());
	this->write_mode = ResponseWriteMode_WriteCustom;
}

void Response::write_json(const Json::Value& val){
	set_header("Content-Type", "application/json");
	output.writeData(Json::FastWriter().write(val));
	this->write_mode = ResponseWriteMode_WriteCustom;
}

void Response::set_status_code(int code){
	this->status_code = code;
}

void Response::set_header(const string& key, const string& value){
	this->headers[key] = value;
}

void Response::remove_header(const string& name){
	this->headers.erase(name); // headers是个map类型，通过erase移除name
}

bool Response::has_header(const string& name){
	return this->headers.find(name) != this->headers.end();
}

string Response::get_header(const string& name){
	auto iter = this->headers.find(name);
	if(iter != this->headers.end())
		return iter->second;
	return "";
}

string Response::header_string(){
	string output_string;
	for(auto& item : headers){
		output_string += item.first + ": " + item.second + "\r\n";
	}
	return output_string;
}

const string& Response::output_string(){
	return output.writedMemory();
}

Session::Session(){
}

Session::Session(SessionID id){
	this->conn_id = id;
}

static void error_process(const shared_ptr<Session>& session, int code){
	session->response.set_status_code(code);
	session->response.set_header("Content-Type", "application/json");

	Json::Value response;
	response["status"] = "error";
	response["code"] = code;
	response["message"] = mg_status_message(code);
	response["time"] = iLogger::time_now();
	session->response.write_json_styled(response);
}

static void parse_uri_vars(const string& uri, unordered_map<string, string>& save){

	if(uri.empty())
		return;

	const char *p, *e, *s;
	int len;
	const char* begin = uri.c_str();
	p = begin;
	e = begin + uri.size();
	char buffer[1024];

	for(;p < e; ++p){
		if(p == begin || p[-1] == '&'){
			s = (const char *) memchr(p, '=', (size_t)(e - p));
			if(s == nullptr)
				s = e;

			len = mg_url_decode(p, (size_t)(s - p), buffer, sizeof(buffer), 1);
			if (len == -1) 
				break;

			string name(buffer, buffer + len);
			if(s == e){
				save[move(name)];
				break;
			}

			p = s + 1;
			s = (const char *) memchr(p, '&', (size_t)(e - p));
			if(s == nullptr)
				s = e;

			len = mg_url_decode(p, (size_t)(s - p), buffer, sizeof(buffer), 1);
			if (len == -1){
				save[move(name)];
				break;
			}

			string value(buffer, buffer + len);
			save[move(name)] = move(value);
			p = s;
		}
	}
}

class SessionManager{
public:
	shared_ptr<Session> get(SessionID id){

		unique_lock<mutex> l(lck_);
		auto iter = idmap_.find(id);
		if(iter == idmap_.end())
			return nullptr;

		return iter->second;
	}

	template<typename... _Args>
	shared_ptr<Session> emplace_create(_Args&&... __args){
		unique_lock<mutex> l(lck_);
		shared_ptr<Session> newitem(new Session(forward<_Args>(__args)...));
		idmap_[newitem->conn_id] = newitem; // 建立ID到会话的映射
		return newitem;
	}

	void remove(SessionID id){
		unique_lock<mutex> l(lck_);
		idmap_.erase(id);
	}

private:
	mutex lck_;
	unordered_map<SessionID, shared_ptr<Session>> idmap_;
};
 
enum HandlerType : int{
	HandlerType_None = 0,
	HandlerType_Callback = 1,
	HandlerType_Controller = 2
};

struct Handler{
	HandlerCallback callback;
	shared_ptr<Controller> controller;
	HandlerType type = HandlerType_None;

	Handler(){}

	Handler(const HandlerCallback& callback){
		this->callback = callback;
		this->type = HandlerType_Callback;
	}

	Handler(const shared_ptr<Controller>& controller){
		this->controller = controller;
		this->type = HandlerType_Controller;
	}
};



void Controller::initialize(const string& url, HttpServer* server){
	mapping_url_ = url;

	for(auto& router : router_mapping_.routers){
		for(auto& method : router.second){
			server->add_router(
				iLogger::format("%s%s", mapping_url_.c_str(), router.first.c_str()), 
				bind(&Controller::process_module, this, placeholders::_1, method.second),
				method.first
			);
		}
	}
}

void Controller::process(const shared_ptr<Session>& session){
	error_process(session, 404);
}

void Controller::process_module(const shared_ptr<Session>& session, const ControllerProcess& func){

	Json::Value param;
	// 解析multipart/form-data格式数据
	if (!(session->request.headers.find("Content-Type") == session->request.headers.end())  	// 代表头部信息中是否有Content-Type字段
		&& session->request.headers["Content-Type"].find("multipart/form-data;", 0) >= 0 )
    {
		std::string pattern ="boundary=";
		int i = session->request.headers["Content-Type"].find("; "+pattern, 0); 
		i+=pattern.size()+2;
		std::string boundary = session->request.headers["Content-Type"].substr(i);
		std::shared_ptr<std::string> sptr_data(new std::string(session->request.body));

		// std::cout << session->request.body.substr(0,1000)<<std::endl;

		FormDataParser fdp(sptr_data,0,"--"+boundary);
		auto p = fdp.parse();

		for (std::vector<FormItem>::iterator it = p->begin(); it != p->end();++it) {
			if((*(it)).getFileName()!=""){ // 如果文件名不为空，那么说明是个文件，那么就存储为test.zip
				iLogger::save_file("test.zip",  (*(it)).getContent());
				param["filename"] = "test.zip";
			}
			else{ 
				param[(*(it)).getName()] = (*(it)).getContent();
			}	

			// std::cout << (*(it)).getName() <<std::endl; //<< (*(it)).getContent() <<std::endl;
		}
		// std::cout<<  session->request.headers["Content-Type"] << "j=" << boundary << std::endl;

		// 查看解析结果是否正确
		// for (std::vector<FormItem>::iterator it = p->begin(); it != p->end();++it) {
		// 	std::cout << (*(it)).getName() <<std::endl; //<< (*(it)).getContent() <<std::endl;
		// }
		// std::cout<<  session->request.headers["Content-Type"] << "j=" << boundary << std::endl;
	}
	else{ // 解析json格式数据
		auto param = Json::parse_string(session->request.body); // 将body解析为json格式，存入 param
	}
	
	auto tid = this_thread::get_id();
	{
		unique_lock<mutex> l(this->session_lock_);
		this->current_session_[tid] = session;
	};
	
	auto ret = func(param);
	if(session->response.write_mode == ResponseWriteMode_WriteReturnJson){
		session->response.output.writeData(ret.toStyledString());
	}

	// 删除id
	{
		unique_lock<mutex> l(this->session_lock_);
		this->current_session_.erase(tid);
	};

}

Controller::ControllerProcess Controller::find_match(const string& url, const string& method){

	if(url.size() < mapping_url_.size())
		return nullptr;

	auto split_url = url.substr(mapping_url_.size());
	auto it = router_mapping_.routers.find(split_url);
	if(it != router_mapping_.routers.end()){
		auto subit = it->second.find(method);
		if(subit == it->second.end())
			subit = it->second.find("*");

		if(subit != it->second.end()){
			return subit->second;
		}
	}
	return nullptr;
}

int Controller::add_router(const string& url, const string& method, const ControllerProcess& process){
	router_mapping_.routers[url][method] = process;
	return 0;
}

bool Controller::is_begin_match(){
	return false;
}

shared_ptr<Session> Controller::get_current_session(){
	unique_lock<mutex> l(this->session_lock_);
	auto it = this->current_session_.find(this_thread::get_id()); // this_thread::get_id()获取当前线程ID；current_session_是一个map——<当前线程ID,Session>
	if(it == this->current_session_.end()) // 如果没有找到此线程。   每个线程用于处理一个会话，curren_session_保存了这样的键值对。
		return nullptr;
	return it->second;
}


class FileRedirectController : public Controller{
public:
	FileRedirectController(const string& root_directory, const string& root_redirect_file){
		root_directory_ = root_directory;
		root_redirect_file_ = root_redirect_file;

		if(root_directory_.empty())
			root_directory_ = "static";

		if(root_redirect_file_.empty())
			root_redirect_file_ = "index.html";

		if(root_directory_.back() == '/' || root_directory_.back() == '\\')
			root_directory_.pop_back();
	}

	bool is_begin_match() override{
		return true;
	}

	virtual void process(const shared_ptr<Session>& session) override{
		
		if(session->request.url.size() < mapping_url_.size()){
			session->response.set_status_code(404);
			return;
		}

		auto split_url = session->request.url.substr(mapping_url_.size());
		if(!split_url.empty() && split_url.back() == '/')
			split_url.pop_back();

		if(split_url.empty())
			split_url = root_redirect_file_;

		int lp = split_url.find('?');
		if(lp != -1)
			split_url = split_url.substr(0, lp);

		int p = split_url.rfind('.');
		int e = split_url.rfind('/');
		const char* context_type = "application/octet-stream";
		if(p > e){
			auto suffix = split_url.substr(p);
			transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);
			auto iter = CONTENT_TYPE.find(suffix);
			if(iter != CONTENT_TYPE.end()){
				context_type = iter->second.c_str();
			}
		}

		string merge_path = iLogger::format("%s/%s", root_directory_.c_str(), split_url.c_str());
		if(!iLogger::exists(merge_path)){
			merge_path = iLogger::format("%s/%s", root_directory_.c_str(), root_redirect_file_.c_str());
		}

		if(!iLogger::isfile(merge_path)){
			error_process(session, 404);
			return;
		}

		session->response.set_header("Content-Type", context_type);
		time_t file_last_modify = iLogger::last_modify(merge_path);
		auto gmt = iLogger::gmtime(file_last_modify);
		if(session->request.has_header("If-Modified-Since")){
			auto time = session->request.get_header("If-Modified-Since");
			if(!time.empty()){
				time_t modified_since = iLogger::gmtime2ctime(time);
				if(modified_since == file_last_modify){
					const int SC_NOT_MODIFIED = 304;
					session->response.set_status_code(SC_NOT_MODIFIED);
					session->response.set_header("Cache-Control", "max-age=315360000");
					session->response.set_header("Last-Modified", iLogger::gmtime(file_last_modify));
					return;
				}
			}
		}
		//match by ccutil::gmtime
		//INFO("Write file: %s", merge_path.c_str());
		session->response.write_file(merge_path);
	}

private:
	string root_redirect_file_;
	string root_directory_;
};

shared_ptr<Controller> create_redirect_access_controller(const string& root_directory, const string& root_redirect_file){
	return make_shared<FileRedirectController>(root_directory, root_redirect_file);
}

class FileAccessController : public Controller{
public:
	FileAccessController(const string& root_directory){
		root_directory_ = root_directory;

		if(root_directory_.empty()){
			root_directory_ = "static";
			return;
		}

		if(root_directory_.back() == '/' || root_directory_.back() == '\\')
			root_directory_.pop_back();
	}

	bool is_begin_match() override{
		return true;
	}

	virtual void process(const shared_ptr<Session>& session) override{
		
		if(session->request.url.size() < mapping_url_.size()){
			session->response.set_status_code(404);
			return;
		}

		auto split_url = session->request.url.substr(mapping_url_.size());
		if(!split_url.empty() && split_url.back() == '/')
			split_url.pop_back();

		int lp = split_url.find('?');
		if(lp != -1)
			split_url = split_url.substr(0, lp);

		int p = split_url.rfind('.');
		int e = split_url.rfind('/');
		const char* context_type = "application/octet-stream";
		if(p > e){
			auto suffix = split_url.substr(p);
			transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);
			auto iter = CONTENT_TYPE.find(suffix);
			if(iter != CONTENT_TYPE.end()){
				context_type = iter->second.c_str();
			}
		}

		string merge_path = iLogger::format("%s/%s", root_directory_.c_str(), split_url.c_str());
		if(!iLogger::isfile(merge_path)){
			error_process(session, 404);
			return;
		}

		session->response.set_header("Content-Type", context_type);
		time_t file_last_modify = iLogger::last_modify(merge_path);
		auto gmt = iLogger::gmtime(file_last_modify);
		if(session->request.has_header("If-Modified-Since")){
			auto time = session->request.get_header("If-Modified-Since");
			if(!time.empty()){
				time_t modified_since = iLogger::gmtime2ctime(time);
				if(modified_since == file_last_modify){
					const int SC_NOT_MODIFIED = 304;
					session->response.set_status_code(SC_NOT_MODIFIED);
					session->response.set_header("Cache-Control", "max-age=315360000");
					session->response.set_header("Last-Modified", iLogger::gmtime(file_last_modify));
					return;
				}
			}
		}
		//match by ccutil::gmtime
		//INFO("Write file: %s", merge_path.c_str());
		session->response.write_file(merge_path);
	}

private:
	string root_directory_;
};

shared_ptr<Controller> create_file_access_controller(const string& root_directory){
	return make_shared<FileAccessController>(root_directory);
}

 class HttpServerImpl : public HttpServer
{
public:
	virtual ~HttpServerImpl(){
		this->close();
	}

	virtual void verbose() override{
		verbose_ = true;
	}

	size_t size_jobs(){
		return jobs_.size();
	}

	bool start(const string& address, int num_threads = 32);
	virtual void add_router(const string& url, const HandlerCallback& callback, const string& method) override;
	virtual void add_router_post(const string& url, const HandlerCallback& callback) override;
	virtual void add_router_get(const string& url, const HandlerCallback& callback) override;
	virtual void add_controller(const string& url, shared_ptr<Controller> controller) override;
	void close();
	void loop();
	int poll(unsigned int timeout);
	void worker_thread_proc();
	static void on_work_complete(struct mg_connection *nc, int ev, void *ev_data);

	void commit(shared_ptr<Session> user);

private:
	unordered_map<string, unordered_map<string, Handler>> router_map_; 		// 什么链接对应什么处理函数。第一个string代表链接，第二个string代表请求类型（GET、POST），Handler代表处理函数
																		    // Handler本质就是一个函数指针（std::function）
	vector<tuple<string, Handler>> begin_match_router_;		// etc, static file access

private:
	static void on_http_event(mg_connection *connection, int event_type, void *event_data);

	mg_mgr mgr_;
	atomic<bool> keeprun_{false};
	string docDirectory_;
	string docUrl_;
	bool useResourceAccess_ = false;
	vector<shared_ptr<thread>> threads_;
	queue<shared_ptr<Session>> jobs_;  // 各个客户端发送过来的请求，都会用一个会话进行管理。这些会话放在jobs_中。
	mutex lck_;
	condition_variable cv_; // condition_variable条件变量是利用线程间共享的全局变量进行同步的一种机制，主要包括两个动作：
							// 一个线程等待条件变量的条件成立而挂起;另一个线程使条件成立（给出条件成立信号）。
							// 为了防止竞争，条件变量的使用总是和一个互斥量结合在一起。

	SessionID s_next_id_ = 0;
	SessionManager session_manager_;
	shared_ptr<thread> loop_thread_;
	bool verbose_ = false;
};

void HttpServerImpl::on_work_complete(struct mg_connection *nc, int ev, void *ev_data) {
  
	(void) ev;
	struct mg_connection *c=nc;
	WorkerResult* res = (WorkerResult*)ev_data;
	HttpServerImpl* server = (HttpServerImpl*)nc->mgr->user_data;

	if(c->user_data == NULL)
		return;
  
	if ((SessionID)c->user_data != res->conn_id)
		return;

	auto session = server->session_manager_.get(res->conn_id);
	if(!session){
		mg_http_send_error(c, 404, "Not Found");
		return;
	}

	auto& resp = session->response;
	if(resp.write_mode == ResponseWriteMode_WriteFile){
		auto& file = resp.file_path;
		string context_type = "application/octet-stream";
		if(!resp.has_header("Content-Type"))
			context_type = resp.get_header("Content-Type");

		mg_http_serve_file3(c, 
			mg_mk_str(session->request.get_header("Range").c_str()),
			mg_mk_str(session->request.get_header("Connection").c_str()),
			mg_mk_str(session->request.proto.c_str()),
			iLogger::last_modify(file) + 28800,
			file.c_str(), mg_mk_str(context_type.c_str()), mg_mk_str("Cache-Control: max-age=315360000"));
		server->session_manager_.remove(res->conn_id);
		return;
	}

	mg_printf(c, "HTTP/1.1 %d %s\r\n", 
		resp.status_code,
		mg_status_message(resp.status_code)
	);

	for(auto& iter : resp.headers)
		mg_printf(c, "%s: %s\r\n", iter.first.c_str(), iter.second.c_str());

	auto& data = resp.output_string();
	mg_printf(c, "Content-Length: %ld\r\n\r\n", data.size());
	if (!data.empty())
		mg_send(c, data.data(), data.size());
	server->session_manager_.remove(res->conn_id);
}
 
void HttpServerImpl::worker_thread_proc() {

	while (keeprun_) {  // 只有线程被删除，keeprun_才会编程false
		shared_ptr<Session> session;
		{
			unique_lock<mutex> l(lck_);
			cv_.wait(l, [&]{return !jobs_.empty() || !keeprun_;});

			if(!keeprun_) break;
			session = jobs_.front(); // 将会话取出
			jobs_.pop();			// 将会话删掉
		};
 
		bool found_router = false;
		auto it = router_map_.find(session->request.url);  // 查找链接对应的请求方式和处理函数
		if(it == router_map_.end()){ // 代表此链接在router_map_中没有对应的处理函数。那么就查找一下此链接是否是对应某些静态文件

			// match url* 
			string& url = session->request.url;
			for(auto& item : begin_match_router_){ // 
				if(iLogger::begin_with(url, get<0>(item))){
					found_router = true;

					Handler& handler = get<1>(item);
					if(handler.type == HandlerType_Callback){
						handler.callback(session);
					}else if(handler.type == HandlerType_Controller){
						handler.controller->process(session);
					}
				}
			}
		}else{
			auto subit = it->second.find(session->request.method); // 通过请求方式查找处理函数
			if(subit == it->second.end())
				subit = it->second.find("*");

			if(subit != it->second.end()){
				found_router = true;

				if(verbose_){
					INFO("Found match: %s [%s] -> %s [%s]", session->request.url.c_str(), session->request.method.c_str(), it->first.c_str(), subit->first.c_str());
				}

				Handler& handler = subit->second;
				// 有两种处理函数——回调函数和控制器处理函数
				if(handler.type == HandlerType_Callback){ 
					handler.callback(session);
				}else if(handler.type == HandlerType_Controller){
					handler.controller->process(session);
				}
			}
		}

		WorkerResult result;
		result.conn_id = session->conn_id;
		
		if (!found_router){
			error_process(session, 404);
		}
		mg_broadcast(&mgr_, on_work_complete, &result, sizeof(result)); // 将给定长度的消息传递给所有连接。发给所有链接干嘛？？
	}
}

// 绑定事件，开启监听。初始化一些不知道用来干嘛的线程？
bool HttpServerImpl::start(const string& address, int num_threads)
{
	this->close(); // 等待所有线程运行完毕，关闭所有线程和清空必要数据。

	//signal(SIGTERM, SIG_IGN);
  	//signal(SIGINT, SIG_IGN);
	mg_mgr_init(&mgr_, nullptr);    	// mg_开头的函数基本都是mongoose中的函数，具体可参见https://www.cnblogs.com/codingbigdog/p/16271138.html
	mgr_.user_data = this; 		    	// user_data是一个void指针。this指针指向的空间中保存的只有成员变量。
	mg_connection *connection = mg_bind(&mgr_, address.c_str(), HttpServerImpl::on_http_event); // 当事件发生了自动调用on_http_event。如request来到了
	if (connection == nullptr){
		INFOE("bind %s fail", address.c_str());
		return false;
	}

	mg_set_protocol_http_websocket(connection); // Set up HTTP server parameters

	keeprun_ = true; // 什么作用？答:当keeprun_ = true时，线程数组thread_的回调函数worker_thread_proc一直有效。当keeprun_变为false时，线程退出。
	loop_thread_.reset(new thread(bind(&HttpServerImpl::loop, this))); // reset将指针指向新的对象。loop是一个循环，用于处理客户的连接。

	for (int i = 0; i < num_threads; i++)// 启动num_threads个线程，并用数组threads_保存
		threads_.emplace_back(new thread(bind(&HttpServerImpl::worker_thread_proc, this))); // bind就是把成员函数抠出来当作静态函数单独用。非静态成员函数则需要传递this指针作为第一个参数
																							// emplace_back在容器尾部添加一个元素
																							// 发送数据的语句在worker_thread_proc中。
																							// worker_thread_proc作用：

	// 对favicon处理，网页图标
	this->add_router_get("/favicon.ico", [](const std::shared_ptr<Session>& session){
		session->response.write_file("favicon.jpg"); // 这里设置的回调函数，这里是匿名回调函数。
													 // 当访问/favicon.ico时，回调函数中调用了wirite_file将favicon.jpg文件所在的路径设置到session的reponse中。
													 // 浏览器中输入http://127.0.0.1:8090/favicon.ico，即可访问
	});
	return true;
}

int HttpServerImpl::poll(unsigned int timeout){
	return mg_mgr_poll(&mgr_, timeout);
}

void HttpServerImpl::loop(){

	while (keeprun_)
		mg_mgr_poll(&mgr_, 1000); // ms
}

void HttpServerImpl::commit(shared_ptr<Session> user){
	{
		unique_lock<mutex> l(lck_);
		jobs_.push(user); // 将user添加到session队列jobs中
	};
	cv_.notify_one(); // 唤醒线程处理此session
}

void HttpServerImpl::on_http_event(mg_connection *connection, int event_type, void *event_data){  // 用于处理http request和close

	HttpServerImpl* server = (HttpServerImpl*)connection->mgr->user_data; // server代表的就是this，但是不知道在回调函数on_http_event中能不能互相替换？？
 
	switch (event_type) {
	case MG_EV_ACCEPT:{
		break;
	}



	case MG_EV_HTTP_REQUEST: {
		http_message *http_req = (http_message *)event_data; // event_data如何被发送过来，为什么直接将http_req给初始化了
		connection->user_data = (void*)++server->s_next_id_;  // s_next_id_为SessionID，SessionID随着http连接的变多，而逐渐升高。但是从后面的代码可以看出：被处理掉一个session以后，sessionid并没有减一
		SessionID id = (SessionID)connection->user_data;
		auto user = server->session_manager_.emplace_create(id); 	// 向session管理器中添加一个会话，并返回此会话。session管理器的核心就是一个“id到session的映射”
		user->request.url = string(http_req->uri.p, http_req->uri.len); // 从http_req->uri.p开始取出len个字符
		user->request.body = string(http_req->body.p, http_req->body.len); // http请求包括请求行（request line）、请求头部（header）、空行和请求数据四个部分组成。body就是请求数据
		user->request.query_string = string(http_req->query_string.p, http_req->query_string.len); // 如http://10.50.4.227:8090/favicon.ico?pretty=true中，问号以后的就是query
		user->request.method = string(http_req->method.p, http_req->method.len); // 如GET，POST
		user->request.proto = string(http_req->proto.p, http_req->proto.len); // 如"HTTP/1.1"
		parse_uri_vars(user->request.query_string, user->request.vars);  // 解析问号以后的东西

		if(!user->request.url.empty() && user->request.url.back() != '/' || user->request.url.empty()) // 要求url必须以"/"结尾
			user->request.url.push_back('/');

		int i = 0;
		//  http请求包括请求行（request line）、请求头部（header）、空行和请求数据四个部分组成。header_names就是请求头
		while(http_req->header_names[i].len > 0 && i < MG_MAX_HTTP_HEADERS){
			auto& name = http_req->header_names[i];
			auto& value = http_req->header_values[i];
			user->request.headers[string(name.p, name.len)] = string(value.p, value.len);
			i++;
		}
		server->commit(user);
		break;
	}

	case MG_EV_CLOSE: 
		if (connection->user_data){ // 为什么这里的user_data就是sessionid？？
			SessionID id = (SessionID)connection->user_data;
			server->session_manager_.remove(id); // 移除某个session。这里是不是有个bug，sessionid 会越来越大
		}
	}
}

void HttpServerImpl::add_controller(const string& url, shared_ptr<Controller> controller){

	string url_remove_back(url);
	if(!url_remove_back.empty() && url_remove_back.back() != '/' || url_remove_back.empty())
		url_remove_back.push_back('/');

	if(controller->is_begin_match()){ // 根据控制器子类定义的不同，is_begin_match()返回True或False
		begin_match_router_.emplace_back(url_remove_back, controller);
		controller->initialize(url_remove_back, this);
	}else{
		router_map_[url_remove_back]["*"] = controller; // 控制器作为回调函数，请求方式为"*"
		controller->initialize(url_remove_back, this);
	}
}

void HttpServerImpl::add_router_post(const string& url, const HandlerCallback& callback){
	this->add_router(url, callback, "POST");
}

void HttpServerImpl::add_router_get(const string& url, const HandlerCallback& callback){
	this->add_router(url, callback, "GET");
}

void HttpServerImpl::add_router(const string &url, const HandlerCallback& callback, const string& method){

	string url_remove_back(url);
	if(!url_remove_back.empty() && url_remove_back.back() != '/' || url_remove_back.empty())
		url_remove_back.push_back('/');
	router_map_[url_remove_back][method] = callback;
}

void HttpServerImpl::close()
{
	if(keeprun_){
		INFO("Shutdown http server.");
		keeprun_ = false;
		cv_.notify_all(); 		// notify_all()：所有线程被一个一个唤醒，先抢到锁的先唤醒
		loop_thread_->join(); // 本线程等待线程loop_thread_执行完毕。loop_thread_线程用于等待用户请求，核心只有一句话：mg_mgr_poll(&mgr_, 1000);

		for(auto& t : threads_)
			t->join();			// 本线程等待线程t执行完毕

		loop_thread_.reset();
		threads_.clear();
		router_map_.clear();
		mg_mgr_free(&mgr_);
	}
}

shared_ptr<HttpServer> createHttpServer(const string& address, int num_threads){
	shared_ptr<HttpServerImpl> ins(new HttpServerImpl());
	if(!ins->start(address, num_threads))
		ins.reset();
	return ins;			 // 1.createHttpServer中创建的对象不应该在栈中吗？出了函数不应该就被删除了吗？
						 // 答：new是在堆上分配空间的，所以出了函数不一定被删除。
						 // 这里shared_ptr被创建时，引用计数为1。按值返回以后，引用计数为2。函数执行完成，引用计数减少一，变为1
						 // 本函数中使用按值返回以后shared_ptr作为返回值似乎不是很有效率的做法，我认为将代码改成如下形式效率更高
	//  HttpServerImpl ins;
	// if(!ins.start(address, num_threads))
	// 	ins.reset(); // 这一行，我不知道改成什么
	// return ins;	

}

Json::Value success(){
	Json::Value ret;
	ret["status"] = "success";
	ret["time"] = iLogger::time_now();
	return ret;
}

Json::Value failuref(const char* fmt, ...){

	va_list vl;
	va_start(vl, fmt);
	char buffer[1000];
	vsnprintf(buffer, sizeof(buffer), fmt, vl);

	Json::Value ret;
	ret["status"] = "error";
	ret["message"] = buffer;
	ret["time"] = iLogger::time_now();
	return ret;
}
