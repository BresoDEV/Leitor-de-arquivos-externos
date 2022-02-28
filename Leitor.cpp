#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include <vector>
#include <windows.h>  
#include <chrono>   
#include <sstream>  
#include <filesystem>
#pragma comment(lib, "urlmon.lib")
#include <direct.h>
using namespace std;

//GTA e RDR2
//#include "natives.h"


namespace Extern_Reader
{
	namespace LOG
	{
		std::string arquivoTXT;

		std::string HoraAtual()
		{
			struct tm current_tm;
			char chLogBuff[5000];
			char chParameters[5000];
			time_t current_time = time(NULL);
			localtime_s(&current_tm, &current_time);
			char szTimestamp[30];
			sprintf_s(szTimestamp, "[%02d:%02d:%02d] = ", current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
			return szTimestamp;
		}

		void Log_ERRO(string texto)
		{
			ofstream Arquivo;
			Arquivo.open(arquivoTXT, std::ios_base::app);
			std::string a = HoraAtual() + "ERRO: " + texto;
			Arquivo << a << endl;
			Arquivo.close();
		}

		void Log(string texto)
		{
			ofstream Arquivo;
			Arquivo.open(arquivoTXT, std::ios_base::app);
			std::string a = HoraAtual() + texto;
			Arquivo << a << endl;
			Arquivo.close();
		}

		void ReiniciarLog()
		{
			ofstream Arquivo;
			Arquivo.open(arquivoTXT);
			Arquivo << "";
			Arquivo.close();
		}
	};

	namespace StringManager
	{
		bool SeContemTexto(std::string string, std::string textoProcurado)
		{
			if (string.find(textoProcurado) != std::string::npos)
				return true;
			else
				return false;
		}

		std::string ReplaceChar(std::string palavra, char letraantiga, char letranova)
		{
			std::string base = palavra;
			std::string str = base;
			str.replace(str.begin(), str.end(), letraantiga, letranova);
			return str;
		}

		std::string ReplaceWord(std::string str, const std::string& from, const std::string& to) {
			size_t start_pos = 0;
			while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
				str.replace(start_pos, from.length(), to);
				start_pos += to.length();
			}
			return str;
		}

