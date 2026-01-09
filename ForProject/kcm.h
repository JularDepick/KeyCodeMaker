#include <string>
#include <vector>
#include <time.h>

//默认字符集 
#define ___KCM_DEFAULT_CHARSET___ "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
//状态码 
#define _KCM_WELL_ 0x00
#define _KCM_ERR_BYTES_ 0x01
//状态码解释详细信息
#define __KCM_WELL__ "一切正常" 
#define __KCM_ERR_BYTES__ "char_bytes 的值非法"
#define __KCM_ERR_MIXMODE__ "mixmode 的值非法" 
#define __KCM_ERR_CHARSET__ "charset 的值非法"
#define __KCM_ERR_ 


//主类 
class kcm {
public: 
	//初始化主类(恢复到默认空白状态) 
	static bool init();
	//查看主类可用性 
	static bool good();
	//查看当前状态详细信息
	static string describe();
	//查看 char_bytes
	static bool bytes();
	//设定 char_bytes 
	static bool bytes(unsigned short);
	//查看 mixmode
	static bool mix();
	//设定 mixmode
	static bool mix(unsigned short);
	//查看 charset
	static charsrc();
	//设定 charset
	static charsrc(std::string);
	//查看 keycode
	static get();
	//生成 keycode
	static std::string make(unsigned int, unsigned int, std::string, std::string (*)(std::string,std::string));
	//校验某 keycode 合法性
	static bool verify(string,unsigned int,unsigned int,bool(*)(std::string));
	//获取格式化的 keycode
	static format(); 
	//获取格式化的指定 keycode
	static format(string); 
protected:
	//字符集单个字符最大所占字节数
	static unsigned short char_bytes;
	//是否启用单/多字节混合字符识别(依据首字节区分)
	static bool mixmode; 
	//主类当前状态,0表示正常可使用,其余值表示故障锁死(故障锁死后将无法进行调用操作) 
	static unsigned short status;
	//生成种子
	static std::string seed;
	//生成使用的字符合集
	static std::string charset;
	//整数转字符串 
	static std::string strint(unsigned long long);
	//生成最新种子
	static std::string newest_seed(); 
	//内置默认校验规则 
	static bool default_verify_rule(std::string,std::string);
	//内置默认格式化函数
	static std::string default_verify_rule(string);
};


//保护成员变量定义
unsigned short kcm::char_bytes=1;
bool kcm::mixmode=0;
unsigned short kcm::status=0;
//kcm::
//kcm::
//kcm::

//保护成员函数定义 


//公有成员函数定义 


