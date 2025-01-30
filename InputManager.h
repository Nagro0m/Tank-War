#pragma once
#include "Singleton.h"
namespace MyInput
{
    using KeyPressed = Event::KeyPressed;
    using Code = Keyboard::Scancode;

    struct InputData
    {
        bool isActived;
        set<Code> codes;
        bool isAnyKey;
        function<void()> callbacks;


        InputData() = default;
        InputData(const function<void()>& _callback, const set<Code>& _codes = {}, const bool _isAnyKey = false)
        {
            callbacks = _callback;
            codes = _codes;
            isAnyKey = _isAnyKey;
            isActived = true;
        }

    public:
        bool TryToExcute(const KeyPressed* _key)
        {
            if (!isAnyKey && !ContainKey(_key->scancode) && isActived) return false;
            callbacks();
            return true;
        }

    private:
        inline bool ContainKey(const Code& _code)
        {
            return codes.contains(_code);
        }
    };


    class InputManager : public Singleton<InputManager>
    {

        map<string,InputData> inputsData;
    public:
        FORCEINLINE void SetActiveInputData(const string& _inputDataName, const bool _isActive)
        {
            inputsData[_inputDataName].isActived = _isActive;
        }

    public:
        void ConsumeData(RenderWindow& _window);


        void BindAction(const set<Code>& _codes, const function<void()>& _callback, 
            string _inputName = "Input_" + to_string(GetUniqueID()),
            const bool _isEnabled = true);

        void BindAction(const Code& _codes, const function<void()>& _callback,
            string _inputName = "Input_" + to_string(GetUniqueID()),
            const bool _isEnabled = true);
    };
}
using namespace MyInput;