		std::string RemoveSpaces(std::string str, const std::string& from = " ", const std::string& to = "") {
			size_t start_pos = 0;
			while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
				str.replace(start_pos, from.length(), to);
				start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
			}
			return str;
		}
	}

	namespace File_Manager
	{
		bool ArquivoExiste(std::string name)
		{
			ifstream file(name);
			if (!file)
				return false;
			else
				return true;
		}

		void DeletarArquivo(string pathFile)
		{
			remove(pathFile.c_str());
		}

		void CriarArquivo(std::string FilePathAndExtension)
		{
			std::ofstream outfile(FilePathAndExtension);
			outfile.close();
		}

		void LimparArquivo(string arquivoTXT)
		{
			ofstream Arquivo;
			Arquivo.open(arquivoTXT);
			Arquivo << "";
			Arquivo.close();
		}

		void CriarDiretorio(const char* Diretorio)
		{
			_mkdir(Diretorio);
		}
	};

	namespace Simple_TXT_file
	{
		std::string TXTFilePath;

		int GetVectorSize(std::vector<string> vetor)
		{
			return vetor.size() - 1;
		}

		namespace String
		{ 
			std::vector<std::string> GetValues()
			{
				std::vector<std::string> TempVECTOR;
				ifstream imput(TXTFilePath);
				string textolido;
				for (string line; getline(imput, line);)
					TempVECTOR.push_back(line);
				return TempVECTOR;
			}

			std::vector<string> Get_More_Values(std::string Arquivo, char separador = ' ')
			{
				std::vector<string> TempVECTOR;
				vector<string> tokens;
				ifstream imput(Arquivo);
				for (string line; getline(imput, line);)
				{
					istringstream tokenizer{ line };
					string token;
					while (getline(tokenizer, token, separador))
					{
						tokens.push_back(token);
					}
				}
				return tokens;

				/*
				* Exemplo de 2 valores::
				for (int i = 0; i <= Extern_Reader::Simple_TXT_file::GetVectorSize(Extern_Reader::Simple_TXT_file::String::Get_More_Values("Teste.txt")); i++)
				{
					cout << "AddOption(" << Extern_Reader::Simple_TXT_file::String::Get_More_Values("Teste.txt")[i] << "," << Extern_Reader::Simple_TXT_file::String::Get_More_Values("Teste.txt")[i + 1] << ");" << endl;
					i++;
				}

				* Exemplo de 3 valores::
				for (int i = 0; i <= Extern_Reader::Simple_TXT_file::GetVectorSize(Extern_Reader::Simple_TXT_file::String::Get_More_Values("Teste.txt")); i++)
				{
					if (i <= (Extern_Reader::Simple_TXT_file::GetVectorSize(Extern_Reader::Simple_TXT_file::String::Get_More_Values("Teste.txt")) + 3))
					{
						cout << "AddOption(" << Extern_Reader::Simple_TXT_file::String::Get_More_Values("Teste.txt")[i] << ", " << Extern_Reader::Simple_TXT_file::String::Get_More_Values("Teste.txt")[i + 1] << ", " << Extern_Reader::Simple_TXT_file::String::Get_More_Values("Teste.txt")[i + 2] << ");" << endl;
						i++;
						i++;
					}
				}
				*/
			}
		}

		namespace Int
		{ 
			std::vector<int> GetValues()
			{
				std::vector<int> TempVECTOR;
				ifstream imput(TXTFilePath);
				string textolido;
				for (string line; getline(imput, line);)
					TempVECTOR.push_back(stoi(line));
				return TempVECTOR;
			}
		}

		namespace Float
		{
			std::vector<float> GetValues()
			{
				std::vector<float> TempVECTOR;
				ifstream imput(TXTFilePath);
				string textolido;
				for (string line; getline(imput, line);)
					TempVECTOR.push_back(stof(line));
				return TempVECTOR;
			}
		}

	};

	namespace INIFile
	{
		std::string INIFilePath;//Exemplo no mesmo diretorio do EXE:   .\\ArquivoINI.ini

		namespace String
		{
			void GravarString(std::string string, std::string app, std::string key)
			{
				WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), INIFilePath.c_str());
			}

			std::string LerString(std::string app, std::string key)
			{
				char buf[100];
				GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, INIFilePath.c_str());
				return (std::string)buf;
			}
		}
		
		namespace Int
		{
			void GravarInt(int value, std::string app, std::string key)
			{
				String::GravarString(std::to_string(value), app, key);
			}
			int LerInt(std::string app, std::string key)
			{
				return std::stoi(String::LerString(app, key));
			}
		}

		namespace Float
		{
			void GravarFloat(float value, std::string app, std::string key)
			{
				String::GravarString(std::to_string(value), app, key);
			}
			float LerFloat(std::string app, std::string key)
			{
				return std::stof(String::LerString(app, key));
			}
		}
	}

	namespace WEB
	{
		void DownloadFile(std::string URL, std::string DiretorioENomeDoArquivo)
		{
			string str = URL;
			std::wstring widestr = std::wstring(str.begin(), str.end());
			const wchar_t* widecstr = widestr.c_str();

			string str2 = DiretorioENomeDoArquivo;
			std::wstring widestr2 = std::wstring(str2.begin(), str2.end());
			const wchar_t* widecstr2 = widestr2.c_str();
			URLDownloadToFile(NULL, widecstr, widecstr2, 0, NULL);
		}

		std::vector<string> GetIPInfo()
		{
			/*
			Como Usar:

			int tamanho = Extern_Reader::Simple_TXT_file::GetVectorSize(Extern_Reader::WEB::GetIPInfo());
			for (int i = 0; i <= tamanho; i++)
			{
				cout << Extern_Reader::WEB::GetIPInfo()[i] << endl;
				i++;
			}


			exemplo 2:

			std::vector<std::string> IP = Extern_Reader::WEB::GetIPInfo();
			cout << "ip" << IP[2] << endl;
			cout << "version" << IP[4] << endl;
			cout << "city" << IP[6] << endl;
			cout << "region" << IP[8] << endl;
			cout << "region_code" << IP[10] << endl;
			cout << "country" << IP[12] << endl;
			cout << "country_name" << IP[14] << endl;
			cout << "country_code" << IP[16] << endl;
			cout << "country_code_iso3" << IP[18] << endl;
			cout << "country_capital" << IP[20] << endl;
			cout << "country_tld" << IP[22] << endl;
			cout << "continent_code" << IP[24] << endl;
			cout << "in_eu" << IP[26] << endl;
			cout << "postal" << IP[28] << endl;
			cout << "latitude" << IP[30] << endl;
			cout << "longitude" << IP[32] << endl;
			cout << "timezone" << IP[34] << endl;
			cout << "utc_offset" << IP[36] << endl;
			cout << "country_calling_code" << IP[38] << endl;
			cout << "currency" << IP[40] << endl;
			cout << "currency_name" << IP[42] << endl;
			cout << "languages" << IP[44] << endl;
			cout << "country_area" << IP[46] << endl;
			cout << "country_population" << IP[48] << endl;
			cout << "asn" << IP[50] << endl;
			cout << "org" << IP[52] << endl;
			*/
			if (Extern_Reader::File_Manager::ArquivoExiste("IP.txt"))
			{

				std::vector<string> TempVECTOR;
				vector<string> tokens;
				ifstream imput("IP.txt");
				for (string line; getline(imput, line);)
				{
					istringstream tokenizer{ line };
					string token;
					while (getline(tokenizer, token, ':'))
					{
						if (Extern_Reader::StringManager::SeContemTexto(token, ","))
						{
							tokens.push_back(Extern_Reader::StringManager::ReplaceWord(token, ",", ""));
						}
						else if (Extern_Reader::StringManager::SeContemTexto(token, "}"))
						{
							tokens.push_back(Extern_Reader::StringManager::ReplaceWord(token, "}", ""));
						}
						else if (Extern_Reader::StringManager::SeContemTexto(token, "{"))
						{
							tokens.push_back(Extern_Reader::StringManager::ReplaceWord(token, "{", ""));
						}
						else if (Extern_Reader::StringManager::SeContemTexto(token, "   "))
						{
							tokens.push_back(Extern_Reader::StringManager::ReplaceWord(token, "   ", ""));
						}
						else
							tokens.push_back(token);
					}
				}
				return tokens;
			}
			else
			{
				Extern_Reader::WEB::DownloadFile("https://ipapi.co/json", "IP.txt");
			}
		}
	}

	namespace MouseAndScreen
	{
		void MoveMouseTo(int x, int y)
		{
			SetCursorPos(x, y);
		}

		int GetScreenX()
		{
			return GetSystemMetrics(SM_CXSCREEN);
		}

		int GetScreenY()
		{
			return GetSystemMetrics(SM_CYSCREEN);
		}

		void CrazyMouse()
		{
			int count = 800;
			int movex, movey;
			float angle = 0.0f;
			SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
			for (int i = 0; i <= count; i++) {
				angle = .3 * i;
				movex = (angle * cos(angle) * 2) + GetSystemMetrics(SM_CXSCREEN) / static_cast<float>(2);
				movey = (angle * sin(angle) * 2) + GetSystemMetrics(SM_CYSCREEN) / 2;
				SetCursorPos(movex, movey);
				Sleep(1);
			}
		}
	}
};


