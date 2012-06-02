#pragma once

#include <list>
#include <stdint.h>
#include <tr1/functional>

class NoParam {};

template <
	class P1 = NoParam,
	class P2 = NoParam,
	class P3 = NoParam,
	class P4 = NoParam>
class Signal
{
};

template <class P1, class P2, class P3>
class Signal<P1, P2, P3, NoParam>
{
public:
	typedef std::tr1::function<void (P1, P2, P3)> functor;

	Signal() : _handler() {}	

	void emit(const P1& arg1, const P2& arg2, const P3& arg3)
	{
		typename std::list<functor>::iterator it;
		for(it = _handler.begin(); it != _handler.end(); it++)
		{
			(*it)(arg1, arg2, arg3);
		}
	}

	void connect(functor fun)
	{
		_handler.push_back(fun);
	}
private:
	std::list<functor> _handler;
};

template <class P1, class P2>
class Signal<P1, P2, NoParam, NoParam>
{
public:
	typedef std::tr1::function<void (P1, P2)> functor;

	Signal() : _handler() {}	

	void emit(const P1& arg1, const P2& arg2)
	{
		typename std::list<functor>::iterator it;
		for(it = _handler.begin(); it != _handler.end(); it++)
		{
			(*it)(arg1, arg2);
		}
	}

	void connect(functor fun)
	{
		_handler.push_back(fun);
	}
private:
	std::list<functor> _handler;
};

template <class P1>
class Signal<P1, NoParam, NoParam, NoParam>
{
public:
	typedef std::tr1::function<void (P1)> functor;

	Signal() : _handler() {}	

	void emit(const P1& arg1)
	{
		typename std::list<functor>::iterator it;
		for(it = _handler.begin(); it != _handler.end(); it++)
		{
			(*it)(arg1);
		}
	}

	void connect(functor fun)
	{
		_handler.push_back(fun);
	}
private:
	std::list<functor> _handler;
};

template <>
class Signal<NoParam, NoParam, NoParam, NoParam>
{
public:
	typedef std::tr1::function<void ()> functor;

	Signal() : _handler() {}	

	void emit()
	{
		std::list<functor>::iterator it;
		for(it = _handler.begin(); it != _handler.end(); it++)
		{
			(*it)();
		}
	}

	void connect(functor fun)
	{
		_handler.push_back(fun);
	}
private:
	std::list<functor> _handler;
};
