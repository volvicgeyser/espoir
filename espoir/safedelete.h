#pragma once

namespace espoir{

//メンバ関数Release()を呼び出し、ポインタにNULLを格納します
//template<class T>
//void safe_release(T* t){
//    if(t){
//        const ULONG cnt = t->Release();
//        DOut dout;
//        dout << _T("safe_release 参照カウンタ=") << cnt;
//
//        if(cnt)
//            throw std::runtime_error("safe_releaseリソースが解放されていません");
//        t = NULL;
//    }
//}

}
