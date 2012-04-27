#pragma once

//侵入型参照カウント方式
//Comオブジェクト用
void intrusive_ptr_add_ref(IUnknown* ptr);
void intrusive_ptr_release(IUnknown* ptr);

//デバッグ用
#if _DEBUG
void intrusive_ptr_add_ref(IDirect3D9* ptr);
void intrusive_ptr_release(IDirect3D9* ptr);
#endif