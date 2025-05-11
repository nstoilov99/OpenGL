#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace test {
	class Test
	{
	public:
		Test() = default;
		virtual ~Test() = default;
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test: " << name << std::endl;
			m_Tests.push_back({ name, []() { return new T(); } });
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}