namespace GTA
{
	struct Spawn_Struct
	{
		std::string Model;
		float PosX;
		float PosY;
		float PosZ;
		float RotX;
		float RotY;
		float RotZ;
	};

	void LoadMap_Props(std::string INIPath)
	{
		//Exemplo::
		//GTA::LoadMap_Props(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");
				
				//Void de spawn aqui
				
				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}

	void LoadMap_Peds(std::string INIPath)
	{
		//Exemplo::
		//GTA::LoadMap_Props(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");

				//Void de spawn aqui

				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}

	void LoadMap_Vehicles(std::string INIPath)
	{
		//Exemplo::
		//GTA::LoadMap_Props(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");

				//Void de spawn aqui

				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}

	void CriarModeloDeSpawn(std::string ININame, int NumeroDeItens)
	{
		//Exemplo::
		//GTA::CriarModeloDeSpawn(".\\Mapa.ini", 1000);
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = ININame;
		for (int i = 1; i <= NumeroDeItens; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			Extern_Reader::INIFile::String::GravarString("", buffer, "Modelo");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosX");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosY");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosZ");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotX");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotY");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotZ");

		}
	}
}

namespace RDR2
{
	struct Spawn_Struct
	{
		std::string Model;
		float PosX;
		float PosY;
		float PosZ;
		float RotX;
		float RotY;
		float RotZ;
	};

	void LoadMap_Props(std::string INIPath)
	{
		//Exemplo::
		//GTA::LoadMap_Props(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");

				//Void de spawn aqui

				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}

	void LoadMap_Peds(std::string INIPath)
	{
		//Exemplo::
		//GTA::LoadMap_Props(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");

				//Void de spawn aqui

				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}

	void LoadMap_Vehicles(std::string INIPath)
	{
		//Exemplo::
		//GTA::LoadMap_Props(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");

				//Void de spawn aqui

				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}

	void CriarModeloDeSpawn(std::string ININame, int NumeroDeItens)
	{
		//Exemplo::
		//GTA::CriarModeloDeSpawn(".\\Mapa.ini", 1000);
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = ININame;
		for (int i = 1; i <= NumeroDeItens; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			Extern_Reader::INIFile::String::GravarString("", buffer, "Modelo");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosX");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosY");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosZ");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotX");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotY");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotZ");

		}
	}
}

int main()
{
	 
	 
	return 0;
}
