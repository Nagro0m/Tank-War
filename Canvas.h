#pragma once
#include "Widget.h"

namespace UI
{
	class Canvas : public Widget
	{
		set<Widget*> allWidgets;
		map<Widget*, Vector2f> offSet;

	public:
		/*template <typename Type = Widget, IS_BASE_OF(Widget, Type)>
		FORCEINLINE void AddWidget(Type* _widget)
		{
		AddChild(_widget, AT_KEEP_RELATIVE);
		}
		template <typename Type = Widget, IS_BASE_OF(Widget, Type)>
		FORCEINLINE void RemoveWidget(Type* _widget)
		{
		RemoveChild(_widget);
		}*/
		FORCEINLINE void Hide()const
		{
			for (Widget* _current : allWidgets)
			{
				_current->SetVisibility(Hidden);
			}
		}

		FORCEINLINE void Show()const
		{
			for (Widget* _current : allWidgets)
			{
				_current->SetVisibility(Visible);
			}
		}

		FORCEINLINE Widget* GetWidgetAtIndex(u_int _index)const
		{
			set<Widget*>::iterator _it = allWidgets.begin();
			advance(_it, _index);
			return *_it;
		}

		template<typename Type = Widget, IS_BASE_OF(Widget, Type)>
		FORCEINLINE Type* GetFirstWidgetOf() const
		{
			for (Widget* _current : allWidgets)
			{
				if (Type* _casted = dynamic_cast<Type*>(_current))
				{
					return _casted;
				}
			}
			return nullptr;
		}

		FORCEINLINE void AddWidget(Widget* _widget)
		{
			allWidgets.insert(_widget);
			const Vector2f& _widgetPosition = _widget->GetPosition();
			const Vector2f& _offSet = Vector2f(_widgetPosition - GetPosition());
			offSet.insert(make_pair(_widget, _offSet));
		}
		FORCEINLINE void RemoveWidget(Widget* _widget)
		{
			allWidgets.erase(_widget);
		}

	public:
		Canvas(const string& _name, const RenderType& _type = Screen);

		void Render(RenderWindow& _window);

	public:
		virtual void Construct() override;
		void UpdateWidgets();
	};
}

