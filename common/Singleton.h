#pragma once

#include "Main.h"

//=============================
// �V���O���g���e���v���[�g�N���X
//===============================
template <class T> 
class Singleton
{
protected:
    Singleton() = default;
    ~Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    static T& GetInstance(void)
    {
        static T m_Instance;
        return m_Instance;
    }
};