#pragma once

#include <list>
#include <stdint.h>
#include <tr1/functional>

class NoParam {};

template <class FunctorType>
class SignalBase
{
public:
	typedef std::tr1::function<FunctorType> functor;
	
	SignalBase() : _handler() {}

	void connect(functor fun)
	{
		_handler.push_back(fun);
	}

protected:
	std::list<functor> _handler;
};

template <
	class P1 = NoParam,
	class P2 = NoParam,
	class P3 = NoParam,
	class P4 = NoParam>
class Signal
{
};

template <class P1, class P2, class P3>
class Signal<P1, P2, P3, NoParam> : SignalBase<void (P1, P2, P3)>
{
public:
	void emit(const P1& arg1, const P2& arg2, const P3& arg3)
	{
		typedef SignalBase<void (P1, P2, P3)> parent;
		typename std::list<typename parent::functor>::iterator it;
		for(it = parent::_handler.begin(); it != parent::_handler.end(); it++)
		{
			(*it)(arg1, arg2, arg3);
		}
	}
};

template <class P1, class P2>
class Signal<P1, P2, NoParam, NoParam> : public SignalBase<void (P1, P2)>
{
public:
	void emit(const P1& arg1, const P2& arg2)
	{
		typedef SignalBase<void (P1, P2)> parent;
		typename std::list<typename parent::functor>::iterator it;
		for(it = parent::_handler.begin(); it != parent::_handler.end(); it++)
		{
			(*it)(arg1, arg2);
		}
	}
};

template <class P1>
class Signal<P1, NoParam, NoParam, NoParam> : public SignalBase<void (P1)>
{
public:
	void emit(const P1& arg1)
	{
		typedef SignalBase<void (P1)> parent;
		typename std::list<typename parent::functor>::iterator it;
		for(it = parent::_handler.begin(); it != parent::_handler.end(); it++)
		{
			(*it)(arg1);
		}
	}
};

template <>
class Signal<NoParam, NoParam, NoParam, NoParam> : public SignalBase<void ()>
{
public:
	void emit()
	{
		typedef SignalBase<void ()> parent;
		typename std::list<parent::functor>::iterator it;
		for(it = parent::_handler.begin(); it != parent::_handler.end(); it++)
		{
			(*it)();
		}
	}
};
