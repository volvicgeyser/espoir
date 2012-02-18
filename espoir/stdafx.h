// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#ifdef OLD_CODE
#include <cstdlib>
#include <malloc.h>
#include <memory.h>
#endif
#include<iostream>
#include <tchar.h>
#include<string>
#include<sstream>
#include<vector>
#include <comip.h>

//例外のエラーとか
#include <stdexcept>

//メモリリーク検出
#include <crtdbg.h>

#include<boost/unordered_map.hpp>
#include<boost/shared_ptr.hpp>
#include<boost/scoped_ptr.hpp>
#include<boost/function.hpp>

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>
#include <boost/utility.hpp>
#include<boost/function.hpp>
#include<boost/bind.hpp>
#include<boost/signals2.hpp>
//#include <boost/format.hpp>
#include <d3d9.h>
#include <boost/preprocessor.hpp>

//マクロ集
#include"macro.h"

#include"point.h"
#include"rect.h"
#include"typedef.h"
#include"config.h"



//実行時型生成
template <typename T> struct ComPtr{
	typedef ::_com_ptr_t<::_com_IIID< T , &__uuidof( T )>> type;
};



// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
