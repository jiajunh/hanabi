#pragma once
#ifndef HANABI_TEXTURE_H
#define HANABI_TEXTURE_H

#include "Core/base.h"

namespace Hanabi {

    class Texture {
    public:
        virtual ~Texture() = default;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetRendererID() const = 0;
        virtual const std::string &GetPath() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual bool IsLoaded() const = 0;

        virtual bool operator==(const Texture &other) const = 0;
    };

    class Texture2D : public Texture {
    public:
        static Ref<Texture2D> Create(const std::string &path);
    };

}

#endif