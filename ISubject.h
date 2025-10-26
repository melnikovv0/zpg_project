#pragma once
#include <vector>
#include <algorithm> 
#include "IObserver.h"

class IObserver;

class ISubject {
public:
    virtual ~ISubject() = default;

    void addObserver(IObserver* observer) {
        m_observers.push_back(observer);
    }

    void removeObserver(IObserver* observer) {
        m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
    }

protected:
    void notifyObservers() {
        for (IObserver* observer : m_observers) {
            observer->update(this);
        }
    }

private:
    std::vector<IObserver*> m_observers;
};