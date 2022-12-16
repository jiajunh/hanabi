#pragma once
#ifndef HANABI_ASSERT_H
#define HANABI_ASSERT_H

#include <assert.h>
#include <stdio.h>

// for linux only
#include <signal.h>
#define HANABI_DEBUGBREAK() raise(SIGTRAP)

#define HANABI_ASSERT(check, msg)          \
    {                                      \
        if (!(check)) {                    \
            fprintf(stderr, "%s \n", msg); \
            HANABI_DEBUGBREAK();           \
        }                                  \
    }

#endif