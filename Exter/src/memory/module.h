#pragma once
#include "pch/pch.h"
#include "mem.h"

class hmodule
{
public:
	hmodule(std::string_view name = {}) : m_name(name), m_handle(get()), m_base(m_handle)
	{
		if (!m_handle)
		{
			m_size = 0;
			return;
		}

		auto dos_header = m_base.as<IMAGE_DOS_HEADER*>();
		if (!dos_header || dos_header->e_magic != IMAGE_DOS_SIGNATURE)
		{
			m_base = {};
			m_size = 0;
			return;
		}

		auto nt_header = m_base.add(dos_header->e_lfanew).as<IMAGE_NT_HEADERS*>();
		if (!nt_header || nt_header->Signature != IMAGE_NT_SIGNATURE)
		{
			m_base = {};
			m_size = 0;
			return;
		}

		m_size = nt_header->OptionalHeader.SizeOfImage;
	}

	mem begin() const
	{
		return m_base;
	}

	mem end() const
	{
		return begin().add(size());
	}

	size_t size() const
	{
		return m_size;
	}

	bool valid() const
	{
		return m_handle && m_base && m_size != 0;
	}

	FARPROC getProcess(const std::string& search) const
	{
		if (!m_handle)
			return nullptr;

		return GetProcAddress(m_handle, search.c_str());
	}

	HMODULE get() const
	{
		if (m_name.empty())
			return GetModuleHandleA(nullptr);
		return GetModuleHandleA(m_name.data());
	}

	std::string_view name() const
	{
		return m_name;
	}

private:
	std::string_view m_name{};
	HMODULE m_handle{};
	mem m_base{};
	size_t m_size{};
};
