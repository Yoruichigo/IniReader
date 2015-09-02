/*

	iniテキストデータを読み込むクラス
	ソース

*/


#include "MyLibINIReader.h"



using namespace MyLib;



//読み込み
bool INIReader::LoadFile(const std::string _FileLocation)
{
	std::ifstream ifs(_FileLocation, std::ifstream::binary);
	if (ifs.fail())
	{
		std::cerr << "失敗" << std::endl;
		ifs.close();
		return false;
	}

	std::string str(
		(std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());

	ifs.close();

	TextData = str;

	return true;
}





//値取得　int
bool INIReader::GetPutValue(const std::string _Keyword, int* _Storage)
{
	//GetPutStringValueで文字列の取得後、変換
	std::string _stringvalue;
	if (GetPutStringValue(_Keyword,&_stringvalue) == false){
		return false;
	}

	//int変換し、引数ポインタに代入
	(*_Storage) = std::stoi(_stringvalue);

	return true;
}


//値取得  bool
bool INIReader::GetPutBoolValue(const std::string _Keyword, bool* _Storage)
{
	//文字列取得後、true or false判断、代入
	std::string _stringvalue;
	if (GetPutStringValue(_Keyword,&_stringvalue) == false){
		return false;
	}

	//bool変換
	if (_stringvalue.compare("TRUE") == 0 ||
		_stringvalue.compare("True") == 0 ||
		_stringvalue.compare("true") == 0){
		//true
		(*_Storage) = true;
	}
	else if (
		_stringvalue.compare("FALSE") == 0 ||
		_stringvalue.compare("False") == 0 ||
		_stringvalue.compare("false") == 0 ){
		//false
		(*_Storage) = false;
	}
	else{
		//bool変換失敗
		return false;
	}

	return true;
}


//値取得　string
bool INIReader::GetPutStringValue(const std::string _Keyword, std::string* _Storage)
{
	//キーワードのインデックス位置
	int KeyIndexPos;
	
	
	{
		//キーワードをデータから探す
		for (int InitialsIndex = 0; InitialsIndex < (int)TextData.size(); InitialsIndex++)
		{
			//キーワードの頭文字を検索
			InitialsIndex = TextData.find(_Keyword.at(0), InitialsIndex);
			
			//nposだったら抜ける
			if(InitialsIndex == std::string::npos){
				KeyIndexPos = std::string::npos;
				break;
			}//頭文字があった位置からキーワード全体の比較
			else if (TextData.compare(InitialsIndex, _Keyword.size(), _Keyword)
				== 0){
				//成功したなら代入して抜ける
				KeyIndexPos = InitialsIndex;
				break;
			}
			else{
				//無いなら再検索
				continue;
			}

		}
		//文字がなかったなら失敗
		if (KeyIndexPos == std::string::npos){
			return false;
		}
	}




	//KeyIndexからKeywordの文字数を足した部分に=があるか探す
	int EqualIndexPos;
	std::string str_Equal = "=";
	EqualIndexPos = TextData.find_first_of(str_Equal, KeyIndexPos);
	if (EqualIndexPos == std::string::npos ||
		EqualIndexPos != (KeyIndexPos + _Keyword.size())){
		//無いなら失敗
		return false;
	}

	//改行までを探す(nposでもいい)
	int ValueLastIndex;
	int LFIndex;
	int CRIndex;
	std::string str_EndlLF = "\n";
	std::string str_EndlCR = "\r";
	LFIndex = TextData.find_first_of(str_EndlLF, EqualIndexPos);
	CRIndex = TextData.find_first_of(str_EndlCR, EqualIndexPos);

	//最後(npos)
	if(LFIndex == std::string::npos && CRIndex == std::string::npos){
		ValueLastIndex = std::string::npos;
	}//改行コード２つ
	else if (LFIndex != std::string::npos && CRIndex != std::string::npos){
		if (LFIndex < CRIndex){//LF手前
			ValueLastIndex = LFIndex - 1;
		}
		else{//CR手前
			ValueLastIndex = CRIndex - 1;
		}
	}//改行コード１つ
	else{
		if (LFIndex != std::string::npos){
			ValueLastIndex = LFIndex - 1;
		}
		else if(CRIndex != std::string::npos){
			ValueLastIndex = CRIndex - 1;
		}
		else{//エラー
			return false;
		}
	}


	//文字をストレージに格納する
	if (ValueLastIndex != std::string::npos){
		//ValueLastIndexの位置が途中なら
		(*_Storage) = TextData.substr(
			(EqualIndexPos + 1),//イコールの次のインデクスから
			(ValueLastIndex - EqualIndexPos)//文字数
			);
	}
	else{
		//ValueLastIndexの位置が最後(npos)なら
		(*_Storage) = TextData.substr(
			(EqualIndexPos + 1),
			ValueLastIndex);//最後まで
	}

	return true;
}
