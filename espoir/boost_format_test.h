#pragma once

TEST(boostformattest, boostformattest){
	boost::format("abc");
	String str = (Format(_T("abcdef"))).str();
	String str2 = boost::str( Format(_T("abcdef")));
}