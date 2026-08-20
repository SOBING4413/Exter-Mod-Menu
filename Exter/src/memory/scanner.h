#pragma once
#include "pch/pch.h"
#include "mem.h"
#include "module.h"
#include "core/logger.h"

inline u16 g_foundSigCount{};
inline u16 g_totalSigCount{};
inline u16 g_failedSigCount{};

inline std::optional<u8> charToHex(cc c)
{
	if (c >= 'a' && c <= 'f')
		return static_cast<u8>(static_cast<i32>(c) - 87);
	if (c >= 'A' && c <= 'F')
		return static_cast<u8>(static_cast<i32>(c) - 55);
	if (c >= '0' && c <= '9')
		return static_cast<u8>(static_cast<i32>(c) - 48);
	return {};
}

inline std::vector<std::optional<u8>> createBytesFromString(const std::string& ptr)
{
	std::vector<std::optional<u8>> bytes{};
	for (size_t i{}; i < ptr.size();)
	{
		if (std::isspace(static_cast<unsigned char>(ptr[i])))
		{
			++i;
			continue;
		}

		if (ptr[i] == '?')
		{
			bytes.emplace_back();
			++i;
			if (i < ptr.size() && ptr[i] == '?')
				++i;
			continue;
		}

		const auto high = charToHex(ptr[i]);
		const auto low = i + 1 < ptr.size() ? charToHex(ptr[i + 1]) : std::nullopt;
		if (high && low)
		{
			bytes.emplace_back(static_cast<u8>((*high << 4) | *low));
			i += 2;
		}
		else
		{
			++i;
		}
	}
	return bytes;
}

inline bool doesMemoryMatch(u8* target, const std::optional<u8>* sig, u64 len)
{
	for (u64 i{}; i != len; ++i)
	{
		if (sig[i] && *sig[i] != target[i])
		{
			return false;
		}
	}
	return true;
}

inline u64 findPatternBruteforce(const std::vector<std::optional<u8>>& bytes, const hmodule& module = {})
{
	if (!module.valid() || bytes.empty() || bytes.size() > module.size())
		return NULL;

	const auto scan_limit = module.size() - bytes.size();
	for (u64 i{}; i <= scan_limit; ++i)
	{
		if (doesMemoryMatch(module.begin().add(i).as<u8*>(), bytes.data(), bytes.size()))
			return module.begin().as<u64>() + i;
	}
	return NULL;
}

inline u64 findPatternBoyerMooreHorspool(const std::vector<std::optional<u8>>& bytes, const hmodule& module = {})
{
	if (!module.valid() || bytes.empty() || bytes.size() > module.size())
		return NULL;

	const auto module_begin = module.begin().as<u8*>();
	const auto scan_limit = module.size() - bytes.size();
	for (u64 curIdx{}; curIdx <= scan_limit; ++curIdx)
	{
		if (doesMemoryMatch(module_begin + curIdx, bytes.data(), bytes.size()))
			return module.begin().add(curIdx).as<u64>();
	}

	return NULL;
}

class scanner
{
public:
	scanner(std::string name, std::string pattern, const hmodule& module = {}) :
		m_name(std::move(name)), m_pattern(std::move(pattern)), m_module(module),
		m_elements(createBytesFromString(m_pattern))
	{
	}

	mem get()
	{
		g_totalSigCount++;
		mem res{findPatternBoyerMooreHorspool(m_elements, m_module)};
		if (res)
		{
			g_foundSigCount++;
			LOG_DEBUG("Found {} at GTA5.exe+0x{:X}", m_name, res.as<u64>() - m_module.begin().as<u64>())
		}
		else
		{
			g_failedSigCount++;
			LOG(Info, "Failed to find {}", m_name)
		}
		return res;
	}

private:
	std::string m_name{};
	std::string m_pattern{};
	hmodule m_module{};
	std::vector<std::optional<u8>> m_elements{};
};

inline mem scan(const std::string& key, const std::string& ptr, const hmodule& module = {})
{
	return scanner(key, ptr, module).get();
}

inline std::vector<mem> getAllResults(const std::string& ptr, const hmodule& module = {})
{
	std::vector bytes{createBytesFromString(ptr)};
	std::vector<mem> results{};
	if (!module.valid() || bytes.empty() || bytes.size() > module.size())
		return results;

	const auto scan_limit = module.size() - bytes.size();
	for (u64 i{}; i <= scan_limit; ++i)
	{
		if (doesMemoryMatch(module.begin().add(i).as<u8*>(), bytes.data(), bytes.size()))
			results.push_back(module.begin().add(i));
	}
	return results;
}
