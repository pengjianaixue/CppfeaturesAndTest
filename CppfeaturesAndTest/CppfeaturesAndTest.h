// CppfeaturesAndTest.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>

// TODO: 在此处引用程序需要的其他标头。
namespace TestArea
{


	static size_t size{ 0 };
# define  CAPI    __declspec(dllexport)
	void sumFun(long long i, long long &sum)
	{
		sum += i;
	}
	class father
	{
	public:
		father() {};
		~father() {};
		inline virtual void TestArea() { std::cout << "father" << std::endl; };
		inline void testCall() { this->TestArea(); };
		inline virtual void testCallPrivate() { testprivate(); };
	private:
		virtual void testprivate(void) { std::cout << "father private" << std::endl; };
	};

	class child :public father
	{

	public:
		child() {};
		~child() {};
		inline virtual void TestArea() { std::cout << "child" << std::endl; };
		inline void testCall() { this->TestArea(); };
		void testprivate(void) override { std::cout << "child private" << std::endl; };
	private:

	};

	/*
	Solution 1:
	此方案可以实现整个程序全局只有一个UnVisibleClass 的 instance , 依赖于C++ 17 inline static 初始化特性
	*/
	class SingleToneWarpper;
	/*此类为设置了全局只能有一个实例的类,且不能直接获取其对象*/
	class UnVisibleClass
	{
		friend SingleToneWarpper;
	private:
		inline UnVisibleClass() {};
		inline ~UnVisibleClass() {};
		int size{ 100 };
	private:
		inline void printMem() { std::cout << size << std::endl; };
		inline void addSize() { ++size; };

	};
	class SingleToneWarpper
	{
	public:
		inline SingleToneWarpper() {};
		inline ~SingleToneWarpper() {};
		inline void printMem() { singleInstance.printMem(); };
		inline void addSize() { singleInstance.addSize(); };
		static SingleToneWarpper& getInstance()
		{
			static SingleToneWarpper singleToneWarpper;
			return singleToneWarpper;
		};
	private:
		inline static UnVisibleClass singleInstance{};
	};
	void Test()
	{
		SingleToneWarpper testA;
		SingleToneWarpper testB;
		testA.printMem();
		testB.addSize();
		testB.printMem();
		SingleToneWarpper::getInstance().addSize();
		SingleToneWarpper::getInstance().printMem();
	}


	/*Solution 1 end*/

	// 不能实现全局绝对SingleTone 且不能编译通过
	class SingleTone
	{
	public:
		inline SingleTone()
		{
			if (!singleInstance)
			{
				singleInstance = new SingleTone();
			}
		}
		inline ~SingleTone() {};
		inline void printMem() { singleInstance->printMem(); };
		inline void addSize() { singleInstance->addSize(); };

	private:
		inline static SingleTone* singleInstance{ nullptr };
	};

}