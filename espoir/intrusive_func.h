#pragma once

//侵入型参照カウント方式
void intrusive_ptr_add_ref(IUnknown* ptr);
void intrusive_ptr_release(IUnknown* ptr);

void intrusive_ptr_add_ref(LPD3DXFONT);
void intrusive_ptr_release(LPD3DXFONT);