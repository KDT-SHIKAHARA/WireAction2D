#pragma once

#define WINDOW_W 	SystemConfig::Instance().window_w()
#define WINDOW_H	SystemConfig::Instance().window_h()
#define WINDOW_C	SystemConfig::Instance().window_c()
#define BACK_COLOR	 SystemConfig::Instance().back_color()


class SystemConfig {
	SystemConfig()
		:window_w_(1280), window_h_(720), window_c_(32), back_color_(128){}
	virtual ~SystemConfig() = default;

public:
	SystemConfig(const SystemConfig&) = delete;
	SystemConfig& operator=(const SystemConfig&) = delete;

	static SystemConfig& Instance() {
		static SystemConfig instance;
		return instance;
	}

	int window_w()const { return window_w_; }
	int window_h()const { return window_h_; }
	int window_c()const { return window_c_; }
	int back_color()const { return back_color_; }

private:
	int window_w_,window_h_,window_c_;
	int back_color_;

};