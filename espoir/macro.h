#pragma once
//マクロ集


//スマートポインタで内包されてる記述に置き換える
#define SP(x) boost::shared_ptr<x>

//スマートポインタで内包された型を定義する
#define SP_TDEF(name) typedef SP(name) BOOST_PP_CAT(SP, name);


//ファイル名＆行番号表示マクロ
#define DSTM _T(" File: ") <<  __FILE__ << _T("Line: ") << __LINE__

//ループマクロ(i版)
#define loop_i(n, statement) \
	for(int i = 0; i < n; i++){\
			statement\
	}
//ループマクロ(j版）
#define loop_j(n, statement) \
	for(int j = 0; j < n; j++){\
		statement\
	}

