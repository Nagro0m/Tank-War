#include "InputManager.h"
#include "CameraManager.h"
using namespace Camera;


void MyInput::InputManager::ConsumeData(RenderWindow& _window)
{
    while (const optional _event = _window.pollEvent())
    {
        if (_event->is<Event::Closed>())
        {
            _window.close();
        }

        else if (const Event::KeyPressed* _key = _event->getIf<Event::KeyPressed>())
        {
            keyStates[_key->scancode] = true;

            for (InputData& _inputData : inputData)
            {
                _inputData.TryToExcute(_key);
            }
        }
        else if (const Event::KeyReleased* _key = _event->getIf<Event::KeyReleased>())
        {
            keyStates[_key->scancode] = false;
        }
    }
}

void MyInput::InputManager::BindAction(const set<Code>& _codes, const function<void()>& _callback)
{
    inputData.push_back(InputData(_callback, _codes, _codes.empty()));

}

void MyInput::InputManager::BindAction(const Code& _codes, const function<void()>& _callback)
{
    inputData.push_back(InputData(_callback, { _codes }));
}