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
#pragma region TODO REMOVE


        else if (const Event::KeyPressed* _key = _event->getIf<Event::KeyPressed>())
        {
            if (_key->code == Keyboard::Key::Up)
            {
                M_CAMERA.GetCurrent()->Move(Vector2f(0.0f, -50.0f));
            }
            else if (_key->code == Keyboard::Key::Down)
            {
                M_CAMERA.GetCurrent()->Move(Vector2f(0.0f, 50.0f));
            }
            else if (_key->code == Keyboard::Key::Left)
            {
                M_CAMERA.GetCurrent()->Move(Vector2f(-50.0f, 0.0f));
            }
            else if (_key->code == Keyboard::Key::Right)
            {
                M_CAMERA.GetCurrent()->Move(Vector2f(50.0f, 0.0f));
            }
        }
#pragma endregion
        else if (const Event::KeyPressed* _key = _event->getIf<Event::KeyPressed>())
        {
            for (pair<string, InputData> _inputData : inputsData)
            {
                if (_inputData.second.TryToExcute(_key)) break;
            }
        }
    }
}

void MyInput::InputManager::BindAction(const set<Code>& _codes, const function<void()>& _callback,
    string _inputName, const bool _isEnabled)
{
    //if (inputsData.contains(_inputName))
    //{
    //    //TODO enlever c'est juste au cas ou vous voulez vous en servir (si oui enlever le return)
    //    //_inputName = "Input_" + to_string(GetUniqueID());
    //    return;
    //}
    inputsData[_inputName] = InputData(_callback, _codes, _codes.empty());
    inputsData[_inputName].isActived = _isEnabled;
}

void MyInput::InputManager::BindAction(const Code& _codes, const function<void()>& _callback,
    string _inputName, const bool _isEnabled)
{
    //if (inputsData.contains(_inputName))
    //{
    //    //TODO enlever c'est juste au cas ou vous voulez vous en servir (si oui enlever le return)
    //    //_inputName = "Input_" + to_string(GetUniqueID());
    //    return;
    //}
    inputsData[_inputName] = InputData(_callback, { _codes });
    inputsData[_inputName].isActived = _isEnabled;
}