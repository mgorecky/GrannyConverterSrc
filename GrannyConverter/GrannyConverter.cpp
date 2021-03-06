#include "stdafx.h"
#include <exception>
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <iterator>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <shlobj.h>
#include <direct.h>

namespace fs = std::experimental::filesystem;

int main()
{
	std::string directory_old = "old";
	std::string extension = ".gr2";
	std::ofstream tmp("granny_list");
	int i = 0;

	try // Может быть исключение, например, если папки не существует
	{
		for (auto &p : fs::recursive_directory_iterator(directory_old)) // Для всех файлов в папке
		{
			if (!fs::is_regular_file(p.status()))
			{
				continue; // Пропускаем, если это не простой файл, а папка или что-то другое
			}

			std::string name(p.path().string());

			// Проверяем, что имя заканчивается нужным расширением
			// В С++20 можно будет просто `bool match = name.ends_with(extension);`
			bool match = !name.compare(name.size() - extension.size(), extension.size(), extension);
			if (!match)
			{
				continue;
			}

			// Тут делаем с путем то, что нужно
			name.erase(0, 4);

			// создаем папки в папке "new"
			char current_work_dir[FILENAME_MAX];
			std::string directory = _getcwd(current_work_dir, sizeof(current_work_dir));
			directory += "\\new\\";

			std::string::size_type n = name.find("\\");
			if (n != std::string::npos)
			{
				directory += name.substr(0, name.find_last_of("\\"));
			}

			SHCreateDirectoryExA(NULL, directory.c_str(), NULL);
			
			tmp << name.c_str() << std::endl;

			char preprocessorStripImages[256] = "preprocessor.bin TouchVersion old\\";
			strcat_s(preprocessorStripImages, name.c_str());
			strcat_s(preprocessorStripImages, " -output new\\");
			strcat_s(preprocessorStripImages, name.c_str());
			system(preprocessorStripImages);

			char preprocessorCompress[256] = "preprocessor.bin Compress new\\";
			strcat_s(preprocessorCompress, name.c_str());
			strcat_s(preprocessorCompress, " -output new\\");
			strcat_s(preprocessorCompress, name.c_str());
			system(preprocessorCompress);

			char preprocessorKillUncommonData[256] = "preprocessor.bin KillUncommonData new\\";
			strcat_s(preprocessorKillUncommonData, name.c_str());
			strcat_s(preprocessorKillUncommonData, " -output new\\");
			strcat_s(preprocessorKillUncommonData, name.c_str());
			system(preprocessorKillUncommonData);

			std::cout << i++ << ". " << name.c_str() << '\n';
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}

	tmp.close();

	std::cout << "----------------------------+----------------------------" << '\n';
	std::cout << i << " Models successfully Transformed to granny 2.11.8" << '\n';
	std::cout << "New files will be in the folder \"new\"" << '\n';
	std::cout << "With love from nikita322 :D" << '\n';
	std::cout << "----------------------------+----------------------------" << '\n';

	std::cin.get();
}
