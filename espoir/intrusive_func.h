#pragma once

//�N���^�Q�ƃJ�E���g����
//Com�I�u�W�F�N�g�p
void intrusive_ptr_add_ref(IUnknown* ptr);
void intrusive_ptr_release(IUnknown* ptr);

//�f�o�b�O�p
#if _DEBUG
void intrusive_ptr_add_ref(IDirect3D9* ptr);
void intrusive_ptr_release(IDirect3D9* ptr);
#endif