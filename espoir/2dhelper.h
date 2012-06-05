#pragma once

namespace espoir{

class 2DHelper{
public:
	//小さすぎると描画できない。
	//そんな時に描画されるかどうかチェックする関数
	bool IsDrawableRect(RECT rect){
		const long width = rect.right - rect.left;
		const long height = rect.bottom - rect.top;
		if(1 <  width && 1 < height)
			return true;
		return false;
	}

	//四角形の面積を取得
	static long GetRectSize(RECT rect){
		const long width = rect.right - rect.left;
		const long height = rect.bottom - rect.top;
		const long size = width * height;
		return size;
	}
};

}
