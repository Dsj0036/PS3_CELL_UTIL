#pragma once

struct opd {
	unsigned int entry;
	unsigned int toc;
};
template<typename F>
inline opd* get_opd(F f) {
	return reinterpret_cast<opd*>(f);
}