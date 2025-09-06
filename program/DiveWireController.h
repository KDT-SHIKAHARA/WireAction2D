#pragma once
#include"Component.h"
#include"dive wire.h"


class DiveWireController : public Component {

public:
	DiveWireController() = default;
	virtual ~DiveWireController() = default;

	void Initialize(std::shared_ptr<DiveWire> diveWire) {
		diveWire_ = diveWire;
	}

	void Update();

private:
	std::shared_ptr<DiveWire> diveWire_;

};
