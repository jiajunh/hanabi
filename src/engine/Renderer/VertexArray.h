#pragma once
#ifndef HANABI_VERTEX_ARRAY_H
#define HANABI_VERTEX_ARRAY_H

#include "Core/base.h"
#include "Renderer/Buffer.h"
#include "pch.h"

namespace Hanabi {

    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer> &GetIndexBuffer() const = 0;

        static Ref<VertexArray> Create();
    };
}

#endif