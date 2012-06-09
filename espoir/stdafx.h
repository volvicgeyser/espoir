// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
#define D3D_DEBUG_INFO				//ウォッチウィンドウからDirect3Dのデバッグ情報の詳細が見れるようにします。

// Windows ヘッダー ファイル:
#include <windows.h>
//#include<atlbase.h>
//extern CComModule _Module;
//#include<atlwin.h>

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

#include <shlwapi.h>

//例外のエラーとか
#include <stdexcept>

//メモリリーク検出
#include <crtdbg.h>

#include <boost/range/algorithm/for_each.hpp>
#include<boost/unordered_map.hpp>
#include<boost/intrusive_ptr.hpp>
#include<boost/shared_ptr.hpp>
#include<boost/make_shared.hpp>
#include<boost/shared_array.hpp>
#include<boost/scoped_ptr.hpp>
#include<boost/static_assert.hpp>
#include<boost/function.hpp>
#include <boost/foreach.hpp>

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>
#include <boost/utility.hpp>
#include<boost/function.hpp>
#include<boost/bind.hpp>
#include<boost/signals2.hpp>
#include <boost/format.hpp>
#include <d3d9.h>
#include<d3dx9.h>
//#include<XInput.h>
//direct input 8 を使う
#define DIRECTINPUT_VERSION 0x800
#include<dinput.h>
#include <boost/preprocessor.hpp>
#include <boost/scope_exit.hpp>
#include <gtest/gtest.h>

//for_eachで２つのコンテナから順番に取り出していったり
#include<boost/range/combine.hpp>
#include<boost/range/counting_range.hpp>

//メタ系
#include <boost/function_types/result_type.hpp>

//演算子のオーバーロード
#include<boost/operators.hpp>

//マクロ集
#include"macro.h"

#include"point.h"
//#include"rect.h"
#include"typedef.h"
#include"config.h"

//Microsoft Visual C++向け
#if defined(_MSC_VER)
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "dinput8.lib")

#ifdef NDEBUG
	#pragma comment(lib, "gtest.lib")
	#pragma comment(lib, "gtest_main.lib")
#else
	#pragma comment(lib, "gtestd.lib")
	#pragma comment(lib, "gtest_maind.lib")
#endif
#endif



//実行時Comptr型生成

template <typename T> struct ComPtr_t{
    typedef ::_com_ptr_t<::_com_IIID< T , &__uuidof( T )>> type;
};







// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
