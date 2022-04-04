//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/system/Logic.h"

std::vector<Behaviour*> Logic::_behaviourList;
unsigned long int ::Logic::_tickIndex;

void Logic::start() {
    for (auto & it : _behaviourList) {
        it->Start();
    }
}

void Logic::reset() {
    _tickIndex = 0;
}

void Logic::update() {
    for (auto & it : _behaviourList) {
        if (it->getEnable())
            it->Update();
    }
}

void Logic::tick() {
    ++_tickIndex;
}

void Logic::fixedUpdate() {
    for (auto & it : _behaviourList) {
        if (it->getEnable())
            it->FixedUpdate();
    }
}

void Logic::lateUpdate() {
    for (auto & it : _behaviourList) {
        if (it->getEnable())
            it->LateUpdate();
    }
}

void Logic::destroy() {
    _behaviourList.clear();
}

void Logic::removeFromList(Behaviour* behaviour) {
    _behaviourList.erase(std::remove(_behaviourList.begin(), _behaviourList.end(), behaviour), _behaviourList.end());
}

void Logic::addToUpdateList(Behaviour* behaviour) {
    _behaviourList.push_back(behaviour);
}

unsigned long int Logic::getTickIndex() {
    return _tickIndex;
}

void Behaviour::init() {
    Logic::addToUpdateList(this);
}

void Behaviour::destroy() {
    OnDestroy();
    Logic::removeFromList(this);
}

void Behaviour::Start() {}
void Behaviour::Update() {}
void Behaviour::FixedUpdate() {}
void Behaviour::LateUpdate() {}
void Behaviour::OnDestroy() {}