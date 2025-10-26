#pragma once

class ISubject; 

class IObserver {
public:
    virtual ~IObserver() = default;

    virtual void update(ISubject* subject) = 0;
};