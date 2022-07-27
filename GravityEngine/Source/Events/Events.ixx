export module Events;
import stdlib;

namespace EVNT
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum class EventCategory
	{
		None = 0,
		Window = (1 << 0),
		Input = (1 << 1),
		Keyboard = (1 << 2),
		Mouse = (1 << 3),
		MouseButton = (1 << 4)
	};

	export class Event
	{
	protected:
		bool Handled = false;

		Event() = default;

	public:
		virtual ~Event() = default;

		virtual EventType GetType() const = 0;
		virtual EventCategory GetCategories() const = 0;

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (GetType() == T::GetStaticType())
			{
				Handled |= func(static_cast<T&>(*this));
				return true;
			}
			return false;
		}
	};

	export using EventCallbackFn = std::function<void(Event&)>;

	export class WindowResizeEvent : public Event
	{
	private:
		uint32_t Width, Height;

	public:
		WindowResizeEvent(const uint32_t width, const uint32_t height)
			: Width(width), Height(height) {}

		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetType() const final override { return EventType::WindowResize; }
		virtual EventCategory GetCategories() const final override { return EventCategory::Window; }

		uint32_t GetWidth() const { return Width; }
		uint32_t GetHeight() const { return Height; }
	};

	export class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		static EventType GetStaticType() { return EventType::WindowClose; }
		virtual EventType GetType() const final override { return EventType::WindowClose; }
		virtual EventCategory GetCategories() const final override { return EventCategory::Window; }
	};
}