#pragma once


namespace status{
	class Power {
		int power_;
	public:
		explicit Power(int arg_power) :power_(arg_power) {}
		int Get()const { return power_; }
		void Set(const int& arg_power) { power_ = arg_power; }

		Power operator+(const Power& arg_power) { return Power(power_ + arg_power.Get()); }
	};
}
