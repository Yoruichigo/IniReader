/*

	iniテキストを読み込むクラス
	ヘッダ

	
	GetValue/GetStringValueは、
	半角イコール「=」で代入してあるキーワードにのみ
	対応しています。
*/

#pragma once

#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>


namespace MyLib
{

	class INIReader{
	public:
		INIReader(){};
		~INIReader(){};

		//指定されたファイルを読み込みます(false失敗)
		bool LoadFile(const std::string _FileLocation);

		//(int型)キーワードに代入された値を、渡された変数に入れます
		bool GetPutValue(const std::string _Keyword, int* _Storage);

		//(bool型)キーワードに代入された値を、渡された変数に入れます
		bool GetPutBoolValue(const std::string _Keyword, bool* _Storage);

		//(string型)キーワードに代入された値を、渡された変数に入れます
		bool GetPutStringValue(const std::string _Keyword, std::string* _Storage);
		

		//データを取得します
		inline std::string GetData()const{
			return TextData;
		}

	private:
		//読み込んだデータの保存用
		std::string TextData;
	};

}