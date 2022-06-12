#pragma once

class IObject {
public:
	IObject() {}
	virtual ~IObject() {}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};