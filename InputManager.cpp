#include "InputManager.h"
#include "CameraManager.h"

void  MyInput::InputManager::ConsumeData(RenderWindow& _window)
{
    while (const optional _event = _window.pollEvent())
    {
        if (_event->is<Event::Closed>())
        {
            _window.close();
        }

        if (const Event::KeyPressed* _key = _event->getIf<Event::KeyPressed>())
        {
            if (_key->code == Keyboard::Key::Up)
            {
                Camera::M_CAMERA.GetCurrent()->Move(Vector2f(0.0f, -50.0f));
            }
            else if (_key->code == Keyboard::Key::Down)
            {
                Camera::M_CAMERA.GetCurrent()->Move(Vector2f(0.0f, 50.0f));
            }
            else if (_key->code == Keyboard::Key::Left)
            {
                Camera::M_CAMERA.GetCurrent()->Move(Vector2f(-50.0f, 0.0f));
            }
            else if (_key->code == Keyboard::Key::Right)
            {
                Camera::M_CAMERA.GetCurrent()->Move(Vector2f(50.0f, 0.0f));
            }
        }

        if (const Event::KeyPressed* _key = _event->getIf<Event::KeyPressed>())
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

void MyInput::InputManager::BindActionWithState(const Code& _codes, const function<void(bool)>& _callback, bool _state)
{
    inputData.push_back(InputData(
        [callback = _callback, _state]() { callback(_state); }, { _codes }));
}