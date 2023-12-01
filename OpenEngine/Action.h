#pragma once

#include <functional>
#include <boost/serialization/unordered_map.hpp>

namespace OpenEngine {
	using ListenerID = uint64_t;
	template <class... argTypes>
	class Action {
	public:
		Action() : m_currentID(0) {}
		using CallbackFunc = void(argTypes...);
		using Callback = std::function<void(argTypes...)>;
		/*
		* Add a function callback to this action
		* @param callback
		* @return The ID of the new listener
		*/
		ListenerID AddListener(Callback callback) {
			m_currentID++;
			m_callbacks.emplace(m_currentID, callback);
			return m_currentID;
		}
		/*
		* Remove a function callback to this action using a listenerID
		* @param listenerID
		* @return whether remove the function callback identified by given listenerID
		*/
		bool RemoveListener(ListenerID id) {
			return m_callbacks.erase(id) != 0;
		}
		/*
		* Call every callbacks attached to this action
		*/
		void Invoke(argTypes... args) {
			for (auto const& [key, value] : m_callbacks)
				value(args...);
		}
		/*
		* Remove all function callback to this action
		*/
		void RemoveAllListeners() {
			m_callbacks.clear();
		}

	private:
		std::unordered_map<ListenerID, Callback> m_callbacks;
		ListenerID m_currentID;
	};
}