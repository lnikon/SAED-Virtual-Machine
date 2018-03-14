#pragma once

#include <memory>
#include <iostream>

class CIOManager
{
public:
	CIOManager() = default;
	~CIOManager() = default;

	CIOManager(CIOManager const&) = delete;
	CIOManager(CIOManager &&) = delete;

	void operator=(CIOManager const&) = delete;
	void operator=(CIOManager &&) = delete;

	void foo()
	{
		std::cout << "Just test" << std::endl;
	}
};

using CIOManagerPtr = std::shared_ptr<CIOManager>;