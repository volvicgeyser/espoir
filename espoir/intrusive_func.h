#pragma once

//侵入型参照カウント方式
//Comオブジェクト用
void intrusive_ptr_add_ref(IUnknown* ptr);
void intrusive_ptr_release(IUnknown* ptr);
