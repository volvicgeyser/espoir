#pragma once

typedef boost::fusion::vector<int, int> Point_tuple;



//マルチバイトとユニコードを自動で切り替えてくれるtypedef
#ifdef _MSC_VER

//cygwin gcc
#else
	typedef TCHAR wchar_t
#endif

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> String;
typedef std::basic_stringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > Stringstream;
typedef std::basic_ostream<TCHAR, std::char_traits<TCHAR> > Ostream;
typedef std::basic_streambuf<TCHAR, std::char_traits<TCHAR> > Streambuf;
typedef std::char_traits<TCHAR>::int_type Int_type;