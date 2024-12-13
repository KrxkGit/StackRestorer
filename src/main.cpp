#include <iostream>
#include <sstream>

#include "main.h"

const char* PROGRAM_NAME = "StackRestorer.exe";
const char* VERSION_NUM = "1.0";

std::list<std::pair<std::string, std::string>> stack_targets;
std::FILE* input_file = nullptr;
extern FILE* yyin;

/**
添加解析结构到链表中，导出由 bison 调用
*/
void add_items(const char* addr, const char* executable_name) {
	stack_targets.emplace_back(std::string(addr), std::string(executable_name));
}

static void exec_restore() {
	std::ostringstream oss;

	for (const auto& target : stack_targets) {
		oss << "addr2line -f -e " << target.second << " " << target.first << std::endl;

		system(oss.str().c_str());

		oss.str("");
	}
}

int run_core() {
	auto res = run_stack_dumper();
	if (res != 0) {
		return res;
	}

	exec_restore();

	return 0;
}

static void print_help() {
	std::cout << "用法:" << PROGRAM_NAME << " [-h | -v][-i 输入文件]" << std::endl
		<< "选项:" << std::endl
		<< "  -h, --help    显示帮助信息" << std::endl
		<< "  -v, --version 显示版本信息" << std::endl
		<< "  -i, --input   指定输入文件" << std::endl;
}

static void print_version() {
	std::cout << PROGRAM_NAME << " v" << VERSION_NUM << std::endl
		<< "作者: <Krxk>\n";
}

static void set_input(const char* input_file_name) {
	errno_t err = fopen_s(&input_file, input_file_name, "r");
	if (err != 0 || input_file == nullptr) {
		std::cerr << "无法打开输入文件: " << input_file_name << std::endl;
		exit(1);
	}
	yyin = input_file;
}

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; i++) { // 从 1 开始，跳过程序名称
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			print_help();
			return 0;
		}
		else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
			print_version();
			return 0;
		}
		else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
			if (i + 1 >= argc) {
				std::cerr << "缺少输出文件名\n";
				return 1;
			}
			set_input(argv[++i]);
		}
		else {
			std::cerr << "未知选项： " << argv[i] << std::endl;
			return 1;
		}
	}

	auto res = run_core();

	if (input_file != nullptr) {
		fclose(input_file);
	}

	return res;
}