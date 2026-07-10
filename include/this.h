#pragma once
#ifndef __THIS__
#define __THIS__ ((unsigned int)this)
#else
static_assert("THIS is multiply defined.")
#endif